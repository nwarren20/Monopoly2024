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

    bool valid = false;
    string anotherPlayer;

    while(!valid)
    {
        cout << "Is there another player? enter y/n" << endl;
        
        cin >> anotherPlayer;

        valid = (anotherPlayer.compare("y") == 0 || anotherPlayer.compare("n") == 0);
    }
    
    while (anotherPlayer.compare("y") == 0 && playerCount <= 8)
    {
        cout << "Please enter player name: ";
        cin >> name;

        Player * nextPlayer = new Player(name, playerCount);
        playerCount++;

        AddPlayerToGame(nextPlayer);
        SelectToken(nextPlayer);

        valid = false;

        while(!valid)
        {
            cout << "Is there another player? enter y/n" << endl;
            
            cin >> anotherPlayer;

            valid = (anotherPlayer.compare("y") == 0 || anotherPlayer.compare("n") == 0);
        }
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

            CheckPlayerForBankrupcy(player->GetPlayerId(), paid, amount);

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

            CheckPlayerForBankrupcy(opponent->GetPlayerId(), paid, amount);

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
    
    int totalBill = hotelTotalCost + houseTotalCost;

    int paid = player->PayGeneric(totalBill);

    if (paid < totalBill)
    {
        stringstream ss;
        ss << "You are BANKRUPT and are no longer in the game.";

        MonopolyUtils::OutputMessage(ss.str(), 1000);

        RemovePlayerFromGame(player->GetPlayerId());
    }

    std::stringstream ss;
    ss << player->GetName() << " paid a total of $" << paid << " for all houses and hotels";

    MonopolyUtils::OutputMessage(ss.str(), 1000);
}

void Banker::UtilityTransaction(const int customerId, const int ownerId, const int diceRoll, const bool bothUtilitiesOwned, const bool chance, bool mortgaged)
{
    Player * customer = m_allPlayers[customerId];
    Player * owner = m_allPlayers[ownerId];

    int bill = diceRoll * 4;

    std::stringstream ss;
    ss << "Property is owned by " << owner->GetName();

    MonopolyUtils::OutputMessage(ss.str(), 1000);

    if (chance)
    {
        string input = string("");

        while(input.compare("r") != 0)
        {
            MonopolyUtils::OutputMessage("enter 'r' to roll dice for billed amount", 0);
            cin >> input;
        }
        
        int diceTotal = customer->RollDice();
        bill = diceTotal * 10;

        ss = stringstream("");
        ss << owner->GetName() << " your bill is tens times the amount on the dice: $" << bill;

        MonopolyUtils::OutputMessage(ss.str(), 1000);

    }
    else if (bothUtilitiesOwned)
    {
        bill = diceRoll * 10;

        ss = stringstream("");
        ss << owner->GetName() << " owns both utilities, your bill is tens times the amount on the dice: $" << bill;

        MonopolyUtils::OutputMessage(ss.str(), 1000);
    }
    else
    {
        ss = stringstream("");
        ss << owner->GetName() << " owns one utility, your bill is four times the amount on the dice: $" << bill;

        MonopolyUtils::OutputMessage(ss.str(), 1000);
    }

    if (mortgaged)
    {
        ss = stringstream("");
        ss << "Property is currently mortgaged so rent can not be collected.\nYou would have owed $" << bill;

        MonopolyUtils::OutputMessage(ss.str(), 1000);
    }
    else
    {
        int paid = customer->PayRent(bill);

        CheckPlayerForBankrupcy(customerId, paid, bill);

        owner->CollectRent(paid);

        ss = stringstream("");
        ss << owner->GetName() << " collected $" << paid;

        MonopolyUtils::OutputMessage(ss.str(), 1000);
    }
    
}

