/**
 *  clog.h
 *  Console logging.
 *
 *  @author Nathan Campos <nathanpc@dreamintech.net>
 */

#ifndef _CLOG_H_
#define _CLOG_H_

#include <string>

class Log {
  public:
	static void Error(std::string message);
};

#endif
