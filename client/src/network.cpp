#include "network.h"

#include <QTcpSocket>
#include <QHostAddress>
#include <QStringList>


Network::Network() {
	socket = new QTcpSocket();
}


// private functions
void Network::parseMessage(QString msg) {
	if(msg.startsWith("MSG")) {
		int start = msg.indexOf("Nick: ");
		int end = msg.indexOf("\n", start);
		QString fromNick = msg.mid(start + 6, end - start - 6);
		
		start = msg.indexOf("Color: ");
		end = msg.indexOf("\n", start);
		QString color = msg.mid(start + 7, end - start - 7);
		
		start = msg.indexOf("Style: ");
		end = msg.indexOf("\n", start);
		QString style = msg.mid(start + 7, end - start - 7);
		
		start = msg.indexOf("MSG:");
		end = msg.lastIndexOf("\n\r");
		msg = msg.mid(start + 5, end - start - 5);
		
		emit newMessage(fromNick, color, style, msg);
	} else if(msg.startsWith("UCON")) {
		int start = msg.indexOf("Nick: ");
		int end = msg.indexOf("\n", start);
		QString newNick = msg.mid(start + 6, end - start - 6);
		emit nickAdded(newNick);
	} else if(msg.startsWith("UDCON")) {
		int start = msg.indexOf("Nick: ");
		int end = msg.indexOf("\n", start);
		QString oldNick = msg.mid(start + 6, end - start - 6);
		emit nickRemoved(oldNick);
	} else if(msg.startsWith("CHNCK")) {
		int start = msg.indexOf("ONick: ");
		int end = msg.indexOf("\n", start);
		QString oldNick = msg.mid(start + 7, end - start - 7);
		
		start = msg.indexOf("Nick: ", end);
		end = msg.indexOf("\n", start);
		QString newNick = msg.mid(start + 6, end - start - 6);
				
		emit nickChanged(oldNick, newNick);
	} else if(msg.startsWith("CON")) {
		if(msg == "CON\nWRONGPW\n\r") {
			emit wrongPW();
		} else if(msg == "CON\n\r") {
			emit connected(QStringList());
		} else {
			QString text = msg.mid(12, msg.length()-14);
			QStringList nicks = text.split("\n");
			emit connected(nicks);
		}
	}
}


//private slots
void Network::sendLogin() {
	QString msg = "CON\nNick: " + nick +"\nPW: " + password + "\n\r";
	socket->write(msg.toUtf8());
	
	connect(socket, SIGNAL(readyRead()), this, SLOT(recv()));
}

void Network::recv() {
	message.append(socket->readAll());
	int pos;
	
	QString msg = QString::fromUtf8(message.data());
	
	while((pos = msg.indexOf("\n\r")) > -1) {
		parseMessage(msg.left(pos+2));
		msg = msg.mid(pos+2);
	}
	message.clear();
	message = msg.toUtf8();
}

void Network::error(QAbstractSocket::SocketError err) {
	emit errorMessage(socket->errorString());
	disconnectFrom();
}


// public slots
void Network::connectTo(QString _nick, QString _password, bool host, QString hostip, int port) {
	nick = _nick;
	password = _password;
	
	if(host) {
		socket->connectToHost(hostip,port);
	} else {
		QHostAddress address(hostip);
		socket->connectToHost(address,port);
	}
	
	connect(socket, SIGNAL(connected()), this, SLOT(sendLogin()));
	connect(socket, SIGNAL(error(QAbstractSocket::SocketError)), this, SLOT(error(QAbstractSocket::SocketError)));
}

void Network::disconnectFrom() {
	socket->disconnectFromHost();
	delete socket;
	socket = new QTcpSocket();
	message.clear();
}

void Network::sendMessage(QString msg, QString color, QString style) {
	msg = "MSG\nNick: " + nick + "\nColor: " + color + "\nStyle: " + style + "\nMSG:\n" + msg + "\n\r";
	socket->write(msg.toUtf8());
}

void Network::changeNick(QString newNick) {
	
	QString msg = "CHNCK\nONick: " + newNick + "\nNick: " + nick + "\n\r";
	socket->write(msg.toUtf8());
	
	nick = newNick;
}
