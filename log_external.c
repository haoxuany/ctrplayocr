#include "config.h"
#include "log.h"
#include "log_external.h"

#include <stdio.h>
#include <stdarg.h>
#include <libavutil/avutil.h>

char log_buffer[LOG_BUFFER_SIZE];
int print_prefix = 1;

// FIXME: haoxuany - ffmpeg says this must be threadsafe
// it needs to be anyway due to log_buffer
void ffmpeg_to_log(void *avcl, int level, const char *fmt, va_list vl)
{
	if (level == AV_LOG_QUIET) return;

	av_log_format_line(avcl, AV_LOG_INFO, fmt, vl,
			log_buffer, LOG_BUFFER_SIZE, &print_prefix);

	log_level lv;
	switch (level)
	{
		case AV_LOG_PANIC:
		case AV_LOG_FATAL:
			lv = log_level_fatal;
			break;
		case AV_LOG_ERROR:
			lv = log_level_error;
			break;
		case AV_LOG_WARNING:
			lv = log_level_warning;
			break;
		case AV_LOG_INFO:
			lv = log_level_info;
			break;
		case AV_LOG_VERBOSE:
		case AV_LOG_DEBUG:
		case AV_LOG_TRACE:
			lv = log_level_debug;
			break;
		default:
			// shouldn't happen, but if it does, prompt to stderr.
			// Do NOT recursive call. This is just asking for trouble.
			// Just briefly warn and escape.
			lv = log_level_warning;
			fprintf(stderr, "Unknown AV_LOG_LEVEL: %d, updated API?\n",
					level);
			break;
	}

	log_vwrap(NULL, -1, lv, fmt, vl);
}

void log_connect_ffmpeg_to_log() { av_log_set_callback(ffmpeg_to_log); }
