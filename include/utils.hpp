# pragma once
#include <string>
#include <vector>

using namespace std;

class Property;
class RailRoad;
class BoardSpace;
class CardDeck;

namespace Houses
{
    static const vector< pair<string, int> > ColorGroupPerHousePrice = {
      { "DarkPurple", 50 },
      { "LightBlue" , 50 },
      { "Purple", 100 },
      { "Orange", 100 },
      { "Red", 150 },
      { "Yellow", 150 },
      { "Green", 200 },
      { "Blue", 200 }
    };

  static const vector< pair<string, int> > ColorGroupMaxHouseCount = {
      { "DarkPurple", 10 },
      { "LightBlue" , 15 },
      { "Purple", 15 },
      { "Orange", 15 },
      { "Red", 15 },
      { "Yellow", 15 },
      { "Green", 15 },
      { "Blue", 10 }
    };

   int GetMaxHousesForGroup(string group);

   int GetHousePriceForGroup(string group);
} // namespace Houses




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

