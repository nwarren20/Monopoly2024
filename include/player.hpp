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

    bool WasDoublesRolledThreeTimes();

    int AdvancePlayer(int numSpaces);

    void MoveToSpace(int space);

    void PassGo();

    void GoToJail();

    bool GetOutOfJail(const int price);

    int GetJailRolls() {
        return m_jailRolls;
    }

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

    int Liquidate(const int target);

    bool TryToRollOutOfJail();

    void BeginTurn();

    bool IsTurnOver(bool playerJailedToBeginTurn);

    void CardTransaction(int amount);

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

    bool IsJailed() {
        return (m_jailRolls > 0);
    }

    int GetCash() {
        return m_bankAccount;
    }

  private:
    int m_playerId;
    string m_name;
    string m_initial;
    int m_bankAccount;
    int m_position;
    int m_rolledDice_1;
    int m_rolledDice_2;
    int m_jailRolls;
    int m_doublesCount;
    vector<pair<string, string> > m_properties;
};
