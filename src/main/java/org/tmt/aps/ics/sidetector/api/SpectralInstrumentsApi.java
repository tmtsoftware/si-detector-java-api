package org.tmt.aps.ics.sidetector.api;

import java.awt.image.BufferedImage;
import javax.imageio.ImageIO;
import java.io.File;
import java.util.List;
import java.util.ArrayList;
import java.util.HashMap;
import java.util.Map;

public class SpectralInstrumentsApi {


    private static final int UNITS_PRESSURE_IN_S800_UNITS = 1;
    private static final int UNITS_PRESSURE_IN_MILLITORR = 2;
    private static final int UNITS_TEMPERATURE_KELVIN_TIMES_10 = 3;
    private static final int UNITS_MILLIVOLTS = 4;
    private static final int UNITS_VOLTS = 5;
    private static final int UNITS_MILLIAMPS = 6;
    private static final int UNITS_MILLISECONDS = 7;
    private static final int UNITS_LIST_INDEX = 8;
    private static final int UNITS_SPARSE_LIST_INDEX = 9;
    private static final int UNITS_BIT_FIELD = 10;
    private static final int UNITS_NO_UNITS = 11;
    private static final int UNITS_CUSTOM_UNITS = 12;
    private static final int UNITS_IP_ADDRESS = 13;
    private static final int UNITS_RELATIVE_HUMIDITY_PERCENT_TIMES_100 = 14;
    private static final int UNITS_NANOMETERS = 15;
    private static final int UNITS_NANOSECONDS = 16;
    private static final int UNITS_TEXT_BYTES_ASCII = 17;


    private static void checkException(String retcodeStr) throws Exception {
        int retcode = new Integer(retcodeStr);
        checkException(retcode);
    }

    private static void checkException(int retcode) throws Exception {
        if (retcode == 0) return;

        // TODO: use retcode to find exception message, create and throw exception
        String[] returnVal = sdk_cpp_con.getErrorString(retcode);
        String errorMessage = returnVal[0];

        throw new Exception(errorMessage);
    }

	public static void loadDll() throws Exception {
		System.loadLibrary("sdkcppcon");
	 	int retcode = sdk_cpp_con.loadDll();
	 	checkException(retcode);
	}

    public static String scanInterfaces(boolean forceRescan) throws Exception {
        String[] returnArray = sdk_cpp_con.scanInterfaces(forceRescan);
        checkException(returnArray[0]);
        return returnArray[1];
    }

    /* Not supported by MapSiLib */
    /*
    public static String getSoftwareSummary(int camHandle) throws Exception {
        String[] returnArray = sdk_cpp_con.getSoftwareSummay(camHandle);
        checkException(returnArray[0]);
        return returnArray[1];
    }
    */



    public static int openCamera(String deviceName, String pluginName) throws Exception {
		String[] camInfo = {deviceName, pluginName};
		int retcode = sdk_cpp_con.openCamera(camInfo);
		checkException(retcode);
		return retcode;
	}

	/* Not supported by MapSiLib */
    /*
    public static int CameraHwReset (String deviceName, String pluginName) throws Exception {
        String[] camInfo = {deviceName, pluginName};
        int retcode = sdk_cpp_con.cameraHwReset(camInfo);
        checkException(retcode);
        return retcode;
    }
    */
	
	public static void closeCamera(int camHandle) throws Exception {
		int retcode = sdk_cpp_con.closeCamera(camHandle);
		checkException(retcode);
	}

	public static String getXmlFiles(int camHandle) {
		String[] textArray = sdk_cpp_con.getXmlFiles(camHandle);
		return textArray[0];
	}

    public static String getXmlFile(int camHandle, String fileName) throws Exception {
	    String[] cppRetArray = sdk_cpp_con.getXmlFile(camHandle, fileName);
	    checkException(cppRetArray[0]);
	    return cppRetArray[1];
    }



	//******* Status related API **********//

    public static void getStatus(int camHandle) throws Exception {
        int retcode = sdk_cpp_con.getStatus(camHandle);
        checkException(retcode);
    }

    // TODO: this could return retcode in the textArray first element
    // and use element index 1 for the data
    public static List<NameListItem> getStatusNames(int camHandle) {
        String[] textArray = sdk_cpp_con.getStatusNames(camHandle);

        List<NameListItem> nameList = NameListItem.generateList(textArray[0]);

        return nameList;
    }

    public static StatusItemInfo getStatusItem(int camHandle, String displayName) throws Exception {

        String[] statusItemInfoArray = sdk_cpp_con.getStatusItem(camHandle, displayName);
        checkException(statusItemInfoArray[0]);
        return new StatusItemInfo(displayName, statusItemInfoArray);
    }

