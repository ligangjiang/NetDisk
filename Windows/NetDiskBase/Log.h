#pragma once
#include <time.h>
#include <Windows.h>

#undef ERROR

enum LOG_LEVEL {
  DEBUG,
  INFO,
  WARNING,
  ERROR,
  FATAL,
  TRANSACTION,
};

class Log{
private:
  static time_t start_time_;

#ifdef WIN32
  static HANDLE console_handle;
#endif //WIN32

public:
  static void LogMessage(LOG_LEVEL level, char* file_path, long line_number, char* function_name, char* format, ...);
};

#define LOG0(level, format) Log::LogMessage(level, __FILE__,  __LINE__, __FUNCTION__, format)
#define LOG1(level, format, arg1) Log::LogMessage(level, __FILE__,  __LINE__, __FUNCTION__, format, arg1)
#define LOG2(level, format, arg1, arg2) Log::LogMessage(level, __FILE__,  __LINE__, __FUNCTION__, format, arg1, arg2)
#define LOG3(level, format, arg1, arg2, arg3) Log::LogMessage(level, __FILE__,  __LINE__, __FUNCTION__, format, arg1, arg2, arg3)
#define LOG4(level, format, arg1, arg2, arg3, arg4) Log::LogMessage(level, __FILE__,  __LINE__, __FUNCTION__, format, arg1, arg2, arg3, arg4)
#define LOG5(level, format, arg1, arg2, arg3, arg4, arg5) Log::LogMessage(level, __FILE__,  __LINE__, __FUNCTION__, format, arg1, arg2, arg3, arg4, arg5)
#define LOG6(level, format, arg1, arg2, arg3, arg4, arg5, arg6) Log::LogMessage(level, __FILE__,  __LINE__, __FUNCTION__, format, arg1, arg2, arg3, arg4, arg5, arg6)

#ifdef _DEBUG
  #define ASSERT(x) (void)((!!(x)) || (LOG1(FATAL, "Assertion failed: %s.", #x), throw, 0))
#else
  #define ASSERT(x) ((void)0)
#endif