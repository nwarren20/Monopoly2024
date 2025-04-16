#include "../include/player.hpp"
#include "../include/boardspace.hpp"
#include <cstdlib>
#include <ctime>
#include <iostream>
#include <thread>
#include <chrono>
#include <sstream>
#include <algorithm>
#include "../include/utils.hpp"

using namespace std;
//using namespace MonopolyUtils;

const int drawPositions[40] = 
{ 20, 21, 22, 23, 24, 25, 26, 27, 28, 29, 30, 19, 31, 18, 32, 17, 33, 16, 34, 15, 35, 14, 36, 13, 37, 12, 38, 11, 39, 10, 9, 8, 7, 6, 5, 4, 3, 2, 1, 0 };

Player::Player(const string name, const int playerId)
  : m_name(name),
    m_playerId(playerId)
{
    m_bankAccount = 1500;
    m_position = 0;
    m_initial = name.substr(0,1);
    m_token = "";
    m_jailRolls = 0;
    m_rolledDice_1 = 0;
    m_rolledDice_2 = 0;
    m_doublesCount = 0;
    m_getOutOfJailFreeCardCount = 0;
    m_payRailRoadDouble = false;
    m_payUtilityTenTimes = false;

    srand(time(0));
}

Player::~Player()
{

}

void Player::SetToken(const string token)
{
    size_t len = token.length();

    if (len == 1)
    {
        m_token = token;
    }
    else
    {
        cout << " Token too many characters" << endl;
    }
}

void Player::CardTransaction(int amount)
{
    if (amount > 0)
    {
        m_bankAccount += amount;

        std::stringstream ss;
        ss << "You received $" << amount << "!";

        MonopolyUtils::OutputMessage(ss.str(), 1000);
    }
    else if (amount < 0)
    {
        int paid = amount * -1;

        if (paid > m_bankAccount)
        {
            paid = m_bankAccount;

            Liquidate(paid);
        }

        m_bankAccount -= paid;

        std::stringstream ss;
        ss << "You paid $" << paid << ".";

        MonopolyUtils::OutputMessage(ss.str(), 1000);
    }
}

int Player::RollDice(int gaffRoll)
{
    int low = 1;
    int high = 6;

    m_rolledDice_1 = (rand() % high) + low;
    m_rolledDice_2 = (rand() % high) + low;

    GaffDice(gaffRoll);

    std::this_thread::sleep_for(std::chrono::milliseconds(500));

    PrintDiceRoll(m_rolledDice_1);

    std::this_thread::sleep_for(std::chrono::milliseconds(200));

    PrintDiceRoll(m_rolledDice_2);

    std::stringstream ss;
    ss << m_name << " rolled a " << GetRolledDiceTotal();

    MonopolyUtils::OutputMessage(ss.str(), 1000);

    if (m_jailRolls > 0)
    {
        m_jailRolls--;
    }

    return GetRolledDiceTotal();
}

void Player::GaffDice(int gaffRoll)
{
    switch(gaffRoll)
    {
        case 2:
            m_rolledDice_1 = 1;
            m_rolledDice_2 = 1;
            break;
        case 3:
            m_rolledDice_1 = 1;
            m_rolledDice_2 = 2;
            break;
        case 4:
            m_rolledDice_1 = 3;
            m_rolledDice_2 = 1;
            break;
        case 5:
            m_rolledDice_1 = 2;
            m_rolledDice_2 = 3;
            break;
        case 6:
            m_rolledDice_1 = 4;
            m_rolledDice_2 = 2;
            break;
        case 7:
            m_rolledDice_1 = 3;
            m_rolledDice_2 = 4;
            break;
        case 8:
            m_rolledDice_1 = 3;
            m_rolledDice_2 = 5;
            break;
        case 9:
            m_rolledDice_1 = 5;
            m_rolledDice_2 = 4;
            break;
        case 10:
            m_rolledDice_1 = 6;
            m_rolledDice_2 = 4;
            break;
        case 11:
            m_rolledDice_1 = 6;
            m_rolledDice_2 = 5;
            break;
        case 12:
            m_rolledDice_1 = 6;
            m_rolledDice_2 = 6;
            break;
    }
}

bool Player::RolledDoubles()
{
    return (m_rolledDice_1 == m_rolledDice_2);
}

