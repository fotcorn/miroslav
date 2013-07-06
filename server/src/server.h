#include <QTcpServer>

#include <QStringList>

class QTcpSocket;
class Connection;

class QFile;
class QTextStream;

class Server : public QTcpServer {

	Q_OBJECT
	
	
	QString pw;
	
	QFile *file;
	QTextStream *stream;
	
	QStringList nickList;

	public:
	Server();

	public slots:
	void newConnection();
	void connected(Connection* con, QString nick);
	void disconnected(Connection *con, QString nick);
	void changeNick(QString oldNick, QString newNick);
	
	void writeLog(QString text);

	signals:
	void newMessage(QString);
	
	
};
