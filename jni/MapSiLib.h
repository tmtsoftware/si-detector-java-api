#ifndef MAPSIDLL_H
#define MAPSIDLL_H
//#ifdef _MSC_VER			// check if we are building on VS
#include "common_def.h"
#include "errordef.h"
#include <dlfcn.h>
//#include "OSSpecific.h"

// check if we are building on VS
//#ifdef _MSC_VER
//#define LOAD_DLL(x) hmDll = LoadLibrary(x)
//#define RESOLVE_DLL_FUNCTION(x) GetProcAddress(hmDll,x)
//#else					// QT cases here -- need LINUX here as well
//#define LOAD_DLL(x) QLibrary myLib(x);
//#define RESOLVE_DLL_FUNCTION(x) myLib.resolve(x)
//#endif
#define SI_CAM int							// camera handle
#define LIB_HANDLE void*
#define LOAD_LIB(x) dlopen(x, RTLD_LAZY)
#define RESOLVE_DLL_FUNCTION(x,y) dlsym(x, y)
#define UNLOAD_LIB(x) dlclose(x) 
#define MAX_PATH 256

//int CallBackFunc(int iN, uint32_t uN);	-- not used currently
typedef int (*CALLBACK_FUNC)				(int,uint32_t);	
// general support
typedef int (*GET_ERROR_STRING)				(uint32_t errNum, char * strBuf, uint32_t * strSize);
typedef int (*SCAN_INTERFACES)				(char * xmlList, uint32_t * xmlSize, bool forceRescan);
// camera setup
typedef int (*OPEN_CAMERA)					(char *device_name,char *plugin_name);
typedef int (*CLOSE_CAMERA)					(int si_cam);
typedef int (*SET_BAUD_RATE)				(int si_cam, int baudrate);
typedef int (*GET_BAUD_RATE)				(int si_cam);
// parameter handling
typedef int (*GET_STATUS_NAMES)				(int cam, char * list_buffer, long list_buffer_length);
typedef int (*GET_PARAMETER_NAMES)			(int cam, char * list_buffer, long list_buffer_length);
typedef int (*GET_STATUS)					(int cam);
typedef int (*GET_STATUS_VALUE)				(int cam, char * displayName, char * valStr, int valStrSize);
typedef int (*GET_STATUS_ITEM)				(int cam, char * displayName, char * valStr, int valStrSize, short * unit_type,char * unitStr, int unitLen, char * stepStr, int stepLen);
typedef int (*GET_STATUS_BIT_FIELD)			(int cam, char * displayName, char * maskStr, int maskStrLen, char * display, int displayLen);
typedef int (*GET_PARAMETERS)				(int cam);
typedef int (*GET_PARAMETER_VALUE)			(int cam, const char * displayName, char * valStr, int valStrSize);
typedef int (*GET_PARAMETER_ITEM)			(int cam, char * displayName,
											 char * valStr, int valLen, char * minStr, int minLen, char * max, int maxLen, unsigned short * unit_type,
											 char * unitStr, int unitLen, char * stepStr, int stepLen);
typedef int (*GET_PARAMETER_UNIT_STRING)	(int cam, const char * displayName, char * unitStr, int strLen);
typedef int (*GET_PARAMETER_PULLDOWN_ITEM)	(int cam, char * displayName, int PulldownIndex, char * PulldownValStr, int ValStrLen, char * PulldownName, int sizeOfNameArray);
typedef int (*SET_PARAMETER_VALUE)			(int cam, const char * displayName, const char * valStr);
typedef int (*SEND_PARAMETERS)				(int cam);
// imaging operation
typedef int (*GET_IMAGE_SIZE)				(int cam, uint32_t * serLen, uint32_t * parLen, uint32_t * is16, uint32_t * nSerCCD, uint32_t * nParCCD, uint32_t * nSerSect, uint32_t * nParSect);
typedef int (*PREPARE_FILE_SAVE)			(SI_CAM cam, char * file_name, char * img_hdr, char * file_type);
typedef int (*PREPARE_ACQ_FILM)				(SI_CAM cam, uint16_t SerLen, uint16_t ParLen, void * buffArray, uint16_t nBuffers, bool is16);
typedef int (*PREPARE_ACQ)					(int cam,uint16_t SerLen,uint16_t ParLen,void * buffA,void * buffB,bool is16,int n_frames,char *file_name,char *fits_hdr);
typedef int (*END_ACQ)						(int cam, bool force_abort);
typedef int (*ACQ_STATUS)					(SI_CAM cam, uint16_t *percent_read, uint32_t * current_frame, uint32_t * buffer_flags);

typedef int (*GET_XML_FILE)					(int cam, const char * fileName, char * xmlFile, uint32_t * xmlSize);
typedef int (*POST_XML_DATA)				(int cam, char * xmlFile, uint32_t xmlSize);
typedef int (*ISSUE_COMMAND)				(int cam, const char * postName, const char * argStr,char * retStr, uint32_t retSize);
typedef int (*REGISTER_CALLBACK)			(int cam, CALLBACK_FUNC callBack);


///const char * displayName,char * valStr,int valLen,char * minStr,int minLen,char * maxStr,int maxLen,unsigned short * unit_type, char * unitStr, int unitLen, char * stepStr, int stepLen

//SIVCAMDLL_API int RegisterCallback(SI_CAM cam, CallBackFunc callBack);

class CMapSiDll
{
public:
	CMapSiDll(void);
	~CMapSiDll(void);
        int MapDll(char * dllFileName);
	bool	dllLoaded;
		GET_ERROR_STRING		GetErrorString;
        SCAN_INTERFACES			ScanInterfaces;
		OPEN_CAMERA				OpenCamera;
        CLOSE_CAMERA			CloseCamera;
        SET_BAUD_RATE			SetBaudRate;
        GET_BAUD_RATE			GetBaudRate;
		GET_STATUS_NAMES		GetStatusNames;
		GET_PARAMETER_NAMES		GetParameterNames;
		GET_STATUS_VALUE		GetStatusValue;
        GET_STATUS_ITEM			GetStatusItem;
		GET_STATUS_BIT_FIELD    GetStatusBitField;
        GET_PARAMETERS			GetParameters;
        GET_PARAMETER_VALUE		GetParameterValue;
        GET_PARAMETER_ITEM		GetParameterItem;
        GET_PARAMETER_PULLDOWN_ITEM	GetParameterPulldownItem;
        SET_PARAMETER_VALUE		SetParameterValue;
        SEND_PARAMETERS			SendParameters;
		PREPARE_FILE_SAVE		PrepareFileSave;
		PREPARE_ACQ_FILM		PrepareAcqFilm;
		PREPARE_ACQ				PrepareAcq;
		END_ACQ					EndAcq;
		ACQ_STATUS				AcqStatus;
		GET_STATUS				GetStatus;
		GET_XML_FILE			GetXmlFile;
		POST_XML_DATA			PostXmlData;
		ISSUE_COMMAND			IssueCommand;
		GET_IMAGE_SIZE			GetImageSize;
		REGISTER_CALLBACK		RegisterCallback;
		CALLBACK_FUNC			callBack;
		LIB_HANDLE	hmDll;
//#ifdef _MSC_VER
//		HINSTANCE hmDll;
//#else
//		void * hmDll;
//#endif

};
#endif // MAPSIDLL_H
