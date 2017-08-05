# source 
[git for QT](http://code.qt.io/cgit/)
[download url](http://download.qt.io/archive/)


## skip modules
[ref](https://wiki.qt.io/Android)
./configure -xplatform android-g++ -nomake tests -nomake examples -android-ndk <path/to/ndk> -android-sdk <path/to/sdk> -android-ndk-host <e.g. linux-x86_64> -android-toolchain-version <e.g. 4.8> -skip qttranslations -skip qtwebkit -skip qtserialport -skip qtwebkit-examples -no-warnings-are-errors

## build on Ubuntu
./configure -prefix /home/tom/workspace.qt-install -opensource -confirm-license -debug -release -gif  -ico -sql-sqlite   -sqlite  -c++std c++1z -icu    -zlib  -qt-xcb -recheck -proprietary-codecs -pepper-plugins -embedded -printing-and-pdf  -webrtc -alsa -pulseaudio -webp -pulseaudio -ffmpeg  -skip qtscript -skip qtsensors -skip qtquickcontrols2 -skip qtwebview 