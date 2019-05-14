CXX= g++
CXXFLAGS= -g -Wall -pedantic
LDFLAGS=
EXECUTABLE= Pazaak
SOURCE_FOLDER = ./Source
CARDS_FOLDER = $(SOURCE_FOLDER)/Cards
PLAYER_FOLDER =  $(SOURCE_FOLDER)/Player
UTILITIES_FOLDER =  $(SOURCE_FOLDER)/Utilities
OUTPUT_FOLDER =  ./Output

CARDS_SOURCE = $(CARDS_FOLDER)/Card.h $(CARDS_FOLDER)/DoubleCard.h $(CARDS_FOLDER)/DualCard.h $(CARDS_FOLDER)/FlexCard.h $(CARDS_FOLDER)/FlipCard.h $(CARDS_FOLDER)/CardDatabase.h $(CARDS_FOLDER)/Card.cpp $(CARDS_FOLDER)/DoubleCard.cpp $(CARDS_FOLDER)/DualCard.cpp $(CARDS_FOLDER)/FlexCard.cpp $(CARDS_FOLDER)/FlipCard.cpp $(CARDS_FOLDER)/CardDatabase.cpp
PLAYERS_SOURCE =  $(PLAYER_FOLDER)/Player/Player.h $(PLAYER_FOLDER)/Player/HumanPlayer.h $(PLAYER_FOLDER)/Player/ComputerPlayer.h $(PLAYER_FOLDER)/Player/Player.cpp $(PLAYER_FOLDER)/Player/HumanPlayer.cpp $(PLAYER_FOLDER)/Player/ComputerPlayer.cpp
CARD_CONTAINERS_SOURCE = $(PLAYER_FOLDER)/Deck/Deck.h $(PLAYER_FOLDER)/Hand.h $(PLAYER_FOLDER)/PlayerBoard.h $(PLAYER_FOLDER)/Deck/Deck.cpp $(PLAYER_FOLDER)/Hand.cpp $(PLAYER_FOLDER)/PlayerBoard.cpp
UTILITIES_SOURCE =  $(UTILITIES_FOLDER)/RandomNumberGenerator.h $(UTILITIES_FOLDER)/DeckParser.h  $(UTILITIES_FOLDER)/RandomNumberGenerator.cpp $(UTILITIES_FOLDER)/DeckParser.cpp
GAME_SOURCE= $(SOURCE_FOLDER)/MainMenu.h $(SOURCE_FOLDER)/Game.h  $(SOURCE_FOLDER)/MainMenu.cpp $(SOURCE_FOLDER)/Game.cpp
MAIN_SOURCE = ./main.cpp

OBJECTS = ./Card.o  ./DoubleCard.o ./DualCard.o ./FlexCard.o ./FlipCard.o ./CardDatabase.o ./DeckParser.o ./Player.o ./HumanPlayer.o ./ComputerPlayer.o  ./Deck.o ./Hand.o ./PlayerBoard.o ./MainMenu.o  ./Game.o ./main.o 

cards: $(CARDS_SOURCE)
	$(CXX) $(CXXFLAGS) -c $(LDFLAGS) $(CARDS_SOURCE)

players: $(PLAYERS_SOURCE)
	$(CXX) $(CXXFLAGS) -c $(LDFLAGS) $(PLAYERS_SOURCE)

card_containers: $(CARD_CONTAINERS_SOURCE)
	$(CXX) $(CXXFLAGS) -c $(LDFLAGS) $(CARD_CONTAINERS_SOURCE)

utilities: $(UTILITIES_SOURCE)
	$(CXX) $(CXXFLAGS) -c $(LDFLAGS) $(UTILITIES_SOURCE)

game: $(GAME_SOURCE)
	$(CXX) $(CXXFLAGS) -c $(LDFLAGS) $(GAME_SOURCE)

main: $(MAIN_SOURCE)
	$(CXX) $(CXXFLAGS) -c $(LDFLAGS) $(MAIN_SOURCE)



compile: cards players card_containers game utilities main
	$(CXX) $(CXXFLAGS) -o $(LDFLAGS) $(OBJECTS)

clean: 
	rm -f ./*.o
