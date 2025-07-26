use futures::{SinkExt, StreamExt};
use lazy_static::lazy_static;
use std::sync::{Arc, Mutex};
use tokio::sync::mpsc::{self, UnboundedSender};
use tokio::task;
use tokio_tungstenite::connect_async;
use tokio_tungstenite::tungstenite::Message;

// Learn more about Tauri commands at https://tauri.app/develop/calling-rust/
#[tauri::command]
fn greet(name: &str) -> String {
    format!("Hello, {}! You've been greeted from Rust!", name)
}

type MessageCallback = Arc<dyn Fn(String) + Send + Sync + 'static>;

lazy_static! {
    static ref WS_STATE: Arc<Mutex<Option<WebSocketState>>> = Arc::new(Mutex::new(None));
}

struct WebSocketState {
    sender: UnboundedSender<String>,
    callback: Option<MessageCallback>,
}

#[tauri::command]
fn ws_set_on_message<F>(callback: F)
where
    F: Fn(String) + Send + Sync + 'static,
{
    let mut state = WS_STATE.lock().unwrap();
    if let Some(ws) = state.as_mut() {
        ws.callback = Some(Arc::new(callback));
    }
}

#[tauri::command]
fn ws_connect(url: &str) {
    let url = url.to_string();
    let state = WS_STATE.clone();

    task::spawn(async move {
        let (ws_stream, _) = connect_async(&url).await.expect("Failed to connect");
        let (mut write, mut read) = ws_stream.split();

        let (tx, mut rx) = mpsc::unbounded_channel::<String>();

        {
            let mut state_lock = state.lock().unwrap();
            *state_lock = Some(WebSocketState {
                sender: tx.clone(),
                callback: None,
            });
        }

        let read_state = state.clone();
        task::spawn(async move {
            while let Some(Ok(msg)) = read.next().await {
                if let Message::Text(text) = msg {
                    let cb_opt = {
                        let state = read_state.lock().unwrap();
                        state.as_ref().and_then(|s| s.callback.as_ref().cloned())
                    };
                    if let Some(cb) = cb_opt {
                        cb(text);
                    }
                }
            }
        });

        while let Some(msg) = rx.recv().await {
            write.send(Message::Text(msg)).await.ok();
        }
    });
}

#[tauri::command]
fn ws_send(msg: &str) {
    if let Some(ws) = &*WS_STATE.lock().unwrap() {
        ws.sender.send(msg.to_string()).ok();
    }
}

#[tauri::command]
fn ws_close() {
    let mut state = WS_STATE.lock().unwrap();
    *state = None;
}

#[cfg_attr(mobile, tauri::mobile_entry_point)]
pub fn run() {
    tauri::Builder::default()
        .plugin(tauri_plugin_opener::init())
        .invoke_handler(tauri::generate_handler![greet])
        .run(tauri::generate_context!())
        .expect("error while running tauri application");
}
