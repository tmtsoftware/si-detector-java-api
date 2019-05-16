#ifndef COMMON_DEF_H
#define COMMON_DEF_H

#ifdef _WIN32

//#include "targetver.h"
// The following macros define the minimum required platform.  The minimum required platform
// is the earliest version of Windows, Internet Explorer etc. that has the necessary features to run 
// your application.  The macros work by enabling all features available on platform versions up to and 
// including the version specified.

// Modify the following defines if you have to target a platform prior to the ones specified below.
// Refer to MSDN for the latest info on corresponding values for different platforms.
#ifndef WINVER                          // Specifies that the minimum required platform is Windows Vista.
#define WINVER 0x0600           // Change this to the appropriate value to target other versions of Windows.
#endif

#ifndef _WIN32_WINNT            // Specifies that the minimum required platform is Windows Vista.
#define _WIN32_WINNT 0x0600     // Change this to the appropriate value to target other versions of Windows.
#endif

#ifndef _WIN32_WINDOWS          // Specifies that the minimum required platform is Windows 98.
#define _WIN32_WINDOWS 0x0410 // Change this to the appropriate value to target Windows Me or later.
#endif

#ifndef _WIN32_IE                       // Specifies that the minimum required platform is Internet Explorer 7.0.
#define _WIN32_IE 0x0700        // Change this to the appropriate value to target other versions of IE.
#endif

#ifdef _DEBUG
#define DbgOut(_x_) {char dbgStr[2000]; sprintf_s _x_ ; OutputDebugString(dbgStr);}
#else
#define DbgOut(_x_)
#endif

#define WIN32_LEAN_AND_MEAN             // Exclude rarely-used stuff from Windows headers

// Windows Header Files:
#include <windows.h>
#include <Mmsystem.h>
#include <crtdbg.h>

#endif /* _WIN32 */

#include <stdint.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#if  defined (__GNUC__)
#include <pthread.h>
#include <dirent.h>
#include <dlfcn.h>
#include <unistd.h>
#include <assert.h>
#include <sys/time.h>
#include <sys/select.h>

/* These calls are not available in linux or darwin (OS X)
 * They must be Microsoft specific
 */

#define sprintf_s snprintf
#define strcpy_s(dest, size, src) strncpy(dest, src, size)
#define strncpy_s(dest, size, src, numElems) strncpy(dest, src, (size < numElems) ? size : numElems)
#define strtok_s( strToken, strDelimit, context) strtok_r( strToken, strDelimit, context);
#define strcat_s( strDestination, numberOfElements, strSource ) strncat( strDestination, strSource, numberOfElements);
#define strncat_s(dest, size, src, numElems) strncat(dest, src, (size < numElems) ? size : numElems);
// ### consider using nanosleep
#define Sleep(ms) usleep(1000 * ms)

#define _ASSERT(x) assert(x)

#if _DEBUG && _DEBUG_PRINT
#define OutputDebugString(dbgStr) std::cerr << dbgStr;
#define DbgOut(_x_) {char dbgStr[4096]; snprintf  _x_ ; OutputDebugString(dbgStr);}
#else
#define DbgOut(_x_)
#endif

#define MB_ICONERROR 1
#define MessageBox(window, description, error, icon) std::cerr << error << ": " << description << std::endl
///MessageBox(NULL,"\"Installed CCDs\" parameter does not match number of Focal Plane entries","Parameter Mismatch",MB_ICONERROR);
//unsigned int timeGetTime()
//{
//	struct timeval now;
//	gettimeofday(&now, NULL);
//	return now.tv_usec/1000;
//}
#endif /* __GNUC__ */

// DLL - SO interface declaration
#ifdef _WIN32
	#define SI_LIB_API extern "C" __declspec(dllexport)
#else
    #define SI_LIB_API  extern "C" __attribute__ ((visibility("default")))
#endif

typedef void *si_handle;




#endif	/* COMMON_DEF_H */

