#include "AIPlayer.hpp"

#include "Game.hpp"
#include "Player.hpp"
#include "Trade.hpp"

Monopoly::AIPlayer::AIPlayer(Game* game, int index)
{
  m_game = game;
  m_index = index;
}

Monopoly::AIPlayer::~AIPlayer()
{

}

void Monopoly::AIPlayer::turnStart(int index)
{
  m_game->rollTurn();
}
    
void Monopoly::AIPlayer::turnEnd(int index)
{

}
    
bool Monopoly::AIPlayer::acceptTrade(const Trade& trade)
{
  double before = computeUtility(m_money, m_owned);
  
  std::vector<Property*> owned = m_owned;
  
	for (std::vector<Property*>::const_iterator it = trade.property_to.begin(); it != trade.property_to.end(); ++it)
    owned.push_back((*it));

	double after = computeUtility(m_money + trade.money_to - trade.money_from, owned);

  return (after > before);
}
   
bool Monopoly::AIPlayer::buyProperty(int index)
{
  return considerProperty(index);
}
    
bool Monopoly::AIPlayer::considerProperty(int index)
{
	return true;
}

void Monopoly::AIPlayer::raiseFunds(int amount)
{
  int raised = 0;

  // First sell avalible houses
  while (raised < amount && hasHouses())
    raised += sellNextHouse();

  // If the AI still needs to raise more mortage houses
  if (raised < amount)
  {
    while (raised < amount && hasUnmortgaged())
      raised += mortgageNextProperty();
  }

  // If we get here and raised < amount we are bankrupt
}