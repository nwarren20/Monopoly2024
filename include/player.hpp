# pragma once

#include <string>
#include <vector>

using namespace std;

class BoardSpace;

struct PlayerStats
{
    int rentCollected = 0;
    int rentPaid = 0;
    int taxesPaid = 0;
    int cardCollected = 0;
    int cardPaid = 0;
    int diceRolledCount = 0;
    int spacesMoved = 0;
    int totalDoublesRolled = 0;
    int passedGoCount = 0;
    int timesJailded = 0;
};

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

    int PayTax(const int fee);

    int PayRent(const int amount);

    int PayGeneric(const int amount);

    void PayRailRoadDouble(const bool active = true) { m_payRailRoadDouble = active; };
    bool GetPayRailRoadDouble() { return m_payRailRoadDouble; }

    void PayUtilityTenTimes(const bool active = true) { m_payUtilityTenTimes = active; };
    bool GetPayUtilityTenTimes() { return m_payUtilityTenTimes; }

    void CollectRent(const int amount);

    void CollectGeneric(const int amount);

    void OutputPlayerStats(vector<BoardSpace *> & board);

    void PrintPropertyGroup(string group);

    void PrintBoardPosition(vector<BoardSpace *> & board);

    void PrintDiceRoll(int roll);

    int Liquidate(const int target);

    bool TryToRollOutOfJail();

    void BeginTurn();

    bool IsTurnOver(bool playerJailedToBeginTurn);

    void CardTransaction(int amount);

    void MortgageMenu();

    void MortgageProperty(const string propertyName, int value);

    bool IsPropertyMortgaged(const string propertyName);

    bool HasMortgagedProperty();

    void MortgageToBuyProperty(const int price);

    void UnMortgageMenu();

    void UnMortgageProperty(const string propertyName, int value);

    int GetNetWorth();

    int GetRentPotential(vector<BoardSpace *> & board);

    void PlayerCheckForMonopolies(vector<BoardSpace *> & board);

    void AddMonopoly(string group);

    void BuyHouseMenu(vector<BoardSpace *> & board, int & houseInventory, int & hotelInventory);

    void SellHouseMenu();

    void AddHousesToGroup(vector<BoardSpace *> & board, string group, int numHouses);

    void RemoveHousesFromGroup(string group, int numHouses);

    int GetHouseCountForGroup(vector<BoardSpace *> & board, const string colorGroup);

    int GetHouseCountForGroup(const string colorGroup);

    bool BuyHouses(const int count, const int price);

    bool SellHouses(const int count, const int price);

    bool DoesColorGroupHaveAMortgage(string colorGroup);

    bool DoesColorGroupHaveImprovements(string colorGroup);

    bool DoesPropertyInColorGroupHaveImprovements(string propertyName);

    void UpdateNameInPropertyLists(string targetName, int houseCount);

    string UpdatePropertyName(string name, string target, int houseCount);

    string GetRawPropertyName(string name);

    int GetHouseCountForPropery(string propertyName);

    int GetTotalHouseCount();

    int GetTotalHotelCount();

    int ReturnHouseInventory(vector<BoardSpace *> & board);

    bool OwnsHouseOrHotel() {
        return (GetTotalHouseCount() > 0 || GetTotalHotelCount() > 0);
    }

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
        return !m_propertyGroups.empty();
    }

    bool OwnsMonopoly() {
        return !m_monopolies.empty();
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
    vector<pair<string, string> > m_propertyGroups;
    vector<pair<string, int> > m_propertyPrice;
    vector<string> m_monopolies;
    PlayerStats m_stats;
};
