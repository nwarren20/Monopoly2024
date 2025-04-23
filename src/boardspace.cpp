#include "../include/boardspace.hpp"
#include <iostream>
#include <thread>
#include <chrono>
#include <sstream>
#include "../include/utils.hpp"

using namespace std;

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
    if (GetOwner() == -1)
    {
        stringstream ss;
        ss << GetName() << " is for sale at the low price of $" << m_purchasePrice << ".\nYou currently have $" << player->GetCash() << " cash, would you like to buy? y/n";

        MonopolyUtils::OutputMessage(ss.str(), 0);

        vector<string> options = { "y", "n" };
        string buy = MonopolyUtils::GetValidInput("", options);

        if (buy.compare("y") == 0)
        {
          bool success = GetBanker()->BuyPropertyTransaction(player, m_purchasePrice, GetName(), GetGroupName());

          if (success)
          {
            m_owner = player->GetPlayerId();
            MonopolyUtils::OutputMessage("Congratulations! you purchased " + GetName(), 1000);
          }
        }
    }
    else if (GetOwner() == player->GetPlayerId())
    {
        MonopolyUtils::OutputMessage("You own " + GetName(), 1000);
    }
    else
    {
        bool monopoly = DoesOwnerHaveMonopoly();

        bool mortgaged = GetBanker()->IsPropertyMortgaged(GetName(), GetOwner());

        GetBanker()->RentTransaction(player->GetPlayerId(), GetOwner(), GetRent(), GetName(), GetGroupName(), GetHouseCount(), monopoly, mortgaged);
    }

    return false;
}

int Property::GetRent()
{
    int rent = m_baseRent;

    if (DoesOwnerHaveMonopoly())
    {
        const int houseCount = GetHouseCount();

        if (houseCount > 0 && houseCount <= 5)
        {
            rent = m_houseRents[houseCount];
        }
        else
        {
            rent *= 2;
        }
    }

    return rent;
}

bool Property::DoesOwnerHaveMonopoly()
{
    bool monopoly = true;

    for (int i = 0; i < m_group.size(); i++)
    {
        bool doesOwn = (m_group[i]->GetOwner() == GetOwner());
        monopoly &= doesOwn;
    }

  return monopoly;
}

void Property::AddHouse()
{
    m_houseCount++;

    if (m_houseCount > 5)
    {
        m_houseCount = 5;
    }
}

void Property::RemoveHouse()
{
    if (m_houseCount > 0)
    {
        m_houseCount--;
    }
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
    if (GetOwner() == -1)
    {
        stringstream ss;
        ss << "Railroads for sale $200, get'em while they're hot! buy? y/n\n";
        ss << "You have $" << player->GetCash() << " cash";

        MonopolyUtils::OutputMessage(ss.str(), 0);

        vector<string> options = { "y", "n" };
        string buy = MonopolyUtils::GetValidInput("", options);

        if (buy.compare("y") == 0)
        {
            bool success = player->BuyRailRoad(GetName());

            if (success)
            {
                m_owner = player->GetPlayerId();
                MonopolyUtils::OutputMessage("Congratulations! you purchased " + GetName(), 1000);
            }
        }
    }
    else if (GetOwner() == player->GetPlayerId())
    {
        MonopolyUtils::OutputMessage("You own " + GetName(), 1000);
    }
    else
    {
        const int ownerRailroadCount = GetRailroadsOwnedByPlayer(GetOwner());

        bool mortgaged = GetBanker()->IsPropertyMortgaged(GetName(), GetOwner());

        GetBanker()->RailRoadTransaction(player->GetPlayerId(), GetOwner(), GetTicketPrice(), ownerRailroadCount, player->GetPayRailRoadDouble(), mortgaged);
    }

    player->PayRailRoadDouble(false);

    return false;
}

