#ifndef _AI_PLAYER_H_
#define _AI_PLAYER_H_

#include <vector>

#include "GameListener.hpp"

namespace Monopoly
{
  class Game;
  class Property;

  struct Trade;

  class AIPlayer : public GameListener
  {
  public:

    /**
    Construct a new AIPlayer.
    */
    AIPlayer(Game* game, int index);

    /**
    Destruct this AIPlayer.
    */
    ~AIPlayer();

    /**
    Implement GameListener methods.
    */
    void turnStart(int index);
    void turnEnd(int index);
    bool acceptTrade(int player, const Trade& trade);
    bool buyProperty(int player, int property);
    void raiseFunds(int player, int amount);

  private:

		void buyHouses();

    int sellNextHouse();
    int mortgageNextProperty();

    bool hasUnmortgaged();
    bool hasHouses();

    double computeUtility(int money, const std::vector<Property*>& property);

    /**
    Consider buying property, return true if it should be bought.
    */
    bool considerProperty(int index);
    
    // Pointer to game instance
    Game* m_game;

    // Index of this ai player within the game.
    int m_index;

    std::vector<Property*> m_owned;

    int m_money;

    // Static probabilites used to buy/improve properties.
    static float* ms_boardReturns;
    static float* ms_boardProbabilites;
  };
};

#endif //_AI_PLAYER_H_