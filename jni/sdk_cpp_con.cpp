#include <stdio.h>
#include <stdint.h>
#include "sdk_cpp_con.h"
#include "common_def.h"
#include "errordef.h"
//#include "OSSpecific.h" 
#include "MapSiLib.h"


char **getArgs() {
  static char *values[3];
  values[0] = "Dave";
  values[1] = "Mike";
  values[2] = 0;
  return &values[0];
}


int loadDll() {

	int error;
	pDll = new CMapSiDll;						// create dll object
	bool is32bit = sizeof(void*) == 4;			// running on 32 bit?

	//if (is32bit) error = pDll->MapDll("SiVCamDll.dll");	// map dll
	//else  error = pDll->MapDll("SiVCamDll_64.dll");
	if (is32bit) error = pDll->MapDll("libsivcam.so");	// map dll
	else  error = pDll->MapDll("libsivcam.so");
	if (error) {
		printf("DLL could not be mapped\n");
		return -1;
	}
	printf("DLL loaded\n");
	return 0;
}

char** getErrorString(int error) {

    //char errorStr[512];
	uint32_t strSize = 512;

	static char* retArray[2];
	retArray[1] = 0;  // terminate string array
	retArray[0] = new char[512];

	pDll->GetErrorString(error, retArray[0],&strSize);	// strSize returns the real length of the string

    return &retArray[0];
}

char** scanInterfaces (bool forceRescan) {

    uint32_t strSize = 10000;
    static char retcodeStr[PAR_SIZE];
	static char* retArray[3];
	retArray[1] = new char[10000];
	retArray[2] = 0;  // terminate string array

    int retcode = pDll->ScanInterfaces(retArray[1],&strSize, forceRescan);

    sprintf(retcodeStr,"%d",retcode);
    retArray[0] = retcodeStr;

    return &retArray[0];
}
/* Not supported by MapSiLib */
/*
char** getSoftwareSummary(int cam) {

    static char retcodeStr[PAR_SIZE];
	static char* retArray[3];
	retArray[1] = new char[10000];
	retArray[2] = 0;  // terminate string array


    int retcode = pDll->GetSoftwareSummary (cam, retArray[1], 10000);

    sprintf(retcodeStr,"%d",retcode);
    retArray[0] = retcodeStr;

    return &retArray[0];

}
*/

int openCamera(char *info[]) {
	int si_cam = pDll->OpenCamera(info[0], info[1]);	// open camera and get handle (handles are positive numbers)
	return si_cam;
}

/* not supported in MapSLiLib
int cameraHwReset(char *info[]) {
	si_cam = pDll->CameraHwReset(info[0], info[1]);	// open camera and get handle (handles are positive numbers)
	return si_cam;
}
*/

int closeCamera(int camHandle) {
	return pDll->CloseCamera(camHandle);	// close camera
}

int getStatus(int camHandle) {
	int retcode = pDll->GetStatus(camHandle);
	return retcode;
}

int getParameters(int camHandle) {
	int retcode = pDll->GetParameters(camHandle);
	return retcode;
}

char** getXmlFiles(int camHandle) {

	int error;
	uint32_t bSize = 1000000;
	static char* bXml[2];
	bXml[1] = 0;  // terminate string array
	bXml[0] = new char[bSize];							// create 1M large text buffer
	uint32_t thisSize = bSize;
	error = pDll->GetXmlFile(camHandle,"files.xml",bXml[0],&thisSize);	// files.xml is in every camera. It lists which XML files can be retrieved

	return &bXml[0];
}

char** getStatusNames(int camHandle) {

	int error;
	uint32_t bSize = 1000000;
	static char* bXml[2];
	bXml[1] = 0;  // terminate string array
	bXml[0] = new char[bSize];							// create 1M large text buffer
	uint32_t thisSize = bSize;
	error = pDll->GetStatusNames(camHandle, bXml[0], bSize);

	return &bXml[0];
}

char** getParameterNames(int camHandle) {

	int error;
	uint32_t bSize = 1000000;
	static char* bXml[2];
	bXml[1] = 0;  // terminate string array
	bXml[0] = new char[bSize];							// create 1M large text buffer
	uint32_t thisSize = bSize;
	error = pDll->GetParameterNames(camHandle, bXml[0], bSize);

	return &bXml[0];
}

