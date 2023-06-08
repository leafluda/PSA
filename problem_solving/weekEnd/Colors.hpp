#pragma once
#include <iostream>
#include <string>
#include <conio.h>
#include <windows.h>
#include <sstream>
#include <vector>
#include <thread>
#include <chrono>
#include "Colors.hpp"
#include <variant>

#define TextBlack "\033[30m"
#define TextRed "\033[31m"
#define TextGreen "\033[32m"
#define TextYellow "\033[33m"
#define TextBlue "\033[34m"
#define TextPink "\033[35m"
#define TextMint "\033[36m"
#define TextLgray "\033[37m"
#define TextGray "\033[90m"
#define TextLred "\033[91m"
#define TextLgreen "\033[92m"
#define TextLyellow "\033[93m"
#define TextLblue "\033[94m"
#define TextLpink "\033[95m"
#define TextLmint "\033[96m"
#define TextWhite "\033[97m"

#define BgBlack "\033[40m"
#define BgRed "\033[41m"
#define BgGreen "\033[42m"
#define BgYellow "\033[43m"
#define BgBlue "\033[44m"
#define BgPink "\033[45m"
#define BgMint "\033[46m"
#define BgLgray "\033[47m"
#define BgGray "\033[100m"
#define BgLred "\033[101m"
#define BgLgreen "\033[102m"
#define BgLyellow "\033[103m"
#define BgLblue "\033[104m"
#define BgLpink "\033[105m"
#define BgLmint "\033[106m"
#define BgWhite "\033[107m"

#define Black TextBlack BgBlack
#define Red TextRed BgRed
#define Green TextGreen BgGreen
#define Yellow TextYellow BgYellow
#define Blue TextBlue BgBlue
#define Pink TextPink BgPink
#define Mint TextMint BgMint
#define Lgray TextLgray BgLgray
#define Gray TextGray BgGray
#define Lred TextLred BgLred
#define Lgreen TextLgreen BgLgreen
#define Lyellow TextLyellow BgLyellow
#define Lblue TextLblue BgLblue
#define Lpink TextLpink BgLpink
#define Lmint TextLmint BgLmint 
#define White TextWhite BgWhite
#define Text TextBlack BgWhite

#define Reset "\033[0m"
