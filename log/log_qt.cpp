extern "C"
{
#include "config.h"
#include "log.h"
}

#include <cstdarg>
#include <cstdlib>
#include <QApplication>
#include <QWidget>
#include <QListWidget>

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
	log_wrap(context.file, context.line, context.function,
			lv, "%s", ba.data());
}

void log_connect_qt_to_log() { qInstallMessageHandler(qt_to_log); }

QListWidget *log_list;
bool register_exit = false;

void qt_logger(const log_level level, const char *msg)
{
	QListWidgetItem *item = new QListWidgetItem(msg);
	QBrush brush;
	switch (level)
	{
		case log_level_info:
			brush = Qt::black;
			break;
		case log_level_debug:
			brush = Qt::blue;
			break;
		case log_level_warning:
			brush = Qt::darkYellow;
			break;
		case log_level_error:
		case log_level_fatal:
			brush = Qt::red;
			break;
	}
	item->setForeground(brush);

	log_list->addItem(item);
}

void remove_debug_log_window() { if (log_list) delete log_list; }

void log_connect_log_to_debug_window()
{
	remove_debug_log_window();
	if (!register_exit)
	{
		if (std::atexit(remove_debug_log_window))
			log_w("Unable to register debug log ui free on exit,"
					" potential memleak");
		register_exit = true;
	}

	log_list = new QListWidget(NULL);
	log_list->setWordWrap(true);
	log_list->show();

	log_set(qt_logger);
}
