#include <QSystemTrayIcon>

class QMenu;
class QAction;

class TrayIcon : public QSystemTrayIcon {
	
	Q_OBJECT
	
	QMenu *menu;
	
	QAction *showAction;
	QAction *exitAction;
	
	bool visible;
	
	public:
	TrayIcon(QWidget *parent = 0);
	
	
	private slots:
	void showHideWindow(QSystemTrayIcon::ActivationReason reason);
	
	public slots:
	void showHideWindow();
	
	signals:
	void showChatWindow(bool show = false);
	void requestExit();
	
};