char** getParameterItem(int camHandle, char *paramName) {

	int error;

	// one parameter example
	static char valStr[PAR_SIZE];
	static char maxStr[PAR_SIZE];
	static char minStr[PAR_SIZE];
	static char unitStr[PAR_SIZE];
	static char stepStr[PAR_SIZE];
	static char unitType[PAR_SIZE];
	static char retcode[PAR_SIZE];
	static unsigned short unit_type;

	static char paramNameStatic[PAR_SIZE];  // the argument needs to be static and needs passed argument value copied for GetParameterItem call to work
	strcpy(paramNameStatic, paramName);

	error = pDll->GetParameterItem(camHandle,paramNameStatic,valStr,PAR_SIZE,minStr,PAR_SIZE,maxStr,PAR_SIZE,&unit_type,unitStr,PAR_SIZE,stepStr,PAR_SIZE);

	// encode return values
	static char* retVal[8];
	sprintf(retcode,"%d",error);
	retVal[0] = retcode;
	retVal[1] = valStr;
	retVal[2] = minStr;
	retVal[3] = maxStr;
	retVal[4] = unitStr;
	retVal[5] = stepStr;
	sprintf(unitType,"%d",unit_type);
	retVal[6] = unitType;
	retVal[7] = 0;

	return retVal;
}

char** getParameterValue(int camHandle, char *paramName) {

	int error;

	// one parameter example
	static char valStr[PAR_SIZE];
	static char retcode[PAR_SIZE];

	static char paramNameStatic[PAR_SIZE];  // the argument needs to be static and needs passed argument value copied for GetParameterItem call to work
	strcpy(paramNameStatic, paramName);

	error = pDll->GetParameterValue(camHandle,paramNameStatic,valStr,PAR_SIZE);

	// encode return values
	static char* retVal[3];
	sprintf(retcode,"%d",error);
	retVal[0] = retcode;
	retVal[1] = valStr;
	retVal[2] = 0;

	return retVal;
}

char** getParameterPulldownItem(int camHandle, char *displayName, int pulldownIndex) {

    int error;

	static char displayNameStatic[PAR_SIZE];  // the argument needs to be static and needs passed argument value copied for GetStatusValue call to work
	strcpy(displayNameStatic, displayName);

	static char pulldownValStr[PAR_SIZE];
	static char pulldownName[PAR_SIZE];
    static char retcode[PAR_SIZE];

    error = pDll->GetParameterPulldownItem (camHandle, displayNameStatic, pulldownIndex, pulldownValStr, PAR_SIZE, pulldownName, PAR_SIZE);

	static char* retVal[4];
	sprintf(retcode,"%d",error);
	retVal[0] = retcode;
	retVal[1] = pulldownValStr;
	retVal[2] = pulldownName;
	retVal[3] = 0;

	return retVal;

}
/* Not supported by MapSiLib */
/*
char** getParameterBitField (char *displayName) {

   int error;

	static char displayNameStatic[PAR_SIZE];  // the argument needs to be static and needs passed argument value copied for GetStatusValue call to work
	strcpy(displayNameStatic, displayName);

	static char maskStr[PAR_SIZE];
	static char display[PAR_SIZE];
    static char retcode[PAR_SIZE];

    error = pDll->GetParameterBitField (si_cam, displayNameStatic, maskStr, PAR_SIZE, display, PAR_SIZE);

	static char* retVal[4];
	sprintf(retcode,"%d",error);
	retVal[0] = retcode;
	retVal[1] = display;
	retVal[2] = maskStr;
	retVal[3] = 0;

	return retVal;

}
*/

char** getStatusItem(int camHandle, char *displayName) {

	int error;

	// one parameter example
	static char valStr[PAR_SIZE];
	static char unitStr[PAR_SIZE];
	static char stepStr[PAR_SIZE];
	static char unitType[PAR_SIZE];
	static char retcode[PAR_SIZE];
	static short unit_type;

	static char displayNameStatic[PAR_SIZE];  // the argument needs to be static and needs passed argument value copied for GetStatusItem call to work
	strcpy(displayNameStatic, displayName);

	error = pDll->GetStatusItem(camHandle,displayNameStatic,valStr,PAR_SIZE,&unit_type,unitStr,PAR_SIZE,stepStr,PAR_SIZE);

	// encode return values
	static char* retVal[6];
	sprintf(retcode,"%d",error);
	retVal[0] = retcode;
	retVal[1] = valStr;
	retVal[2] = unitStr;
	retVal[3] = stepStr;
	sprintf(unitType,"%d",unit_type);
	retVal[4] = unitType;
	retVal[5] = 0;

	return retVal;
}

