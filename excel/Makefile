# Makefile para compilar a interface excel da biblioteca libpsychro
#CXX = i586-mingw32msvc-g++  #g++


biblioteca =  ../src/gas_perfeito.cpp ../src/ashrae.cpp ../src/giacomo.cpp
# CINCL = ../include


psychro.dll: excel_interface.cpp $(biblioteca) $(header) 
	$(CXX) -shared -o psychro.dll -I../include  excel_interface.cpp dllmain.cpp $(biblioteca) -Wl,--out-implib,libpsychro.a -Wl,--add-stdcall-alias -Wl,--output-def,psychro.def
   

