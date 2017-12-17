extern "C"
{
#include "config.h"
#include "log.h"
}

#include <cstdarg>
#include <QApplication>

void qt_to_log(QtMsgType type,
		const QMessageLogContext &context,
		const QString &msg)
{
	log_level lv;
	switch (type)
	{
		case QtDebugMsg:
			lv = log_level_debug;
			break;
		case QtInfoMsg:
			lv = log_level_info;
			break;
		case QtWarningMsg:
			lv = log_level_warning;
			break;
		case QtCriticalMsg:
		case QtFatalMsg:
			lv = log_level_fatal;
			break;
		default:
			// shouldn't happen, but if it does, prompt to stderr.
			// Do NOT recursive call. This is just asking for trouble.
			// Just briefly warn and escape.
			lv = log_level_warning;
			std::fprintf(stderr,
					"Unknown QtMsgType: %d, updated API?\n",
					type);
			break;
	}

	QByteArray ba = msg.toLocal8Bit();
	log_wrap(context.file, context.line, lv, "%s", ba.data());
}

void log_connect_qt_to_log() { qInstallMessageHandler(qt_to_log); }