int RailRoad::GetTicketPrice()
{
    int ticketPrice = 25;

    const int railRoadsOwned = GetRailroadsOwnedByPlayer(GetOwner());

    if (railRoadsOwned == 2)
    {
      ticketPrice = 50;
    }
    else if (railRoadsOwned == 3)
    {
      ticketPrice = 100;
    }
    else if (railRoadsOwned == 4)
    {
      ticketPrice = 200;
    }

    return ticketPrice;
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
    if (GetOwner() == -1)
    {
        stringstream ss;
        ss << "Psss... I have a utility in my pocket, you wanna buy for $150? y/n" << endl;
        ss << "You have $" << player->GetCash() << " cash";

        MonopolyUtils::OutputMessage(ss.str(), 0);

        vector<string> options = { "y", "n" };
        string buy = MonopolyUtils::GetValidInput("", options);

        if (buy.compare("y") == 0)
        {
            bool success = player->BuyUtility(GetName());

            if (success)
            {
                m_owner = player->GetPlayerId();
                MonopolyUtils::OutputMessage("Congratulations! you purchased " + GetName(), 1000);
            }
        }
    }
    else if (GetOwner() == player->GetPlayerId())
    {
        MonopolyUtils::OutputMessage("You own " + GetName(), 1000);
    }
    else
    {
        bool ownsBoth = DoesPlayerOwnBothUtilities(GetOwner());

        bool mortgaged = GetBanker()->IsPropertyMortgaged(GetName(), GetOwner());

        GetBanker()->UtilityTransaction(player->GetPlayerId(), GetOwner(), player->GetRolledDiceTotal(), ownsBoth, player->GetPayUtilityTenTimes(), mortgaged);
    }

    player->PayUtilityTenTimes(false);

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

        moved = PerformCardAction(player, picked);

        m_cardStack->ReturnChanceCard(picked);
    }
    else if (GetName().compare("Community Chest") == 0)
    {
        Card picked = m_cardStack->PickupCommunityChestCard();

        moved = PerformCardAction(player, picked);

        m_cardStack->ReturnCommunityChestCard(picked);
    }

    return moved;
}

bool TakeCard::PerformCardAction(Player * player, Card card)
{
  MonopolyUtils::OutputMessage(card.text, 4000);

  PerformTransaction(player, card);

  bool moved = PerformMoveTo(player, card);

  moved |= PerformMoveRelative(player, card);

  PerfromFree(player, card);

  PerformImprovements(player, card);

  return moved;
}

void TakeCard::PerformTransaction(Player * player, Card card)
{
  if (card.transaction != 0)
  {
      if(card.payOtherPlayers == true)
      {
        GetBanker()->PayEachPlayer(player, card.transaction);
      }
      else if (card.collectOtherPlayers == true)
      {
        GetBanker()->CollectEachPlayer(player, card.transaction);
      }
      else
      {
        GetBanker()->CardTransaction(player->GetPlayerId(), card.transaction);
      }
  }
}

bool TakeCard::PerformMoveTo(Player * player, Card card)
{
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

            return true;
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

            return true;
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

            return true;
        }
        else if (card.moveTo >= 0)
        {
            if (currentPos > card.moveTo)
            {
              player->PassGo();
            }

            player->MoveToSpace(card.moveTo);

            return true;
        }
    }

    return false;
}

bool TakeCard::PerformMoveRelative(Player * player, Card card)
{
    if (card.moveRelative != 0)
    {
        player->AdvancePlayer(card.moveRelative);

        return true;
    }

    return false;
}

void TakeCard::PerfromFree(Player * player, Card card)
{
    if (card.free == true)
    {
        player->AwardGetOutOfJailFreeCard();
    }
}

void TakeCard::PerformImprovements(Player * player, Card card)
{
    if (card.costPerHotel > 0 || card.costPerHouse > 0)
    {
        GetBanker()->PayPerHouseAndHotel(player, card.costPerHotel, card.costPerHouse);
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

bool Tax::HandlePlayerVisit(Player * player)
{
    int amount = m_taxAmount;

    if (m_taxAmount == 200)
    {
        int tenPercent = (player->GetNetWorth() / 10);

        if (tenPercent < 200)
        {
            amount = tenPercent;
        }
    }

    GetBanker()->TaxTransaction(player->GetPlayerId(), amount);

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