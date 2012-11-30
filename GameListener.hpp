#ifndef _GAME_LISTENER_H_
#define _GAME_LISTENER_H_

namespace Monopoly
{
  struct Trade;

  class GameListener
  {
  public:

    virtual void turnStart(int index) = 0;
    virtual void turnEnd(int index) = 0;
    virtual bool acceptTrade(const Trade& trade) = 0;
    virtual bool buyProperty(int index) = 0;
    virtual void raiseFunds(int amount) = 0;
  };
};

#endif //_GAME_LISTENER_H_