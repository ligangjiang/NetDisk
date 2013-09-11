#include "stdafx.h"
#include "Log.h"

time_t Log::start_time_ = time(NULL) - clock() / CLOCKS_PER_SEC;

#ifdef WIN32
HANDLE Log::console_handle = GetStdHandle(STD_OUTPUT_HANDLE);
#endif //WIN32

void Log::LogMessage(LOG_LEVEL level, char* file_path, long line_number, char* function_name, char* format, ...) {
#ifndef _DEBUG
  if (level < INFO) return;
#endif

#ifdef WIN32
  UINT16 text_color = FOREGROUND_BLUE | FOREGROUND_GREEN | FOREGROUND_RED;
  if (level == DEBUG) text_color = FOREGROUND_INTENSITY;
  else if (level == INFO) text_color = FOREGROUND_BLUE | FOREGROUND_GREEN | FOREGROUND_RED;
  else if (level == WARNING) text_color = FOREGROUND_GREEN | FOREGROUND_RED;
  else if (level == ERROR || level == FATAL) text_color = FOREGROUND_RED;
  else if (level == TRANSACTION) text_color = FOREGROUND_RED | FOREGROUND_INTENSITY;

  SetConsoleTextAttribute(console_handle, text_color);
#endif //WIN32

#ifdef _DEBUG
  clock_t current_clock = clock();
  time_t current_time = start_time_ + current_clock / CLOCKS_PER_SEC;
  struct tm * time_info = localtime(&current_time);

  char* file_name = file_path + strlen(file_path);
  while (file_name > file_path && file_name[-1] != '\\') file_name--;

  printf("\n%02d:%02d:%02d.%03d %s:%d %s(): ", time_info->tm_hour, time_info->tm_min, time_info->tm_sec,
    (current_clock % CLOCKS_PER_SEC) * 1000 / CLOCKS_PER_SEC, file_name, line_number, function_name);
#else
  printf("\n");
#endif

  va_list args;
  va_start(args, format);
  vprintf(format, args);
  va_end(args);

#ifdef WIN32
  SetConsoleTextAttribute(console_handle, FOREGROUND_INTENSITY|FOREGROUND_BLUE | FOREGROUND_GREEN | FOREGROUND_RED);
#endif
}