char** getStatusValue(int camHandle, char *displayName) {

	int error;

	// one parameter example
	static char valStr[PAR_SIZE];
	static char retcode[PAR_SIZE];

	static char displayNameStatic[PAR_SIZE];  // the argument needs to be static and needs passed argument value copied for GetStatusValue call to work
	strcpy(displayNameStatic, displayName);

	error = pDll->GetStatusValue(camHandle,displayNameStatic,valStr,PAR_SIZE);

	// encode return values
	static char* retVal[3];
	sprintf(retcode,"%d",error);
	retVal[0] = retcode;
	retVal[1] = valStr;
	retVal[2] = 0;

	return retVal;
}

/* not supported in MapSLiLib *
/*
char** getStatusPulldownItem(char *displayName, int pulldownIndex) {

    int error;

	static char displayNameStatic[PAR_SIZE];  // the argument needs to be static and needs passed argument value copied for GetStatusValue call to work
	strcpy(displayNameStatic, displayName);

	static char pulldownValStr[PAR_SIZE];
	static char pulldownName[PAR_SIZE];
    static char retcode[PAR_SIZE];

    error = pDll->GetStatusPulldownItem (si_cam, displayNameStatic, pulldownIndex, pulldownValStr, PAR_SIZE, pulldownName, PAR_SIZE);

	static char* retVal[4];
	sprintf(retcode,"%d",error);
	retVal[0] = retcode;
	retVal[1] = pulldownValStr;
	retVal[2] = pulldownName;
	retVal[3] = 0;

	return retVal;

}
*/

char** getStatusBitField (int camHandle, char *displayName) {

   int error;

	static char displayNameStatic[PAR_SIZE];  // the argument needs to be static and needs passed argument value copied for GetStatusValue call to work
	strcpy(displayNameStatic, displayName);

	static char maskStr[PAR_SIZE];
	static char display[PAR_SIZE];
    static char retcode[PAR_SIZE];

    error = pDll->GetStatusBitField (camHandle, displayNameStatic, maskStr, PAR_SIZE, display, PAR_SIZE);

	static char* retVal[4];
	sprintf(retcode,"%d",error);
	retVal[0] = retcode;
	retVal[1] = display;
	retVal[2] = maskStr;
	retVal[3] = 0;

	return retVal;

}


int setParameterValue(int cameraHandle, char *displayName, char * valStr) {

    int error;

    static char displayNameStatic[PAR_SIZE];  // the argument needs to be static and needs passed argument value copied for GetStatusValue call to work
	strcpy(displayNameStatic, displayName);
    static char valStrStatic[PAR_SIZE];  // the argument needs to be static and needs passed argument value copied for GetStatusValue call to work
	strcpy(valStrStatic, valStr);

    return pDll->SetParameterValue (cameraHandle, displayNameStatic, valStrStatic);

}





int sendParameters(int cameraHandle) {
    return pDll->SendParameters(cameraHandle);
}

/* Not supported by MapSiLib */
/*
int updateParameters(int cameraHandle) {
    return pDll->UpdateParameters(cameraHandle);
}
*/

int getImageSize(int camHandle, int result[]) {

	static uint32_t nSerCCD;
	static uint32_t nParCCD;
	static uint32_t nSerSect;
	static uint32_t nParSect;
	static uint32_t serLen;
	static uint32_t parLen;
	static uint32_t is16;
    static int retcode;

    retcode = pDll->GetImageSize (camHandle, &serLen, &parLen, &is16, &nSerCCD, &nParCCD, &nSerSect, &nParSect);

	result[0] = (int)serLen;
	result[1] = (int)parLen;
	result[2] = (int)is16;
	result[3] = (int)nSerCCD;
	result[4] = (int)nParCCD;
	result[5] = (int)nSerSect;
	result[6] = (int)nParSect;

	return retcode;
}



/* Not supported by MapSiLib and not implemented here */
/*
int PrepareAcqU16 (SI_CAM cam, uint16_t SerLen, uint16_t ParLen, uint16_t _buffA, uint16_t _buffB,
int n_frames, char _file_name, char _fits_hdr)
Same as PrepareAcq(), except it is hard coded for unsigned 16 bit images.
int PrepareAcqI32 (SI_CAM cam, uint16_t SerLen, uint16_t ParLen, int32_t _buffA, int32_t _buffB,
int n_frames, char _file_name, char _fits_hdr)
Same as PrepareFramesAcquisition(), except it is hard coded for signed 32 bit images.
int ExposureRemainingTime (SI_CAM cam, uint32_t _remainingTime)
Returns the remaining exposure time.
*/


