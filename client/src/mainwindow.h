#include <QMainWindow>

class QMenu;
class QAction;

class MainWidget;

class TrayIcon;

class QCloseEvent;


class MainWindow : public QMainWindow {
	
	Q_OBJECT

	QMenu *fileMenu;
	QMenu *settingsMenu;
	
	QAction *connectAction;
	QAction *reconnectAction;
	QAction *disconnectAction;
	QAction *closeWindowAction;
	QAction *quitAction;
	
	QAction *changeNickAction;
	QAction *changeColorAction;
	//QAction *changeStyleAction;

	MainWidget *mainWidget;
	TrayIcon *trayIcon;
		
	public:
	MainWindow();

	public slots:
	void closeWindow();
	// Connect mit MainWidget::newMessage(QString);
	void newMessage(QString nick, QString msg);
	void flashWindow();
	
	
	void canConnect(bool can);
	void canDisconnect(bool can);
	void canChangeNick(bool can);
	void canChangeColor(bool can);
	
	protected:
	void closeEvent(QCloseEvent *e);
	
};
