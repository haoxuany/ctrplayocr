extern "C"
{
#include "log.h"
#include "log_ffmpeg.h"
}
#include "log_qt.h"

#include <QApplication>


int main(int argc, char *argv[])
{
	log_connect_ffmpeg_to_log();
	log_connect_qt_to_log();

	QApplication app(argc, argv);

	return app.exec();
}
