CXX = g++

CXXFLAGS = -std=c++17 -Iinclude
LDFLAGS = -Llib
LIBS = -lraylib

TARGET = sokoban
SOURCE = sokoban.cpp

DEL_CMD = rm

ifeq ($(OS),Windows_NT)
	LIBS += -lgdi32 -lwinmm
	TARGET = sokoban.exe
	DEL_CMD = del
endif

$(TARGET): $(SOURCE)
	$(CXX) -o $(TARGET) $(SOURCE) $(CXXFLAGS) $(LDFLAGS) $(LIBS)

clean:
	$(DEL_CMD) $(TARGET)
