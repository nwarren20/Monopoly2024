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

bool Property::HandlePlayerVisit(Player * player)
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

  return false;
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

bool RailRoad::HandlePlayerVisit(Player * player)
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

    GetBanker()->RailRoadTransaction(player->GetPlayerId(), m_owner, ownerRailroadCount, player->GetPayRailRoadDouble());

    player->PayRailRoadDouble(false);
  }

  return false;
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

bool Utility::HandlePlayerVisit(Player * player)
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

    GetBanker()->UtilityTransaction(player->GetPlayerId(), m_owner, player->GetRolledDiceTotal(), ownsBoth, player->GetPayUtilityTenTimes());

    player->PayUtilityTenTimes(false);
  }

  return false;
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

bool TakeCard::HandlePlayerVisit(Player * player)
{
    bool moved = false;

    if (GetName().compare("Chance") == 0)
    {
      Card picked = m_cardStack->PickupChanceCard();

      moved = PerformCard(player, picked);

      m_cardStack->ReturnChanceCard(picked);
    }
    else if (GetName().compare("Community Chest") == 0)
    {
      Card picked = m_cardStack->PickupCommunityChestCard();

      moved = PerformCard(player, picked);
    }

    return moved;
}

bool TakeCard::PerformCard(Player * player, Card card)
{
  MonopolyUtils::OutputMessage(card.text, 4000);

  bool moved = false;

  if (card.transaction != 0)
  {
      if(card.transaction == -50)
      {
        GetBanker()->PayEachPlayer(player, 50);
      }
      else
      {
        player->CardTransaction(card.transaction);
      }
  }

  if (card.moveTo != -1)
  {
      int currentPos = player->GetPosition();

      // Go to jail.
      if (card.moveTo == 10)
      {
          player->MoveToSpace(card.moveTo);

          player->GoToJail();
      }
      else if (card.moveTo == 0)
      {
          // advance to go
          player->MoveToSpace(card.moveTo);

          player->PassGo();
      }
      else if (card.moveTo == 5)
      {
          // reading railroad
          if (currentPos > 5)
          {
            player->PassGo();
          }

          player->MoveToSpace(card.moveTo);

          moved = true;
      }
      else if (card.moveTo == -2)
      {
          // Move to nearest railroad
          if (currentPos < 5 || currentPos > 35)
          {
              if (currentPos > 35)
              {
                player->PassGo();
              }

              player->MoveToSpace(5);
          }
          else if (currentPos < 15)
          {
            player->MoveToSpace(15);
          }
          else if (currentPos < 25)
          {
            player->MoveToSpace(25);
          }
          else
          {
            player->MoveToSpace(35);
          }

          player->PayRailRoadDouble();

          moved = true;
      }
      else if (card.moveTo == -3)
      {
          // Move to nearest utility
          if(currentPos < 12 || currentPos > 28)
          {
              if (currentPos > 28)
              {
                player->PassGo();
              }

              player->MoveToSpace(12);
          }
          else
          {
              player->MoveToSpace(28);
          }

          player->PayUtilityTenTimes();

          moved = true;
      }
      else if (card.moveTo >= 0)
      {
          if (currentPos > card.moveTo)
          {
             player->PassGo();
          }

          player->MoveToSpace(card.moveTo);

          moved = true;
      }
  }

  if (card.moveRelative != 0)
  {
      player->AdvancePlayer(card.moveRelative);

      moved = true;
  }

  if (card.free == true)
  {
      player->AwardGetOutOfJailFreeCard();
  }

  return moved;
}

Tax::Tax(const string name, const int position, const int taxAmount)
  : BoardSpace(tax, name, position), 
  m_taxAmount(taxAmount)
{

}
Tax::~Tax()
{

}

bool Tax::HandlePlayerVisit(Player * player)
{
  player->PayTax(m_taxAmount);

  return false;
}

FreeSpace::FreeSpace(const string name, const int position, const int award)
  : BoardSpace(freespace, name, position),
    m_award(award)
{

}
FreeSpace::~FreeSpace()
{

}

bool FreeSpace::HandlePlayerVisit(Player * player)
{
  return false;
}

Jail::Jail(const string name, const int position)
  : BoardSpace(jail, name, position)
{

}
Jail::~Jail()
{

}

bool Jail::HandlePlayerVisit(Player * player)
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

  return false;
}