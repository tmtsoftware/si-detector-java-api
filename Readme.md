# javaplc
A Java front-end to plcio library that supports reading and writing Java data into PLC Tags using the plcio library.  This package also supports packing multiple Java data items into plcio tag members.

Code Origin and Description of Changes
--------------------------------------
This code is modified from the DKIST abplc Java library.  The main changes are that the Channel and Connection classes have been omitted and calls are made directly to the PlcMaster class.  In addition, all DKIST framework dependencies: central Cache, PropertyDB, and supporting classes such as Property, Attribute, AttributeTable, etc have been removed from the package and from the code.  The bulk of the work in changing class implementations involved removing framework access from data classes such as PlcTag and PlcTagItem, which are retained in this package, but now only serve as true data classes with no external dependencies or methods resulting in side-effects.  To support this, the constructors for PlcTag and PlcTagItem have been modified so that configuration metadata is passed into the constructor rather than read from the framework inside these classes, and an additional public method has been added to PlcTag to access tag item values.

How the Library Works
---------------------
### Tag Concepts
#### Tag Members
A tag member is one of the tag’s sequence of data as declared in the plcio pcFormat string that fully describes the contents of the tag (e.g. “j8“ would describe data that consists of 2 integers (1 integer has length 4 bytes), this would be equivalent to “jj”.)  The pcFormat string describes the tag member data in the order it is defined in the tag, e.g. "jjic" would describe an 11 byte tag consisting of a 4 byte integer member followed by another 4 byte integer member followed by a 2 byte 'short' integer member followed by an 1 byte character or byte data member.

The plcio library supports the following member types:
<pre><code>
c   char      Character or Byte Data (8-bit)
i   short     Short Integer (16-bit)
j   int       Integer (32-bit for UNIX computers)
q   quad      Long-Long Integer (64-bit on UNIX computers)
r   float     Floating point (32-bit)
d   double    Double Precision Floating Point (64-bit)
</code></pre>

Note that 1-bit Boolean is not supported.

#### Tag Items
A tag item is the actual Java data (and its metadata description) that is mapped and potentially packed and unpacked to/from a Tag Member.  For example, note that 'boolean' is not a supported plcio library member type.  However, it is possible to pack multiple boolean values as bits (tag items) into a tag member (short or integer).  For example a tag member of pcFormat 'j', it is possible to pack 32 boolean bits as tag items into that member.

Tag Items require necessary metadata to describe their name, type, member and position within the member.
Tag Item contain the following metadata:
<pre><code>
   private final String itemName;
    private String itemTypeString;
    private final int memberNum;
    private final char memberPlcioType;
    private final int bytePos;
    private final int bitPos;
 </code></pre>

### Packing and Unpacking Java Data
The PlcTag class contains the metadata for all Tag Items in a PlcTag.  When the PlcMaster reads a tag, it reads each member and converts each member to its Java data type.  The array of members is stored in the PlcTag.

### Example usage

Note: The package comes with a class TestMain.java, which contains this and other examples of reading and writing single member and multiple member PLC Tags.

<pre><code>
// create the class ABPlcioMaster
IABPlcioMaster master = new ABPlcioMaster();

// setup for command (open)
PlcioCall plcioCallOpen = new PlcioCall(IPlcioCall.PlcioMethodName.PLC_OPEN, "cip 192.168.1.20", "Scott_Conn", 0);

// execute command (open)
master.plcAccess(plcioCallOpen);

// setup to read the compound tag Jimmy created on the PLC

// create a boolean tag item with it's name, type, member number, member pcFormat type, byte and bit position
TagItem tagItemB = new TagItem("myBooleanValue", IPlcTag.PropTypes.BOOLEAN.getTypeString(), 0, PlcioPcFormat.TYPE_J, 
   0, 0);

// create an integer tag item
TagItem tagItemS = new TagItem("myDecimalValue", IPlcTag.PropTypes.INTEGER.getTypeString(), 1, PlcioPcFormat.TYPE_J, 
   0, 0);

// create a floating point tag item
TagItem tagItemR = new TagItem("myRealValue", IPlcTag.PropTypes.REAL.getTypeString(), 2, PlcioPcFormat.TYPE_R, 0, 0);

// create a list of the tag items in the order that they will appear in the tag
TagItem[] tagItemsU = {tagItemB, tagItemS, tagItemR};

// create the PlcTag object, with the tag name, the pcFormat string ("jjr"), timeout, memberCount, byteCount 
//  and tagItem array.
PlcTag plcTagU = new PlcTag("Scott_U", IPlcTag.DIRECTION_READ,
""+ PlcioPcFormat.TYPE_J + PlcioPcFormat.TYPE_J + PlcioPcFormat.TYPE_R,
10000, 3, 12, tagItemsU);

// setup call for read command, passing in the open connection, and the plcTag object we just created
PlcioCall plcioCallReadU = new PlcioCall(IPlcioCall.PlcioMethodName.PLC_READ, "cip 192.168.1.20","Scott_R_Conn", 
   0, plcTagU);

// read the tag.  Once completed, the values for the tag are populated within the plcTagU object we passed in
master.plcAccess(plcioCallReadU);

// setup for command (close)
PlcioCall plcioCallClose = new PlcioCall(IPlcioCall.PlcioMethodName.PLC_CLOSE, "cip 192.168.1.20", "Scott_R_Conn", 0);

// execute command (close)
master.plcAccess(plcioCallClose);

// read item values by tag item name from the plcTagU object
String readValueU1 = plcTagU.getTagItemValue("myRealValue");
String readValueU2 = plcTagU.getTagItemValue("myDecimalValue");
String readValueU3 = plcTagU.getTagItemValue("myBooleanValue");

// print them out
System.out.println("readValueU1 read by client: " + readValueU1);
System.out.println("readValueU2 read by client: " + readValueU2);
System.out.println("readValueU3 read by client: " + readValueU3);
</code></pre>


Installing and Running
----------------------
### Installation
Download or clone this repository.
<pre><code>
cd java-plcio/jni
./scottMake.sh
cd java-plcio
sbt publishLocal
</code></pre>

### Running the Example
Note: TestMain.java does not currently support any other PLC but the one in the lab.  Tweaking the TestMain.java source code to point to a new IP is all that is needed to point to another one.

<pre><code>
sbt run
</code></pre>
