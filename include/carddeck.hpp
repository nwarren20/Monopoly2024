# pragma once

#include <string>
#include <vector>

using namespace std;

struct Card
{
    string text = "";
    int transaction = 0;
    int moveRelative = 0;
    int moveTo = -1;
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

        void ShuffleChanceCards();

        void ShuffleCommunityChestCards();

    private:

        vector<Card> m_chanceCards;

        vector<Card> m_communityChestCards;

};