# pragma once 

#include <string>
#include <vector>
#include "player.hpp"
#include "banker.hpp"

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

    virtual void HandlePlayerVisit(Player * player) = 0;

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
      return type;
    }

  private:

    BoardSpaceType type;
    string m_name;
    int m_position;
    Banker * m_banker;
};

class Property : public BoardSpace
{
  public:

    Property(const string name, const int position, string groupName, int purchasePrice, vector<int> & houseRents);
    ~Property();

    void HandlePlayerVisit(Player * player);

    void BuyHouses();

    bool DoesOwnerHaveMonopoly(const int playerId);

    void SetGroup(vector<Property *> & group) {
      m_group = group;
    }

    string GetGroupName() {
      return m_groupName;
    }

    int GetOwner() {
      return m_owner;
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

    void HandlePlayerVisit(Player * player);

    int GetRailroadsOwnedByPlayer(const int ownerId);

    void SetGroup(vector<RailRoad *> & group) {
      m_group = group;
    }

    int GetOwner() {
      return m_owner;
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

    void HandlePlayerVisit(Player * player);

    bool DoesPlayerOwnBothUtilities(const int playerId);

    int GetOwner() {
      return m_owner;
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
    TakeCard(const string name, const int position, vector<int> * cardStack);
    ~TakeCard();

    void HandlePlayerVisit(Player * player);

  private:

    vector<int> * m_cardStack;
};

class Tax : public BoardSpace
{
  public:
    Tax(const string name, const int position, const int taxAmount);
    ~Tax();

    void HandlePlayerVisit(Player * player);

  private:

    int m_taxAmount;
};

class FreeSpace : public BoardSpace
{
  public:
    FreeSpace(const string name, const int position, const int award);
    ~FreeSpace();

    void HandlePlayerVisit(Player * player);

  private:

    int m_award;
};

class Jail : public BoardSpace
{
  public:
    Jail(const string name, const int position);
    ~Jail();

    void HandlePlayerVisit(Player * player);

  private:

    int m_turn;
};
