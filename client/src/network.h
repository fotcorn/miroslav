#include <QObject>

#include <QByteArray>
#include <QString>
#include <QStringList>

#include <QAbstractSocket>

class QTcpSocket;



class Network : public QObject {

	Q_OBJECT
	
	QTcpSocket *socket;
	QByteArray message;
	
	QString nick;
	QString password;


	public:
	Network();
	
	private:
	void parseMessage(QString msg);
	
	private slots:
	void sendLogin();
	void recv();
	void error(QAbstractSocket::SocketError err);
	
	public slots:
	void connectTo(QString _nick, QString _password, bool host, QString hostip, int port);
	void disconnectFrom();
	void sendMessage(QString msg, QString color, QString style);
	void changeNick(QString newNick);
	
	signals:
	// QStringList nicks
	void connected(QStringList);
	
	void wrongPW();
	
	// QString nick, QString color, QString style, QString msg
	void newMessage(QString, QString, QString, QString);
	
	// QString addedNick
	void nickAdded(QString);
	
	// QString removedNick
	void nickRemoved(QString);
	
	// QString oldNick QString newNick
	void nickChanged(QString, QString);
	
	// QString errorString
	void errorMessage(QString);
};
