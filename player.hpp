# pragma once

#include <string>
#include <vector>

using namespace std;

class Player
{
  public:
    Player(const string name, const int playerId);
    ~Player();

    int RollDice();
    int GetRolledDice() {
        return m_rolledDice;
    }

    int AdvancePlayer(int numSpaces);

    bool BuyProperty(int cost, string prop, string group);

    bool BuyRailRoad(string name);

    bool BuyUtility(string name);

    bool PayTax(const int fee);

    int PayRent(const int amount);
    void CollectRent(const int amount);

    void OutputPlayerStats();

    void PrintPropertyGroup(string group);

    int GetPosition() {
        return m_position;
    }

    string GetName() {
        return m_name;
    }

    int GetPlayerId() {
        return m_playerId;
    }

  private:
    int m_playerId;
    string m_name;
    int m_bankAccount;
    int m_position;
    int m_rolledDice;
    vector<pair<string, string> > m_properties;
};
