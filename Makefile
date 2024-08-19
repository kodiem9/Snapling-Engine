INCLUDE_PATH = raylib/
LIBRARY_PATH = libraylib.a
SOURCE_FILES = main.cpp source/*.cpp
ARGUMENTS =
PRECOMPILED_HEADER_PATH = source/include/common
PROGRAM_NAME = game
CPP_VERSION = 17

default:
	time g++ $(ARGUMENTS) -include $(PRECOMPILED_HEADER_PATH)/PCH.hpp -I $(INCLUDE_PATH) $(SOURCE_FILES) -std=c++$(CPP_VERSION)  -L $(INCLUDE_PATH) -framework CoreVideo -framework IOKit -framework Cocoa -framework GLUT -framework OpenGL $(INCLUDE_PATH)$(LIBRARY_PATH) -o $(PROGRAM_NAME)  &&  ./$(PROGRAM_NAME)

pch:
	g++ -std=c++$(CPP_VERSION) -I raylib/ -x c++-header $(PRECOMPILED_HEADER_PATH)/PCH.cpp -o $(PRECOMPILED_HEADER_PATH)/PCH.hpp.gch