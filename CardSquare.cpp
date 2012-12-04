#include "CardSquare.hpp"

#include "CardDeck.hpp"
#include "Game.hpp"
#include "Player.hpp"

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
	bool jail;

	if (m_type == 1)
	{
		jail = m_game->getChanceCards()->drawCard(player);
	}
	else
	{
		jail = m_game->getCommunityCards()->drawCard(player);
	}

	if (jail)
	{
		m_game->getPlayer(player)->keep_card(m_type);
	}
}