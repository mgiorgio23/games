CXX = g++
CXXFLAGS = -std=c++17 -Wall -Wextra

TARGET = game

SFML_INCLUDE = /opt/homebrew/include
SFML_LIB = /opt/homebrew/lib
SFML_LIBS = -lsfml-graphics -lsfml-window -lsfml-system
SRCS = main.cpp board.cpp
OBJS = $(SRCS:.cpp=.o)

all: $(TARGET)

$(TARGET): $(OBJS)
	$(CXX) $(OBJS) -L$(SFML_LIB) $(SFML_LIBS) -o $(TARGET)

%.o: %.cpp
	$(CXX) $(CXXFLAGS) -I$(SFML_INCLUDE) -c $< -o $@

clean:
	rm -f $(OBJS) $(TARGET)

.PHONY: all clean
