


WX_CPP_FLAGS=$(wx-config --cxxflags)
WX_CPP_LIBS=$(wx-config --libs)
RUNTIME_LIBS=static
echo "WX_CPP_FLAGS: $WX_CPP_FLAGS"
echo "WX_CPP_LIBS: $WX_CPP_LIBS"
g++ hello-world.cpp -Wno-error -fpermissive  -I.  $WX_CPP_FLAGS $WX_CPP_LIBS -o hello-world
