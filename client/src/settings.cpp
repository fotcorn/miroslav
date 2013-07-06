#include "settings.h"


Settings::Settings(QObject *parent) : QSettings("BBC", "Miroslav Client", parent) {}

void Settings::writeSettings(QString nick, QString password, bool host, QString hostip, int port) {
	setValue("nick", nick);
	setValue("pwsaved", true);
	setValue("password", password);
	setValue("host", host);
	setValue("hostip", hostip);
	setValue("port", port);
}
void Settings::writeSettings(QString nick, bool host, QString hostip, int port) {
	setValue("nick", nick);
	setValue("pwsaved", false);
	setValue("password", "");
	setValue("host", host);
	setValue("hostip", hostip);
	setValue("port", port);
}

void Settings::writeNick(QString nick) {
	if(exists()) {
		setValue("nick", nick);
	}
}

void Settings::writeBold(bool bold) {
	setValue("bold", bold);
}
void Settings::writeItalic(bool italic) {
	setValue("italic", italic);
}
void Settings::writeUnderline(bool underline) {
	setValue("underline", underline);
}
void Settings::writeColor(QString color) {
	setValue("color", color);
}

// read

bool Settings::exists() {
	return contains("nick");
}
bool Settings::passwordSaved() {
	return value("pwsaved").toBool();
}

QString Settings::nick() {
	return value("nick").toString();
}
QString Settings::password() {
	return value("password").toString();
}

bool Settings::host() {
	return value("host").toBool();
}
QString Settings::hostip() {
	return value("hostip").toString();
}
int Settings::port()  {
	return value("port").toInt();
}

bool Settings::bold() {
	return value("bold").toBool();
}
bool Settings::italic() {
	return value("italic").toBool();
}
bool Settings::underline() {
	return value("underline").toBool();
}
QString Settings::color() {
	return value("color").toString();
}




