using Avalonia.Controls;

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
}
