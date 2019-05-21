CXX=g++
LD=g++

CXXFLAGS=-std=c++11  -Wall -pedantic -Wno-long-long -g
LDFLAGS=

TARGET = Pazaak
DEBUGGER = valgrind
DOXYGEN_CONFIGURATION_FILE = Doxyfile
OBJECT_OUTPUT_FILE = ./Output
LOGIN = koristo1

OBJECTS = $(OBJECT_OUTPUT_FILE)/main.o \
    	$(OBJECT_OUTPUT_FILE)/Source/Game.o \
	$(OBJECT_OUTPUT_FILE)/Source/MainMenu.o \
	$(OBJECT_OUTPUT_FILE)/Source/Cards/BasicCard.o \
	$(OBJECT_OUTPUT_FILE)/Source/Cards/Card.o \
	$(OBJECT_OUTPUT_FILE)/Source/Cards/CardDatabase.o \
	$(OBJECT_OUTPUT_FILE)/Source/Cards/DoubleCard.o \
	$(OBJECT_OUTPUT_FILE)/Source/Cards/DualCard.o \
	$(OBJECT_OUTPUT_FILE)/Source/Cards/FlexCard.o \
	$(OBJECT_OUTPUT_FILE)/Source/Cards/FlipCard.o \
	$(OBJECT_OUTPUT_FILE)/Source/Player/Hand.o \
	$(OBJECT_OUTPUT_FILE)/Source/Player/PlayerBoard.o \
	$(OBJECT_OUTPUT_FILE)/Source/Player/Deck/Deck.o \
	$(OBJECT_OUTPUT_FILE)/Source/Player/Player/ComputerPlayer.o \
	$(OBJECT_OUTPUT_FILE)/Source/Player/Player/HumanPlayer.o \
	$(OBJECT_OUTPUT_FILE)/Source/Player/Player/Player.o \
	$(OBJECT_OUTPUT_FILE)/Source/Utilities/DeckParser.o \
	$(OBJECT_OUTPUT_FILE)/Source/Utilities/RandomNumberGenerator.o \

all: $(OBJECT_OUTPUT_FILE) doc compile

compile: $(OBJECT_OUTPUT_FILE) $(OBJECTS)
	$(LD) $(LDFLAGS) $(OBJECTS) -o $(TARGET)

$(OBJECT_OUTPUT_FILE)/%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

clean:
	rm -rf $(TARGET)
	rm -rf Output doc

doc:
	doxygen $(DOXYGEN_CONFIGURATION_FILE)	

run: compile
	./$(TARGET)

debug: compile
	$(DEBUGGER) ./$(TARGET)

$(OBJECT_OUTPUT_FILE):
	mkdir $(OBJECT_OUTPUT_FILE)
	mkdir $(OBJECT_OUTPUT_FILE)/Source
	mkdir $(OBJECT_OUTPUT_FILE)/Source/Cards $(OBJECT_OUTPUT_FILE)/Source/Player
	mkdir $(OBJECT_OUTPUT_FILE)/Source/Utilities
	mkdir $(OBJECT_OUTPUT_FILE)/Source/Player/Deck
	mkdir $(OBJECT_OUTPUT_FILE)/Source/Player/Player