int Player::AdvancePlayer(int numSpaces)
{
    m_position += numSpaces;

    if (m_position > 39)
    {
        m_position -= 40;

        PassGo();
    }
    else if (m_position < 0)
    {
        m_playerId += 40;
    }

    return m_position;
}

void Player::PassGo()
{
    m_bankAccount+=200;

    MonopolyUtils::OutputMessage(" YOU PASSED GO! COLLECT $200", 1000);
}

void Player::MoveToSpace(int space)
{
    if (space >= 0 && space < 40)
    {
        m_position = space;
    }
}

void Player::GoToJail()
{
    MoveToSpace(10);
    m_jailRolls = 3;
}

bool Player::GetOutOfJail(const int price)
{
    bool success = false;

    if (m_bankAccount >= price)
    {
        m_bankAccount -= price;
        m_jailRolls = 0;
        success = true;

        std::stringstream ss;
        ss << "You paid $" << price << " to get out of jail.";

        MonopolyUtils::OutputMessage(ss.str(), 1000);
    }
    else
    {
        MonopolyUtils::OutputMessage("You do not have enough money to get out of jail!", 1000);

        // TODO: Make player come up with money.
    }

    return success;
}

bool Player::TryToRollOutOfJail()
{
    bool getOutOfJail = false;

    if (RolledDoubles())
    {
        MonopolyUtils::OutputMessage("You got out of jail!", 1000);

        getOutOfJail = GetOutOfJail(0);
                        
    }
    else if (GetJailRolls() == 0)
    {
        MonopolyUtils::OutputMessage("Third roll, you must pay $50 to leave jail.", 1000);

        getOutOfJail = GetOutOfJail(50);
    }
    else
    {
        MonopolyUtils::OutputMessage("You did not get out of jail!", 1000);
    }

    return getOutOfJail;
}

void Player::AwardGetOutOfJailFreeCard()
{
    m_getOutOfJailFreeCardCount++;
}

bool Player::UseGetOutOfJailFreeCard()
{
    bool success = false;

    if (m_getOutOfJailFreeCardCount > 0)
    {
        success = GetOutOfJail(0);

        if (success)
        {
            m_getOutOfJailFreeCardCount--;
        }
    }
    
    return success;
}

void Player::BeginTurn()
{
    m_doublesCount = 0;
}

bool Player::WasDoublesRolledThreeTimes()
{
    if (RolledDoubles())
    {
        m_doublesCount++;

        if (m_doublesCount >= 3)
        {
            GoToJail();
            
            MonopolyUtils::OutputMessage(GetName() + " Rolled doubles 3 times, go to jail!", 1000);

            return true;
        }
    }

    return false;
}

bool Player::IsTurnOver(bool playerJailedToBeginTurn)
{
    if (!IsJailed() && !playerJailedToBeginTurn && RolledDoubles())
    {
        MonopolyUtils::OutputMessage(" You rolled doubles, roll again", 1000);

        return false;
    }

    return true;
}

bool Player::PayTax(const int fee)
{
    bool success = true;

    if (fee <= m_bankAccount)
    {
        m_bankAccount -= fee;
        stringstream ss;
        ss << "Paid tax of $" << fee;
        MonopolyUtils::OutputMessage(ss.str(), 1000);
    }
    else
    {
        // todo: make player come up with money.
        m_bankAccount = -1;
        cout << "Cannot afford to pay taxes" << endl;
        success = false;
    }

    return success;
}

bool Player::BuyUtility(string name)
{
    int price = 150;

    if (m_bankAccount >= price)
    {
        m_bankAccount -= price;

        pair<string, string> newGroup = make_pair(name, "Utility");
        m_propertyGroups.push_back(newGroup);

        pair<string, int> newPrice = make_pair(name, price);
        m_propertyPrice.push_back(newPrice);
    }
    else
    {
        cout << "Sorry, not enough cash to buy Utility" << endl;
        return false;
    }

    return true;
}

bool Player::BuyRailRoad(string name)
{
    int price = 200;

    if (m_bankAccount >= price)
    {
        m_bankAccount -= price;

        pair<string, string> newGroup = make_pair(name, "RailRoad");
        m_propertyGroups.push_back(newGroup);

        pair<string, int> newPrice = make_pair(name, price);
        m_propertyPrice.push_back(newPrice);
    }
    else
    {
        cout << "Sorry, not enough cash to buy railroad" << endl;
        return false;
    }

    return true;
}

