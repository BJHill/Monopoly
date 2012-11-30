#ifndef _GAME_H_
#define _GAME_H_

#include <map>

namespace Monopoly
{
	class AIPlayer;
	class GameListener;
	class Player;
	class Property;

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
		void registerPlayer(const char* name);

		/**
		Start the game
		*/
		void startGame();

		/**
		Get the number of players in the game
		*/
		int getNumberPlayers() const;

		/**
		Get the Player data for a player in the game.
		*/
		const Player* getPlayer(int index) const;

		/**
		Get the Property data for a property in the game.
		*/
		const Property* getProperty(int index) const;

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
		void proposeTrade(const Trade& trade, int index);

	private:
		
		// Listener for the ui
		GameListener* m_uiListener;

		// Map of player index to ai object
		std::map<int, AIPlayer*> m_aiPlayers;
	};
};

#endif //_GAME_H_