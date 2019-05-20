# variables: compiler
CXX=g++
LD=g++

# variables: flags
CXXFLAGS=-std=c++11  -Wall -pedantic -Wno-long-long -O0 -ggdb
LDFLAGS=-std=c++11 -Wall -pedantic -Wno-long-long -O0 -ggdb

# compile and generate documentation
all: obj compile doc

# just compile
compile: obj obj/main.o obj/Source/Game.o obj/Source/MainMenu.o obj/Source/Cards/BasicCard.o obj/Source/Cards/Card.o \
         obj/Source/Cards/CardDatabase.o obj/Source/Cards/DoubleCard.o obj/Source/Cards/DualCard.o obj/Source/Cards/FlexCard.o \
         obj/Source/Cards/FlipCard.o obj/Source/Player/Hand.o obj/Source/Player/PlayerBoard.o obj/Source/Player/Deck/Deck.o \
         obj/Source/Player/Player/ComputerPlayer.o obj/Source/Player/Player/HumanPlayer.o obj/Source/Player/Player/Player.o \
         obj/Source/Utilities/DeckParser.o obj/Source/Utilities/RandomNumberGenerator.o
	$(LD) $(LDFLAGS) obj/main.o obj/Source/Game.o obj/Source/MainMenu.o obj/Source/Cards/BasicCard.o obj/Source/Cards/Card.o \
                         obj/Source/Cards/CardDatabase.o obj/Source/Cards/DoubleCard.o obj/Source/Cards/DualCard.o obj/Source/Cards/FlexCard.o \
                         obj/Source/Cards/FlipCard.o obj/Source/Player/Hand.o obj/Source/Player/PlayerBoard.o obj/Source/Player/Deck/Deck.o \
                         obj/Source/Player/Player/ComputerPlayer.o obj/Source/Player/Player/HumanPlayer.o obj/Source/Player/Player/Player.o \
                         obj/Source/Utilities/DeckParser.o obj/Source/Utilities/RandomNumberGenerator.o \
                         -o gamesa 

obj/%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

# make directory clean again
clean:
	rm -rf gamesa
	obj doc

# make doxygen documentation
doc:
	doxygen Doxyfile
# run program
run:
	./gamesa
# create dir for storing object files
obj:
	mkdir obj
	mkdir obj/Source
	mkdir obj/Source/Cards obj/Source/Player obj/Source/Utilities
	mkdir obj/Source/Player/Deck obj/Source/Player/Player

# automaticaly generated dependancies
main.o: main.cpp Source/Game.h Source/Player/Player/Player.h \
 Source/Player/Player/../Deck/Deck.h \
 Source/Player/Player/../Deck/../../Cards/Card.h \
 Source/Player/Player/../Deck/../../Cards/BasicCard.h \
 Source/Player/Player/../Deck/../../Cards/Card.h \
 Source/Player/Player/../Deck/../../Cards/DoubleCard.h \
 Source/Player/Player/../Deck/../../Cards/FlexCard.h \
 Source/Player/Player/../Deck/../../Cards/DualCard.h \
 Source/Player/Player/../Deck/../../Cards/FlipCard.h \
 Source/Player/Player/../Deck/../../Utilities/RandomNumberGenerator.h \
 Source/Player/Player/../Deck/../../Cards/CardDatabase.h \
 Source/Player/Player/../PlayerBoard.h \
 Source/Player/Player/../../Cards/Card.h \
 Source/Player/Player/../../Cards/BasicCard.h \
 Source/Player/Player/../../Utilities/RandomNumberGenerator.h \
 Source/Player/Player/../../Cards/CardDatabase.h \
 Source/Player/Player/../Hand.h \
 Source/Player/Player/../../Cards/CardDatabase.h \
 Source/Utilities/RandomNumberGenerator.h Source/Cards/CardDatabase.h \
 Source/MainMenu.h Source/Cards/CardDatabase.h
Game.o: Game.cpp Game.h Player/Player/Player.h \
 Player/Player/../Deck/Deck.h Player/Player/../Deck/../../Cards/Card.h \
 Player/Player/../Deck/../../Cards/BasicCard.h \
 Player/Player/../Deck/../../Cards/Card.h \
 Player/Player/../Deck/../../Cards/DoubleCard.h \
 Player/Player/../Deck/../../Cards/FlexCard.h \
 Player/Player/../Deck/../../Cards/DualCard.h \
 Player/Player/../Deck/../../Cards/FlipCard.h \
 Player/Player/../Deck/../../Utilities/RandomNumberGenerator.h \
 Player/Player/../Deck/../../Cards/CardDatabase.h \
 Player/Player/../PlayerBoard.h Player/Player/../../Cards/Card.h \
 Player/Player/../../Cards/BasicCard.h \
 Player/Player/../../Utilities/RandomNumberGenerator.h \
 Player/Player/../../Cards/CardDatabase.h Player/Player/../Hand.h \
 Player/Player/../../Cards/CardDatabase.h \
 Utilities/RandomNumberGenerator.h Cards/CardDatabase.h \
 Utilities/Exceptions.h Utilities/DeckParser.h \
 Utilities/../Player/Deck/Deck.h
