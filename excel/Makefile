# Makefile para compilar a interface excel da biblioteca libpsychro
#CXX = i586-mingw32msvc-g++  #g++

biblioteca =  ../psychro/src/GasPerfeito.cpp ../psychro/src/Ashrae.cpp ../psychro/src/Giacomo.cpp
header = ../psychro/src/*.h


psychro.dll: excel_interface.cpp $(biblioteca) $(header) 
	$(CXX) -shared -o psychro.dll -I../psychro/src excel_interface.cpp dllmain.cpp $(biblioteca) -Wl,--out-implib,libpsychro.a -Wl,--add-stdcall-alias -Wl,--output-def,psychro.def
   
