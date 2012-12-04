#include "CardSquare.hpp"

#include "CardDeck.hpp"
#include "Game.hpp"

Monopoly::CardSquare::CardSquare(Game* game, int type, const char *name) :
  Square(game, 0, name)
{
	m_type = type;
}

Monopoly::CardSquare::~CardSquare()
{

}

void Monopoly::CardSquare::action(int player, int roll)
{
	if (m_type == 1)
	{
		m_game->getChanceCards()->drawCard(player);
	}
	else
	{
		m_game->getCommunityCards()->drawCard(player);
	}
}