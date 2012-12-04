#include "Property.hpp"

#include <assert.h>

#include "Game.hpp"
#include "Player.hpp"

Monopoly::Property::Property(Game* game, int index, int type, int group, int size, const char* name) :
  Square(game, 0, name)
{
  m_index = index;

	m_group = group;
	m_groupSize = size;

	m_owned = false;
	m_owner = NULL;

	m_mortgaged = false;

	m_propertyType = type;

	for (int i = 0; i < 6; i++)
	{
		m_rentBands[i] = 0;
	}

	m_houses = 0;

	m_buyPrice = 0;
	m_housePrice = 0;
}

Monopoly::Property::~Property()
{

}

void Monopoly::Property::action(int player, int roll)
{
  if (!m_owned)
  {
		// If a player has enough money offer the chance to buy
		if (m_game->getPlayer(player)->get_money() > m_buyPrice)
		{
			bool buy = m_game->notifyOfferPurchase(m_index);

			if (buy)
			{
				m_game->getPlayer(player)->add_property(m_index, m_group, m_groupSize);
				m_game->getPlayer(player)->pay_money(m_buyPrice);
    
				m_owned = true;
				m_owner = m_game->getPlayer(player);
			}
		}
  }
  else
  {
		switch (m_propertyType)
		{
		case 1:
			payRentStreet(player);
			break;
		case 2:
			payRentRailway(player);
			break;
		case 3:
			payRentUtility(player, roll);
			break;
		}
  }
}

void Monopoly::Property::buyHouse()
{
	assert(m_propertyType == 1);
	assert(m_houses < 5);

	std::vector<int> streets = m_owner->return_all_cards_in_group(m_group);	

	bool canBuy = streets.size() == m_group;

	for (std::vector<int>::iterator it = streets.begin(); it != streets.end(); ++it)
	{
		int houses = m_game->getProperty(*it)->getNumberHouses();

		if (houses < m_houses)
		{
			canBuy = false;
		}
	}

	if (canBuy)
	{
		m_owner->pay_money(m_housePrice);
		m_houses++;
	}
}

int Monopoly::Property::getHousePrice()
{
	return m_housePrice;
}

int Monopoly::Property::getNumberHouses()
{
	return m_houses;
}

int Monopoly::Property::getPrice()
{
	return m_buyPrice;
}

int Monopoly::Property::getType()
{
	return m_propertyType;
}

void Monopoly::Property::payRentRailway(int player)
{
	std::vector<int> railways = m_owner->return_all_cards_in_group(m_group);
	
	m_game->getPlayer(player)->pay_money(m_rentBands[railways.size() - 1]);
	m_owner->get_money(m_rentBands[railways.size() - 1]);
}

void Monopoly::Property::payRentStreet(int player)
{
	std::vector<int> streets = m_owner->return_all_cards_in_group(m_group);

	if (streets.size() == m_groupSize)
	{
		int rent = m_rentBands[m_houses];

		if (m_houses == 0)
		{
			rent *= 2;
		}

		m_game->getPlayer(player)->pay_money(rent);
		m_owner->get_money(rent);	
	}
	else
	{
		m_game->getPlayer(player)->pay_money(m_rentBands[0]);
		m_owner->get_money(m_rentBands[0]);	
	}
}

void Monopoly::Property::payRentUtility(int player, int roll)
{
	std::vector<int> utilities = m_owner->return_all_cards_in_group(m_group);
	
	m_game->getPlayer(player)->pay_money(m_rentBands[utilities.size() - 1] * roll);
	m_owner->get_money(m_rentBands[utilities.size() - 1] * roll);
}

void Monopoly::Property::sellHouse()
{
	assert(m_propertyType == 1);
	assert(m_houses > 0);

	std::vector<int> streets = m_owner->return_all_cards_in_group(m_group);	

	bool canSell = streets.size() == m_group;

	for (std::vector<int>::iterator it = streets.begin(); it != streets.end(); ++it)
	{
		int houses = m_game->getProperty(*it)->getNumberHouses();

		if (houses > m_houses)
		{
			canSell = false;
		}
	}

	if (canSell)
	{
		m_owner->get_money(m_housePrice / 2);
		m_houses--;
	}
}


void Monopoly::Property::setPrice(int buy, int house)
{
	m_buyPrice = buy;
	m_housePrice = house;
}

void Monopoly::Property::setRent(int rent1, int rent2, int rent3, int rent4, int rent5, int rent6)
{
	m_rentBands[0] = rent1;
	m_rentBands[1] = rent2;
	m_rentBands[2] = rent3;
	m_rentBands[3] = rent4;
	m_rentBands[4] = rent5;
	m_rentBands[5] = rent6;
}