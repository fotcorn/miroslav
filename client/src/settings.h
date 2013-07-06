#include <QSettings>


class Settings : public QSettings {
	
	Q_OBJECT
	
	public:
	Settings(QObject *parent = 0);
	
	// write
	void writeSettings(QString nick, QString password, bool host, QString hostip, int port);
	void writeSettings(QString nick, bool host, QString hostip, int port);
	
	void writeNick(QString nick);
	
	public slots:
	void writeBold(bool bold);
	void writeItalic(bool italic);
	void writeUnderline(bool underline);
	void writeColor(QString color);
	
	// read
	bool exists();
	bool passwordSaved();
	
	QString nick();
	QString password();
	bool host();
	QString hostip();
	int port();
	
	bool bold();
	bool italic();
	bool underline();
	QString color();
	
};
