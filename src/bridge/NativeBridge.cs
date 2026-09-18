using System.Runtime.InteropServices;

namespace WinZipIde.Bridge;

internal static class NativeBridge
{
    [DllImport("winzip_native.dll",
        CallingConvention = CallingConvention.Cdecl,
        CharSet = CharSet.Unicode)]
    internal static extern int GetArchitecture(
        string path,
        out ushort machine);
}
