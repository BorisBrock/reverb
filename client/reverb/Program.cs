using System.Runtime.InteropServices;
using Avalonia;
using Avalonia.ReactiveUI;
using Avalonia.Controls.ApplicationLifetimes;

namespace reverb;

public class Program
{
    [DllImport("chat", CallingConvention = CallingConvention.Cdecl)]
    private static extern void chat_dummy();

    [DllImport("voice", CallingConvention = CallingConvention.Cdecl)]
    private static extern void voice_dummy();

    public static void Main(string[] args)
    {
        chat_dummy();
        voice_dummy();
        BuildAvaloniaApp().StartWithClassicDesktopLifetime(args);
    }

    public static AppBuilder BuildAvaloniaApp()
        => AppBuilder.Configure<App>()
            .UsePlatformDetect()
            .LogToTrace()
            .UseReactiveUI();
}
