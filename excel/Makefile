# Makefile para compilar a interface excel da biblioteca libpsychro
#CXX = i586-mingw32msvc-g++  #g++


biblioteca =  ../src/GasPerfeito.cpp ../src/Ashrae.cpp ../src/Giacomo.cpp
CINCL = ../include


psychro.dll: excel_interface.cpp $(biblioteca) $(header) 
	$(CXX) -shared -o psychro.dll -I$(CINCL)../psychro/src excel_interface.cpp dllmain.cpp $(biblioteca) -Wl,--out-implib,libpsychro.a -Wl,--add-stdcall-alias -Wl,--output-def,psychro.def
   

