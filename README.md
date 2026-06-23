A plasmoid to control your laptop's fan through `nbfc` utility. Maybe also supports nbfc-linux port, but never tested.

Targeting Plasma 6, for Plasma 5 there is a separate branch but it's not supported anymore.

This Plugin will install a helper Plugin that uses KAuth so you don't have to type root password every time.

-- Build instructions --

cd /where/your/applet/is/generated
mkdir build
cd build
cmake -DCMAKE_INSTALL_PREFIX=MYPREFIX .. 
make 
make install