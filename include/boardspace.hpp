# pragma once 

#include <string>
#include <vector>
#include "player.hpp"
#include "banker.hpp"
#include "carddeck.hpp"

using namespace std;

enum BoardSpaceType
{
  property = 0,
  railroad,
  utility,
  takecare,
  tax,
  freespace,
  jail
};

class BoardSpace
{
  public:

    BoardSpace(BoardSpaceType type, string name, const int position);
    ~BoardSpace();

    virtual bool HandlePlayerVisit(Player * player) = 0;

    string GetName() {
      return m_name;
    }

    Banker * GetBanker() {
      return m_banker;
    }

    void SetBanker(Banker * banker) {
      m_banker = banker;
    }

    BoardSpaceType GetType() {
      return m_type;
    }

    int GetPosition() {
      return m_position;
    }

  private:

    BoardSpaceType m_type;
    string m_name;
    int m_position;
    Banker * m_banker;
};

class Property : public BoardSpace
{
  public:

    Property(const string name, const int position, string groupName, int purchasePrice, vector<int> & houseRents);
    ~Property();

    bool HandlePlayerVisit(Player * player);

    void AddHouse();

    int GetHouseCount() {
      return m_houseCount;
    }

    bool DoesOwnerHaveMonopoly();

    void SetGroup(vector<Property *> & group) {
      m_group = group;
    }

    string GetGroupName() {
      return m_groupName;
    }

    int GetRent();

    int GetOwner() {

      if (m_owner != -1)
      {
          if (GetBanker()->IsPlayerActive(m_owner) == false)
          {
              m_owner = -1;
          }
      }

      return m_owner;
    }

    string GetOwnerInitial()
    {
      if (m_owner != -1)
      {
        return GetBanker()->GetPlayerInitial(m_owner);
      }

      return string("");
    }

  private:

    string m_groupName;
    std::vector<Property *> m_group;

    int m_purchasePrice;

    int m_baseRent;

    vector<int> m_houseRents;
    
    int m_houseCount;

    int m_owner;
};

class RailRoad : public BoardSpace
{
  public:
    RailRoad(const string name, const int position);
    ~RailRoad();

    bool HandlePlayerVisit(Player * player);

    int GetRailroadsOwnedByPlayer(const int ownerId);

    void SetGroup(vector<RailRoad *> & group) {
      m_group = group;
    }

    int GetTicketPrice();

    int GetOwner() {

      if (m_owner != -1)
      {
          if (GetBanker()->IsPlayerActive(m_owner) == false)
          {
              m_owner = -1;
          }
      }

      return m_owner;
    }

    string GetOwnerInitial()
    {
      if (m_owner != -1)
      {
        return GetBanker()->GetPlayerInitial(m_owner);
      }

      return string("");
    }

  private:
    
    int m_owner;

    vector<RailRoad *> m_group;
};

class Utility : public BoardSpace
{
  public:
    Utility(const string name, const int position);
    ~Utility();

    bool HandlePlayerVisit(Player * player);

    bool DoesPlayerOwnBothUtilities(const int playerId);

    int GetOwner() {

      if (m_owner != -1)
      {
          if (GetBanker()->IsPlayerActive(m_owner) == false)
          {
              m_owner = -1;
          }
      }

      return m_owner;
    }

    string GetOwnerInitial()
    {
      if (m_owner != -1)
      {
        return GetBanker()->GetPlayerInitial(m_owner);
      }

      return string("");
    }

    void SetGroup(vector<Utility *> & group) {
      m_group = group;
    }

  private:
    
    int m_owner;

    vector<Utility *> m_group;
};

class TakeCard : public BoardSpace
{
  public:
    TakeCard(const string name, const int position, CardDeck * cardStack);
    ~TakeCard();

    bool HandlePlayerVisit(Player * player);

    bool PerformCardAction(Player * player, Card card);

  private:

    void PerformTransaction(Player * player, Card card);

    bool PerformMoveTo(Player * player, Card card);

    bool PerformMoveRelative(Player * player, Card card);

    void PerfromFree(Player * player, Card card);

    void PerformImprovements(Player * player, Card card);

    CardDeck * m_cardStack;
};

class Tax : public BoardSpace
{
  public:
    Tax(const string name, const int position, const int taxAmount);
    ~Tax();

    bool HandlePlayerVisit(Player * player);

  private:

    int m_taxAmount;
};

class FreeSpace : public BoardSpace
{
  public:
    FreeSpace(const string name, const int position, const int award);
    ~FreeSpace();

    bool HandlePlayerVisit(Player * player);

  private:

    int m_award;
};

class Jail : public BoardSpace
{
  public:
    Jail(const string name, const int position);
    ~Jail();

    bool HandlePlayerVisit(Player * player);

  private:

    int m_turn;
};
