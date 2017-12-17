extern "C"
{
#include "log_ffmpeg.h"
}
#include "log_qt.h"

void log_pipe_external()
{
	log_connect_ffmpeg_to_log();
	log_connect_qt_to_log();
}

void log_pipe_to_window() { log_connect_log_to_debug_window(); }
