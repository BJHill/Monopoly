#ifndef _GAME_H_
#define _GAME_H_

#include <map>
#include <vector>

namespace Monopoly
{
	class AIPlayer;
	class GameListener;
	class Player;
	class CardDeck;
	class Property;
	class Square;

	struct Trade;

	class Game
	{
	public:

		/**
		Construct a new Game. 
		*/
		Game();

		/**
		Destruct this Game.
		*/
		~Game();

		/**
		Register the UI listener for callbacks.
		*/
		void registerUIListener(GameListener* listener);

		/**
		Register a new player with the game
		*/
		void registerPlayer(const char* name, int type);

		/**
		Start the game
		*/
		void startGame();
       
    /**
    Get the chance card CardDeck.
    */
    CardDeck* getChanceCards();

    /**
    Get the community card CardDeck.
    */
    CardDeck* getCommunityCards();

		/**
		Get the number of players in the game
		*/
		int getNumberPlayers() const;

		/**
		Get the Player data for a player in the game.
		*/
		Player* getPlayer(int index);

		/**
		Get the Property data for a property in the game.
		*/
		Property* getProperty(int index);
    
		/**
		Buy an amount of houses on a property.
		*/
		void buyHouses(int index, int amount);

		/**
		Sell an amount of houses on a property.
		*/
		void sellHouses(int index, int amount);

		/**
		Mortgage a property.
		*/
		void mortgageProperty(int index);

		/**
		Unmortgage a property.
		*/
		void unmortgageProperty(int index);

		/**
		Roll for the current players turn
		*/
		void rollTurn();

		/**
		Propose trade.
		*/
		bool proposeTrade(const Trade& trade, int index);

    /**
    Prompt a player to raise an amount of money to avoid bankruptcy.
    */
    void raiseFunds(int player, int amount);

    /**
    Offer a player a chance to buy a property.
    */
    bool offerPurchase(int index);

	private:

    /**
    Construct the game board.
    */
    void constructBoard();

    /**
    Test if the game is over, i.e there is only one non-bankrupt player.
    */
		bool gameOver();

    // Current player turn
		int m_turn;

    // Number of doubles rolled
    int m_doubles;

    // Players
		std::vector<Player*> m_players;

    // Board
		std::vector<Square*> m_board;

    // Deck of community cards
		CardDeck* m_communuityCard;

    // Deck of chance cards
		CardDeck* m_chanceCard;
    		
		// Listener for the ui
		GameListener* m_uiListener;

		// Map of player index to ai object
		std::map<int, AIPlayer*> m_aiPlayers;
	};
};

#endif //_GAME_H_