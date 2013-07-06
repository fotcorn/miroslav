#include "nomultistart.h"

#include <QFile>
#include <QDir>

#include <QMessageBox>

bool NoMultiStart::start() {
	
	QFile file(QDir::tempPath() + "/miroslav.pid");
	if(file.exists()) {
		QMessageBox::critical(0, "Error", tr("Miroslav can only be started once!"));
		return false;
	} else {
		file.open(QIODevice::WriteOnly);
		file.close();
		return true;
	}
}

void NoMultiStart::stop() {
	QFile file(QDir::tempPath() + "/miroslav.pid");
	file.remove();
}
