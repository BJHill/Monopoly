#ifndef _TRADE_H_
#define _TRADE_H_

#include <vector>

namespace Monopoly
{
	class Property;

	struct Trade
	{
		int trader;
		int tradee;

		int money_to;
		int money_from;

		std::vector<Property*> property_from;
		std::vector<Property*> property_to;
 	};
};

#endif //_TRADE_H_