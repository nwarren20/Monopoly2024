#include "../include/carddeck.hpp"

#include <algorithm>


CardDeck::CardDeck()
{
    m_chanceIndex = 9;
    m_communityChestIndex = 0;

    LoadDecks();
}

CardDeck::~CardDeck()
{

}

void CardDeck::LoadDecks()
{
    LoadChanceDeck();

    LoadCommunityChestCards();
}

Card CardDeck::PickupChanceCard()
{
    return m_chanceCards[m_chanceIndex];
}

Card CardDeck::PickupCommunityChestCard()
{
    return m_communityChestCards[m_communityChestIndex];
}

void CardDeck::ReturnChanceCard(Card card)
{
    m_chanceIndex = (m_chanceIndex + 1) % m_chanceCards.size();
}

void CardDeck::ReturnCommunityChestCard(Card card)
{
    m_communityChestIndex = (m_communityChestIndex + 1) % m_communityChestCards.size();
}

void CardDeck::ShuffleChanceCards()
{
    // Seed the random number generator
    std::random_device rd;
    std::mt19937 gen(rd());

    std::shuffle(m_chanceCards.begin(), m_chanceCards.end(), gen);
}

void CardDeck::ShuffleCommunityChestCards()
{
    // Seed the random number generator
    std::random_device rd;
    std::mt19937 gen(rd());

    std::shuffle(m_communityChestCards.begin(), m_communityChestCards.end(), gen);
}

void CardDeck::LoadChanceDeck()
{
    Card card_1;
    card_1.text = "PAY POOR TAX OF 15";
    card_1.transaction = -15;

    Card card_2;
    card_2.text = "ADVANCE TO ILLINOIS AVE.";
    card_2.moveTo = 24;

    Card card_3;
    card_3.text = "TAKE A RIDE ON THE READING\nIF YOU PASS GO COLLECT $200";
    card_3.moveTo = 5;

    Card card_4;
    card_4.text = "GO DIRECTLY TO JAIL\nDO NOT PASS GO, DO NOT COLLECT $200";
    card_4.moveTo = 10;

    Card card_5;
    card_5.text = "GET OUT OF JAIL FREE";
    card_5.free = true;
    
    Card card_6;
    card_6.text = "Advance token to the nearest Railroad\nand pay owner Twice the Rental to which he is otherwise entitled.\nIf Railroad is unowned, you may buy it from the Bank.";
    card_6.moveTo = -2;

    Card card_7;
    card_7.text = "BANK PAYS YOU DIVIDEND OF $50";
    card_7.transaction = 50;

    Card card_8;
    card_8.text = "GO BACK 3 SPACES";
    card_8.moveRelative = -3;

    Card card_9;
    card_9.text = "YOUR BUILDING AND LOAN MATURES\nCOLLECT $150";
    card_9.transaction = 150;

    Card card_10;
    card_10.text = "ADVANCE TOKEN TO NEAREST UTILITY\nIF UNOWNED you may buy it from the bank\nIF OWNED. throw dice and pay owner a total of ten times the amount thrown";
    card_10.moveTo = -3;

    Card card_11;
    card_11.text = "TAKE A WALK ON THE BOARD WALK\nADVANCE TOKEN TO BOARD WALK";
    card_11.moveTo = 39;

    Card card_12;
    card_12.text = "ADVANCE TO ST. CHARLES PLACE\nIF YOU PASS GO. COLLECT $200";
    card_12.moveTo = 11;

    Card card_13;
    card_13.text = "You have been ELECTED CHAIRMAN OF THE BOARD\nPAY EACH PLAYER $50";
    card_13.transaction = 50;
    card_13.payOtherPlayers = true;

    Card card_14;
    card_14.text = "Make General Repairs On All Your Property\nFOR EACH HOUSE PAY $25\nFOR EACH HOTEL $100";
    card_14.costPerHotel = 100;
    card_14.costPerHouse = 25;
    
    Card card_15;
    card_15.text = "ADVANCE TO GO (COLLECT $200)";
    card_15.moveTo = 0;

    Card card_16;
    card_16.text = "Advance token to the nearest Railroad\nand pay owner Twice the Rental to which he is otherwise entitled.\nIf Railroad is unowned, you may buy it from the Bank.";
    card_16.moveTo = -2;

    m_chanceCards.push_back(card_1);
    m_chanceCards.push_back(card_2);
    m_chanceCards.push_back(card_3);
    m_chanceCards.push_back(card_4);
    m_chanceCards.push_back(card_5);
    m_chanceCards.push_back(card_6);
    m_chanceCards.push_back(card_7);
    m_chanceCards.push_back(card_8);
    m_chanceCards.push_back(card_9);
    m_chanceCards.push_back(card_10);
    m_chanceCards.push_back(card_11);
    m_chanceCards.push_back(card_12);
    m_chanceCards.push_back(card_13);
    m_chanceCards.push_back(card_14);
    m_chanceCards.push_back(card_15);
    m_chanceCards.push_back(card_16);
}

