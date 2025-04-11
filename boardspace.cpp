#include "boardspace.hpp"
#include <iostream>

using namespace std;

void TestFunction(const int money)
{
  std::cout << " Money = " << money << std::endl;
}

BoardSpace::BoardSpace(BoardSpaceType type, string name, const int position)
 : m_name(name),
   m_position(position)
{

}
    
BoardSpace::~BoardSpace()
{

}

Property::Property(const string name, const int position, string groupName, int purchasePrice, vector<int> & houseRents)
  : BoardSpace(property, name, position),
  m_groupName(groupName),
  m_purchasePrice(purchasePrice),
  m_houseRents(houseRents)
{
  m_owner = -1;
  m_houseCount = 0;
  m_baseRent = houseRents[0];
}
    
Property::~Property()
{

}

void Property::HandlePlayerVisit(Player * player)
{
  if (m_owner == -1)
  {
    cout << GetName() << " is for sale at the low price of $" << m_purchasePrice << ", would you like to buy? y/n" << endl;
    string buy;
    cin >> buy;

    if (buy.compare("y") == 0)
    {
      bool success = player->BuyProperty(m_purchasePrice, GetName(), GetGroupName());

      if (success)
      {
        m_owner = player->GetPlayerId();
        cout << " Congradulations! you purchased " << GetName() << endl;
      }
    }
  }
  else if (m_owner == player->GetPlayerId())
  {
    cout << "You own " << GetName() << endl;
  }
  else
  {
    bool monopoly = DoesOwnerHaveMonopoly(m_owner);

    GetBanker()->RentTransaction(player->GetPlayerId(), m_owner, m_baseRent, GetGroupName(), monopoly);
  }
}

bool Property::DoesOwnerHaveMonopoly(const int playerId)
{
  bool monopoly = true;

  for (uint i = 0; i < m_group.size(); i++)
  {
    bool doesOwn = (m_group[i]->GetOwner() == playerId);
    monopoly &= doesOwn;
  }

  return monopoly;
}

void Property::BuyHouses()
{

}

RailRoad::RailRoad(const string name, const int position)
  : BoardSpace(railroad, name, position)
{
  m_owner = -1;
}

RailRoad::~RailRoad()
{

}

void RailRoad::HandlePlayerVisit(Player * player)
{
  if (m_owner == -1)
  {
    cout << "Railroads for sale, get'em while they're hot! buy? y/n" << endl;
    string buy;
    cin >> buy;

    if (buy.compare("y") == 0)
    {
      bool success = player->BuyRailRoad(GetName());

      if (success)
      {
        m_owner = player->GetPlayerId();
        cout << " Congradulations! you purchased " << GetName() << endl;
      }
    }
  }
  else if (m_owner == player->GetPlayerId())
  {
    cout << "You own " << GetName() << endl;
  }
  else
  {
    const int ownerRailroadCount = GetRailroadsOwnedByPlayer(m_owner);

    GetBanker()->RailRoadTransaction(player->GetPlayerId(), m_owner, ownerRailroadCount);
  }
}

int RailRoad::GetRailroadsOwnedByPlayer(const int ownerId)
{
    int count = 0;

    for (uint i = 0; i < m_group.size(); i++)
    {
      if (m_group[i]->GetOwner() == ownerId)
      {
        count++;
      }
    }

    return count;
}

Utility::Utility(const string name, const int position)
  : BoardSpace(utility, name, position)
{
  m_owner = -1;
}

Utility::~Utility()
{

}

void Utility::HandlePlayerVisit(Player * player)
{
  if (m_owner == -1)
  {
    cout << "psss... I have a utility in my pocket, you wanna buy? y/n" << endl;
    string buy;
    cin >> buy;

    if (buy.compare("y") == 0)
    {
      bool success = player->BuyUtility(GetName());

      if (success)
      {
        m_owner = player->GetPlayerId();
        cout << " Congradulations! you purchased " << GetName() << endl;
      }
    }
  }
  else if (m_owner == player->GetPlayerId())
  {
    cout << "You own " << GetName() << endl;
  }
  else
  {
    bool ownsBoth = DoesPlayerOwnBothUtilities(m_owner);

    GetBanker()->UtilityTransaction(player->GetPlayerId(), m_owner, player->GetRolledDice(), ownsBoth);
  }
}

bool Utility::DoesPlayerOwnBothUtilities(const int playerId)
{
  int count = 0;

    for (uint i = 0; i < m_group.size(); i++)
    {
      if (m_group[i]->GetOwner() == playerId)
      {
        count++;
      }
    }

    return (count == 2);
}

TakeCard::TakeCard(const string name, const int position, vector<int> * cardStack)
  : BoardSpace(takecare, name, position),
    m_cardStack(cardStack)
{

}
    
TakeCard::~TakeCard()
{

}

void TakeCard::HandlePlayerVisit(Player * player)
{

}

Tax::Tax(const string name, const int position, const int taxAmount)
  : BoardSpace(tax, name, position), 
  m_taxAmount(taxAmount)
{

}
Tax::~Tax()
{

}

void Tax::HandlePlayerVisit(Player * player)
{
  player->PayTax(m_taxAmount);
}

FreeSpace::FreeSpace(const string name, const int position, const int award)
  : BoardSpace(freespace, name, position),
    m_award(award)
{

}
FreeSpace::~FreeSpace()
{

}

void FreeSpace::HandlePlayerVisit(Player * player)
{

}

Jail::Jail(const string name, const int position)
  : BoardSpace(jail, name, position)
{

}
Jail::~Jail()
{

}

void Jail::HandlePlayerVisit(Player * player)
{

}