MainMenu.o: MainMenu.cpp MainMenu.h Cards/CardDatabase.h Cards/Card.h \
 Game.h Player/Player/Player.h Player/Player/../Deck/Deck.h \
 Player/Player/../Deck/../../Cards/Card.h \
 Player/Player/../Deck/../../Cards/BasicCard.h \
 Player/Player/../Deck/../../Cards/Card.h \
 Player/Player/../Deck/../../Cards/DoubleCard.h \
 Player/Player/../Deck/../../Cards/FlexCard.h \
 Player/Player/../Deck/../../Cards/DualCard.h \
 Player/Player/../Deck/../../Cards/FlipCard.h \
 Player/Player/../Deck/../../Utilities/RandomNumberGenerator.h \
 Player/Player/../Deck/../../Cards/CardDatabase.h \
 Player/Player/../PlayerBoard.h Player/Player/../../Cards/Card.h \
 Player/Player/../../Cards/BasicCard.h \
 Player/Player/../../Utilities/RandomNumberGenerator.h \
 Player/Player/../../Cards/CardDatabase.h Player/Player/../Hand.h \
 Player/Player/../../Cards/CardDatabase.h \
 Utilities/RandomNumberGenerator.h Player/Player/HumanPlayer.h \
 Player/Player/Player.h Player/Player/ComputerPlayer.h
BasicCard.o: BasicCard.cpp BasicCard.h Card.h
Card.o: Card.cpp Card.h
CardDatabase.o: CardDatabase.cpp CardDatabase.h Card.h FlipCard.h \
 DualCard.h BasicCard.h DoubleCard.h FlexCard.h ../Utilities/Exceptions.h \
 ../Utilities/DeckParser.h ../Utilities/../Player/Deck/Deck.h \
 ../Utilities/../Player/Deck/../../Cards/Card.h \
 ../Utilities/../Player/Deck/../../Cards/BasicCard.h \
 ../Utilities/../Player/Deck/../../Cards/DoubleCard.h \
 ../Utilities/../Player/Deck/../../Cards/FlexCard.h \
 ../Utilities/../Player/Deck/../../Cards/FlipCard.h \
 ../Utilities/../Player/Deck/../../Utilities/RandomNumberGenerator.h \
 ../Utilities/../Player/Deck/../../Cards/CardDatabase.h
DoubleCard.o: DoubleCard.cpp DoubleCard.h Card.h
DualCard.o: DualCard.cpp DualCard.h Card.h
FlexCard.o: FlexCard.cpp FlexCard.h DualCard.h Card.h
FlipCard.o: FlipCard.cpp FlipCard.h DualCard.h Card.h
Hand.o: Hand.cpp Hand.h ../Cards/Card.h ../Cards/CardDatabase.h \
 ../Cards/Card.h ../Utilities/Exceptions.h ../Utilities/DeckParser.h \
 ../Utilities/../Player/Deck/Deck.h \
 ../Utilities/../Player/Deck/../../Cards/Card.h \
 ../Utilities/../Player/Deck/../../Cards/BasicCard.h \
 ../Utilities/../Player/Deck/../../Cards/Card.h \
 ../Utilities/../Player/Deck/../../Cards/DoubleCard.h \
 ../Utilities/../Player/Deck/../../Cards/FlexCard.h \
 ../Utilities/../Player/Deck/../../Cards/DualCard.h \
 ../Utilities/../Player/Deck/../../Cards/FlipCard.h \
 ../Utilities/../Player/Deck/../../Utilities/RandomNumberGenerator.h \
 ../Utilities/../Player/Deck/../../Cards/CardDatabase.h
PlayerBoard.o: PlayerBoard.cpp PlayerBoard.h ../Cards/Card.h \
 ../Cards/BasicCard.h ../Cards/Card.h \
 ../Utilities/RandomNumberGenerator.h ../Cards/CardDatabase.h \
 ../Utilities/Exceptions.h ../Utilities/DeckParser.h \
 ../Utilities/../Player/Deck/Deck.h \
 ../Utilities/../Player/Deck/../../Cards/Card.h \
 ../Utilities/../Player/Deck/../../Cards/BasicCard.h \
 ../Utilities/../Player/Deck/../../Cards/DoubleCard.h \
 ../Utilities/../Player/Deck/../../Cards/Card.h \
 ../Utilities/../Player/Deck/../../Cards/FlexCard.h \
 ../Utilities/../Player/Deck/../../Cards/DualCard.h \
 ../Utilities/../Player/Deck/../../Cards/FlipCard.h \
 ../Utilities/../Player/Deck/../../Utilities/RandomNumberGenerator.h \
 ../Utilities/../Player/Deck/../../Cards/CardDatabase.h
