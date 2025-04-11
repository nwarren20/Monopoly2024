#include "../include/player.hpp"
#include <cstdlib>
#include <ctime>
#include <iostream>

using namespace std;

const int drawPositions[40] = 
{ 20, 21, 22, 23, 24, 25, 26, 27, 28, 29, 30, 19, 31, 18, 32, 17, 33, 16, 34, 15, 35, 14, 36, 13, 37, 12, 38, 11, 39, 10, 9, 8, 7, 6, 5, 4, 3, 2, 1, 0 };

Player::Player(const string name, const int playerId)
  : m_name(name),
    m_playerId(playerId)
{
    m_bankAccount = 1500;
    m_position = 0;

    srand(time(0));
}

Player::~Player()
{

}

int Player::RollDice()
{
    int low = 1;
    int high = 6;

    int dice_1 = (rand() % high) + low;
    int dice_2 = (rand() % high) + low;

    int total = (dice_1 + dice_2);

    cout << m_name << " rolled a " << total << endl;

    m_rolledDice = total;

    return total;
}

int Player::AdvancePlayer(int numSpaces)
{
    m_position += numSpaces;

    if (m_position > 39)
    {
        m_bankAccount+=200;
        m_position -= 40;

        cout << " YOU PASSED GO! COLLECT $200" << endl;
    }

    return m_position;
}

bool Player::PayTax(const int fee)
{
    bool success = true;

    if (fee <= m_bankAccount)
    {
        m_bankAccount -= fee;
        cout << "Paid tax of $" << fee << endl;
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

    if (amount <= m_bankAccount)
    {
        paid = amount;
    }
    else
    {
        // Todo: make player come up with money.
        paid = m_bankAccount;
    }

    m_bankAccount -= paid;

    return paid;
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

void DrawBoardPosition(int & index, const int currentPosition)
{
    int position = 40;

    if (index < 40)
    {
        position = drawPositions[index];
    }

    if (position == currentPosition)
    {
        cout << "__*__|";
    }
    else
    {
        cout << "_____|";
    }

    ++index;
}

void Player::PrintBoardPosition()
{
    
    int drawIndex = 0;

    cout << endl;
    cout << "___________________________________________________________________" << endl
         << "|Free |Kntky| Chn | Ind | ILL | RR  | Atl | Vent| WW  |MarGr| Jail|" << endl << "|";

    for(uint32_t i = 0; i < 11; i++)
    {
        DrawBoardPosition(drawIndex, GetPosition());
    }

    cout << endl << "| NY  |                                                     | Pacf|" << endl << "|";
    DrawBoardPosition(drawIndex, GetPosition());
    cout << "                                                     |";
    DrawBoardPosition(drawIndex, GetPosition());

    cout << endl << "|Tenn |                                                     |  NC |" << endl << "|";
    DrawBoardPosition(drawIndex, GetPosition());
    cout << "                                                     |";
    DrawBoardPosition(drawIndex, GetPosition());

    cout << endl << "| CC  |                                                     |  CC |" << endl << "|";
    DrawBoardPosition(drawIndex, GetPosition());
    cout << "                                                     |";
    DrawBoardPosition(drawIndex, GetPosition());

    cout << endl << "|StJam|                                                     | Penn|" << endl << "|";
    DrawBoardPosition(drawIndex, GetPosition());
    cout << "                                                     |";
    DrawBoardPosition(drawIndex, GetPosition());

    cout << endl << "| RR  |                                                     |  RR |" << endl << "|";
    DrawBoardPosition(drawIndex, GetPosition());
    cout << "                                                     |";
    DrawBoardPosition(drawIndex, GetPosition());

    cout << endl << "| Vir |                                                     | Chn |" << endl << "|";
    DrawBoardPosition(drawIndex, GetPosition());
    cout << "                                                     |";
    DrawBoardPosition(drawIndex, GetPosition());

    cout << endl << "|State|                                                     |ParkP|" << endl << "|";
    DrawBoardPosition(drawIndex, GetPosition());
    cout << "                                                     |";
    DrawBoardPosition(drawIndex, GetPosition());
         
    cout << endl << "| EC  |                                                     | LxTx|" << endl << "|";
    DrawBoardPosition(drawIndex, GetPosition());
    cout << "                                                     |";
    DrawBoardPosition(drawIndex, GetPosition());

    cout << endl << "|StCh |                                                     |Board|" << endl << "|";
    DrawBoardPosition(drawIndex, GetPosition());
    cout << "_____________________________________________________|";
    DrawBoardPosition(drawIndex, GetPosition());

    cout << endl << "|Jail |Conn |Verm | Chn |Orien| RR  | InTx|Balt | CC  | Med | GO  |" << endl << "|";

    for(uint32_t i = 0; i < 11; i++)
    {
        DrawBoardPosition(drawIndex, GetPosition());
    }

    cout << endl << endl;
}