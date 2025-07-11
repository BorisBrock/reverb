$ErrorActionPreference = 'Stop'

$ScriptDir = Split-Path -Parent $MyInvocation.MyCommand.Definition
$RootDir = $ScriptDir

$OutputDir = Join-Path $RootDir 'output/windows'
$BuildDir = Join-Path $OutputDir 'build'
$BinDir   = Join-Path $OutputDir 'bin'

New-Item -ItemType Directory -Force -Path $BuildDir, $BinDir | Out-Null

# Build native libraries
cmake -B $BuildDir -S $RootDir -DCMAKE_BUILD_TYPE=Release
cmake --build $BuildDir --config Release

# Copy native libraries to bin directory
Get-ChildItem -Path $BuildDir -Filter '*.dll' -Recurse | ForEach-Object { Copy-Item $_.FullName $BinDir }

# Publish the .NET GUI application
$env:DOTNET_CLI_TELEMETRY_OPTOUT = '1'
dotnet publish "$RootDir/client/reverb/reverb.csproj" -c Release -r win-x64 --self-contained false -o $BinDir

Write-Host "Build completed. Binaries are in $BinDir"
