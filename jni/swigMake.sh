

swig -c++ -java -package org.tmt.aps.ics.sidetector.api -outdir ../src/main/java/org/tmt/aps/ics/sidetector/api sdk_cpp_con.i

g++ -g -ldl -c  sdk_cpp_con.cpp -fPIC -Wno-write-strings -I/usr/lib/jvm/java-1.8.0-openjdk-1.8.0.161-0.b14.el7_4.x86_64/include -I/usr/lib/jvm/java-1.8.0-openjdk-1.8.0.161-0.b14.el7_4.x86_64/include/linux

g++ -g -ldl -c MapSiLib.cpp -fPIC -I/usr/lib/jvm/java-1.8.0-openjdk-1.8.0.161-0.b14.el7_4.x86_64/include -I/usr/lib/jvm/java-1.8.0-openjdk-1.8.0.161-0.b14.el7_4.x86_64/include/linux

g++ -g -ldl -c sdk_cpp_con_wrap.cxx -fPIC -I/usr/lib/jvm/java-1.8.0-openjdk-1.8.0.161-0.b14.el7_4.x86_64/include -I/usr/lib/jvm/java-1.8.0-openjdk-1.8.0.161-0.b14.el7_4.x86_64/include/linux

g++ -shared sdk_cpp_con.o sdk_cpp_con_wrap.o MapSiLib.o  -o libsdkcppcon.so -ldl -lpthread

sudo cp libsdkcppcon.so /usr/local/lib