bool Player::BuyProperty(int price, string prop, string group)
{
    if (m_bankAccount >= price)
    {
        m_bankAccount -= price;

        pair<string, string> newGroup = make_pair(prop, group);
        m_propertyGroups.push_back(newGroup);

        pair<string, int> newPrice = make_pair(prop, price);
        m_propertyPrice.push_back(newPrice);
    }
    else
    {
        cout << "Sorry, not enough cash to buy property" << endl;
        return false;
    }

    return true;
}

int Player::PayRent(const int amount)
{
    int paid = 0;
    bool finished = false;

    while(!finished)
    {
        cout << "Enter 'p' to pay rent\n"
             << "Enter 'd' to make deal\n";

        string input;
        cin >> input;

        if (input.compare("p") == 0)
        {
            if (amount <= m_bankAccount)
            {
                paid = amount;
            }
            else
            {
                paid = Liquidate(amount);
            }

            m_bankAccount -= paid;
            finished = true;
        }
        else if (input.compare("d") == 0)
        {
            cout << " deal feature not yet implemented\n";
        }
    }

    return paid;
}

int Player::PayGeneric(const int amount)
{
    int paid = 0;

    if (amount <= m_bankAccount)
    {
        paid = amount;
    }
    else
    {
        paid = Liquidate(amount);
    }

    m_bankAccount -= paid;

    return paid;
}

int Player::Liquidate(const int target)
{
    cout << "you do not have enought cash pay rent, you must liquidate assets for $" << target << endl;

    //while (m_bankAccount < target)
    {
        // Mortgage / Sell houses / trade
    }

    return m_bankAccount;
}
    
void Player::CollectRent(const int amount)
{
    m_bankAccount += amount;
}

void Player::CollectGeneric(const int amount)
{
    m_bankAccount += amount;
}

void Player::MortgageMenu()
{
    // Sort the prices
    std::sort(m_propertyPrice.begin(), m_propertyPrice.end(), [](const auto& a, const auto& b) {
        return a.second < b.second;
    });

    vector< pair<string, int> > eligibleForMortgage;

    for (auto property : m_propertyPrice)
    {
        if (IsPropertyMortgaged(property.first) == false)
        {
            int mortgageValue = property.second / 2;
            eligibleForMortgage.push_back( make_pair(property.first, mortgageValue) );
        }
    }

    cout << "==============================================\n";
    cout << " Mortgage Menu\n";
    cout << "  Select property to mortagage\n";

    int index = 1;

    for (auto property : eligibleForMortgage)
    {
        cout << "  " << index++ << ". " << property.first << " for $" << property.second << endl;
    }

    if (eligibleForMortgage.size() == 0)
    {
        cout << "  All properties are currently mortgaged" << endl;
    }

    cout << "  " << index << ". to exit" << endl;

    int input = 0;
    cin >> input;

    while(input < 1 || input > index)
    {
        cout << " invalid entry" << endl;

        cin >> input;
    }

    if (input != index && input > 0 && input <= (int)eligibleForMortgage.size())
    {
        index = input - 1;

        cout << " You chose to mortage " << eligibleForMortgage[index].first << "for $" << eligibleForMortgage[index].second << " ? (y/n)" << endl;

        string inputStr = "";
        cin >> inputStr;

        while (inputStr.compare("y") != 0 && inputStr.compare("n") != 0)
        {
            cout << "invalid entry" << endl;
            cin >> inputStr;
        }

        if (inputStr.compare("y") == 0)
        {
            MortgageProperty(eligibleForMortgage[index].first, eligibleForMortgage[index].second);
        }
    }
}

void Player::MortgageProperty(const string propertyName, int value)
{
    // write the property as mortgaged
    for (auto & property : m_propertyPrice)
    {
        if (property.first.compare(propertyName) == 0)
        {
            property.first = string("(M)" + propertyName);
        }
    }

    for (auto & property : m_propertyGroups)
    {
        if (property.first.compare(propertyName) == 0)
        {
            property.first = string("(M)" + propertyName);
        }
    }

    m_bankAccount += value;

    stringstream ss;
    ss << " You have successfully mortgaged " << propertyName << " for $" << value;

    MonopolyUtils::OutputMessage(ss.str(), 1000);
}

