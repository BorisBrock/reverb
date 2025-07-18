using System;
using System.Runtime.InteropServices;

namespace reverb;

internal static class VoiceInterop
{
    [DllImport("voice", CallingConvention = CallingConvention.Cdecl)]
    private static extern IntPtr voice_get_output_devices(out int count);

    [DllImport("voice", CallingConvention = CallingConvention.Cdecl)]
    private static extern IntPtr voice_get_capture_devices(out int count);

    [DllImport("voice", CallingConvention = CallingConvention.Cdecl)]
    private static extern void voice_free_device_list(IntPtr list, int count);

    [DllImport("voice", CallingConvention = CallingConvention.Cdecl)]
    private static extern void voice_ws_connect([MarshalAs(UnmanagedType.LPStr)] string uri);

    [DllImport("voice", CallingConvention = CallingConvention.Cdecl)]
    private static extern void voice_ws_disconnect();

    public static string[] GetOutputDevices()
    {
        IntPtr list = voice_get_output_devices(out int count);
        return ConsumeList(list, count);
    }

    public static string[] GetCaptureDevices()
    {
        IntPtr list = voice_get_capture_devices(out int count);
        return ConsumeList(list, count);
    }

    private static string[] ConsumeList(IntPtr list, int count)
    {
        if (list == IntPtr.Zero || count <= 0)
            return Array.Empty<string>();

        var devices = new string[count];
        for (int i = 0; i < count; i++)
        {
            IntPtr ptr = Marshal.ReadIntPtr(list, i * IntPtr.Size);
            devices[i] = Marshal.PtrToStringAnsi(ptr) ?? string.Empty;
        }
        voice_free_device_list(list, count);
        return devices;
    }

    public static void ConnectWebSocket(string uri)
    {
        voice_ws_connect(uri);
    }

    public static void DisconnectWebSocket()
    {
        voice_ws_disconnect();
    }
}
