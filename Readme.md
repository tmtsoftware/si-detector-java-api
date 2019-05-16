# si-detector-java-api
A Java front-end to Spectral Instruments C++ API, plus convenience functions for constructing full structures of all
parameters and status items.


Installing and Running
----------------------
### Installation of Spectral Instruments Dlls
TBW

### Installation
Download or clone this repository.
<pre><code>
cd si-detector-java-api/jni
./swigMake.sh
cd si-detector-java-api
sbt publishLocal
</code></pre>

### Running the Example
The full API is in the class: SpectralInstrumentsApi.java.  A main() method is included in the class that exercises all API methods.
This can be executed using:
<pre><code>
sbt run
</code></pre>
