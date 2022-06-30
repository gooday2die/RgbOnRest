//
// @file : Misc.cpp
// @author : Gooday2die (Isu Kim) @ dev.gooday2die@gmail.com
// @brief : A file that implements all member functions for class Misc
//

#include "Misc.h"


wstring Misc::convertWstring(string argString) {
    wstring newString = wstring(argString.begin(), argString.end());
    return newString;
}