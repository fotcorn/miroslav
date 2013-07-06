#include <QObject>

#include <QByteArray>
#include <QString>
#include <QStringList>

class QTcpSocket;


class Connection : public QObject {
	
	
	Q_OBJECT
	
	
	QTcpSocket *socket;
	QByteArray message;
	
	QString nick;
	QString password;
	
	bool auth;
	
	private:
	void parseMessage(QString msg);
	
	private slots:
	void recv();
	void disconnect();
	
	public:
	Connection(QTcpSocket *_socket, QString _password);
	void sendNicks(QStringList nicks);
	
	public slots:
	void sendMessage(QString);
	
	signals:
	void newMessage(QString);
	// this, nickname
	void connected(Connection*, QString);
	void disconnected(Connection*, QString);
	void nickChanged(QString, QString);
	
	void writeLog(QString text);
};
