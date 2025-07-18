using Avalonia.Controls;
using Avalonia.Interactivity;
using System;


namespace reverb;

public partial class MainWindow : Window
{
    public MainWindow()
    {
        InitializeComponent();
        LoadDevices();
    }

    private void LoadDevices()
    {
        var inputs = VoiceInterop.GetCaptureDevices();
        InputDeviceBox.ItemsSource = inputs;
        if (inputs.Length > 0)
            InputDeviceBox.SelectedIndex = 0;

        var outputs = VoiceInterop.GetOutputDevices();
        OutputDeviceBox.ItemsSource = outputs;
        if (outputs.Length > 0)
            OutputDeviceBox.SelectedIndex = 0;
    }

    private void ConnectClicked(object? sender, RoutedEventArgs e)
    {
        ConnectButton.IsEnabled = false;
        DisconnectButton.IsEnabled = true;

        string server = ServerBox.Text ?? string.Empty;
        ushort port = (ushort)(PortBox.Value ?? 0);
        string user = UserNameBox.Text ?? string.Empty;

        Console.WriteLine($"Connect: server={server} port={port} user={user}");

        string uri = $"ws://{server}:{port}/";
        VoiceInterop.ConnectWebSocket(uri);
    }

    private void DisconnectClicked(object? sender, RoutedEventArgs e)
    {
        ConnectButton.IsEnabled = true;
        DisconnectButton.IsEnabled = false;
        VoiceInterop.DisconnectWebSocket();
        Console.WriteLine("Disconnect");
    }
}
