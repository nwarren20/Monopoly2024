#include "banker.hpp"
#include <iostream>



Banker::Banker()
{

}

Banker::~Banker()
{

}

void Banker::WhoesPlaying()
{
    int playerCount = 0;

    string name;
    cout << "Please enter player 1 name: ";
    cin >> name;

    Player * player1 = new Player(name, playerCount);
    playerCount++;

    AddPlayerToGame(player1);

    cout << "Please enter player 2 name: ";
    cin >> name;

    Player * player2 = new Player(name, playerCount);
    playerCount++;

    AddPlayerToGame(player2);

    cout << "Is there another player? enter y/n" << endl;
    string anotherPlayer;
    cin >> anotherPlayer;

    while (anotherPlayer.compare("y") == 0)
    {
        cout << "Please enter player name: ";
        cin >> name;

        Player * nextPlayer = new Player(name, playerCount);
        playerCount++;

        AddPlayerToGame(nextPlayer);

        cout << "Is there another player? enter y/n" << endl;
        cin >> anotherPlayer;
    }
}

void Banker::AddPlayerToGame(Player * player)
{
    m_allPlayers.push_back(player);

    m_activePlayers.push_back(player->GetPlayerId());
}

int Banker::GetNumActivePlayers()
{
    return m_activePlayers.size();
}

Player * Banker::GetActivePlayerForTurn(const int turn)
{
    if (turn < m_activePlayers.size())
    {
        int playerId = m_activePlayers[turn];

        Player * player = m_allPlayers[playerId];

        return player;
    }
    
    return nullptr;
}

void Banker::UtilityTransaction(const int customerId, const int ownerId, const int diceRoll, const int utilitiesOwned)
{
    Player * customer = m_allPlayers[customerId];
    Player * owner = m_allPlayers[ownerId];

    int bill = diceRoll * 4;

    cout << "Property is owned by " << owner->GetName() << endl;

    if (utilitiesOwned == 2)
    {
        bill = diceRoll * 10;
        cout << owner->GetName() << " owns both utilities, your bill is tens times the amount on the dice: $" << bill << endl;
    }
    else
    {
        cout << owner->GetName() << " owns one utility, your bill is four times the amount on the dice: $" << bill << endl;
    }

    int paid = customer->PayRent(bill);
    owner->CollectRent(paid);

    cout << owner->GetName() << " collected $" << paid << endl;
}

void Banker::RailRoadTransaction(const int passangerId, const int ownerId, const int railRoadsOwned)
{
    Player * customer = m_allPlayers[passangerId];
    Player * owner = m_allPlayers[ownerId];

    int ticketPrice = 25;

    if (railRoadsOwned == 2)
    {
      ticketPrice = 50;

      cout << "Luggage fees are a pain, " << owner->GetName() << " is getting a little greedy with two lines." << endl;
    }
    else if (railRoadsOwned == 3)
    {
      ticketPrice = 100;

      cout << "Bathroom fees, this is getting rediculous, someone needs to put a stop to " << owner->GetName() << endl;
    }
    else if (railRoadsOwned == 4)
    {
      ticketPrice = 200;

      cout << owner->GetName() << " is a real tycoon, we are paying out the nose now." << endl;
    }
    else
    {
        cout << "That was a nice trip, " << owner->GetName() << " only has one Rail line so they didn't overcharge." << endl;
    }

    cout << "Your ticket price was $" << ticketPrice << endl;

    int paid = customer->PayRent(ticketPrice);
    owner->CollectRent(paid);

    cout << owner->GetName() << " collected $" << paid << endl;
}

void Banker::RentTransaction(const int renterId, const int ownerId, const int amount, string group, bool monopoly)
{
    Player * renter = m_allPlayers[renterId];
    Player * owner = m_allPlayers[ownerId];

    int rent = amount;

    cout << "Property is owned by " << owner->GetName() << endl;

    if (monopoly)
    {
        rent *= 2;
        
        cout << owner->GetName() << " has a monopoly on " << group << " so rent is doubled from $" << amount << " to $" << rent << endl;
    }

    cout << "You owe " << owner->GetName() << " rent of $" << rent << endl;

    int paid = renter->PayRent(rent);
    owner->CollectRent(paid);

    cout << owner->GetName() << " collected $" << paid << endl;
}

bool Banker::DoesPlayerOwnMonopoly(Player * player, string group)
{
    bool monopoly = true;

    int playerId = player->GetPlayerId();

    //for (uint i = 0; i < m_gameBoard.size(); i++)
    {
        //if (m_gameBoard[i]->GetType() == BoardSpaceType::property)
        {
            //Property * prop = reinterpret_cast<Property *>(m_gameBoard[i]);

            //if (prop->GetGroup().compare(group) == 0)
            {
                //bool doesOwn = (prop->GetOwner() == playerId);
                //monopoly &= doesOwn;
            }
        }
    }

    return monopoly;
}

void Banker::RemovePlayerFromGame(const int playerId)
{
    int index = GetPlayerActiveIndex(playerId);

    m_activePlayers.erase(m_activePlayers.begin() + index);
}

bool Banker::IsPlayerActive(const int playerId)
{
    for (int i = 0; i < m_activePlayers.size(); i++)
    {
        if (m_activePlayers[i] == playerId)
        {
            return true;
        }
    }

    return false;
}

int Banker::GetPlayerActiveIndex(const int playerId)
{
    for (int i = 0; i < m_activePlayers.size(); i++)
    {
        if (m_activePlayers[i] == playerId)
        {
            return i;
        }
    }

    return -1;
}

string Banker::GetPlayerName(const int playerId)
{
    string name;

    if (playerId < m_allPlayers.size())
    {
        name = m_allPlayers[playerId]->GetName();
    }

    return name;
}