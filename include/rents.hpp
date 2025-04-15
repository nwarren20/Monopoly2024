# pragma once

#include <vector>
#include <iostream>

using namespace std;

namespace Rents
{
    static vector<int> meditereanRents = { 2, 10, 30, 90, 160, 250 };
    static vector<int> balticRents = { 4, 20, 60, 180, 320, 450 };
    static vector<int> orientalRents = { 6, 30, 90, 270, 400, 550 };
    static vector<int> vermontRents = { 6, 30, 90, 270, 400, 550 };
    static vector<int> connecticutRents = { 8, 40, 100, 300, 450, 600 };
    static vector<int> stCharlesRents = { 10, 50, 150, 400, 625, 750 };
    static vector<int> statesRents = { 10, 50, 150, 400, 625, 750 };
    static vector<int> virginiaRents = { 12, 60, 180, 500, 700, 900 };
    static vector<int> stJamesRents = { 14, 70, 200, 550, 750, 950 };
    static vector<int> tennesseeRents = { 14, 70, 200, 550, 750, 950 };
    static vector<int> newYorkRents = { 16, 80, 220, 600, 800, 1000 };
    static vector<int> kentuckyRents = { 18, 90, 250, 700, 875, 1050 };
    static vector<int> indianRents = { 18, 90, 250, 700, 875, 1050 };
    static vector<int> illinoisRents = { 20, 100, 300, 925, 1100 };
    static vector<int> atlanticRents = { 22, 110, 330, 800, 975, 1150 };
    static vector<int> ventnorRents = { 22, 110, 330, 800, 975, 1150 };
    static vector<int> marvinGardensRents = { 24, 120, 360, 850, 1125, 1200 };
    static vector<int> pacificRents = { 26, 130, 390, 900, 1100, 1275 };
    static vector<int> northcarolinaRents = { 26, 130, 390, 900, 1100, 1275 };
    static vector<int> pennsylvaniaRents = { 28, 150, 450, 1000, 1200, 1400 };
    static vector<int> parkPlaceRents = { 35, 175, 500, 1100, 1300, 1500 };
    static vector<int> boardwalkRents = { 50, 200, 600, 1400, 1700, 2000 };


    static void LoadRents()
    {
        cout << "LoadRents" << endl;
        meditereanRents.push_back(2);
        meditereanRents.push_back(10);
        meditereanRents.push_back(30);
        meditereanRents.push_back(90);
        meditereanRents.push_back(160);
        meditereanRents.push_back(250);

        balticRents.push_back(4);
        balticRents.push_back(20);
        balticRents.push_back(60);
        balticRents.push_back(180);
        balticRents.push_back(320);
        balticRents.push_back(450);

        orientalRents.push_back(6);
        orientalRents.push_back(30);
        orientalRents.push_back(90);
        orientalRents.push_back(270);
        orientalRents.push_back(400);
        orientalRents.push_back(550);

        vermontRents.push_back(6);
        vermontRents.push_back(30);
        vermontRents.push_back(90);
        vermontRents.push_back(270);
        vermontRents.push_back(400);
        vermontRents.push_back(550);

        connecticutRents.push_back(8);
        connecticutRents.push_back(40);
        connecticutRents.push_back(100);
        connecticutRents.push_back(300);
        connecticutRents.push_back(450);
        connecticutRents.push_back(600);

        stCharlesRents.push_back(10);
        stCharlesRents.push_back(50);
        stCharlesRents.push_back(150);
        stCharlesRents.push_back(450);
        stCharlesRents.push_back(625);
        stCharlesRents.push_back(750);

        statesRents.push_back(10);
        statesRents.push_back(50);
        statesRents.push_back(150);
        statesRents.push_back(450);
        statesRents.push_back(625);
        statesRents.push_back(750);

        virginiaRents.push_back(12);
        virginiaRents.push_back(60);
        virginiaRents.push_back(180);
        virginiaRents.push_back(500);
        virginiaRents.push_back(700);
        virginiaRents.push_back(900);

        stJamesRents.push_back(14);
        stJamesRents.push_back(70);
        stJamesRents.push_back(200);
        stJamesRents.push_back(550);
        stJamesRents.push_back(750);
        stJamesRents.push_back(950);

        tennesseeRents.push_back(14);
        tennesseeRents.push_back(70);
        tennesseeRents.push_back(200);
        tennesseeRents.push_back(550);
        tennesseeRents.push_back(750);
        tennesseeRents.push_back(950);

        newYorkRents.push_back(16);
        newYorkRents.push_back(80);
        newYorkRents.push_back(220);
        newYorkRents.push_back(600);
        newYorkRents.push_back(800);
        newYorkRents.push_back(1000);

        kentuckyRents.push_back(18);
        kentuckyRents.push_back(90);
        kentuckyRents.push_back(250);
        kentuckyRents.push_back(700);
        kentuckyRents.push_back(875);
        kentuckyRents.push_back(1050);

        indianRents.push_back(18);
        indianRents.push_back(90);
        indianRents.push_back(250);
        indianRents.push_back(700);
        indianRents.push_back(875);
        indianRents.push_back(1050);

        illinoisRents.push_back(20);
        illinoisRents.push_back(100);
        illinoisRents.push_back(300);
        illinoisRents.push_back(750);
        illinoisRents.push_back(925);
        illinoisRents.push_back(1100);

        atlanticRents.push_back(22);
        atlanticRents.push_back(110);
        atlanticRents.push_back(330);
        atlanticRents.push_back(800);
        atlanticRents.push_back(975);
        atlanticRents.push_back(1150);

        ventnorRents.push_back(22);
        ventnorRents.push_back(110);
        ventnorRents.push_back(330);
        ventnorRents.push_back(800);
        ventnorRents.push_back(975);
        ventnorRents.push_back(1150);

        marvinGardensRents.push_back(24);
        marvinGardensRents.push_back(120);
        marvinGardensRents.push_back(360);
        marvinGardensRents.push_back(850);
        marvinGardensRents.push_back(1025);
        marvinGardensRents.push_back(1200);

        pacificRents.push_back(26);
        pacificRents.push_back(130);
        pacificRents.push_back(390);
        pacificRents.push_back(900);
        pacificRents.push_back(1100);
        pacificRents.push_back(1275);

        northcarolinaRents.push_back(26);
        northcarolinaRents.push_back(130);
        northcarolinaRents.push_back(390);
        northcarolinaRents.push_back(900);
        northcarolinaRents.push_back(1100);
        northcarolinaRents.push_back(1275);

        pennsylvaniaRents.push_back(28);
        pennsylvaniaRents.push_back(150);
        pennsylvaniaRents.push_back(450);
        pennsylvaniaRents.push_back(1000);
        pennsylvaniaRents.push_back(1200);
        pennsylvaniaRents.push_back(1400);

        parkPlaceRents.push_back(35);
        parkPlaceRents.push_back(175);
        parkPlaceRents.push_back(500);
        parkPlaceRents.push_back(1100);
        parkPlaceRents.push_back(1300);
        parkPlaceRents.push_back(1500);

        boardwalkRents.push_back(50);
        boardwalkRents.push_back(200);
        boardwalkRents.push_back(600);
        boardwalkRents.push_back(1400);
        boardwalkRents.push_back(1700);
        boardwalkRents.push_back(2000);

    }
    

}
