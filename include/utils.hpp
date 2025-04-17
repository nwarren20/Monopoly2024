# pragma once
#include <string>
#include <vector>

using namespace std;

class Property;
class RailRoad;
class BoardSpace;
class CardDeck;

class MonopolyUtils
{
  public:
    static void OutputMessage(string message, int delay);

    static void CreateDarkPurpleGroup(vector<Property *> & group);

    static void CreateLightBlueGroup(vector<Property *> & group);

    static void CreatePurpleGroup(vector<Property *> & group);

    static void CreateOrangeGroup(vector<Property *> & group);

    static void CreateRedGroup(vector<Property *> & group);

    static void CreateYellowGroup(vector<Property *> & group);

    static void CreateGreenGroup(vector<Property *> & group);

    static void CreateBlueGroup(vector<Property *> & group);

    static void CreateRailRoadGroup(vector<RailRoad *> & group);

    static void LoadBoard(vector<BoardSpace *> & gameBoard, CardDeck * cardDeck);

    static void PringWelcomeMessage();
};

