
#include <iostream>
#include "../include/boardspace.hpp"
#include "../include/player.hpp"
#include <vector>
#include "../include/rents.hpp"
#include "../include/banker.hpp"
#include <thread>
#include <cstdint>

using namespace std;

void CreateDarkPurpleGroup(vector<Property *> & group)
{
    Property * Mediteranean = new Property("Mediteranean Avenue", 1, "DarkPurple", 60, Rents::meditereanRents);
    Property * Baltic = new Property("Baltic Avenue", 3, "DarkPurple", 60, Rents::balticRents);

    group.push_back(Mediteranean);
    group.push_back(Baltic);

    Mediteranean->SetGroup(group);
    Baltic->SetGroup(group);
}

void CreateLightBlueGroup(vector<Property *> & group)
{
    Property * Oriental = new Property("Oriental Avenue", 6, "LightBlue", 100, Rents::orientalRents);
    Property * Vermont = new Property("Vermont Avenue", 8, "LightBlue", 100, Rents::vermontRents);
    Property * Connecticut = new Property("Connecticut Avenue", 9, "LightBlue", 120, Rents::connecticutRents);

    group.push_back(Oriental);
    group.push_back(Vermont);
    group.push_back(Connecticut);

    Oriental->SetGroup(group);
    Vermont->SetGroup(group);
    Connecticut->SetGroup(group);
}

void CreatePurpleGroup(vector<Property *> & group)
{
    Property * StCharles = new Property("St. Charles Place", 11, "Purple", 140, Rents::stCharlesRents);
    Property * States = new Property("States Avenue", 13, "Purple", 140, Rents::statesRents);
    Property * Virginia = new Property("Virginia Avenue", 14, "Purple", 160, Rents::virginiaRents);

    group.push_back(StCharles);
    group.push_back(States);
    group.push_back(Virginia);

    StCharles->SetGroup(group);
    States->SetGroup(group);
    Virginia->SetGroup(group);
}

void CreateOrangeGroup(vector<Property *> & group)
{
    Property * StJames = new Property("St. James Place", 16, "Orange", 180, Rents::stJamesRents);
    Property * Tennessee = new Property("Tennessee Avenue", 18, "Orange", 180, Rents::tennesseeRents);
    Property * NewYork = new Property("New York Avenue", 19, "Orange", 200, Rents::newYorkRents);

    group.push_back(StJames);
    group.push_back(Tennessee);
    group.push_back(NewYork);

    StJames->SetGroup(group);
    Tennessee->SetGroup(group);
    NewYork->SetGroup(group);
}

void CreateRedGroup(vector<Property *> & group)
{
    Property * Kentucky = new Property("Kentucky Avenue", 21, "Red", 220, Rents::newYorkRents);
    Property * Indiana = new Property("Indiana Avenue", 23, "Red", 220, Rents::newYorkRents);
    Property * Illinois = new Property("Illinois Avenue", 24, "Red", 240, Rents::newYorkRents);

    group.push_back(Kentucky);
    group.push_back(Indiana);
    group.push_back(Illinois);

    Kentucky->SetGroup(group);
    Indiana->SetGroup(group);
    Illinois->SetGroup(group);
}

void CreateYellowGroup(vector<Property *> & group)
{
    Property * Atlantic = new Property("Atlantic Avenue", 26, "Yellow", 260, Rents::newYorkRents);
    Property * Ventnor = new Property("Ventnor Avenue", 27, "Yellow", 260, Rents::newYorkRents);
    Property * MarvinGardens = new Property("Marvin Gardens", 29, "Yellow", 280, Rents::newYorkRents);

    group.push_back(Atlantic);
    group.push_back(Ventnor);
    group.push_back(MarvinGardens);

    Atlantic->SetGroup(group);
    Ventnor->SetGroup(group);
    MarvinGardens->SetGroup(group);
}

