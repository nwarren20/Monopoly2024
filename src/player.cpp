#include "../include/player.hpp"
#include "../include/boardspace.hpp"
#include <cstdlib>
#include <ctime>
#include <iostream>
#include <thread>
#include <chrono>
#include <sstream>
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
    m_jailRolls = 0;
    m_rolledDice_1 = 0;
    m_rolledDice_2 = 0;
    m_doublesCount = 0;

    srand(time(0));
}

Player::~Player()
{

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

int Player::RollDice()
{
    int low = 1;
    int high = 6;

    m_rolledDice_1 = (rand() % high) + low;
    m_rolledDice_2 = (rand() % high) + low;

    std::this_thread::sleep_for(std::chrono::milliseconds(500));

    PrintDiceRoll(m_rolledDice_1);

    std::this_thread::sleep_for(std::chrono::milliseconds(200));

    PrintDiceRoll(m_rolledDice_2);

    cout << m_name << " rolled a " << GetRolledDiceTotal() << endl;

    std::this_thread::sleep_for(std::chrono::seconds(1));

    if (m_jailRolls > 0)
    {
        m_jailRolls--;
    }

    return GetRolledDiceTotal();
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
        MonopolyUtils::OutputMessage("Paid tax of $", 1000);
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
        pair<string, string> newProp = make_pair(name, "Utility");
        m_properties.push_back(newProp);
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
        pair<string, string> newProp = make_pair(name, "RailRoad");
        m_properties.push_back(newProp);
    }
    else
    {
        cout << "Sorry, not enough cash to buy railroad" << endl;
        return false;
    }

    return true;
}

bool Player::BuyProperty(int cost, string prop, string group)
{
    if (m_bankAccount >= cost)
    {
        m_bankAccount -= cost;
        pair<string, string> newProp = make_pair(prop, group);
        m_properties.push_back(newProp);
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

void Player::OutputPlayerStats()
{
    cout << "Player Stats: " << endl;
    cout << " bank account: " << m_bankAccount << endl;

    if (m_properties.size() > 0)
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

    for (int i = 0; i < m_properties.size(); i++)
    {
        if (m_properties[i].second.compare(group) == 0)
        {
            names.push_back(m_properties[i].first);
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

void DrawBoardPosition(vector<BoardSpace *> & board, int & index, const int currentPosition)
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

    if (position == currentPosition)
    {
        cout << "_*__|";
    }
    else
    {
        cout << "____|";
    }

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
        DrawBoardPosition(board, drawIndex, GetPosition());
    }

    cout << endl << "| NY  |                                                     | Pacf|" << endl << "|";
    DrawBoardPosition(board, drawIndex, GetPosition());
    cout << "                                                     |";
    DrawBoardPosition(board, drawIndex, GetPosition());

    cout << endl << "|Tenn |                                                     |  NC |" << endl << "|";
    DrawBoardPosition(board, drawIndex, GetPosition());
    cout << "                                                     |";
    DrawBoardPosition(board, drawIndex, GetPosition());

    cout << endl << "| CC  |                                                     |  CC |" << endl << "|";
    DrawBoardPosition(board, drawIndex, GetPosition());
    cout << "                                                     |";
    DrawBoardPosition(board, drawIndex, GetPosition());

    cout << endl << "|StJam|                                                     | Penn|" << endl << "|";
    DrawBoardPosition(board, drawIndex, GetPosition());
    cout << "                                                     |";
    DrawBoardPosition(board, drawIndex, GetPosition());

    cout << endl << "| RR  |                                                     |  RR |" << endl << "|";
    DrawBoardPosition(board, drawIndex, GetPosition());
    cout << "                                                     |";
    DrawBoardPosition(board, drawIndex, GetPosition());

    cout << endl << "| Vir |                                                     | Chn |" << endl << "|";
    DrawBoardPosition(board, drawIndex, GetPosition());
    cout << "                                                     |";
    DrawBoardPosition(board, drawIndex, GetPosition());

    cout << endl << "|State|                                                     |ParkP|" << endl << "|";
    DrawBoardPosition(board, drawIndex, GetPosition());
    cout << "                                                     |";
    DrawBoardPosition(board, drawIndex, GetPosition());
         
    cout << endl << "| EC  |                                                     | LxTx|" << endl << "|";
    DrawBoardPosition(board, drawIndex, GetPosition());
    cout << "                                                     |";
    DrawBoardPosition(board, drawIndex, GetPosition());

    cout << endl << "|StCh |                                                     |Board|" << endl << "|";
    DrawBoardPosition(board, drawIndex, GetPosition());
    cout << "_____________________________________________________|";
    DrawBoardPosition(board, drawIndex, GetPosition());

    cout << endl << "|Jail |Conn |Verm | Chn |Orien| RR  | InTx|Balt | CC  | Med | GO  |" << endl << "|";

    for(uint32_t i = 0; i < 11; i++)
    {
        DrawBoardPosition(board, drawIndex, GetPosition());
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