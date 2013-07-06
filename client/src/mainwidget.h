#include <QSplitter>

class QVBoxLayout; 
class QHBoxLayout;

class QWidget;

class QLabel;
class QPushButton;

class QTextEdit;

class ChatEdit;

class ListView;
class QStringListModel;

class Network;

class Highlighter;

class Settings;

class MainWidget : public QSplitter {

	Q_OBJECT

	// Widgets
	QWidget *leftWidget;
	QVBoxLayout *leftLayout;
	
	
	QHBoxLayout *nickLayout;
	QLabel *nickLabel;
	QPushButton *changeNickButton;
	
	QTextEdit *messageViewer;
	
	QHBoxLayout *fontLayout;
	QPushButton *colorButton;
	QPushButton *boldButton;
	QPushButton *italicButton;
	QPushButton *underlineButton;
	
	QHBoxLayout *messageLayout;
	ChatEdit *messageInput;
	QPushButton *sendButton;

	ListView *onlineUserView;
	QStringListModel *model;
	
	Network *network;
	
	Highlighter *highlighter;

	Settings *settings;
	
	public:
	MainWidget(QWidget *parent = 0);
	
	private slots:
	void sendMSG();
	
	public slots:
	void requestConnection();
	void requestDisconnect();
	void addMessage(QString nick, QString msgColor, QString style, QString msg);
	void wrongPW();
	void connected(QStringList nicks);
	void errorMessage(QString errorStr);
	
	void addNick(QString nick);
	void removeNick(QString nick);
	void changeNick(QString oldNick, QString newNick);
	
	void requestChangeNick();
	
	void requestChangeColor();
	
	void loadSettings();
	
	signals:
	// QString msg, QString color, QString style
	void sendMessage(QString, QString, QString);
	// Für MainWindow und TrayIcon
	// QString nick, QString message
	void newMessage(QString, QString);
	
	void canConnect(bool);
	void canDisconnect(bool);
	void canChangeNick(bool);
	void canChangeColor(bool);
};
