# pragma once

#include <string>
#include <vector>

using namespace std;

class BoardSpace;

class Player
{
  public:
    Player(const string name, const int playerId);
    ~Player();

    int RollDice();

    int GetRolledDiceTotal() {
        return m_rolledDice_1 + m_rolledDice_2;
    }

    bool RolledDoubles();

    int AdvancePlayer(int numSpaces);

    void GoToJail();

    bool BuyProperty(int cost, string prop, string group);

    bool BuyRailRoad(string name);

    bool BuyUtility(string name);

    bool PayTax(const int fee);

    int PayRent(const int amount);
    void CollectRent(const int amount);

    void OutputPlayerStats();

    void PrintPropertyGroup(string group);

    void PrintBoardPosition(vector<BoardSpace *> & board);

    void PrintDiceRoll(int roll);

    int GetPosition() {
        return m_position;
    }

    string GetName() {
        return m_name;
    }

    int GetPlayerId() {
        return m_playerId;
    }

    string GetInitial() {
        return m_initial;
    }

    bool OwnsProperty() {
        return !m_properties.empty();
    }

    bool OwnsMonopoly() {
        return false;
    }

  private:
    int m_playerId;
    string m_name;
    string m_initial;
    int m_bankAccount;
    int m_position;
    int m_rolledDice_1;
    int m_rolledDice_2;
    vector<pair<string, string> > m_properties;
};
