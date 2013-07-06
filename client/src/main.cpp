#include <QApplication>

#include <QTranslator>
#include <QLocale>
#include <QLibraryInfo>

#include "mainwindow.h"

//#include "nomultistart.h"

int main(int argc, char *argv[]) {
	
	QApplication app(argc, argv);
	
	//if(!NoMultiStart::start()) {
	//	exit(0);
	//}
	
	QTranslator qtTranslator;
	qtTranslator.load("qt_" + QLocale::system().name(),
		QLibraryInfo::location(QLibraryInfo::TranslationsPath));
	app.installTranslator(&qtTranslator);
	
	QTranslator translator;
	translator.load("i18n/" + QLocale::system().name());
	app.installTranslator(&translator);
	
	MainWindow mainWindow;
	
	int ret = app.exec();
	//NoMultiStart::stop();
	return ret;

}
