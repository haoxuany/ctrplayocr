#pragma once
#include <stdarg.h>

// macros to actually use
#define log_d(format, ...) \
	(log_wrap(__FILE__, __LINE__, \
			log_level_debug, \
			format, ##__VA_ARGS__))

#define log_i(format, ...) \
	(log_wrap(__FILE__, __LINE__, \
			log_level_info, \
			format, ##__VA_ARGS__))

#define log_w(format, ...) \
	(log_wrap(__FILE__, __LINE__, \
			log_level_warning, \
			format, ##__VA_ARGS__))

#define log_e(format, ...) \
	(log_wrap(__FILE__, __LINE__, \
			log_level_error, \
			format, ##__VA_ARGS__))

#define log_f(format, ...) \
	(log_wrap(__FILE__, __LINE__, \
			log_level_fatal, \
			format, ##__VA_ARGS__))

// setting logs only
typedef enum log_level
{
	log_level_debug,
	log_level_info,
	log_level_warning,
	log_level_error,
	log_level_fatal,
} log_level;

typedef void logger(const log_level level, const char *msg);
logger default_logger;

void log_set(logger l);

// wrappers for everything, do not use directly
void log_wrap(
		const char * const filename,
		const int line,
		const log_level level,
		const char *format,
		...);

void log_vwrap(
		const char * const filename,
		const int line,
		const log_level level,
		const char *format,
		va_list args);
