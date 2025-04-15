#include "../include/carddeck.hpp"



CardDeck::CardDeck()
{

}

CardDeck::~CardDeck()
{

}

Card CardDeck::PickupChanceCard()
{
    Card card;
    card.text = "PAY POOR TAX OF 15";
    card.transaction = -15;

    return card;
}

Card CardDeck::PickupCommunityChestCard()
{
    Card card;
    card.text = "GO TO JAIL, GO DIRECTLY TO JAIL\nDO NOT PASS GO, DO NOT COLLECT $200";
    card.moveTo = 10;

    return card;
}

void CardDeck::ReturnChanceCard(Card card)
{

}

void CardDeck::ReturnCommunityChestCard(Card card)
{

}

void CardDeck::ShuffleChanceCards()
{

}

void CardDeck::ShuffleCommunityChestCards()
{

}