    public static String getStatusValue(int camHandle, String displayName) throws Exception {
        String[] statusValueArray = sdk_cpp_con.getStatusValue(camHandle, displayName);
        checkException(statusValueArray[0]);
        return statusValueArray[1];
    }

    /* Not supported by MapSiLib */
    /*
    public static PulldownItem getStatusPulldownItem (String displayName, int pulldownIndex) throws Exception {

        String[] returnArray = sdk_cpp_con.getStatusPulldownItem(displayName, pulldownIndex);
        checkException(returnArray[0]);
        return new PulldownItem(returnArray[2], returnArray[1]);
    }
    */

    public static List<BitField> getStatusBitFields (int camHandle, String displayName) throws Exception {

        String[] returnArray = sdk_cpp_con.getStatusBitField(camHandle, displayName);
        checkException(returnArray[0]);

        return BitField.generateBitFieldList(returnArray[1], returnArray[2]);
    }

    // Master method to bring in the entire status structure
    public static List<StatusItemInfo> getAllStatuses(int camHandle) throws Exception {

        ArrayList<StatusItemInfo> allStatusList = new ArrayList<StatusItemInfo>();

        // get current values from camera
        getStatus(camHandle);
        // get names
        List<NameListItem> statusNameList = getStatusNames(camHandle);
        for (NameListItem statusNameItem : statusNameList) {
            // extract name
            String displayName = statusNameItem.getDisplayName();

            // get status item
            StatusItemInfo statusItemInfo = getStatusItem(camHandle, displayName);
            statusItemInfo.setWriteable(statusNameItem.isWriteable());


            allStatusList.add(statusItemInfo);

            // if the status item type is bit field, get the bit fields
            int unitType = statusItemInfo.getUnitType();
            if (unitType == UNITS_BIT_FIELD) {
                List<BitField> bitFieldList = getStatusBitFields(camHandle, displayName);
                statusItemInfo.setBitFieldList(bitFieldList);
            }
        }

        return allStatusList;
    }




    // *********  Parameter Related API   ********** //

    public static void getParameters(int camHandle) throws Exception {
        int retcode = sdk_cpp_con.getParameters(camHandle);
        checkException(retcode);
    }

    // TODO: this could return retcode in the textArray first element
    // and use element index 1 for the data
    public static List<NameListItem> getParameterNames(int camHandle) {
        String[] textArray = sdk_cpp_con.getParameterNames(camHandle);

        List<NameListItem> nameList = NameListItem.generateList(textArray[0]);

        return nameList;
    }

    public static ParameterItemInfo getParameterItem(int camHandle, String displayName) throws Exception {

        String[] parameterItemInfoArray = sdk_cpp_con.getParameterItem(camHandle, displayName);
        checkException(parameterItemInfoArray[0]);
        return new ParameterItemInfo(displayName, parameterItemInfoArray);
    }

    public static String getParameterValue(int camHandle, String displayName) throws Exception {
        String[] parameterValueArray = sdk_cpp_con.getParameterValue(camHandle, displayName);
        checkException(parameterValueArray[0]);
        return parameterValueArray[1];
    }

    public static void setParameterValue(int camHandle, String displayName, String valStr) throws Exception {
        int retcode = sdk_cpp_con.setParameterValue(camHandle, displayName, valStr);
        checkException(retcode);
    }


    public static PulldownItem getParameterPulldownItem (int camHandle, String displayName, int pulldownIndex) throws Exception {

        String[] returnArray = sdk_cpp_con.getParameterPulldownItem(camHandle, displayName, pulldownIndex);
        checkException(returnArray[0]);
        return new PulldownItem(returnArray[2], returnArray[1]);
    }

    /* Not supported by MapSiLib */
    /*
    public static List<BitField> getParameterBitFields (String displayName) throws Exception {

        String[] returnArray = sdk_cpp_con.getParameterBitField(displayName);
        checkException(returnArray[0]);

        return BitField.generateBitFieldList(returnArray[1], returnArray[2]);
    }
    */

