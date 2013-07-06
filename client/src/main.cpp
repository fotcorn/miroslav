#include <QApplication>

#include <QTranslator>

#include "mainwindow.h"

//#include "nomultistart.h"

int main(int argc, char *argv[]) {
	
	QApplication app(argc, argv);
	
	//if(!NoMultiStart::start()) {
	//	exit(0);
	//}
	
	QTranslator qtTranslator;
	qtTranslator.load("i18n/qt_de");
	app.installTranslator(&qtTranslator);
	
	QTranslator translator;
	translator.load("i18n/de");
	app.installTranslator(&translator);
	
	MainWindow mainWindow;
	
	int ret = app.exec();
	//NoMultiStart::stop();
	return ret;

}