bool Player::IsPropertyMortgaged(const string propertyName)
{
    bool mortgaged = false;

    if(propertyName.compare(0,3,"(M)") == 0)
    {
        return true;
    }

    string mortgagedName = string("(M)" + propertyName);

    for (auto property : m_propertyPrice)
    {
        if (property.first.compare(mortgagedName) == 0)
        {
            mortgaged = true;
        }
    }

    return mortgaged;
}

void Player::OutputPlayerStats()
{
    cout << GetName() << " Player Stats: " << endl;
    cout << " bank account: $" << m_bankAccount << endl;

    if(HasGetOutOfJailFreeCard())
    {
        cout << " *Get Out Of Jail Free Card*" << endl;
    }

    if (m_propertyGroups.size() > 0)
    {
        cout << " properties: " << endl;

        PrintPropertyGroup("RailRoad");
        PrintPropertyGroup("Utility");
        PrintPropertyGroup("DarkPurple");
        PrintPropertyGroup("LightBlue");
        PrintPropertyGroup("Purple");
        PrintPropertyGroup("Orange");
        PrintPropertyGroup("Red");
        PrintPropertyGroup("Yellow");
        PrintPropertyGroup("Green");
        PrintPropertyGroup("Blue");
    }
}

void Player::PrintPropertyGroup(string group)
{
    vector<string> names;

    for (int i = 0; i < m_propertyGroups.size(); i++)
    {
        if (m_propertyGroups[i].second.compare(group) == 0)
        {
            names.push_back(m_propertyGroups[i].first);
        }
    }

    if (names.size() > 0)
    {
        cout << "   " << group << endl << "     ";

        for (int i = 0; i < names.size(); i++)
        {
            cout << names[i];

            if ((i+1) < names.size())
            {
                cout << ", ";
            }
        }

        cout << endl;
    }
}

void DrawBoardPosition(vector<BoardSpace *> & board, int & index, const int currentPosition, string token)
{
    int position = 40;

    if (index < 40)
    {
        position = drawPositions[index];
    }

    // print owner initials
    {
        string strInitial = "_";
        BoardSpaceType type = board[position]->GetType();

        if (type == BoardSpaceType::property)
        {
            int owner = reinterpret_cast<Property *>(board[position])->GetOwner();
            
            if (owner != -1)
            {
                strInitial = reinterpret_cast<Property *>(board[position])->GetOwnerInitial();
            }
        }
        else if (type == BoardSpaceType::railroad)
        {
            int owner = reinterpret_cast<RailRoad *>(board[position])->GetOwner();
            
            if (owner != -1)
            {
                strInitial = reinterpret_cast<RailRoad *>(board[position])->GetOwnerInitial();
            }
        }
        else if (type == BoardSpaceType::utility)
        {
            int owner = reinterpret_cast<Utility *>(board[position])->GetOwner();
            
            if (owner != -1)
            {
                strInitial = reinterpret_cast<Utility *>(board[position])->GetOwnerInitial();
            }
        }

        cout << strInitial;
    }

    // print tokens
    map<string, int> positionMap = board[position]->GetBanker()->GetPlayerPositions();

    vector<pair<int, string>> groupedPositions;

    for (const auto & pair : positionMap) 
    {
        bool found = false;

        for (size_t i = 0; i < groupedPositions.size() && !found; i++)
        {
            if (groupedPositions[i].first == pair.second)
            {
                groupedPositions[i].second += pair.first;
                found = true;
            }
        }

        if (!found)
        {
            groupedPositions.push_back( make_pair(pair.second, pair.first) );
        }
    }

    bool done = false;

    for (size_t i = 0; i < groupedPositions.size() && !done; i++)
    {
        if (groupedPositions[i].first == position)
        {
            size_t length = groupedPositions[i].second.size();

            if (length < 4)
            {
                cout << "_";
            }

            cout << groupedPositions[i].second;

            if (length == 1)
            {
                cout << "__|";
            }
            else if (length == 2)
            {
                cout << "_|";
            }
            else
            {
                cout << "|";
            }

            done = true;
        }
    }

    if (!done)
    {
        cout << "____|";
    }

    // increment to next position.
    ++index;
}

