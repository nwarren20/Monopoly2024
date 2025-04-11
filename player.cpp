#include "player.hpp"
#include <cstdlib>
#include <ctime>
#include <iostream>

using namespace std;

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

    for (uint i = 0; i < m_properties.size(); i++)
    {
        if (m_properties[i].second.compare(group) == 0)
        {
            names.push_back(m_properties[i].first);
        }
    }

    if (names.size() > 0)
    {
        cout << "   " << group << endl << "     ";

        for (uint i = 0; i < names.size(); i++)
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