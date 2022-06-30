//
// @file : Misc.cpp
// @author : Gooday2die (Isu Kim) @ dev.gooday2die@gmail.com
// @brief : A file that implements all member functions for class Misc
//

#include "Misc.h"


/**
 * A member function for class Misc that converts std::string object to std::wstring object.
 * @param argString the std::string object to transform into std::wstring
 * @return returns std::wstring that represents converted string.
 */
wstring Misc::convertWstring(string argString) {
    wstring newString = wstring(argString.begin(), argString.end());
    return newString;
}
