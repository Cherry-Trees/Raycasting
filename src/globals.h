#pragma once
#include <string>

const int MAP_WIDTH = 20;
const int MAP_HEIGHT = 20;

const int WINDOW_CELL_SIZE = 64;
const int CELL_SIZE = 8;

const int WINDOW_WIDTH = 1920;
const int WINDOW_HEIGHT = 1080;

std::string map[MAP_HEIGHT] =
{
    "####################", // 0
    "###++++++++++++++++#", // 1
    "###++++++++++++++++#", // 2
    "####++###########++#", // 3
    "####++#########++++#", // 4
    "####++###++++++++++#", // 5
    "#+++++++#######++###", // 6
    "#+##++++++#####++###", // 7
    "#+####++++++++#++###", // 8
    "#+###+++++++++#++###", // 9
    "#+++++++++++++#++###", // 10
    "##++++#++++++##++###", // 11
    "##++++#########++###", // 12
    "#++++++++++++++++###", // 13
    "#++#+++++++++++++###", // 14
    "#++#####++##########", // 15
    "#++#####++##########", // 16
    "#++++++++++++++++++#", // 17
    "#++++++++++++++++++#", // 18
    "####################"  // 19
};
