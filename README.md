# cfg-cam #
command-line application that saves and loads DirectShow webcam settings to/from the file

## Usage ##
Make sure that cameras are running (this application doesn't build new graph for the device).
All settings stored in cam_sett.cfg file at the same folder as .exe file.

Run without options to load saved settings.

Run with option "--savedev" to save current settings of all enabled DirectShow video input devices.

Run with option "--help" to get brief help info.

## Requirements ##
- Run: Windows 7 or late; any available DirectShow video input device with adjustable Video Proc Amp or Camera Control.
- Compile: Qt v5.8.0; Visual Studio 2013 UPD5 default compilers.

## Build Instructions ##

### Prerequisites
- **Qt 6.9.1** (or compatible version)
- **MinGW 13.1.0** (included with Qt)
- **Windows SDK** (for DirectShow API)

### Environment Setup
1. Install Qt from https://www.qt.io/download
2. Add Qt and MinGW to your PATH:
   ```powershell
   $env:PATH += ";C:\Qt\6.9.1\mingw_64\bin;C:\Qt\Tools\mingw1310_64\bin"
   ```

### Build Steps
1. **Generate Makefile**:
   ```bash
   qmake WebCameraConfig.pro
   ```

2. **Build the project**:
   ```bash
   mingw32-make
   ```

3. **Clean build artifacts** (optional):
   ```bash
   mingw32-make clean
   ```

### Build Output
The executable will be generated in the `release/` directory:
- `WebCameraConfig.exe` - Main application

### Troubleshooting
- **std::byte conflict**: The project includes fixes for C++17 std::byte conflicts with Windows API
- **Missing libraries**: Windows API libraries (ole32, oleaut32, strmiids) are automatically linked
- **Compiler errors**: Ensure C++11 standard is used (configured in .pro file)

## Legal ##
Joined under MPLv2 if other not mentioned but whole project still under GPLv2.

## Conclusion ##
Some stuff just exist.
