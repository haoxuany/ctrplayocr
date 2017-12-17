#pragma once

void log_pipe_external();

// This must happen after QApplication due to use of ui
void log_pipe_to_window();
