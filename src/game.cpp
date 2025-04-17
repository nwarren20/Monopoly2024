#include <thread>
#include <chrono>
#include <cstdint>
#include <vector>
#include <iostream>

#include "../include/boardspace.hpp"
#include "../include/player.hpp"
#include "../include/rents.hpp"
#include "../include/banker.hpp"
#include "../include/carddeck.hpp"
#include "../include/utils.hpp"

using namespace std;

int main()
{
    Banker * banker = new Banker();

    vector<BoardSpace *> gameBoard;

    CardDeck * cardDeck = new CardDeck();

    MonopolyUtils::LoadBoard(gameBoard, cardDeck);

    for (uint32_t i = 0; i < gameBoard.size(); i++)
    {
        gameBoard[i]->SetBanker(banker);
    }

    MonopolyUtils::PringWelcomeMessage();

    banker->WhoesPlaying();

    bool gameOver = false;
    int turn = 0;

    while (!gameOver)
    {
        bool turnOver = false;

        Player * playerThisTurn = banker->GetActivePlayerForTurn(turn);

        playerThisTurn->BeginTurn();

        int gaffDice = 0;

        while (!turnOver)
        {
            playerThisTurn->PrintBoardPosition(gameBoard);

            int position = playerThisTurn->GetPosition();
            string space = gameBoard[position]->GetName();

            cout << "===================================================================\n";
            cout << playerThisTurn->GetName() << " is currently on " << space << endl;
            playerThisTurn->OutputPlayerStats(gameBoard);

            banker->GivePlayOptions(playerThisTurn);

            string input;
            cin >> input;

            if (input.compare("r") == 0)
            {
                bool playerJailedToBeginTurn = playerThisTurn->IsJailed();

                int spacesToMove = playerThisTurn->RollDice(gaffDice);
                gaffDice = 0;

                if (playerJailedToBeginTurn)
                {
                    bool GetOutOfJail = playerThisTurn->TryToRollOutOfJail();

                    if (!GetOutOfJail)
                    {
                        turnOver = true;
                        continue;
                    }
                }
                else if (playerThisTurn->WasDoublesRolledThreeTimes())
                {
                    turnOver = true;
                    continue;
                }

                position = playerThisTurn->AdvancePlayer(spacesToMove);

                bool moved = true;

                while(moved)
                {
                    position = playerThisTurn->GetPosition();

                    playerThisTurn->PrintBoardPosition(gameBoard);

                    space = gameBoard[position]->GetName();

                    MonopolyUtils::OutputMessage(playerThisTurn->GetName() + " landed on " + space, 2000);

                    moved = gameBoard[position]->HandlePlayerVisit(playerThisTurn);
                }

                turnOver = playerThisTurn->IsTurnOver(playerJailedToBeginTurn);
            }
            else if (input.compare("f") == 0 && playerThisTurn->IsJailed() && playerThisTurn->HasGetOutOfJailFreeCard())
            {
                MonopolyUtils::OutputMessage(playerThisTurn->GetName() + " used their 'Get Out of Jail Free' card!", 1000);

                bool GetOutOfJail = playerThisTurn->UseGetOutOfJailFreeCard();

                if (!GetOutOfJail)
                {
                    MonopolyUtils::OutputMessage(playerThisTurn->GetName() + "'s card did not work", 1000);
                    turnOver = true;
                    continue;
                }
            }
            else if (input.compare("t") == 0)
            {
                MonopolyUtils::OutputMessage("Not implemented yet", 0);
            }
            else if (input.compare("m") == 0)
            {
                if (playerThisTurn->OwnsProperty())
                {
                    playerThisTurn->MortgageMenu();
                }
                else
                {
                    MonopolyUtils::OutputMessage("must own property to mortgage", 0);
                }
            }
            else if (input.compare("u") == 0)
            {
                if (playerThisTurn->HasMortgagedProperty())
                {
                    playerThisTurn->UnMortgageMenu();
                }
                else
                {
                    MonopolyUtils::OutputMessage("no property you own is mortgaged", 0);
                }
            }
            else if (input.compare("b") == 0)
            {
                if (playerThisTurn->OwnsMonopoly())
                {
                    playerThisTurn->BuyHousesAndHotels(gameBoard);
                }
                else
                {
                    MonopolyUtils::OutputMessage("must own monopoly to buy houses/hotels!", 0);
                }
            }
            else if (playerThisTurn->IsJailed() && input.compare("p") == 0)
            {
                playerThisTurn->GetOutOfJail(50);
            }
            else if (input.compare("g") == 0)
            {
                bool validRoll = false;
                int roll = 0;

                while (!validRoll)
                {
                    cout << "Enter Roll 2-12" << endl;
                    cin >> roll;

                    validRoll = (roll >=2 && roll <= 12);
                }
                
                gaffDice = roll;
            }
            else
            {
                MonopolyUtils::OutputMessage(string("Invalid Entry: " + input), 0);
            }
        }

        playerThisTurn->OutputPlayerStats(gameBoard);
        
        bool validInput = false;

        while (!validInput)
        {
            cout << "Your turn is finished, enter 'f'                                                      enter 'q' to quit game" << endl;
            string done;
            cin >> done;

            if (done.compare("f") == 0)
            {
                turnOver = true;
                validInput = true;
            }
            else if (done.compare("q") == 0)
            {
                cout << "Game Over" << endl;
                turnOver = true;
                gameOver = true;
                validInput = true;
            }
        }

        turn = (turn + 1) % banker->GetNumActivePlayers();
    }

    return 0;
}