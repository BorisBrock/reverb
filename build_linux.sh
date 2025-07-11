#!/usr/bin/env bash
set -euo pipefail

SCRIPT_DIR="$(cd "$(dirname "${BASH_SOURCE[0]}")" && pwd)"
ROOT_DIR="$SCRIPT_DIR"

OUTPUT_DIR="$ROOT_DIR/output/linux"
BUILD_DIR="$OUTPUT_DIR/build"
BIN_DIR="$OUTPUT_DIR/bin"

mkdir -p "$BUILD_DIR" "$BIN_DIR"

# Build native libraries
cmake -B "$BUILD_DIR" -S "$ROOT_DIR" -DCMAKE_BUILD_TYPE=Release
cmake --build "$BUILD_DIR" --config Release

# Copy native libraries to bin directory
find "$BUILD_DIR" -name '*.so' -exec cp {} "$BIN_DIR" \;
# Copy server executable to bin directory
find "$BUILD_DIR" -name 'reverb-server' -executable -exec cp {} "$BIN_DIR" \;

# Publish the .NET GUI application
DOTNET_CLI_TELEMETRY_OPTOUT=1 dotnet publish "$ROOT_DIR/client/reverb/reverb.csproj" \
  -c Release -r linux-x64 --self-contained false -o "$BIN_DIR"

echo "Build completed. Binaries are in $BIN_DIR"
