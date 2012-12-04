#include <iostream>

#include "Game.hpp"
#include "GameListener.hpp"
#include "player.hpp"

/* Forward decleration */
void init_players(Monopoly::Game& game, int numPlayers, char *argv[]);

struct Printer : public Monopoly::GameListener
{	
	virtual void turnStart(int index) 
	{
    printf("Player %d turn, position %d, money %d\n", index,  game->getPlayer(index)->get_position(), game->getPlayer(index)->get_money());

		int b = game->getPlayer(index)->get_position();

		int in = 1;
		
		printf("Press zero to roll:");
		scanf("%d", &in);
		
		game->rollTurn();

		int a = game->getPlayer(index)->get_position();

	}

	virtual void turnEnd(int index)
	{
    printf("Player %d turn end, position %d, money %d\n", index,  game->getPlayer(index)->get_position(), game->getPlayer(index)->get_money());
	}

	virtual void playerRolled(int player, int die1, int die2) 
	{
		printf("Player %d rolled, die1=%d, die2=%d, total=%d\n", player,  die1, die2, die1+die2);
	}
 
	virtual bool acceptTrade(int player, const Monopoly::Trade& trade){return false;}
	virtual bool buyProperty(int player, int index)
	{
		printf("Landed on property %d\n", index);


		int in = 1;

		printf("Press zero to buy:");
		scanf("%d", &in);

		if (in == 0)
		{
			printf("Buying property %d\n", index); 
			return true;
		}

		return false;
	}

	virtual void cardDrawn(int player, int type, int card) 
	{
		printf("Card drawn for player %d, type %d, card %d\n", player, type, card);
	}

	virtual void raiseFunds(int player, int amount) {}

	Monopoly::Game* game;
};

int main(int argc, char *argv[])
{ 
  int numberPlayers = argc-1;

	Monopoly::Game game;
	Printer listener;

	listener.game = &game;

	game.registerUIListener(&listener);

  init_players(game, numberPlayers, argv);
  
	game.startGame();

	return 0;
}

void init_players(Monopoly::Game& game, int numPlayers, char *argv[])
{    
  for(int i=0; i<numPlayers; i++)
  {
		game.registerPlayer(argv[i+1], 0);
  }
}