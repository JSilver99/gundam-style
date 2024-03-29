/* API Base Implementation - Translation Layer
 *
 * APIBase.cpp
 * fwk4gps version 4.0
 * gam666/dps901/gam670/dps905
 * June 25 2012
 * copyright (c) 2012 Chris Szalwinski 
 * distributed under TPL - see ../Licenses.txt
 */

#define WIN32_LEAN_AND_MEAN
#include <windows.h>
#include <fstream>       // for ostream, <<, close()
#include "APIPlatform.h" // for API headers
#include "APIBase.h"     // for APIBase class definition
#include "iUtilities.h"  // for strcpy, strcat

//-------------------------------- APIBase ------------------------------------
//
// APIBase is the base class for the Translation Layer
//
// Addresses of objects that hold the system configuration
//
iAPIDisplaySet*     APIBase::displaySet    = nullptr;
iAPIInputDeviceSet* APIBase::keyboardSet   = nullptr;
iAPIInputDeviceSet* APIBase::pointerSet    = nullptr;
iAPIInputDeviceSet* APIBase::controllerSet = nullptr;
iAPIDisplay*        APIBase::display       = nullptr;
iAPIWindow*         APIBase::window        = nullptr;

// The API window connectivity is defined by the APIWindow object
//
void*               APIBase::application = nullptr;
void*               APIBase::hwnd        = nullptr;

// The API graphics connectivity is defined by the APIDisplay object
//
IDirect3D9*         APIBase::d3d         = nullptr;
IDirect3DDevice9*   APIBase::d3dd        = nullptr;
IDirect3DTexture9*  APIBase::texture     = nullptr;
ID3DXSprite*        APIBase::manager     = nullptr;

int                 APIBase::width       = 0;
int                 APIBase::height      = 0;
bool                APIBase::runinwndw   = true;

// logError adds msg to the error.log file
//
void APIBase::logError(const wchar_t* msg) {

    std::wofstream fp("error.log", std::ios::app);
    if (fp) {
         fp << msg << std::endl;
         fp.close();
    }
}

// error pops up a Message Box displaying msg and adds the message to log file
//
void APIBase::error(const wchar_t* msg, const wchar_t* more) {

    int len = strlen(msg);
    if (more) len += strlen(more);
    wchar_t* str = new wchar_t[len + 1];
	strcpy(str, msg, len);
	if (more) strcat(str, more, len);

    if (hwnd)
        MessageBox((HWND)hwnd, str, L"Error", MB_OK);

    logError(str);

    delete [] str;
}

