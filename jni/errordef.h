// This file is computer generated and should not be edited
#ifndef _ERRORDEF_H_
#define _ERRORDEF_H_

#define       E_NO_ERROR                          0     // Call was successful (no error).
#define       E_TIMEOUT                           1     // A timeout occurred.
#define       E_UNUSABLE_POINTER                  2     // The pointer provided is not usable for this operation.
#define       E_COM_ERROR                         3     // Communication error.
#define       E_DMA_ACTIVE                        4     // A DMA operation is already in progress.
#define       E_DMA_NOT_ACTIVE                    5     // DMA needs to be active for this operation.
#define       E_RETRIES_EXHAUSTED                 6     // Number of retries exhausted.
#define       E_FILE_NOT_FOUND                    7     // File not found.
#define       E_NO_DRIVERS_INSTALLED              8     // Drivers not installed.
#define       E_DMA_THREAD_FAILED                 9     // DMA engine failed.
#define       E_DEINTERLACE_THREAD_FAILED         10    // de-interlace thread failed.
#define       E_MEMORY_ALLOCATION_FAILED          11    // Couldn't allocate memory.
#define       E_INVALID_DEINTERLACE_MODE          12    // De-Interlace mode is not valid.
#define       E_INVALID_PARAMETER_OFFSET          13    // No parameters exists at requested offset.
#define       E_INVALID_CAMERA_DB_INDEX           14    // Index error in internal DataBase handling.
#define       E_MEDIA_TYPE_NOT_SELECTABLE         15    // Media type is read only.
#define       E_MEDIA_TYPE_INVALID                16    // Invalid Media type.
#define       E_STRING_TOO_LONG                   17    // String too long.
#define       E_NEGATIVE_RESPONSE                 18    // Negative response received from camera.
#define       E_FUNCTION_UNSUPPORTED              19    // Function is not supported in this configuration.
#define       E_UNSUPPORTED_RECORD_TYPE           20    // Record type is unsupported.
#define       E_FRAMING_OVERRUN                   21    // Overrun condition in framing acquisition.
#define       E_FILE_OPEN_ERROR                   22    // Error opening file.
#define       E_MODE_INVALID                      23    // Invalid Mode.
#define       E_NO_PLUGIN_FOUND                   24    // Plugin was not found.
#define       E_PARAMETER_ERROR                   25    // Parameter mismatch. Parameters do not describe a realistic scenario.
#define       E_COM_PORT_ERROR                    26    // Error opening a COM port.
#define       E_IF_SCAN_ERROR                     27    // Interface scan failed.
#define       E_INIT_DRIVER_FAILED                28    // Driver error.
#define       E_CAM_ALREADY_OPEN                  29    // Camera is already open and cannot be opened again.
#define       E_CAMERA_NOT_OPEN                   30    // Camera is not open. OpenCamera needs to be called first.
#define       E_LOAD_PARAMETERS_FAILED            31    // Parameters needed to open a camera could not be loaded.
#define       E_OPEN_CAMERA_FAILED                32    // Camera could not be opened.
#define       E_ERROR_STRING_NOT_FOUND            33    // There is no string for the requested error number.
#define       E_CAM_DAT_PARAMETER_LIST_NOT_FOUND  34    // Parameter document does not exist.
#define       E_CAM_DAT_PARAMETER_ENTRY_NOT_FOUND 35    // Parameter entry not found in document.
#define       E_CAM_DAT_STATUS_ITEM_NOT_FOUND     36    // Status entry not found in document.
#define       E_CAM_DAT_LOAD_FILE_FAILED          37    // Failed to load a data file.
#define       E_CAM_DAT_VALUES_DONT_VERIFY        38    // Parameter in both lists is different.
#define       E_CAM_DAT_VALUE_INVALID             39    // Element at this position has wrong type.
#define       E_CAM_DAT_DOCUMENT_EMPTY            40    // This document has no entries.
#define       E_CAM_DAT_LOAD_FAILED               41    // Loading a document failed.
#define       E_CAM_DAT_MODE_ERROR                42    // Mode wrong.
#define       E_CAM_DAT_MODE_NOT_FOUND            43    // Mode not found.
#define       E_CAM_DAT_BUFFER_TOO_SMALL          44    // Provided buffer is too small to fit the string.
#define       E_CAM_DAT_TOO_MANY_CHANGES          45    // Too many parameter changes requested before sending to camera.
#define       E_XML_FILE_CORRUPT                  46    // File length or CRC error loading XML file.
#define       E_END_ACQ_FAILED                    47    // End acquisition failed to unload threads and data buffers.
#define       E_FRAMES_ACQUISITION_UNSUPPORTED    48    // Camera does not support acquisition of multiple frames.
#define       E_PLUGIN_FILE_LOCATION_ERROR        49    // File location of plugin or configuration file is incorrect.
#define       E_COMMAND_ERROR                     50    // IssueCommand: wrong format or unrecognized command.
#define       E_CAM_DAT_PARAMETER_DOES_NOT_EXIST  51    // No such parameter exists.
#define       E_CAM_DAT_INSERT_STATUS_FAILED      52    // Can't insert Status record.
#define       E_CAM_DAT_READ_ONLY                 53    // Data is read only
#define       E_GX_TRANSLATION_FAILED             54    // Translation of G2-G3-G4 parameters failed
#define       PM_NO_ERROR                         0     // Ping mask: no error
#define       PM_NOT_SUPPORTED                   0xffffffff           // Ping mask: call is not supported
#define       PM_CAMERA_LOST_POWER               0x00001000           // Ping mask: Camera lost power and is not synchronized anymore
#endif // _ERRORDEF_H_
