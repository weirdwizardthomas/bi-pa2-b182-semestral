#Introduction
This is a C++ project developed for the purposes of the Programming and Algorithmics 2 course 
at the Faculty of Information Technology of the Czech Technical University in Prague.

The goal of the project was to demonstrate developed skills in design and implementation in the C++ programming language.

The programme offers a game of two local players against each other, a game against a computer player 
and crafting a deck outside of the game. The game is automatically saved every round and can be loaded.

# About Pazaak
Pazaak is a card game similar to Black Jack or 21. It has been introduced as a mini-game in Bioware's 
[Star Wars: Knights of the Old Republic](https://store.steampowered.com/app/32370/STAR_WARS__Knights_of_the_Old_Republic/) video game series.
Two players take turns against each other, drawing cards from a deck and playing them, trying to get their own personal score as close to 20 without surpassing it.

## Rules

A match of Pazaak consists of a series of rounds. Each player has two decks - a main deck and a side deck.
The main deck consists of cards numbered 1-10, four of each card, whilst the side deck is constructed 
by the player to contain ten cards.

A match of Pazaak is usually played in a best-of-three format, meaning the first player to achieve
 two victorious rounds wins the game.
 
At the start of each turn each player draws four cards from their deck and adds them to their hand
(here the rules differ from the original version, where the hand was drawn only once, at the beginning of the match).

During a round, players take turns. Each turn, a card is drawn from the 'main' deck of the current player and placed upon the game board.
Then the player can play one card from their hand, adding it to the game board. The current player can choose to 'pass'
their turn, which skips the use of a card in their hand. However, even if a player is passing, a card from the main deck is played nonetheless.

If the player is content with their board( = score), they can choose to 'stand' at the start of their turn, prior to playing any card (that includes cards from the main deck).
If they do so, they forfeit playing any cards for the remainder of the round, leaving the opposing party to play as much as they want without interruption.

### Winning the game
There are multiple ways of achieving victory in a round of Pazaak:
1. By outscore - attaining a score higher than the opponent without going over 20
1. By a 'bust' - whenever a player ends their turn with a score of more than 20, they automatically lose the round
1. By filling the table - if a player is able to place 9 cards on the table without going bust, they automatically win the round
1. By using a tiebreaker card - In case that the game is a tie (players have equal score), the player whose last card was a tiebreaker card wins the round

If neither of conditions are filled, the round results in a tie, with neither party gaining any points.

### Cards
Cards are the bread and butter, the backbone of the game. The content of one's side deck is the goal to win the game, as it brings the only way the player can influence the board directly.
There are seven types of cards in total, though some of them are just special cases of others:
1. Plus cards - Cards that add their value to the board, they range from 1 to 6.
2. Minus cards - Cards that subtract their value to the board, also ranging from (-)1 to (-)6.
3. Plus or minus cards - Cards are a combination of 'plus' and 'minus' cards. When played, they offer a choice of sign, 
   i.e. whether the player wants to add or subtract the card's value. These cards also range from 1 to 6.
4. Plus or minus 1/2 cards - A special case of the 'plus or minus' card, this card grants not just a choice of the sign, 
   but also of the value, either 1 or 2.  
5. Flip cards - Cards that have two values (a,b) , but do not influence the board directly. 
   These cards flip the signs of all the cards of the values (a,b),
   e.g. 2&4 inverts the sign of all +2,-2,+4,-4 to the opposite sign on the player's board. These cards range from 1 to 6/1 to 6.
6. Double card - doubles the value of the most recent played card.
7. Tiebreaker card - A 'plus or minus card' with a value of 1, that automatically wins a tie if it occurs.  

## The Computer player
The computer player does not play fair. It cheats. It has access to its entire deck, but is limited in the amount of cards it can play ( it can only play the same amount of cards the player can play). However, it has very flexible cards and can react to situations fairly effectively.

## Strategy
There are many guides and strategies to win Pazaak, below are some appraised ones:
* [Pazaak Guide by nyiaor2](https://gamefaqs.gamespot.com/pc/935881-star-wars-the-best-of-pc/faqs/27359)
* [GameBanshee](http://www.gamebanshee.com/starwarskotor/strategies/pazaak.php)
