#include "../include/utils.hpp"
#include <iostream>
#include <thread>
#include <chrono>
#include "../include/boardspace.hpp"
#include "../include/rents.hpp"

using namespace std;
//using namespace MonopolyUtils;

namespace Houses
{

    int GetHousePriceForGroup(string group)
    {
        for (auto pair : ColorGroupPerHousePrice)
        {
            if (pair.first.compare(group) == 0)
            {
                return pair.second;
            }
        }

        return 0;
    }

    int GetMaxHousesForGroup(string group)
    {
        for (auto pair : ColorGroupMaxHouseCount)
        {
            if (pair.first.compare(group) == 0)
            {
                return pair.second;
            }
        }

        return 0;
    }

}



    void MonopolyUtils::OutputMessage(string message, int delay)
    {
        cout << "===================================================================\n\n";

        cout << message << endl << endl;

        cout << "===================================================================\n\n";

        std::this_thread::sleep_for(std::chrono::milliseconds(delay));
    }

    void MonopolyUtils::CreateDarkPurpleGroup(vector<Property *> & group)
    {
        Property * Mediteranean = new Property("Mediteranean Avenue", 1, "DarkPurple", 60, Rents::meditereanRents);
        Property * Baltic = new Property("Baltic Avenue", 3, "DarkPurple", 60, Rents::balticRents);
        group.push_back(Mediteranean);
        group.push_back(Baltic);
        Mediteranean->SetGroup(group);
        Baltic->SetGroup(group);
    }
    
    void MonopolyUtils::CreateLightBlueGroup(vector<Property *> & group)
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
    
    void MonopolyUtils::CreatePurpleGroup(vector<Property *> & group)
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
    
    void MonopolyUtils::CreateOrangeGroup(vector<Property *> & group)
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
    
    void MonopolyUtils::CreateRedGroup(vector<Property *> & group)
    {
        Property * Kentucky = new Property("Kentucky Avenue", 21, "Red", 220, Rents::kentuckyRents);
        Property * Indiana = new Property("Indiana Avenue", 23, "Red", 220, Rents::indianRents);
        Property * Illinois = new Property("Illinois Avenue", 24, "Red", 240, Rents::illinoisRents);
    
        group.push_back(Kentucky);
        group.push_back(Indiana);
        group.push_back(Illinois);
    
        Kentucky->SetGroup(group);
        Indiana->SetGroup(group);
        Illinois->SetGroup(group);
    }
    
    void MonopolyUtils::CreateYellowGroup(vector<Property *> & group)
    {
        Property * Atlantic = new Property("Atlantic Avenue", 26, "Yellow", 260, Rents::atlanticRents);
        Property * Ventnor = new Property("Ventnor Avenue", 27, "Yellow", 260, Rents::ventnorRents);
        Property * MarvinGardens = new Property("Marvin Gardens", 29, "Yellow", 280, Rents::marvinGardensRents);
    
        group.push_back(Atlantic);
        group.push_back(Ventnor);
        group.push_back(MarvinGardens);
    
        Atlantic->SetGroup(group);
        Ventnor->SetGroup(group);
        MarvinGardens->SetGroup(group);
    }
    
    void MonopolyUtils::CreateGreenGroup(vector<Property *> & group)
    {
        Property * Pacific = new Property("Pacific Avenue", 31, "Green", 300, Rents::pacificRents);
        Property * NC = new Property("North Carolina Avenue", 32, "Green", 300, Rents::northcarolinaRents);
        Property * Penn = new Property("Pennsylvania Avenue", 34, "Green", 320, Rents::pennsylvaniaRents);
    
        group.push_back(Pacific);
        group.push_back(NC);
        group.push_back(Penn);
    
        Pacific->SetGroup(group);
        NC->SetGroup(group);
        Penn->SetGroup(group);
    }
    
    void MonopolyUtils::CreateBlueGroup(vector<Property *> & group)
    {
        Property * ParkPlace = new Property("Park Place", 37, "Blue", 350, Rents::parkPlaceRents);
        Property * Boardwalk = new Property("Boardwalk", 39, "Blue", 400, Rents::boardwalkRents);
    
        group.push_back(ParkPlace);
        group.push_back(Boardwalk);
    
        ParkPlace->SetGroup(group);
        Boardwalk->SetGroup(group);
    }
    
    void MonopolyUtils::CreateRailRoadGroup(vector<RailRoad *> & group)
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

    void MonopolyUtils::CreateUtilityGroup(vector<Utility *> & group)
    {
        Utility * electric = new Utility("Electric Company", 12);
        Utility * water = new Utility("Water Works", 28);
        
        group.push_back( electric );
        group.push_back( water );

        electric->SetGroup(group);
        water->SetGroup(group);
    }
    
    void MonopolyUtils::LoadBoard(vector<BoardSpace *> & gameBoard, CardDeck * cardDeck)
    {
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

        std::vector<Utility *> utilityGroup;
        CreateUtilityGroup(utilityGroup);
        
        gameBoard.push_back( new FreeSpace("Go", 0, 200) );
        gameBoard.push_back( darkPurpleGroup[0] );
        gameBoard.push_back( new TakeCard("Community Chest", 2, cardDeck) );
        gameBoard.push_back( darkPurpleGroup[1] );
        gameBoard.push_back( new Tax("Income Tax", 4, 200) );
        gameBoard.push_back( railRoadGroup[0] );
        gameBoard.push_back( lightBlueGroup[0] );
        gameBoard.push_back( new TakeCard("Chance", 7, cardDeck) );
        gameBoard.push_back( lightBlueGroup[1] );
        gameBoard.push_back( lightBlueGroup[2] );
    
        gameBoard.push_back( new Jail("Jail/JustVisiting", 10) );
        gameBoard.push_back( purpleGroup[0] );
        gameBoard.push_back( utilityGroup[0] );
        gameBoard.push_back( purpleGroup[1] );
        gameBoard.push_back( purpleGroup[2] );
        gameBoard.push_back( railRoadGroup[1] );
        gameBoard.push_back( orangeGroup[0] );
        gameBoard.push_back( new TakeCard("Community Chest", 17, cardDeck) );
        gameBoard.push_back( orangeGroup[1] );
        gameBoard.push_back( orangeGroup[2] );
    
        gameBoard.push_back( new FreeSpace("Free Parking", 20, 0) );
        gameBoard.push_back( redGroup[0] );
        gameBoard.push_back( new TakeCard("Chance", 22, cardDeck) );
        gameBoard.push_back( redGroup[1] );
        gameBoard.push_back( redGroup[2] );
        gameBoard.push_back( railRoadGroup[2] );
        gameBoard.push_back( yellowGroup[0] );
        gameBoard.push_back( yellowGroup[1] );
        gameBoard.push_back( utilityGroup[1] );
        gameBoard.push_back( yellowGroup[2] );
    
        gameBoard.push_back( new Jail("Go to Jail", 30) );
        gameBoard.push_back( greenGroup[0] );
        gameBoard.push_back( greenGroup[1] );
        gameBoard.push_back( new TakeCard("Community Chest", 33, cardDeck) );
        gameBoard.push_back( greenGroup[2] );
        gameBoard.push_back( railRoadGroup[3] );
        gameBoard.push_back( new TakeCard("Chance", 36, cardDeck) );
        gameBoard.push_back( blueGroup[0] );
        gameBoard.push_back( new Tax("Luxury Tax", 38, 75) );
        gameBoard.push_back( blueGroup[1] );
    }

    void MonopolyUtils::PringWelcomeMessage()
    {
        cout << 
        "____________________________________________________________________________________________________________________________________________________" << endl <<
        "|                                                                                                                                                  |" << endl <<
        "|       M             M             OOOOOO        N           NNN        OOOOOO        PPPPPPPPPP           OOOOOO        LLL        YYY       YYY |" << endl <<
        "|      MMM           MMM         OOOOOOOOOOOO     NNN         NNN     OOOOOOOOOOOO     PPPPPPPPPPPP      OOOOOOOOOOOO     LLL         YYY     YYY  |" << endl <<
        "|     MMMMM         MMMMM      OOOO        OOOO   NNNNN       NNN   OOOO        OOOO   PPP      PPPP   OOOO        OOOO   LLL          YYY   YYY   |" << endl <<
        "|     MMMMMM       MMMMMM     OOO            OOO  NNN NNN     NNN  OOO            OOO  PPP      PPPP  OOO            OOO  LLL           YYY YYY    |" << endl <<
        "|    MMM  MMM     MMM  MMM   OOO              OOO NNN   NNN   NNN OOO              OOO PPPPPPPPPPPP  OOO              OOO LLL            YYYYY     |" << endl <<
        "|    MMM   MMM   MMM   MMM   OOO              OOO NNN     NNN NNN OOO              OOO PPPPPPPPPP    OOO              OOO LLL             YYY      |" << endl <<
        "|   MMM     MMM MMM     MMM   OOO            OOO  NNN       NNNNN  OOO            OOO  PPP            OOO            OOO  LLL            YYY       |" << endl <<
        "|   MMM      MMMMM      MMM    OOOO        OOOO   NNN         NNN   OOOO        OOOO   PPP             OOOO        OOOO   LLL           YYY        |" << endl <<
        "|  MMM        MMM        MMM     OOOOOOOOOOOO     NNN          NN     OOOOOOOOOOOO     PPP               OOOOOOOOOOOO     LLLLLLLLLLL  YYY         |" << endl <<
        "|  MMM         M         MMM        OOOOOO        NNN           N        OOOOOO        PPP                  OOOOOO        LLLLLLLLLLL YYY          |" << endl <<
        "|                                                                                                                                                  |" << endl <<
        "|__________________________________________________________________________________________________________________________________________________|" << endl << endl;


    }
