/**
 *  clog.cpp
 *  Console logging.
 *
 *  @author Nathan Campos <nathanpc@dreamintech.net>
 */

#include <iostream>
#include <string>

#include "clog.h"

using namespace std;

void Log::Error(string message) {
	cout << "[ERROR] " << message << endl;
}