    // Master method to bring in the entire status structure
    public static Map<String, List<ParameterItemInfo>> getAllParameters(int camHandle) throws Exception {

        Map<String, List<ParameterItemInfo>> allParameterLists = new HashMap<String, List<ParameterItemInfo>>();

        // get current values from camera
        getParameters(camHandle);
        // get names
        List<NameListItem> parameterNameList = getParameterNames(camHandle);
        for (NameListItem parameterNameItem : parameterNameList) {
            // extract name
            String displayName = parameterNameItem.getDisplayName();
            // extract parameter type
            String listName = parameterNameItem.getListName();

            // get parameter item
            ParameterItemInfo parameterItemInfo = getParameterItem(camHandle, displayName);
            parameterItemInfo.setWriteable(parameterNameItem.isWriteable());

            List<ParameterItemInfo> parameterList = allParameterLists.get(listName);
            if (parameterList == null) {
                parameterList = new ArrayList<ParameterItemInfo>();
                allParameterLists.put(listName, parameterList);
            }

            parameterList.add(parameterItemInfo);

            // add in pulldowns for this parameter, if any

            int unitType = parameterItemInfo.getUnitType();
            if (unitType == UNITS_LIST_INDEX || unitType == UNITS_SPARSE_LIST_INDEX) {
                // we use max value to determine the number of pulldown list entries
                List<PulldownItem> pulldownItemList = new ArrayList<PulldownItem>();
                for (int i=0; i<parameterItemInfo.getMax(); i++) {
                    PulldownItem pulldownItem = getParameterPulldownItem (camHandle, parameterItemInfo.getDisplayName(), i);
                    pulldownItemList.add(pulldownItem);
                }
                parameterItemInfo.setPulldownItemList(pulldownItemList);

            }
        }

        return allParameterLists;
    }



    public static void sendParameters(int cameraHandle) throws Exception {
        int retcode = sdk_cpp_con.sendParameters(cameraHandle);
        checkException(retcode);
    }

    /* Not supported by MapSiLib */
    /*
    public static updateParameters(int cameraHandle) throws Exception {
        int retcode = sdk_cpp_con.updateParameters(cameraHandle);
        checkException(retcode);
    }
    */


    public static ImageSizeInfo getImageSize(int cameraHandle) throws Exception {

        int result[] = new int[7];
        int retcode = sdk_cpp_con.getImageSize(cameraHandle, result);
        checkException(retcode);

        return new ImageSizeInfo(result);
    }

    public static void prepareAcquisition(int camHandle, int serLen, int parLen, int is16) throws Exception {
        int retcode = sdk_cpp_con.prepareAcquisition(camHandle, serLen, parLen, is16);
        checkException(retcode);
    }


    public static String issueCommand(int camHandle, String postName, String argStr) throws Exception {

        String[] cppRetArray = sdk_cpp_con.issueCommand(camHandle, postName, argStr);
        checkException(cppRetArray[0]);

        return cppRetArray[1];
    }

    public static AcqStatusInfo getAcqStatus(int cameraHandle) throws Exception {

        int result[] = new int[3];
        int retcode = sdk_cpp_con.acqStatus(cameraHandle, result);
        checkException(retcode);

        return new AcqStatusInfo(result);
    }


    public static void endAcq(int camHandle, boolean forceAbort, int[] imgBuffer, int arrayLen) throws Exception {

        int retcode = sdk_cpp_con.endAcq(camHandle, forceAbort, imgBuffer, arrayLen);
        checkException(retcode);

    }






