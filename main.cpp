// Windows API headers must come first to avoid std::byte conflict
#define WIN32_LEAN_AND_MEAN
#define NOMINMAX

// Disable std::byte to avoid conflict with Windows API
#define _HAS_STD_BYTE 0

//#include <dshow.h>

#include <string>
#include "loginfo.h"
#include "camset.h"

int verbLevel = VERB_NORMAL; //display messages (default)
bool ignoreFriendlyName = false;
int targetDeviceNumber = -1; // -1 means all devices (default)

void helpme() {
    logMe(LOG_INFO, "");
    logMe(LOG_INFO, "CamCfg.Date.2017.version.1.0");
    logMe(LOG_INFO, "To save and apply DirectShow webcam settings");
    logMe(LOG_INFO, "");
    logMe(LOG_INFO, "Usage: WebCameraConfig.exe [options]");
    logMe(LOG_INFO, "");
    logMe(LOG_INFO, "Options:");
    logMe(LOG_INFO, "--readdev          : Read and print all devices short info.");
    logMe(LOG_INFO, "--savedev          : Save devices current settings into .cfg file.");
    logMe(LOG_INFO, "--profile [string] : Uses string as filename to save/load settings.");
    logMe(LOG_INFO, "--ignorefn         : Ignore FriendlyName when looking for devices.");
    logMe(LOG_INFO, "--device [number]  : Apply settings only to specified device number (1-based).");
    logMe(LOG_INFO, "--verbose          : Enable verbose output (includes debug messages).");
    logMe(LOG_INFO, "--quiet            : Suppress all output except errors.");
    logMe(LOG_INFO, "--debug            : Enable debug output (same as --verbose).");
    logMe(LOG_INFO, "--help             : Display this help info.");
    logMe(LOG_INFO, "");
    logMe(LOG_INFO, "Without [options], it reads existing cam_sett.cfg file and applies settings");
    logMe(LOG_INFO, "to all available devices.");
    logMe(LOG_INFO, "It doesn't build new graph, only uses existing one.");
}

int main(int argc, char *argv[])
{
    //test
    //argc = 2;
    //argv[0] = (char *)"WebCameraConfig.exe";
    //argv[1] = (char *)"--readdev";
    //argv[1] = (char *)"--savedev";
    //argv[1] = (char *)"--ignorefn";

    string ProfStr;
    bool readVideoDevices = false, saveVideoDevices = false;
    int i = 1;
    for(; i < argc; i++) {
        string arg(argv[i]);
        if (arg == "--readdev") {
            readVideoDevices = true;
        } else if (arg == "--savedev") {
            saveVideoDevices = true;
        } else if (arg == "--profile") {
            if (++i < argc) ProfStr = argv[i];
        } else if (arg == "--ignorefn") {
            ignoreFriendlyName = true;
        } else if (arg == "--device") {
            if (++i < argc) {
                try {
                    targetDeviceNumber = stoi(argv[i]);
                } catch (const std::invalid_argument &e) {
                    logMe(LOG_ERR, "Invalid device number: " + string(argv[i]));
                    return -1;
                } catch (const std::out_of_range &e) {
                    logMe(LOG_ERR, "Device number out of range: " + string(argv[i]));
                    return -1;
                }
            }
        } else if (arg == "--verbose" || arg == "--debug") {
            verbLevel = VERB_FULL;
        } else if (arg == "--quiet") {
            verbLevel = VERB_SILENT;
        } else if (arg == "--help") {
            helpme();
            return 0;
        } else
            break; //for
    } //for

    //by default no keys required
    if (argc != i) {
        helpme();
        return -1;
    }

    if (ProfStr == "")
        ProfStr = "cam_sett"; //default file name

    logMe(LOG_INFO, "Debug: readVideoDevices = " + to_string(readVideoDevices));
    logMe(LOG_INFO, "Debug: saveVideoDevices = " + to_string(saveVideoDevices));
    logMe(LOG_INFO, "Debug: ProfStr = " + ProfStr);
    logMe(LOG_INFO, "Debug: verbLevel = " + to_string(verbLevel));
    logMe(LOG_INFO, "Debug: targetDeviceNumber = " + to_string(targetDeviceNumber));

    CamSetAll camupd;
    try {

        if (readVideoDevices) {
            logMe(LOG_INFO, "Debug: Calling displayFoundDevices()");
            camupd.displayFoundDevices();
            return 0; //all OK
        }

        if (saveVideoDevices) {
            logMe(LOG_INFO, "Debug: Calling saveSett(" + ProfStr + ".cfg)");
            camupd.saveSett(ProfStr + ".cfg");
            logMe(LOG_INFO, "Debug: saveSett() completed");
            return 0; //all OK
        }

        //default behavior is to load/apply settings from the .cfg file
        logMe(LOG_INFO, "Debug: Calling loadSett(" + ProfStr + ".cfg)");
        camupd.loadSett(ProfStr + ".cfg", targetDeviceNumber);

    } catch(string e) {
        logMe(LOG_ERR, e);
        return -1;
    }

    return 0;
}
