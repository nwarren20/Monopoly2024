# pragma once
#include <string>
#include <vector>

using namespace std;

class Property;
class RailRoad;
class Utility;
class BoardSpace;
class CardDeck;

namespace Houses
{
    static const int MAX_HOUSE_INVENTORY = 32;
    static const int MAX_HOTEL_INVENTORY = 12;
    static const int MAX_HOUSE_PER_PROPERTY = 4;
    static const int MAX_HOTELS_PER_PROPERTY = 1;

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
      { "DarkPurple", 8 },
      { "LightBlue" , 12 },
      { "Purple", 12 },
      { "Orange", 12 },
      { "Red", 12 },
      { "Yellow", 12 },
      { "Green", 12 },
      { "Blue", 8 }
    };

   int GetMaxHousesForGroup(string group);

   int GetHousePriceForGroup(string group);
} // namespace Houses




class MonopolyUtils
{
  public:
    static void OutputMessage(string message, int delay);

    static int GetValidInput(const int init, const int min, const int max);

    static string GetValidInput(const string init, vector<string> options);

    static void CreateDarkPurpleGroup(vector<Property *> & group);

    static void CreateLightBlueGroup(vector<Property *> & group);

    static void CreatePurpleGroup(vector<Property *> & group);

    static void CreateOrangeGroup(vector<Property *> & group);

    static void CreateRedGroup(vector<Property *> & group);

    static void CreateYellowGroup(vector<Property *> & group);

    static void CreateGreenGroup(vector<Property *> & group);

    static void CreateBlueGroup(vector<Property *> & group);

    static void CreateRailRoadGroup(vector<RailRoad *> & group);

    static void CreateUtilityGroup(vector<Utility *> & group);

    static void LoadBoard(vector<BoardSpace *> & gameBoard, CardDeck * cardDeck);

    static void PringWelcomeMessage();
};

