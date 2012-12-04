#ifndef _CARD_DECK_H_
#define _CARD_DECK_H_

#include <iostream>
#include <fstream>
#include <stdlib.h>

namespace Monopoly
{
  class Game;

  class CardDeck
  {
  public:

    /**
    Construct a new CardDeck from a cards file.
    */
    CardDeck(Game* game, const char* file);

    /**
    Destruct this CardDeck.
    */
    ~CardDeck();

    /**
    Draw a card for a player, returns true if a get out of jail card was drawn.
    */
    bool drawCard(int player);

    /**
    Replace a get out of Jail card.
    */
    void replaceCard();

  private:

    int get_number_cards(std::ifstream& ipf);
    void init_deck(int *deck, int sizeDeck);
    void shuffle(int *deck, int numberCards);
    void delete_card(int position, int length, int *deck);
    int draw_card(int *deck, std::ifstream& ipf);
    void put_card_back(int *deck, int card, int length);
  };
}

#endif //_CARD_DECK_H_