Deck.o: Deck.cpp Deck.h ../../Cards/Card.h ../../Cards/BasicCard.h \
 ../../Cards/Card.h ../../Cards/DoubleCard.h ../../Cards/FlexCard.h \
 ../../Cards/DualCard.h ../../Cards/FlipCard.h \
 ../../Utilities/RandomNumberGenerator.h ../../Cards/CardDatabase.h \
 ../../Utilities/DeckParser.h ../../Utilities/../Player/Deck/Deck.h \
 ../../Utilities/Exceptions.h ../../Utilities/DeckParser.h
ComputerPlayer.o: ComputerPlayer.cpp ComputerPlayer.h Player.h \
 ../Deck/Deck.h ../Deck/../../Cards/Card.h \
 ../Deck/../../Cards/BasicCard.h ../Deck/../../Cards/Card.h \
 ../Deck/../../Cards/DoubleCard.h ../Deck/../../Cards/FlexCard.h \
 ../Deck/../../Cards/DualCard.h ../Deck/../../Cards/FlipCard.h \
 ../Deck/../../Utilities/RandomNumberGenerator.h \
 ../Deck/../../Cards/CardDatabase.h ../PlayerBoard.h ../../Cards/Card.h \
 ../../Cards/BasicCard.h ../../Utilities/RandomNumberGenerator.h \
 ../../Cards/CardDatabase.h ../Hand.h ../../Cards/CardDatabase.h \
 ../../Game.h ../../Player/Player/Player.h \
 ../../Utilities/RandomNumberGenerator.h ../../Utilities/Exceptions.h \
 ../../Utilities/DeckParser.h ../../Utilities/../Player/Deck/Deck.h
HumanPlayer.o: HumanPlayer.cpp HumanPlayer.h Player.h ../Deck/Deck.h \
 ../Deck/../../Cards/Card.h ../Deck/../../Cards/BasicCard.h \
 ../Deck/../../Cards/Card.h ../Deck/../../Cards/DoubleCard.h \
 ../Deck/../../Cards/FlexCard.h ../Deck/../../Cards/DualCard.h \
 ../Deck/../../Cards/FlipCard.h \
 ../Deck/../../Utilities/RandomNumberGenerator.h \
 ../Deck/../../Cards/CardDatabase.h ../PlayerBoard.h ../../Cards/Card.h \
 ../../Cards/BasicCard.h ../../Utilities/RandomNumberGenerator.h \
 ../../Cards/CardDatabase.h ../Hand.h ../../Cards/CardDatabase.h \
 ../../Game.h ../../Player/Player/Player.h \
 ../../Utilities/RandomNumberGenerator.h ../../Utilities/DeckParser.h \
 ../../Utilities/../Player/Deck/Deck.h ../../Utilities/Exceptions.h \
 ../../Utilities/DeckParser.h
Player.o: Player.cpp Player.h ../Deck/Deck.h ../Deck/../../Cards/Card.h \
 ../Deck/../../Cards/BasicCard.h ../Deck/../../Cards/Card.h \
 ../Deck/../../Cards/DoubleCard.h ../Deck/../../Cards/FlexCard.h \
 ../Deck/../../Cards/DualCard.h ../Deck/../../Cards/FlipCard.h \
 ../Deck/../../Utilities/RandomNumberGenerator.h \
 ../Deck/../../Cards/CardDatabase.h ../PlayerBoard.h ../../Cards/Card.h \
 ../../Cards/BasicCard.h ../../Utilities/RandomNumberGenerator.h \
 ../../Cards/CardDatabase.h ../Hand.h ../../Cards/CardDatabase.h \
 ../../Game.h ../../Player/Player/Player.h \
 ../../Utilities/RandomNumberGenerator.h ../../Utilities/DeckParser.h \
 ../../Utilities/../Player/Deck/Deck.h ../../Utilities/Exceptions.h \
 ../../Utilities/DeckParser.h HumanPlayer.h ComputerPlayer.h
DeckParser.o: DeckParser.cpp DeckParser.h ../Player/Deck/Deck.h \
 ../Player/Deck/../../Cards/Card.h ../Player/Deck/../../Cards/BasicCard.h \
 ../Player/Deck/../../Cards/Card.h \
 ../Player/Deck/../../Cards/DoubleCard.h \
 ../Player/Deck/../../Cards/FlexCard.h \
 ../Player/Deck/../../Cards/DualCard.h \
 ../Player/Deck/../../Cards/FlipCard.h \
 ../Player/Deck/../../Utilities/RandomNumberGenerator.h \
 ../Player/Deck/../../Cards/CardDatabase.h Exceptions.h
RandomNumberGenerator.o: RandomNumberGenerator.cpp \
 RandomNumberGenerator.h

