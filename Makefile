CC = g++
CFLAGS = -std=c++11 -Wall
TARGET = app.exe

ifdef DEBUG
	CFLAGS += -g
endif

BUILD_DIR = ./obj
SRC_DIR = ./src
INCLUDE_DIR = ./include

SRCS = main.cpp terminalFunctions.cpp sortAlgorithm.cpp menu.cpp algorithmsMenu.cpp visualizeMenu.cpp commandsMap.cpp
OBJS = $(SRCS:%.cpp=$(BUILD_DIR)/%.o)
DEPS = $(OBJS:.o=.d)

$(BUILD_DIR)/$(TARGET): $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) -o $(TARGET)

$(BUILD_DIR)/%.o: $(SRC_DIR)/%.cpp
	$(CC) $(CFLAGS) -I $(INCLUDE_DIR) -MMD -MP -c $< -o $@

# For headers also compile updates:
-include $(DEPS)

clean:
	rm -f $(BUILD_DIR)/* $(TARGET)