    public static void main(String argv[]) {

	    try {

            loadDll();
            int camHandle = openCamera("SISIM", "SimCamera");
            //System.out.println("camHandle = " + camHandle);

            //int retcode1 = cameraHwReset("SISIM", "SimCamera");
            //System.out.println("retcode1 = " + retcode1);


            getStatus(camHandle);

            Map<String, List<ParameterItemInfo>> allParameterLists = getAllParameters(camHandle);
            System.out.println("all parameters = " + allParameterLists);
            for (List list : allParameterLists.values()) {
                System.out.println("list size = " + list.size());
            }



            String xmlFiles = getXmlFiles(camHandle);
            //System.out.println("xmlFiles = " + xmlFiles);

            List<NameListItem> statusNames = getStatusNames(camHandle);
            //System.out.println("statusNames = " + statusNames);

            StatusItemInfo statusItemInfo = getStatusItem(camHandle,"CCD 0 CCD Temp.");
            //System.out.println(statusItemInfo);

            String statusValue = getStatusValue(camHandle,"CCD 0 CCD Temp.");
            //System.out.println(statusValue);

            List<NameListItem> parameterNames = getParameterNames(camHandle);
            //System.out.println(parameterNames);

            ParameterItemInfo parameterItemInfo = getParameterItem(camHandle,"Exposure Time");
            //System.out.println(parameterItemInfo);

            String parameterValue = getParameterValue(camHandle, "Exposure Time");
            //System.out.println(parameterValue);

            PulldownItem pulldownItem = getParameterPulldownItem(camHandle,"Bits Per Pixel", 0);
            //System.out.println(pulldownItem);

            List<BitField> bitFieldList1 = getStatusBitFields (camHandle, "HKS Flags");
            //System.out.println("bitFields = " + bitFieldList1);

            //List<BitField> bitFieldList2 = getParameterBitFields (camHandle, "HKS Flags");
            //System.out.println("bitFields = " + bitFieldList2);




            List<StatusItemInfo> allStatusList = getAllStatuses(camHandle);
            System.out.println("all statuses = " + allStatusList);
            System.out.println("all statuses size = " + allStatusList.size());

            setParameterValue(camHandle,"Exposure Time", "500");

            setParameterValue(camHandle,"Acquisition mode", "3");

            sendParameters(camHandle);
            //updateParameters(camHandle);


            ImageSizeInfo imageSizeInfo = getImageSize(camHandle);
            //System.out.println(imageSizeInfo);

            String commands = getXmlFile(camHandle, "command.xml");
            System.out.println("getXmlFile::commands = " + commands);



            prepareAcquisition(camHandle, imageSizeInfo.getSerLen(), imageSizeInfo.getParLen(), imageSizeInfo.getIs16());

            String retString = issueCommand(camHandle, "ACQUIRE","0");
            System.out.println("issueCommand::retString = " + retString);


            while(true) {
                AcqStatusInfo acqStatusInfo = getAcqStatus(camHandle);
                System.out.println(acqStatusInfo);
                if (acqStatusInfo.getPercentRead() == 100) break;
                Thread.sleep(100);
            }


            int[] imageBuffer = new int[imageSizeInfo.getSerLen() * imageSizeInfo.getParLen()];
            endAcq(camHandle, true, imageBuffer, imageBuffer.length);


            System.out.println("image values = " + imageBuffer[1005000]);

            BufferedImage image = new BufferedImage(imageSizeInfo.getSerLen()/4, imageSizeInfo.getParLen()/4, BufferedImage.TYPE_INT_RGB);
            for (int y = 0; y < imageSizeInfo.getParLen()/4; y++)
                for (int x = 0; x < imageSizeInfo.getSerLen()/4; x++) {

                    image.setRGB(x, y, toRGB(imageBuffer[y * imageSizeInfo.getSerLen() * 4 + x * 4]));
                }
            try {
                // Once you have the image, you can save it to a file
                ImageIO.write(image, "png", new File("test.png"));

            } catch (Exception e) {
                e.printStackTrace();
            }

            retString = issueCommand(camHandle, "OPSTAT","");
            System.out.println("OPSTAT::retString = " + retString);


            closeCamera(camHandle);

            String interfaces = scanInterfaces(true);
            //System.out.println("interfaces = " + interfaces);

            //String summary = getSoftwareSummary(camHandle);
            //System.out.println("summary = " + summary);

            //checkException(13);

        } catch (Exception e) {
	        e.printStackTrace();
        }


	//int value = sdk_cpp_con.get_test();

	//System.out.println("value = " + value);


/*

	int result[] = new int[3];
	int value2 = sdk_cpp_con.get_cam_info(result);
	
	int serLen = result[0];
	int parLen = result[1];
	int is16 = result[2];
	//int serLen = sdk_cpp_con.getSerLenGlobal();
	//int parLen = sdk_cpp_con.getParLenGlobal();
	//int is16 = sdk_cpp_con.getIs16Global();
	System.out.println("serLen = " +serLen + ", parLen = " + parLen + ", is16 = " + is16);

	int outArray[] = new int[10576*10560];
	//sdk_cpp_con.test(outArray);

	sdk_cpp_con.cam_read(serLen, parLen, is16, outArray);

	// Then, to make the whole image, set all the pixel values

	BufferedImage image = new BufferedImage(serLen/4, parLen/4, BufferedImage.TYPE_INT_RGB);
	for (int y = 0; y < parLen/4; y++)
    	   for (int x = 0; x < serLen/4; x++)
        	image.setRGB(x, y, toRGB(outArray[y*serLen*4 + x*4]));

	try {
	   // Once you have the image, you can save it to a file
	   ImageIO.write(image, "png", new File("test.png"));

	} catch (Exception e) {
	  e.printStackTrace();
	}
*/	
  }

  // Produces a color where all three channels 
  // (RGB - red, green and blue) have the same value, which makes a gray.
  static int toRGB(int value) {
    return value * 0x10101;
  }

}
