#include "../include/boardspace.hpp"
#include <iostream>
#include <thread>
#include <chrono>
#include "../include/utils.hpp"

using namespace std;
//using namespace MonopolyUtils;

void TestFunction(const int money)
{
  std::cout << " Money = " << money << std::endl;
}

BoardSpace::BoardSpace(BoardSpaceType type, string name, const int position)
 : m_type(type),
   m_name(name),
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
    cout << GetName() << " is for sale at the low price of $" << m_purchasePrice << ", your currently have $" << player->GetCash() << " cash, would you like to buy? y/n" << endl;
    string buy;
    cin >> buy;

    if (buy.compare("y") == 0)
    {
      bool success = player->BuyProperty(m_purchasePrice, GetName(), GetGroupName());

      if (success)
      {
        m_owner = player->GetPlayerId();
        MonopolyUtils::OutputMessage(" Congratulations! you purchased " + GetName(), 1000);
      }
    }
  }
  else if (m_owner == player->GetPlayerId())
  {
    MonopolyUtils::OutputMessage("You own " + GetName(), 1000);
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

  for (int i = 0; i < m_group.size(); i++)
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
    cout << "Railroads for sale $200, get'em while they're hot! buy? y/n" << endl;
    cout << " you have $" << player->GetCash() << " cash" << endl;
    string buy;
    cin >> buy;

    if (buy.compare("y") == 0)
    {
      bool success = player->BuyRailRoad(GetName());

      if (success)
      {
        m_owner = player->GetPlayerId();
        MonopolyUtils::OutputMessage(" Congratulations! you purchased " + GetName(), 1000);
      }
    }
  }
  else if (m_owner == player->GetPlayerId())
  {
    MonopolyUtils::OutputMessage("You own " + GetName(), 1000);
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

    for (int i = 0; i < m_group.size(); i++)
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
    cout << "psss... I have a utility in my pocket, you wanna buy for $150? y/n" << endl;
    cout << " you have $" << player->GetCash() << " cash" << endl;
    string buy;
    cin >> buy;

    if (buy.compare("y") == 0)
    {
      bool success = player->BuyUtility(GetName());

      if (success)
      {
        m_owner = player->GetPlayerId();
        MonopolyUtils::OutputMessage(" Congratulations! you purchased " + GetName(), 1000);
      }
    }
  }
  else if (m_owner == player->GetPlayerId())
  {
    MonopolyUtils::OutputMessage("You own " + GetName(), 1000);
  }
  else
  {
    bool ownsBoth = DoesPlayerOwnBothUtilities(m_owner);

    GetBanker()->UtilityTransaction(player->GetPlayerId(), m_owner, player->GetRolledDiceTotal(), ownsBoth);
  }
}

bool Utility::DoesPlayerOwnBothUtilities(const int playerId)
{
  int count = 0;

    for (int i = 0; i < m_group.size(); i++)
    {
      if (m_group[i]->GetOwner() == playerId)
      {
        count++;
      }
    }

    return (count == 2);
}

TakeCard::TakeCard(const string name, const int position, CardDeck * cardStack)
  : BoardSpace(takecare, name, position),
    m_cardStack(cardStack)
{

}
    
TakeCard::~TakeCard()
{

}

void TakeCard::HandlePlayerVisit(Player * player)
{
    if (GetName().compare("Chance") == 0)
    {
      Card picked = m_cardStack->PickupChanceCard();

      PerformCard(player, picked);
    }
    else if (GetName().compare("Community Chest") == 0)
    {
      Card picked = m_cardStack->PickupCommunityChestCard();

      PerformCard(player, picked);
    }
}

void TakeCard::PerformCard(Player * player, Card card)
{
  MonopolyUtils::OutputMessage(card.text, 4000);

  if (card.transaction != 0)
  {
    player->CardTransaction(card.transaction);
  }

  if (card.moveTo != -1)
  {
    player->MoveToSpace(card.moveTo);

    if (card.moveTo == 10)
    {
      player->GoToJail();
    }
    else if (card.moveTo == 0)
    {
      player->PassGo();
    }
  }

  if (card.moveRelative != 0)
  {
    player->AdvancePlayer(card.moveRelative);
  }
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
  if (GetPosition() == 30)
  {
    MonopolyUtils::OutputMessage("GO TO JAIL, do not collect $200", 1000);
    player->GoToJail();
  }
  else
  {
    MonopolyUtils::OutputMessage("Just Visiting", 1000);
  }
}