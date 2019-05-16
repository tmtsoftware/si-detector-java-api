/* ----------------------------------------------------------------------------
 * This file was automatically generated by SWIG (http://www.swig.org).
 * Version 3.0.12
 *
 * Do not make changes to this file unless you know what you are doing--modify
 * the SWIG interface file instead.
 * ----------------------------------------------------------------------------- */

package org.tmt.aps.ics.sidetector.api;

public class sdk_cpp_conJNI {
  public final static native int loadDll();
  public final static native String[] scanInterfaces(boolean jarg1);
  public final static native String[] getSoftwareSummary(int jarg1);
  public final static native int openCamera(String[] jarg1);
  public final static native int closeCamera(int jarg1);
  public final static native String[] getErrorString(int jarg1);
  public final static native int getStatus(int jarg1);
  public final static native int getParameters(int jarg1);
  public final static native String[] getXmlFiles(int jarg1);
  public final static native String[] getXmlFile(int jarg1, String jarg2);
  public final static native String[] getStatusNames(int jarg1);
  public final static native String[] getStatusItem(int jarg1, String jarg2);
  public final static native String[] getStatusValue(int jarg1, String jarg2);
  public final static native String[] getStatusPulldownItem(int jarg1, String jarg2, int jarg3);
  public final static native String[] getStatusBitField(int jarg1, String jarg2);
  public final static native String[] getParameterNames(int jarg1);
  public final static native String[] getParameterItem(int jarg1, String jarg2);
  public final static native String[] getParameterValue(int jarg1, String jarg2);
  public final static native String[] getParameterPulldownItem(int jarg1, String jarg2, int jarg3);
  public final static native String[] getParameterBitField(int jarg1, String jarg2);
  public final static native int setParameterValue(int jarg1, String jarg2, String jarg3);
  public final static native int sendParameters(int jarg1);
  public final static native int updateParameters(int jarg1);
  public final static native int get_cam_info(int[] jarg1);
  public final static native int cam_read(int jarg1, int jarg2, int jarg3, int[] jarg4);
  public final static native int getImageSize(int jarg1, int[] jarg2);
  public final static native int prepareAcquisition(int jarg1, int jarg2, int jarg3, int jarg4);
  public final static native String[] issueCommand(int jarg1, String jarg2, String jarg3);
  public final static native int acqStatus(int jarg1, int[] jarg2);
  public final static native int endAcq(int jarg1, boolean jarg2, int[] jarg3, int jarg4);
}