void CreateGreenGroup(vector<Property *> & group)
{
    Property * Pacific = new Property("Pacific Avenue", 31, "Green", 280, Rents::pacificRents);
    Property * NC = new Property("North Carolina Avenue", 32, "Green", 280, Rents::northcarolinaRents);
    Property * Penn = new Property("Pennsylvania Avenue", 34, "Green", 280, Rents::pennsylvaniaRents);

    group.push_back(Pacific);
    group.push_back(NC);
    group.push_back(Penn);

    Pacific->SetGroup(group);
    NC->SetGroup(group);
    Penn->SetGroup(group);
}

void CreateBlueGroup(vector<Property *> & group)
{
    Property * ParkPlace = new Property("Park Place", 37, "Blue", 350, Rents::parkPlaceRents);
    Property * Boardwalk = new Property("Boardwalk", 39, "Blue", 400, Rents::boardwalkRents);

    group.push_back(ParkPlace);
    group.push_back(Boardwalk);

    ParkPlace->SetGroup(group);
    Boardwalk->SetGroup(group);
}

void CreateRailRoadGroup(vector<RailRoad *> & group)
{
    RailRoad * Reading_RR = new RailRoad("Reading Railroad", 5);
    RailRoad * Pennsylvania_RR = new RailRoad("Pennsylvania Railroad", 15);
    RailRoad * BandO_RR = new RailRoad("B&O Railroad", 25);
    RailRoad * ShortLine_RR = new RailRoad("Short Line Railroad", 35);

    group.push_back(Reading_RR);
    group.push_back(Pennsylvania_RR);
    group.push_back(BandO_RR);
    group.push_back(ShortLine_RR);

    Reading_RR->SetGroup(group);
    Pennsylvania_RR->SetGroup(group);
    BandO_RR->SetGroup(group);
    ShortLine_RR->SetGroup(group);
}

void LoadBoard(vector<BoardSpace *> & gameBoard, vector<Property *> & darkPurpleGroup, vector<Property *> & lightBlueGroup, vector<Property *> & purpleGroup,
    vector<Property *> & orangeGroup, vector<Property *> & redGroup, vector<Property *> & yellowGroup, vector<Property *> greenGroup, vector<Property *> & blueGroup,
    vector<RailRoad *> & railRoadGroup)
{
    vector<int> communityChestCards;
    vector<int> chanceCards;
    
    gameBoard.push_back( new FreeSpace("Go", 0, 200) );
    gameBoard.push_back( darkPurpleGroup[0] );
    gameBoard.push_back( new TakeCard("Community Chest", 2, &communityChestCards) );
    gameBoard.push_back( darkPurpleGroup[1] );
    gameBoard.push_back( new Tax("Income Tax", 4, 200) );
    gameBoard.push_back( railRoadGroup[0] );
    gameBoard.push_back( lightBlueGroup[0] );
    gameBoard.push_back( new TakeCard("Chance", 7, &chanceCards) );
    gameBoard.push_back( lightBlueGroup[1] );
    gameBoard.push_back( lightBlueGroup[2] );

    gameBoard.push_back( new Jail("Jail", 10) );
    gameBoard.push_back( purpleGroup[0] );
    gameBoard.push_back( new Utility("Electric Company", 12) );
    gameBoard.push_back( purpleGroup[1] );
    gameBoard.push_back( purpleGroup[2] );
    gameBoard.push_back( railRoadGroup[1] );
    gameBoard.push_back( orangeGroup[0] );
    gameBoard.push_back( new TakeCard("Community Chest", 17, &communityChestCards) );
    gameBoard.push_back( orangeGroup[1] );
    gameBoard.push_back( orangeGroup[2] );

    gameBoard.push_back( new FreeSpace("Free Parking", 20, 0) );
    gameBoard.push_back( redGroup[0] );
    gameBoard.push_back( new TakeCard("Chance", 22, &chanceCards) );
    gameBoard.push_back( redGroup[1] );
    gameBoard.push_back( redGroup[2] );
    gameBoard.push_back( railRoadGroup[2] );
    gameBoard.push_back( yellowGroup[0] );
    gameBoard.push_back( yellowGroup[1] );
    gameBoard.push_back( new Utility("Water Works", 28) );
    gameBoard.push_back( yellowGroup[2] );

    gameBoard.push_back( new Jail("Go to Jail", 30) );
    gameBoard.push_back( greenGroup[0] );
    gameBoard.push_back( greenGroup[1] );
    gameBoard.push_back( new TakeCard("Community Chest", 33, &communityChestCards) );
    gameBoard.push_back( greenGroup[2] );
    gameBoard.push_back( railRoadGroup[3] );
    gameBoard.push_back( new TakeCard("Chance", 36, &chanceCards) );
    gameBoard.push_back( blueGroup[0] );
    gameBoard.push_back( new Tax("Luxury Tax", 38, 75) );
    gameBoard.push_back( blueGroup[1] );
}