void CardDeck::LoadCommunityChestCards()
{
    Card card_1;
    card_1.text = "Grand Opera Opening\nCOLLECT $50 FROM EVERY PLAYER\nFOR OPENING NIGHT SEATS";
    card_1.transaction = 50;
    card_1.collectOtherPlayers = true;

    Card card_2;
    card_2.text = "RECEIVE FOR SERVICES $25";
    card_2.transaction = 25;

    Card card_3;
    card_3.text = "PAY HOSPITAL $100";
    card_3.transaction = -100;

    Card card_4;
    card_4.text = "ADVANCE TO GO\nCOLLECT $200";
    card_4.moveTo = 0;

    Card card_5;
    card_5.text = "YOU INHERIT $100";
    card_5.transaction = 100;

    Card card_6;
    card_6.text = "INCOME TAX REFUND\nCOLLECT $20";
    card_6.transaction = 20;

    Card card_7;
    card_7.text = "YOU HAVE WON SECOND PRIZE IN A BEAUTY CONTEST\nCOLLECT $10";
    card_7.transaction = 10;

    Card card_8;
    card_8.text = "YOU ARE ASSESSED FOR STREET REPAIRS\n$40 PER HOUSE\n$115 PER HOTEL";
    card_8.costPerHotel = 115;
    card_8.costPerHouse = 40;

    Card card_9;
    card_9.text = "BANK ERROR IN YOUR FAVOR\nCOLLECT $200";
    card_9.transaction = 200;

    Card card_10;
    card_10.text = "XMAS FUND MATURES\nCOLLECT $100";
    card_10.transaction = 100;

    Card card_11;
    card_11.text = "LIFE INSURANCE MATURES\nCOLLECT $100";
    card_11.transaction = 100;

    Card card_12;
    card_12.text = "PAY SCHOOL TAX OF $150";
    card_12.transaction = -150;

    Card card_13;
    card_13.text = "FROM SALE OF STOCK YOU GET $45";
    card_13.transaction = 45;

    Card card_14;
    card_14.text = "GET OUT OF JAIL, FREE";
    card_14.free = true;

    Card card_15;
    card_15.text = "DOCTOR'S FEE PAY $50";
    card_15.transaction = -50;

    Card card_16;
    card_16.text = "GO TO JAIL\nGo Directly to Jail\nDO NOT PASS GO\nDO NOT COLLECT $200";
    card_16.moveTo = 10;

    m_communityChestCards.push_back(card_1);
    m_communityChestCards.push_back(card_2);
    m_communityChestCards.push_back(card_3);
    m_communityChestCards.push_back(card_4);
    m_communityChestCards.push_back(card_5);
    m_communityChestCards.push_back(card_6);
    m_communityChestCards.push_back(card_7);
    m_communityChestCards.push_back(card_8);
    m_communityChestCards.push_back(card_9);
    m_communityChestCards.push_back(card_10);
    m_communityChestCards.push_back(card_11);
    m_communityChestCards.push_back(card_12);
    m_communityChestCards.push_back(card_13);
    m_communityChestCards.push_back(card_14);
    m_communityChestCards.push_back(card_15);
    m_communityChestCards.push_back(card_16);
}