using System;
using System.Runtime.InteropServices;
using Avalonia;
using Avalonia.ReactiveUI;
using Avalonia.Controls.ApplicationLifetimes;

namespace reverb;

public class Program
{
    private delegate void ChatCallback(IntPtr message);

    [DllImport("chat", CallingConvention = CallingConvention.Cdecl)]
    private static extern bool chat_start(ChatCallback cb);

    [DllImport("chat", CallingConvention = CallingConvention.Cdecl)]
    private static extern void chat_publish([MarshalAs(UnmanagedType.LPStr)] string message);

    [DllImport("chat", CallingConvention = CallingConvention.Cdecl)]
    private static extern void chat_stop();

    [DllImport("voice", CallingConvention = CallingConvention.Cdecl)]
    private static extern void voice_dummy();

    public static void Main(string[] args)
    {
        chat_start(OnChatMessage);
        chat_publish("Hello from client");
        voice_dummy();
        BuildAvaloniaApp().StartWithClassicDesktopLifetime(args);
        chat_stop();
    }

    private static void OnChatMessage(IntPtr msg)
    {
        string? text = Marshal.PtrToStringAnsi(msg);
        Console.WriteLine($"[chat] {text}");
    }

    public static AppBuilder BuildAvaloniaApp()
        => AppBuilder.Configure<App>()
            .UsePlatformDetect()
            .LogToTrace()
            .UseReactiveUI();
}
