/* sdk_cpp_con.i */
%module sdk_cpp_con
%include cpointer.i
%include "arrays_java.i"
%include "std_string.i"
%include "typemaps.i"

/*
%typemap(out) uint16_t[] 
%{$result = SWIG_JavaArrayOutUchar(jenv, (uint16_t *)$1, 60); %}
%apply uint16_t[] {uint16_t *};
*/

%typemap(out) int[] 
%{$result = SWIG_JavaArrayOutInt(jenv, (int *)$1, 10576*10560); %}
%apply int[] {int *};


/* This tells SWIG to treat char ** as a special case when used as a parameter
   in a function call */
%typemap(in) char ** (jint size) {

    int i = 0;
    size = (jenv)->GetArrayLength($input);
    $1 = (char **) malloc((size+1)*sizeof(char *));
    /* make a copy of each string */
    for (i = 0; i<size; i++) {
        jstring j_string = (jstring)(jenv)->GetObjectArrayElement($input, i);
        const char * c_string = (jenv)->GetStringUTFChars(j_string, 0);
        $1[i] = (char *)malloc((strlen(c_string)+1)*sizeof(char));
        strcpy($1[i], c_string);
        (jenv)->ReleaseStringUTFChars(j_string, c_string);
        (jenv)->DeleteLocalRef(j_string);
    }
    $1[i] = 0;
}

/* This cleans up the memory we malloc'd before the function call */
%typemap(freearg) char ** {
    int i;
    for (i=0; i<size$argnum-1; i++)
      free($1[i]);
    free($1);
}


/* This allows a C function to return a char ** as a Java String array */
%typemap(out) char ** {
    int i;
    int len=0;
    jstring temp_string;
    const jclass clazz = (jenv)->FindClass("java/lang/String");

    while ($1[len]) len++;    
    jresult = (jenv)->NewObjectArray(len, clazz, NULL);
    /* exception checking omitted */

    for (i=0; i<len; i++) {
      temp_string = (jenv)->NewStringUTF(*result++);
      (jenv)->SetObjectArrayElement(jresult, i, temp_string);
      (jenv)->DeleteLocalRef(temp_string);
    }
}


/* These 3 typemaps tell SWIG what JNI and Java types to use */
%typemap(jni) char ** "jobjectArray"
%typemap(jtype) char ** "String[]"
%typemap(jstype) char ** "String[]"

/* These 2 typemaps handle the conversion of the jtype to jstype typemap type
   and vice versa */
%typemap(javain) char ** "$javainput"
%typemap(javaout) char ** {
    return $jnicall;
  }


%{
/* Put header files here or function declarations like below */
#include<stdint.h>
extern int loadDll();
extern char** scanInterfaces (bool forceRescan);
extern char** getSoftwareSummary (int camHandle);
extern int openCamera(char **info);
//extern int cameraHwReset(char **info);
extern int closeCamera(int camHandle);
extern char** getErrorString(int retcode);
extern int getStatus(int camHandle);
extern int getParameters(int camHandle);
extern char** getXmlFiles(int camHandle);
extern char** getXmlFile(int camHandle, char *fileName);
extern char** getStatusNames(int camHandle);
extern char** getStatusItem(int camHandle, char *displayName);
extern char** getStatusValue(int camHandle, char *displayName);
extern char** getStatusPulldownItem(int camHandle, char *displayName, int pulldownIndex);
extern char** getStatusBitField (int camHandle, char *displayName);
extern char** getParameterNames(int camHandle);
extern char** getParameterItem(int camHandle, char *displayName);
extern char** getParameterValue(int camHandle, char *displayName);
extern char** getParameterPulldownItem(int camHandle, char *displayName, int pulldownIndex);
extern char** getParameterBitField (int camHandle, char *displayName);
extern int setParameterValue(int cameraHandle, char *displayName, char *valStr);
extern int sendParameters(int cameraHandle);
extern int updateParameters(int cameraHandle);
extern int get_cam_info(int result[]);
extern int cam_read(int serLen, int parLen, int is16, int outArray[]);

extern int getImageSize(int camHandle, int result[]);
extern int prepareAcquisition(int camHandle, int serLen, int parLen, int is16);
extern char** issueCommand(int camHandle, char *postName, char *argStr);
extern int acqStatus(int camHandle, int result[]);
extern int endAcq(int camHandle, bool forceAbort, int outArray[], int arraySize);
%}

extern int loadDll();
extern char** scanInterfaces (bool forceRescan);
extern char** getSoftwareSummary (int camHandle);
extern int openCamera(char **info);
//extern int cameraHwReset(char **info);
extern int closeCamera(int camHandle);
extern char** getErrorString(int retcode);
extern int getStatus(int camHandle);
extern int getParameters(int camHandle);
extern char** getXmlFiles(int camHandle);
extern char** getXmlFile(int camHandle, char *fileName);
extern char** getStatusNames(int camHandle);
extern char** getStatusItem(int camHandle, char *displayName);
extern char** getStatusValue(int camHandle, char *displayName);
extern char** getStatusPulldownItem(int camHandle, char *displayName, int pulldownIndex);
extern char** getStatusBitField (int camHandle, char *displayName);
extern char** getParameterNames(int camHandle);
extern char** getParameterItem(int camHandle, char *displayName);
extern char** getParameterValue(int camHandle, char *displayName);
extern char** getParameterPulldownItem(int camHandle, char *displayName, int pulldownIndex);
extern char** getParameterBitField (int camHandle, char *displayName);
extern int setParameterValue(int cameraHandle, char *displayName, char *valStr);
extern int sendParameters(int cameraHandle);
extern int updateParameters(int cameraHandle);
extern int get_cam_info(int result[]);
extern int cam_read(int serLen, int parLen, int is16, int outArray[]);

extern int getImageSize(int camHandle, int result[]);
extern int prepareAcquisition(int camHandle, int serLen, int parLen, int is16);
extern char** issueCommand(int camHandle, char *postName, char *argStr);
extern int acqStatus(int camHandle, int result[]);
extern int endAcq(int camHandle, bool forceAbort, int outArray[], int arraySize);