int acqStatus(int camHandle, int result[]) {

	static uint16_t percentRead;
	static uint32_t currentFrame;
	static uint32_t bufferFlags;
    static int retcode;

    retcode = pDll->AcqStatus(camHandle, &percentRead, &currentFrame, &bufferFlags);

    result[0] = (int)percentRead;
    result[1] = (int)currentFrame;
    result[2] = (int)bufferFlags;

    return retcode;
}

static uint16_t * imgBuffer;


int endAcq(int camHandle, bool forceAbort, int outArray[], int arraySize) {

    int retcode = pDll->EndAcq (camHandle, forceAbort);

    for(int i=0; i< arraySize; i++) {
    	outArray[i] = imgBuffer[i];
    }

    //delete imgBuffer;

    return retcode;
}

char** issueCommand(int camHandle, char *postName, char *argStr) {

    int error;

	static char postNameStatic[PAR_SIZE];
	strcpy(postNameStatic, postName);
	static char argStrStatic[PAR_SIZE];
	strcpy(argStrStatic, argStr);

	static char retStr[512];
    static char retcode[PAR_SIZE];

    error = pDll->IssueCommand (camHandle, postNameStatic, argStrStatic, retStr, 512);

	static char* retVal[3];
	sprintf(retcode,"%d",error);
	retVal[0] = retcode;
	retVal[1] = retStr;
	retVal[2] = 0;

	return retVal;


}

char** getXmlFile(int camHandle, char *fileName) {

    int error;
    static uint32_t bSize = 1000000;
	static char *bXml = new char[bSize];
	static uint32_t thisSize = bSize;

	static char fileNameStatic[PAR_SIZE];
	strcpy(fileNameStatic, fileName);
	static char retcode[PAR_SIZE];

	error = pDll->GetXmlFile(camHandle, fileNameStatic, bXml, &thisSize);

	static char* retVal[3];
    sprintf(retcode,"%d",error);
    retVal[0] = retcode;
    retVal[1] = bXml;
    retVal[2] = 0;

    return retVal;

}




/* this version only supports single frame aquisition and does not automatically save FITS files */
/* TODO: we can create a more full featured version if and when we need to */
int prepareAcquisition(int camHandle, int serLen, int parLen, int is16) {

    int error;
    imgBuffer = new uint16_t[serLen * parLen];

    printf("size = %d, %d", serLen, parLen);

    error = pDll->PrepareAcq(camHandle, serLen, parLen, (void*)imgBuffer, NULL, is16, 1, "", ""); // for 1 frame only 1 buffer needs to be defined

    return error;

}



