#include "server.h"

#include <QTcpSocket>

#include "connection.h"

#include <QFile>
#include <QTextStream>

#include <QDate>

Server::Server() {
	pw = "password";
	listen(QHostAddress::Any, 33333);
	connect(this, SIGNAL(newConnection()), this, SLOT(newConnection()));
	
	file = new QFile("log.txt");
	file->open(QIODevice::Append | QIODevice::Text);
	
	stream = new QTextStream(file);
	writeLog("Miroslav Server started at " + QDate::currentDate().toString());
}

void Server::newConnection() {
	Connection *con = new Connection(nextPendingConnection(), pw);
	
	connect(con, SIGNAL(newMessage(QString)), this, SIGNAL(newMessage(QString)));
	connect(this, SIGNAL(newMessage(QString)), con, SLOT(sendMessage(QString)));
	
	connect(con, SIGNAL(connected(Connection*, QString)), this, SLOT(connected(Connection*, QString)));
	connect(con, SIGNAL(disconnected(Connection*, QString)), this , SLOT(disconnected(Connection*, QString)));
	
	connect(con, SIGNAL(nickChanged(QString, QString)), this, SLOT(changeNick(QString, QString)));
	
	connect(con, SIGNAL(writeLog(QString)), this, SLOT(writeLog(QString)));
}

void Server::connected(Connection* con, QString nick) {
	con->sendNicks(nickList);
	nickList.push_back(nick);
	nickList.sort();
	emit newMessage("UCON\nNick: " + nick + "\n\r");
}

void Server::disconnected(Connection* con, QString nick) {
	con->deleteLater();
	int index = nickList.indexOf(nick);
	nickList.removeAt(index);
	nickList.sort();
	emit newMessage("UDCON\nNick: " + nick + "\n\r");
}

void Server::changeNick(QString oldNick, QString newNick) {
	int index = nickList.indexOf(oldNick);
	nickList.replace(index, newNick);
	nickList.sort();
	emit newMessage("CHNCK\nONick: " + oldNick + "\nNick: " + newNick + "\n\r");
}

void Server::writeLog(QString text) {
	*stream<<text<<"\n";
	stream->flush();
}
