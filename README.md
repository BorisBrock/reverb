# reverb
Free open source voice chat

## Building

### Linux

1. Install CMake, a C++ toolchain and the .NET 9.0 SDK. The repository includes `dotnet-install.sh` that can be used to install the required SDK. During configuration CMake will automatically download the [nng](https://github.com/nanomsg/nng) library.
2. Build the native libraries and server:
   ```
   cmake -B build -S . -DCMAKE_BUILD_TYPE=Release
   cmake --build build --config Release
   ```
3. Publish the GUI for Linux:
   ```
   dotnet publish client/reverb/reverb.csproj -c Release -r linux-x64 --self-contained false
   ```

### Windows

1. Install Visual Studio with the C++ build tools, CMake and the .NET 9.0 SDK.
2. Build the native libraries and server (run from a Developer Command Prompt):
   ```
   cmake -B build -S . -DCMAKE_BUILD_TYPE=Release
   cmake --build build --config Release
   ```
3. Publish the GUI for Windows:
   ```
   dotnet publish client/reverb/reverb.csproj -c Release -r win-x64 --self-contained false
   ```

### Build scripts

Instead of running the commands manually you can execute one of the provided build scripts:

* **Linux:** `./build_linux.sh`
* **Windows:** `build_windows.ps1`

The scripts place all build artifacts into `output/linux/bin` or `output/windows/bin` respectively.
