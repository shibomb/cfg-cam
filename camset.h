#ifndef CAMSET_H
#define CAMSET_H

// Windows API headers must come first to avoid std::byte conflict
#define WIN32_LEAN_AND_MEAN
#define NOMINMAX

// Disable std::byte to avoid conflict with Windows API
#define _HAS_STD_BYTE 0

#include <dshow.h>

#include <string>
#include <vector>
#include <stdint.h>
#include <iostream>
#include <fstream>
#include <exception>

using namespace std;

extern bool ignoreFriendlyName;

enum {
    GET_SETT = 1, //get settings
    SET_SETT = 2, //set settings
    DIS_SETT = 4, //display settings
    DIS_INFO = 8  //display info
};

void ListMyDevicesInfo(); //list of video device info
void MyDevicesSettings(int gsd, int targetDeviceNumber = -1); //device settings manipulation
void DisplayDeviceInformation(IEnumMoniker *pEnum); //display properties of found devices
void DisplayDeviceSettings(); //from RAM
void SetDeviceSettings(IEnumMoniker *pEnum, int targetDeviceNumber = -1); //set settings to devices
void GetDeviceSettings(IEnumMoniker *pEnum); //get settings from devices
HRESULT EnumerateDevices(REFGUID category, IEnumMoniker **ppEnum); //Enumerate devices of given category to get devices monikers
string ConvertBSTRToMBS(BSTR bstr); //general variant string to standard string conversion
string ConvertWCSToMBS(const wchar_t* pstr, long wslen); //intermediate string conversion
bool WaitForDeviceReady(IPropertyBag *pPropBag, int maxRetries = 10); //wait for device to be ready
bool VerifySetting(IAMVideoProcAmp *pProcAmp, IAMCameraControl *pCamCtrl, const string& parameter, long expectedValue, bool expectedManual); //verify if setting was applied correctly

class CamSetAll {
public:
    CamSetAll();
    ~CamSetAll();
    void loadSett(string cfgfilename, int targetDeviceNumber = -1); //load settings from .cfg file
    void saveSett(string cfgfilename); //save current settings to .cfg file
    void displayFoundDevices(); //list all available video capture devices
};

#endif // CAMSET_H
