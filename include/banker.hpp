# pragma once

#include "player.hpp"
#include <vector>

using namespace std;

class Banker
{
  public:
    Banker();
    ~Banker();

    void RentTransaction(const int renterId, const int ownerId, const int amount, string group, bool monopoly);

    void RailRoadTransaction(const int passangerId, const int ownerId, const int railRoadsOwned, const bool chance);

    void UtilityTransaction(const int customerId, const int ownerId, const int diceRoll, const int utilitiesOwned, const bool chance);

    void WhoesPlaying();

    void AddPlayerToGame(Player * player);

    void RemovePlayerFromGame(const int playerId);

    Player * GetActivePlayerForTurn(const int turn);

    bool IsPlayerActive(const int playerId);

    string GetPlayerName(const int playerId);

    string GetPlayerInitial(const int playerId);

    int GetNumActivePlayers();

    bool DoesPlayerOwnMonopoly(Player * player, string group);

    void GivePlayOptions(Player * player);

    void PayEachPlayer(Player * player, int amount);

  private:

    int GetPlayerActiveIndex(const int playerId);

    vector<Player *> m_allPlayers;

    vector<int> m_activePlayers;
};
