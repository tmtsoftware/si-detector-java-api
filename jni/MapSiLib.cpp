#include <dlfcn.h>
#include "common_def.h"
#include "errordef.h"
//#include "OSSpecific.h" 
#include "MapSiLib.h"

//int CallBackFunc(int iN, unsigned long uN)
//{
//	return 99;
//}

CMapSiDll::CMapSiDll(void)
{
	dllLoaded = false;

	ScanInterfaces =			NULL;
	GetErrorString =			NULL;
	OpenCamera =				NULL;
	CloseCamera =				NULL;
	SetBaudRate =				NULL;
	GetBaudRate =				NULL;
	GetStatusNames =			NULL;
	GetParameterNames =			NULL;
	GetStatusValue =			NULL;
	GetStatusItem =				NULL;
	GetStatusBitField =			NULL;
	GetParameters =				NULL;
	GetParameterValue =			NULL;
	GetParameterItem =			NULL;
	GetParameterPulldownItem =	NULL;
	SetParameterValue =			NULL;
	SendParameters =			NULL;
	PrepareFileSave = 			NULL;
	PrepareAcqFilm = 			NULL;
	PrepareAcq =				NULL;
	EndAcq =					NULL;
	AcqStatus =					NULL;
	GetStatus =					NULL;
	GetXmlFile =				NULL;
	PostXmlData =				NULL;
	IssueCommand =				NULL;
	GetImageSize =				NULL;
	RegisterCallback =			NULL;
}
CMapSiDll::~CMapSiDll(void)
{
}
int CMapSiDll::MapDll(char * dllFileName)
{
	hmDll = dlopen(dllFileName, RTLD_LAZY);
	//hmDll = LOAD_LIB(dllFileName);
	//if (hmDll !=0) int test=1;
	//QLibrary myLib(dllFileName);
	if (!(ScanInterfaces =			(SCAN_INTERFACES)				RESOLVE_DLL_FUNCTION(hmDll,"ScanInterfaces")))			return -1;
	if (!(GetErrorString =			(GET_ERROR_STRING)				RESOLVE_DLL_FUNCTION(hmDll,"GetErrorString")))			return -1;
	if (!(ScanInterfaces =			(SCAN_INTERFACES)				RESOLVE_DLL_FUNCTION(hmDll,"ScanInterfaces")))			return -1;
	if (!(OpenCamera =				(OPEN_CAMERA)					RESOLVE_DLL_FUNCTION(hmDll,"OpenCamera")))				return -1;
	if (!(CloseCamera =				(CLOSE_CAMERA)					RESOLVE_DLL_FUNCTION(hmDll,"CloseCamera")))				return -1;
	if (!(GetStatusNames =			(GET_STATUS_NAMES)				RESOLVE_DLL_FUNCTION(hmDll,"GetStatusNames")))			return -1;
	if (!(GetParameterNames =		(GET_PARAMETER_NAMES)			RESOLVE_DLL_FUNCTION(hmDll,"GetParameterNames")))			return -1;
	if (!(GetStatus =				(GET_STATUS)					RESOLVE_DLL_FUNCTION(hmDll,"GetStatus")))					return -1;
	if (!(GetStatusValue =			(GET_STATUS_VALUE)				RESOLVE_DLL_FUNCTION(hmDll,"GetStatusValue")))			return -1;
	if (!(GetStatusItem =			(GET_STATUS_ITEM)				RESOLVE_DLL_FUNCTION(hmDll,"GetStatusItem")))				return -1;
	if (!(GetStatusBitField =		(GET_STATUS_BIT_FIELD)			RESOLVE_DLL_FUNCTION(hmDll,"GetStatusBitField")))			return -1;
	if (!(GetParameters =			(GET_PARAMETERS)				RESOLVE_DLL_FUNCTION(hmDll,"GetParameters")))				return -1;
	if (!(GetParameterValue =		(GET_PARAMETER_VALUE)			RESOLVE_DLL_FUNCTION(hmDll,"GetParameterValue")))			return -1;
	if (!(GetParameterItem =		(GET_PARAMETER_ITEM)			RESOLVE_DLL_FUNCTION(hmDll,"GetParameterItem")))			return -1;
	if (!(GetParameterPulldownItem =(GET_PARAMETER_PULLDOWN_ITEM)	RESOLVE_DLL_FUNCTION(hmDll,"GetParameterPulldownItem")))	return -1;
	if (!(SetParameterValue =		(SET_PARAMETER_VALUE)			RESOLVE_DLL_FUNCTION(hmDll,"SetParameterValue")))			return -1;
	if (!(SendParameters =			(SEND_PARAMETERS)				RESOLVE_DLL_FUNCTION(hmDll,"SendParameters")))			return -1;

	if (!(PrepareFileSave =			(PREPARE_FILE_SAVE)				RESOLVE_DLL_FUNCTION(hmDll,"PrepareFileSave")))			return -1;
	if (!(PrepareAcqFilm =			(PREPARE_ACQ_FILM)				RESOLVE_DLL_FUNCTION(hmDll,"PrepareAcqFilm")))			return -1;
	if (!(PrepareAcq =				(PREPARE_ACQ)					RESOLVE_DLL_FUNCTION(hmDll,"PrepareAcq")))				return -1;
	if (!(EndAcq =					(END_ACQ)						RESOLVE_DLL_FUNCTION(hmDll,"EndAcq")))					return -1;
	if (!(AcqStatus =				(ACQ_STATUS)					RESOLVE_DLL_FUNCTION(hmDll,"AcqStatus")))					return -1;

	if (!(GetXmlFile =				(GET_XML_FILE)					RESOLVE_DLL_FUNCTION(hmDll,"GetXmlFile")))				return -1;
	if (!(PostXmlData =				(POST_XML_DATA)					RESOLVE_DLL_FUNCTION(hmDll,"PostXmlData")))				return -1;
	if (!(IssueCommand =			(ISSUE_COMMAND)					RESOLVE_DLL_FUNCTION(hmDll,"IssueCommand")))				return -1;
	if (!(GetImageSize =			(GET_IMAGE_SIZE)				RESOLVE_DLL_FUNCTION(hmDll,"GetImageSize")))				return -1;
//	if (!(RegisterCallback =		(REGISTER_CALLBACK)				RESOLVE_DLL_FUNCTION(hmDll,"RegisterCallback")))			return -1;

	dllLoaded = true;

	return 0;
}