int main()
{
    cout << "Welcome to MONOPOLY!\n";

    thread myJob;

    Rents::LoadRents();

    //vector<int> v1 = {2, 10, 15};

    Banker * banker = new Banker();

    vector<Property *> darkPurpleGroup;
    CreateDarkPurpleGroup(darkPurpleGroup);

    vector<Property *> lightBlueGroup;
    CreateLightBlueGroup(lightBlueGroup);

    vector<Property *> purpleGroup;
    CreatePurpleGroup(purpleGroup);

    vector<Property *> orangeGroup;
    CreateOrangeGroup(orangeGroup);

    vector<Property *> redGroup;
    CreateRedGroup(redGroup);

    vector<Property *> yellowGroup;
    CreateYellowGroup(yellowGroup);

    vector<Property *> greenGroup;
    CreateGreenGroup(greenGroup);

    vector<Property *> blueGroup;
    CreateBlueGroup(blueGroup);

    vector<RailRoad *> railRoadGroup;
    CreateRailRoadGroup(railRoadGroup);

    vector<BoardSpace *> gameBoard;

    LoadBoard(gameBoard, darkPurpleGroup, lightBlueGroup, purpleGroup, orangeGroup, redGroup, yellowGroup, greenGroup, blueGroup, railRoadGroup);

    for (uint32_t i = 0; i < gameBoard.size(); i++)
    {
        gameBoard[i]->SetBanker(banker);
    }

    banker->WhoesPlaying();

    bool gameOver = false;
    int turn = 0;

    while (!gameOver)
    {
        Player * playerThisTurn = banker->GetActivePlayerForTurn(turn);

        int position = playerThisTurn->GetPosition();
        string space = gameBoard[position]->GetName();

        cout << "=================================\n";
        cout << playerThisTurn->GetName() << " You are currently on " << space << endl;
        playerThisTurn->PrintBoardPosition();
        playerThisTurn->OutputPlayerStats();
        cout << "==> Enter r to roll dice." << endl;

        string input;
        cin >> input;

        int spacesToMove = 0;

        if (input.compare("r") == 0)
        {
          spacesToMove = playerThisTurn->RollDice();

          position = playerThisTurn->AdvancePlayer(spacesToMove);

          playerThisTurn->PrintBoardPosition();

          space = gameBoard[position]->GetName();

          cout << "=============================================\n\n";

          cout << " You landed on " << space << endl << endl;

          cout << "=============================================\n\n";

          gameBoard[position]->HandlePlayerVisit(playerThisTurn);
        }

        playerThisTurn->OutputPlayerStats();
        cout << "Your turn is finished, enter f" << endl;
        string done;
        cin >> done;

        if (done.compare("f") != 0)
        {
          cout << "Game Over" << endl;
          gameOver = true;
        }

        turn = (turn + 1) % banker->GetNumActivePlayers();
    }

    return 0;
}
