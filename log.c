#include "config.h"
#include "log.h"

#include <stdio.h>
#include <string.h>
#include <time.h>

void default_logger(const log_level level, const char *msg);

char log_buffer[LOG_BUFFER_SIZE];
logger *current_logger = default_logger;

typedef struct log_level_info_map
{
	log_level level;
	FILE *handle;
	const char *header;
	const char *footer;
} log_level_info_map;

#define COLOR_GREEN   "\x1B[32m"
#define COLOR_RED   "\x1B[31m"
#define COLOR_YELLOW   "\x1B[33m"
#define COLOR_RESET "\x1B[0m"

void default_logger(const log_level level, const char *msg)
{
	const log_level_info_map info_map[] =
	{
		{ log_level_debug, stdout, COLOR_GREEN "[DEBUG]", COLOR_RESET },
		{ log_level_info, stdout, "[INFO]", "" },
		{ log_level_warning, stderr, COLOR_YELLOW "[WARNING]", COLOR_RESET },
		{ log_level_error, stderr, COLOR_RED "[ERROR]", COLOR_RESET },
		{ log_level_fatal, stderr, COLOR_RED "[FATAL]", "" },
	};
	const int info_map_n =
		sizeof(info_map) / sizeof(log_level_info_map);

	for (int i = 0;i < info_map_n;i++)
		if (info_map[i].level == level)
		{
			const log_level_info_map *info = info_map + i;
			fprintf(info->handle, "%s %s%s\n",
					info->header, msg, info->footer);
			break;
		}
}

void log_set(logger l) { current_logger = l; }

int min(int a, int b) { return a < b ? a : b; }

// haoxuany - this has the potential to be slow
// but shouldn't be critical enough to cause a problem
void log_vwrap(
		const char * const filename,
		const int line,
		const log_level level,
		const char *format,
		va_list args)
{
	int len = LOG_BUFFER_SIZE;
	char *buffer = log_buffer;
	int copy_len;

	time_t now = time(NULL);
	copy_len = strftime(buffer, len, "%X - ", localtime(&now));
	len -= copy_len; buffer += copy_len;

	copy_len = min(strlen(filename), len - 1);
	memcpy(buffer, filename, copy_len);
	len -= copy_len; buffer += copy_len;

	snprintf(buffer, len, ":%d: ", line);
	copy_len = strlen(buffer);
	len -= copy_len; buffer += copy_len;

	vsnprintf(buffer, len, format, args);

	current_logger(level, log_buffer);
}

void log_wrap(
		const char * const filename,
		const int line,
		const log_level level,
		const char * format,
		...)
{
	va_list args;
	va_start(args, format);
	log_vwrap(filename, line, level, format, args);
	va_end(args);
}
