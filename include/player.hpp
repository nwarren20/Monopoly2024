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

    int RollDice(int gaffRoll = 0);

    void GaffDice(int gaffRoll);

    int GetRolledDiceTotal() {
        return m_rolledDice_1 + m_rolledDice_2;
    }

    void SetToken(const string token);

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

    void AwardGetOutOfJailFreeCard();

    bool HasGetOutOfJailFreeCard() {
        return (m_getOutOfJailFreeCardCount > 0);
    }

    bool UseGetOutOfJailFreeCard();

    bool BuyProperty(int cost, string prop, string group);

    bool BuyRailRoad(string name);

    bool BuyUtility(string name);

    bool PayTax(const int fee);

    int PayRent(const int amount);

    int PayGeneric(const int amount);

    void PayRailRoadDouble(const bool active = true) { m_payRailRoadDouble = active; };
    bool GetPayRailRoadDouble() { return m_payRailRoadDouble; }

    void PayUtilityTenTimes(const bool active = true) { m_payUtilityTenTimes = active; };
    bool GetPayUtilityTenTimes() { return m_payUtilityTenTimes; }

    void CollectRent(const int amount);

    void CollectGeneric(const int amount);

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
        return string(m_name + "(" + m_token + ")");
    }

    int GetPlayerId() {
        return m_playerId;
    }

    string GetInitial() {
        return m_initial;
    }

    string GetToken() {
        return m_token;
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
    string m_token;
    int m_bankAccount;
    int m_position;
    int m_rolledDice_1;
    int m_rolledDice_2;
    int m_jailRolls;
    int m_doublesCount;
    int m_getOutOfJailFreeCardCount;
    bool m_payRailRoadDouble;
    bool m_payUtilityTenTimes;
    vector<pair<string, string> > m_properties;
};
