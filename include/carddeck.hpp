# pragma once

#include <string>
#include <vector>
#include <random>

using namespace std;

struct Card
{
    string text = "";
    int transaction = 0;
    int moveRelative = 0;
    int moveTo = -1;
    bool free = false;
};

class CardDeck
{
    public:

        CardDeck();

        ~CardDeck();

        Card PickupChanceCard();

        Card PickupCommunityChestCard();

        void ReturnChanceCard(Card card);

        void ReturnCommunityChestCard(Card card);

    protected:

        void LoadDecks();

        void LoadChanceDeck();

        void ShuffleChanceCards();

        void ShuffleCommunityChestCards();

    private:

        vector<Card> m_chanceCards;

        vector<Card> m_communityChestCards;

        int m_chanceIndex;

};