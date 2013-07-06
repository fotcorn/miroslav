#include "connection.h"

#include <QTcpSocket>
#include <QHostAddress>


Connection::Connection(QTcpSocket *_socket, QString _password) {
	socket = _socket;
	password = _password;
	
	auth = false;
	
	connect(socket, SIGNAL(readyRead()), this, SLOT(recv()));
	connect(socket, SIGNAL(disconnected()), this, SLOT(disconnect()));
}

void Connection::recv() {
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

void Connection::parseMessage(QString msg) {
	
	if(msg.startsWith("MSG") && auth) {
		emit newMessage(msg);
		
	} else if(msg.startsWith("CHNCK") && auth) {
		int start = msg.indexOf("Nick: ");
		int end = msg.indexOf("\n", start);
		QString newNick = msg.mid(start + 6, end - start - 6);
		writeLog(nick + " [" + socket->peerAddress().toString() + "]" + " now known as " + newNick);
		emit nickChanged(nick, newNick);
		nick = newNick;
	} else if(msg.startsWith("CON")) {
		int start = msg.indexOf("Nick: ");
		int end = msg.indexOf("\n", start);
		nick = msg.mid(start + 6, end - start - 6);
		
		start = msg.indexOf("PW: ");
		end = msg.indexOf("\n", start);
		QString pw = msg.mid(start + 4, end - start - 4);
		
		if(pw == password) {
			auth = true;
			emit writeLog(nick + " [" + socket->peerAddress().toString() + "] connected1");
			emit connected(this, nick);
		} else {
			sendMessage("CON\nWRONGPW\n\r");
		}
	}
}

void Connection::sendMessage(QString msg) {
	if(auth == true) {
		socket->write(msg.toUtf8());
	}
}

void Connection::disconnect() {
	socket->deleteLater();
	emit writeLog(nick + " [" + socket->peerAddress().toString() + "] disconnected");
	emit disconnected(this, nick);
}

void Connection::sendNicks(QStringList nicks) {
	emit writeLog(nick + " [" + socket->peerAddress().toString() + "] connected2");

	if(nicks.size() != 0) {
		sendMessage("CON\nNicks: \n" + nicks.join("\n") + "\n\r");
	} else {
		sendMessage("CON\n\r");
	}
}
