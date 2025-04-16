#include "../include/banker.hpp"
#include <iostream>
#include <sstream>
#include <list>
#include "../include/utils.hpp"

Banker::Banker()
{
    m_availableTokens = { "!", "@", "#", "$", "%", "^", "&", "*" };
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
    SelectToken(player1);

    cout << "Please enter player 2 name: ";
    cin >> name;

    Player * player2 = new Player(name, playerCount);
    playerCount++;

    AddPlayerToGame(player2);
    SelectToken(player2);

    cout << "Is there another player? enter y/n" << endl;
    string anotherPlayer;
    cin >> anotherPlayer;

    while (anotherPlayer.compare("y") == 0 && playerCount <= 8)
    {
        cout << "Please enter player name: ";
        cin >> name;

        Player * nextPlayer = new Player(name, playerCount);
        playerCount++;

        AddPlayerToGame(nextPlayer);
        SelectToken(nextPlayer);

        cout << "Is there another player? enter y/n" << endl;
        cin >> anotherPlayer;
    }
}

void Banker::SelectToken(Player * player)
{
    bool match = false;

    while(match == false)
    {
        cout << player->GetName() << ", Please select your Token to move around the board:" << endl;

        list<string>::iterator it;
        for (it = m_availableTokens.begin(); it != m_availableTokens.end(); it++)
        {
            cout << " " << *it << " ";
        }

        cout << endl;

        string input = "";
        cin >> input;

        for (it = m_availableTokens.begin(); it != m_availableTokens.end() && !match; it++)
        {
            match |= (input.compare(*it) == 0);
        }

        if (match)
        {
            player->SetToken(input);

            m_availableTokens.remove(input);
        }
        else
        {
            cout << "Invalid Selection, try again" << endl;
        }
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

map<string, int> Banker::GetPlayerPositions()
{
    map<string, int> positionMap;

    for (size_t i = 0; i < m_activePlayers.size(); i++)
    {
        int playerId = m_activePlayers[i];

        Player * player = m_allPlayers[playerId];

        string token = player->GetToken();
        int position = player->GetPosition();

        positionMap[token] = position;
    }

    return positionMap;
}

void Banker::PayEachPlayer(Player * player, int amount)
{
    for (size_t i = 0; i < m_activePlayers.size(); i++)
    {
        int playerId = m_activePlayers[i];

        Player * opponent = m_allPlayers[playerId];

        if(opponent != player)
        {
            int paid = player->PayGeneric(amount);
            opponent->CollectGeneric(amount);

            std::stringstream ss;
            ss << player->GetName() << " paid " << opponent->GetName() << " $" << paid;

            MonopolyUtils::OutputMessage(ss.str(), 1000);
        }
    }
}

void Banker::CollectEachPlayer(Player * player, int amount)
{
    for (size_t i = 0; i < m_activePlayers.size(); i++)
    {
        int playerId = m_activePlayers[i];

        Player * opponent = m_allPlayers[playerId];

        if(opponent != player)
        {
            player->CollectGeneric(amount);
            int paid = opponent->PayGeneric(amount);

            std::stringstream ss;
            ss << opponent->GetName() << " paid " << player->GetName() << " $" << paid;

            MonopolyUtils::OutputMessage(ss.str(), 1000);
        }
    }
}

void Banker::PayPerHouseAndHotel(Player * player, int perHotelCost, int perHouseCost)
{
    // TODO: get player house and hotel counts.
    int hotelCount = 0;
    int houseCount = 0;

    int hotelTotalCost = hotelCount * perHotelCost;
    int houseTotalCost = houseCount * perHouseCost;
    
    int totalCost = hotelTotalCost + houseTotalCost;

    int paid = player->PayGeneric(totalCost);

    std::stringstream ss;
    ss << player->GetName() << " paid a total of $" << paid << " for all houses and hotels";

    MonopolyUtils::OutputMessage(ss.str(), 1000);
}

void Banker::UtilityTransaction(const int customerId, const int ownerId, const int diceRoll, const bool bothUtilitiesOwned, const bool chance)
{
    Player * customer = m_allPlayers[customerId];
    Player * owner = m_allPlayers[ownerId];

    int bill = diceRoll * 4;

    cout << "Property is owned by " << owner->GetName() << endl;

    if (chance)
    {
        string input = string("");

        while(input.compare("r") != 0)
        {
            cout << "enter 'r' to roll dice for billed amount" << endl;
            cin >> input;
        }
        
        int diceTotal = customer->RollDice();
        bill = diceTotal * 10;

        std::stringstream ss;
        ss << owner->GetName() << " your bill is tens times the amount on the dice: $" << bill;

        MonopolyUtils::OutputMessage(ss.str(), 1000);

    }
    else if (bothUtilitiesOwned)
    {
        bill = diceRoll * 10;

        std::stringstream ss;
        ss << owner->GetName() << " owns both utilities, your bill is tens times the amount on the dice: $" << bill;

        MonopolyUtils::OutputMessage(ss.str(), 1000);
    }
    else
    {
        std::stringstream ss;
        ss << owner->GetName() << " owns one utility, your bill is four times the amount on the dice: $" << bill;

        MonopolyUtils::OutputMessage(ss.str(), 1000);
    }

    int paid = customer->PayRent(bill);
    owner->CollectRent(paid);

    std::stringstream ss;
    ss << owner->GetName() << " collected $" << paid;

    MonopolyUtils::OutputMessage(ss.str(), 1000);
}

void Banker::RailRoadTransaction(const int passangerId, const int ownerId, const int railRoadsOwned, const bool chance)
{
    Player * customer = m_allPlayers[passangerId];
    Player * owner = m_allPlayers[ownerId];

    int ticketPrice = 25;

    if (railRoadsOwned == 2)
    {
      ticketPrice = 50;
    
      stringstream ss;
      ss << "Luggage fees are a pain, " << owner->GetName() << " is getting a little greedy with two lines.";

      MonopolyUtils::OutputMessage(ss.str(), 1000);
    }
    else if (railRoadsOwned == 3)
    {
      ticketPrice = 100;

      stringstream ss;
      ss << "Bathroom fees, this is getting rediculous, someone needs to put a stop to " << owner->GetName();

      MonopolyUtils::OutputMessage(ss.str(), 1000);
    }
    else if (railRoadsOwned == 4)
    {
      ticketPrice = 200;

      stringstream ss;
      ss << owner->GetName() << " is a real tycoon, we are paying out the nose now.";

      MonopolyUtils::OutputMessage(ss.str(), 1000);
    }
    else
    {
        stringstream ss;
        ss << "That was a nice trip, " << owner->GetName() << " only has one Rail line so they didn't overcharge.";

        MonopolyUtils::OutputMessage(ss.str(), 1000);
    }

    if (chance)
    {
        ticketPrice *= 2;

        stringstream ss;
        ss << "You took a CHANCE, and today you pay double";

        MonopolyUtils::OutputMessage(ss.str(), 1000);
    }

    stringstream ss;
    ss << "Your ticket price was $" << ticketPrice;
    MonopolyUtils::OutputMessage(ss.str(), 1000);

    int paid = customer->PayRent(ticketPrice);
    owner->CollectRent(paid);

    ss = stringstream("");
    ss << owner->GetName() << " collected $" << paid;
    MonopolyUtils::OutputMessage(ss.str(), 1000);
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
    string name("");

    if (playerId >= 0 && playerId < m_allPlayers.size())
    {
        name = m_allPlayers[playerId]->GetName();
    }

    return name;
}

string Banker::GetPlayerInitial(const int playerId)
{
    string initial("");

    if (playerId >= 0 && playerId < m_allPlayers.size())
    {
        initial = m_allPlayers[playerId]->GetInitial();
    }

    return initial;
}

void Banker::GivePlayOptions(Player * player)
{
    if (player->IsJailed())
    {
        string message = string("You're currently serving time, pay $50 to get out, or roll doubles");

        if (player->HasGetOutOfJailFreeCard())
        {
            message += string(", or use Get Out of Jail Free Card!");
        }

        if (player->GetJailRolls() == 3)
        {
            message += string("\nThis is your first attempt");
        }
        else if (player->GetJailRolls() == 2)
        {
            message += string("\nThis is your second attempt");
        }
        else if (player->GetJailRolls() == 1)
        {
            message += string("\nThis is your last attempt");
        }
                
        MonopolyUtils::OutputMessage(message, 0);

        cout << "==> Enter p to pay $50 to get out of jail." << endl;

        if (player->HasGetOutOfJailFreeCard())
        {
            cout << "==> Enter f to use Get Out of Jail Free Card." << endl;
        }
     }

    cout << "==> Enter r to roll dice." << endl;
    cout << "==> Enter t to trade." << endl;

    if (player->OwnsProperty())
    {
        cout << "==> Enter m to mortgage." << endl;

        if (player->OwnsMonopoly())
        {
            cout << "==> Enter b to buy houses/hotels" << endl;
        }
     }
}