void Banker::RailRoadTransaction(const int passangerId, const int ownerId, int ticketPrice, const int railRoadsOwned, const bool chance, bool mortgaged)
{
    Player * customer = m_allPlayers[passangerId];
    Player * owner = m_allPlayers[ownerId];

    if (railRoadsOwned == 2)
    {
        stringstream ss;
        ss << "Luggage fees are a pain, " << owner->GetName() << " is getting a little greedy with two lines.";

        MonopolyUtils::OutputMessage(ss.str(), 1000);
    }
    else if (railRoadsOwned == 3)
    {
        stringstream ss;
        ss << "Bathroom fees, this is getting rediculous, someone needs to put a stop to " << owner->GetName();

        MonopolyUtils::OutputMessage(ss.str(), 1000);
    }
    else if (railRoadsOwned == 4)
    {
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

    if (mortgaged)
    {
        stringstream ss = stringstream("");
        ss << "Property is currently mortgaged so rent can not be collected.\nYou would have owed $" << ticketPrice;

        MonopolyUtils::OutputMessage(ss.str(), 1000);
    }
    else
    {
        stringstream ss;
        ss << "Your ticket price was $" << ticketPrice;
        MonopolyUtils::OutputMessage(ss.str(), 1000);

        int paid = customer->PayRent(ticketPrice);

        CheckPlayerForBankrupcy(passangerId, paid, ticketPrice);

        owner->CollectRent(paid);

        ss = stringstream("");
        ss << owner->GetName() << " collected $" << paid;
        MonopolyUtils::OutputMessage(ss.str(), 1000);
    }
}

void Banker::RentTransaction(const int renterId, const int ownerId, const int amount, string name, string group, int houseCount, bool monopoly, bool mortgaged)
{
    Player * renter = m_allPlayers[renterId];
    Player * owner = m_allPlayers[ownerId];

    int rent = amount;

    stringstream ss;
    ss << name << " is owned by " << owner->GetName();

    MonopolyUtils::OutputMessage(ss.str(), 1000);

    if (monopoly)
    {
        if (houseCount > 0)
        {
            stringstream ssHouseTerm = stringstream("");
            
            if (houseCount > 1)
            {
                ssHouseTerm << houseCount << " houses";
            }
            else if (houseCount == 5)
            {
                ssHouseTerm << "a hotel";
            }
            else
            {
                ssHouseTerm << ("a house");
            }

            ss = stringstream("");
            ss << name << " with " << ssHouseTerm.str() << " has a rent of $" << rent;

            MonopolyUtils::OutputMessage(ss.str(), 1000);
        }
        else
        {
            ss = stringstream("");
            ss << owner->GetName() << " has a monopoly on " << group << " so rent is doubled from $" << (rent / 2) << " to $" << rent;
            MonopolyUtils::OutputMessage(ss.str(), 1000);
        }
    }

    if (mortgaged)
    {
        ss = stringstream("");
        ss << name << " is currently mortgaged so rent can not be collected.\nYou would have owed $" << rent;

        MonopolyUtils::OutputMessage(ss.str(), 1000);
    }
    else
    {
        ss = stringstream("");
        ss << "You owe " << owner->GetName() << " rent of $" << rent;

        MonopolyUtils::OutputMessage(ss.str(), 1000);

        int paid = renter->PayRent(rent);

        CheckPlayerForBankrupcy(renterId, paid, rent);

        owner->CollectRent(paid);

        ss = stringstream("");
        ss << owner->GetName() << " collected $" << paid;

        MonopolyUtils::OutputMessage(ss.str(), 1000);
    }
}

void Banker::TaxTransaction(const int playerId, const int amount)
{
    Player * player = m_allPlayers[playerId];

    int fee = amount;

    int paid = player->PayTax(fee);

    CheckPlayerForBankrupcy(playerId, paid, fee);
}

void Banker::CardTransaction(const int playerId, const int amount)
{
    Player * player = m_allPlayers[playerId];

    if (amount > 0)
    {
        player->CollectGeneric(amount);
    }
    else if (amount < 0)
    {
        int fee = amount * -1;

        int paid = player->PayGeneric(fee);

        CheckPlayerForBankrupcy(playerId, paid, amount);
    }
}

void Banker::CheckPlayerForBankrupcy(const int playerId, int paid, int owed)
{
    if (paid < owed)
    {
        stringstream ss = stringstream("");
        ss << "You are BANKRUPT and are no longer in the game.";

        MonopolyUtils::OutputMessage(ss.str(), 1000);

        RemovePlayerFromGame(playerId);
    }
}

bool Banker::IsPropertyMortgaged(string properyName, int ownerId)
{
    Player * owner = m_allPlayers[ownerId];

    return owner->IsPropertyMortgaged(properyName);
}

bool Banker::BuyPropertyTransaction(Player * player, const int price, const string property, const string group)
{
    bool success = player->BuyProperty(price, property, group);

    return success;
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
        cout << "==> Enter m to Mortgage property." << endl;

        if (player->OwnsMonopoly())
        {
            cout << "==> Enter b to buy houses/hotels." << endl;
        }

        if (player->HasMortgagedProperty())
        {
            cout << "==> Enter u to Unmortgage property." << endl;
        }
     }
}