void Player::PrintBoardPosition(vector<BoardSpace *> & board)
{
    
    int drawIndex = 0;

    cout << endl;
    cout << "___________________________________________________________________" << endl
         << "|Free |Kntky| Chn | Ind | ILL | RR  | Atl | Vent| WW  |MarGr| Jail|" << endl << "|";

    for(uint32_t i = 0; i < 11; i++)
    {
        DrawBoardPosition(board, drawIndex, GetPosition(), GetToken());
    }

    cout << endl << "| NY  |                                                     | Pacf|" << endl << "|";
    DrawBoardPosition(board, drawIndex, GetPosition(), GetToken());
    cout << "                                                     |";
    DrawBoardPosition(board, drawIndex, GetPosition(), GetToken());

    cout << endl << "|Tenn |                                                     |  NC |" << endl << "|";
    DrawBoardPosition(board, drawIndex, GetPosition(), GetToken());
    cout << "                                                     |";
    DrawBoardPosition(board, drawIndex, GetPosition(), GetToken());

    cout << endl << "| CC  |                                                     |  CC |" << endl << "|";
    DrawBoardPosition(board, drawIndex, GetPosition(), GetToken());
    cout << "                                                     |";
    DrawBoardPosition(board, drawIndex, GetPosition(), GetToken());

    cout << endl << "|StJam|                                                     | Penn|" << endl << "|";
    DrawBoardPosition(board, drawIndex, GetPosition(), GetToken());
    cout << "                                                     |";
    DrawBoardPosition(board, drawIndex, GetPosition(), GetToken());

    cout << endl << "| RR  |                                                     |  RR |" << endl << "|";
    DrawBoardPosition(board, drawIndex, GetPosition(), GetToken());
    cout << "                                                     |";
    DrawBoardPosition(board, drawIndex, GetPosition(), GetToken());

    cout << endl << "| Vir |                                                     | Chn |" << endl << "|";
    DrawBoardPosition(board, drawIndex, GetPosition(), GetToken());
    cout << "                                                     |";
    DrawBoardPosition(board, drawIndex, GetPosition(), GetToken());

    cout << endl << "|State|                                                     |ParkP|" << endl << "|";
    DrawBoardPosition(board, drawIndex, GetPosition(), GetToken());
    cout << "                                                     |";
    DrawBoardPosition(board, drawIndex, GetPosition(), GetToken());
         
    cout << endl << "| EC  |                                                     | LxTx|" << endl << "|";
    DrawBoardPosition(board, drawIndex, GetPosition(), GetToken());
    cout << "                                                     |";
    DrawBoardPosition(board, drawIndex, GetPosition(), GetToken());

    cout << endl << "|StCh |                                                     |Board|" << endl << "|";
    DrawBoardPosition(board, drawIndex, GetPosition(), GetToken());
    cout << "_____________________________________________________|";
    DrawBoardPosition(board, drawIndex, GetPosition(), GetToken());

    cout << endl << "|Jail |Conn |Verm | Chn |Orien| RR  | InTx|Balt | CC  | Med | GO  |" << endl << "|";

    for(uint32_t i = 0; i < 11; i++)
    {
        DrawBoardPosition(board, drawIndex, GetPosition(), GetToken());
    }

    cout << endl << endl;
}

void Player::PrintDiceRoll(int roll)
{
    if (roll == 1)
    {
        cout << "_________" << endl
             << "|       |" << endl
             << "|   *   |" << endl
             << "|_______|" << endl;
    }
    else if (roll == 2)
    {
        cout << "_________" << endl
             << "|     * |" << endl
             << "|       |" << endl
             << "|_*_____|" << endl;
    }
    else if (roll == 3)
    {
        cout << "_________" << endl
             << "|     * |" << endl
             << "|   *   |" << endl
             << "|_*_____|" << endl;
    }
    else if (roll == 4)
    {
        cout << "_________" << endl
             << "| *   * |" << endl
             << "|       |" << endl
             << "|_*___*_|" << endl;
    }
    else if (roll == 5)
    {
        cout << "_________" << endl
             << "| *   * |" << endl
             << "|   *   |" << endl
             << "|_*___*_|" << endl;
    }
    else if (roll ==6)
    {
        cout << "_________" << endl
             << "| *   * |" << endl
             << "| *   * |" << endl
             << "|_*___*_|" << endl;
    }
}