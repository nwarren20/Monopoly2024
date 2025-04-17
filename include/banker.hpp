# pragma once

#include "player.hpp"
#include <vector>
#include <list>
#include <map>

using namespace std;

class Banker
{
  public:
    Banker();
    ~Banker();

    void RentTransaction(const int renterId, const int ownerId, const int amount, string group, bool monopoly, bool mortgaged);

    void RailRoadTransaction(const int passangerId, const int ownerId, int ticketPrice, const int railRoadsOwned, const bool chance, bool mortgaged);

    void UtilityTransaction(const int customerId, const int ownerId, const int diceRoll, const bool bothUtilitiesOwned, const bool chance, bool mortgaged);

    void TaxTransaction(const int playerId, const int amount);

    void CardTransaction(const int playerId, const int amount);

    bool BuyPropertyTransaction(Player * player, const int price, const string property, const string group);

    void WhoesPlaying();

    void SelectToken(Player * player);

    void AddPlayerToGame(Player * player);

    void RemovePlayerFromGame(const int playerId);

    Player * GetActivePlayerForTurn(const int turn);

    bool IsPlayerActive(const int playerId);

    string GetPlayerName(const int playerId);

    string GetPlayerInitial(const int playerId);

    int GetNumActivePlayers();

    //bool DoesPlayerOwnMonopoly(Player * player, string group);

    void GivePlayOptions(Player * player);

    void PayEachPlayer(Player * player, int amount);

    void CollectEachPlayer(Player * player, int amount);

    void PayPerHouseAndHotel(Player * player, int perHotelCost, int perHouseCost);

    map<string, int> GetPlayerPositions();

    bool IsPropertyMortgaged(string properyName, int ownerId);

  private:

    int GetPlayerActiveIndex(const int playerId);

    void CheckPlayerForBankrupcy(const int playerId, int paid, int owed);

    vector<Player *> m_allPlayers;

    vector<int> m_activePlayers;

    list<string> m_availableTokens;
};