int get_cam_info(int result[])
{

	int error;

	// scan interfaces for active cameras
	uint32_t bufSize = 10000;
	char* ifXml;
	ifXml = new char[bufSize];	// create a large text buffer

	// recurse into all plugins and scan for interfaces and active cameras
	error = pDll->ScanInterfaces(ifXml, (uint32_t *)&bufSize, true);
	// ifXml contains a XML formatted string containing the interface/camera information
	// a pull down menu can be created asking the user which camera to open

	// how to evaluate error messages
	char errorStr[512];
	uint32_t strSize = 512;
	if (error) {
		pDll->GetErrorString(error, errorStr,&strSize);	// strSize returns the real length of the string
		printf("ERROR %d %s\n",error,errorStr);
	}
	printf("%s\n",ifXml);
	// open the camera. Here it is hard coded, but you can get the interface/plugin information from ifXml
	//si_cam = pDll->OpenCamera("SIPCI","PciSi6762Camera");	// open camera and get handle (handles are positive numbers)
	int si_cam = pDll->OpenCamera("SISIM","SimCamera");	// open camera and get handle (handles are positive numbers)
	if (si_cam >= 0){
		uint32_t bSize = 1000000;
		char* bXml;
		bXml = new char[bSize];							// create 1M large text buffer
		uint32_t thisSize = bSize;
		error = pDll->GetXmlFile(si_cam,"files.xml",bXml,&thisSize);	// files.xml is in every camera. It lists which XML files can be retrieved
		printf("%s\n",bXml);

		// get a list of status names.
		error = pDll->GetStatusNames(si_cam, bXml, bSize);
		printf("status names = %s\n",bXml);


		// get list of parameter names
		error = pDll->GetParameterNames(si_cam, bXml, bSize);
		printf("parameter names = %s\n",bXml);

		// get list of allowable commands
		thisSize = bSize;
		error = pDll->GetXmlFile(si_cam,"command.xml",bXml,&thisSize);

		printf("commands = %s\n",bXml);

		// one parameter example
		char valStr[PAR_SIZE];
		char maxStr[PAR_SIZE];
		char minStr[PAR_SIZE];
		char unitStr[PAR_SIZE];
		char stepStr[PAR_SIZE];
		char * endPtr;
		unsigned short unit_type;
		error = pDll->GetParameterItem(si_cam,"Acquisition mode",valStr,PAR_SIZE,minStr,PAR_SIZE,maxStr,PAR_SIZE,&unit_type,unitStr,PAR_SIZE,stepStr,PAR_SIZE);
		printf("GetParameterItem::Aquisition mode:: %s %s %s %d %s %s\n", valStr, minStr, maxStr, unit_type, unitStr, stepStr);


		// how to get pulldown information (unit_type 8,9)
		char pulldownValStr[PAR_SIZE];
		char pulldownName[PAR_SIZE];
		for (int i=0; i<strtoul(maxStr,&endPtr,10); i++) {
			error = pDll->GetParameterPulldownItem(si_cam,"Acquisition mode",i,pulldownValStr,PAR_SIZE,pulldownName,PAR_SIZE);
			printf("Acquisition mode pulldown %d %s %s\n",i,pulldownValStr,pulldownName);
		}
		// set a parameter
		// --> SetParameterValue does not actually send the parameter to camera but marks it for sending.
		error = pDll->SetParameterValue(si_cam,"Acquisition mode","4");
		// --> set more parameters if needed
		error = pDll->SetParameterValue(si_cam,"Exposure Time","500");

		// send parameters to camera
		error = pDll->SendParameters(si_cam);	// this sends the marked (changed) parameters to camera.
		// take an image
		uint32_t nSerCCD;
		uint32_t nParCCD;
		uint32_t nSerSect;
		uint32_t nParSect;
		uint32_t serLen;
		uint32_t parLen;
		uint32_t is16;
		// read the image geometry from the camera parameters
		error = pDll->GetImageSize(si_cam, &serLen, &parLen, &is16, &nSerCCD, &nParCCD, &nSerSect, &nParSect);
		printf("%d %d %d %d %d %d %d\n",serLen, parLen, is16, nSerCCD, nParCCD, nSerSect, nParSect);

		result[0] = (int)serLen;
		result[1] = (int)parLen;
		result[2] = (int)is16;

		delete bXml;
	}
	delete ifXml;	// free the interface XML string

   return 0;
}





int cam_read(int serLenIn, int parLenIn, int is16In, int outArray[]) {

		printf("got to here");

//int cam_read(int serLenIn, int parLenIn, int is16In, int outArray[]) {


		uint32_t serLen = serLenIn;	
		uint32_t parLen = parLenIn;	
		uint32_t is16 = is16In;	


		char retStr[512];
		uint16_t  percent_read;
		uint32_t current_frame;
		uint32_t rd_flags;

		int si_cam = -1;
		int error;

		si_cam = pDll->OpenCamera("SISIM","SimCamera");	// open camera and get handle (handles are positive numbers)
		if (si_cam >= 0){

		imgBuffer = new uint16_t[serLen * parLen];

		printf("%d\n", sizeof(imgBuffer));

		if (imgBuffer){
			error = pDll->PrepareAcq(si_cam,serLen,parLen,(void*)imgBuffer,NULL,is16,1,"","");	// for 1 frame only 1 buffer needs to be defined
			if (!error){
				error = pDll->IssueCommand(si_cam,"ACQUIRE","0",retStr,512);
				int a=0;				
				//error = pDll->EndAcq(si_cam,true);	// cleanup function

				for (int i=0; i<500; i++){
					pDll->AcqStatus(si_cam,&percent_read,&current_frame,&rd_flags);
					printf("read %d  current frame %d  flags %d\n",percent_read, current_frame, rd_flags);
					if ((percent_read == 100) && (current_frame == 1) && (rd_flags & 0x1)) break;
					Sleep(100);
				}
				// imgBuffer is available here for processing

				// --> <--

				// at the end of all reads:
				error = pDll->EndAcq(si_cam,true);	// cleanup function

			}

			for(int i=0; i< serLen*parLen; i++) {
				outArray[i] = imgBuffer[i];
			}

			delete imgBuffer;
		}
		// close the camera again
		error = pDll->CloseCamera(si_cam);

	}

	//delete pDll;	// unload dll object
	return 0;
}


