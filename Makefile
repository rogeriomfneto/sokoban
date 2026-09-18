CXX = g++

CXXFLAGS = -Iinclude
LDFLAGS = -Llib
LIBS = -lraylib -lgdi32 -lwinmm

TARGET = sokoban.exe
SOURCE = sokoban.cpp

$(TARGET): $(SOURCE)
	$(CXX) -o $(TARGET) $(SOURCE) $(CXXFLAGS) $(LDFLAGS) $(LIBS)

clean:
	del $(TARGET)