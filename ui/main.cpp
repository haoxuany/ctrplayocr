extern "C"
{
#include "log.h"
}
#include "log_external.h"

#include <QApplication>


int main(int argc, char *argv[])
{
	log_pipe_external();

	QApplication app(argc, argv);

	log_pipe_to_window();

	return app.exec();
}
