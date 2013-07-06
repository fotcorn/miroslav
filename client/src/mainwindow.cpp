#include "mainwindow.h"

#include <QMenu>
#include <QAction>

#include <QMenuBar>

#include "mainwidget.h"

#include "trayicon.h"

#include <QCloseEvent>

#include <QApplication>

#if defined(Q_WS_WIN)
#include <windows.h>
#endif


MainWindow::MainWindow() : QMainWindow() {
	
	setWindowTitle("Miroslav Beta 7");
	
	menuBar();

	fileMenu = menuBar()->addMenu(tr("File"));
	settingsMenu = menuBar()->addMenu(tr("Settings"));
	
	connectAction = new QAction(tr("Connect..."), this);
	reconnectAction = new QAction(tr("Reconnect"), this);
	disconnectAction = new QAction(tr("Disconnect"), this);
	disconnectAction->setEnabled(false);
	closeWindowAction = new QAction(tr("Close Window"), this);
	quitAction = new QAction(tr("Quit"), this);
	

	fileMenu->addAction(connectAction);
	fileMenu->addAction(reconnectAction);
	fileMenu->addAction(disconnectAction);
	fileMenu->addSeparator();
	fileMenu->addAction(closeWindowAction);
	fileMenu->addAction(quitAction);

	changeNickAction = new QAction(tr("Change Nickname..."), this);
	changeNickAction->setEnabled(false);
	changeColorAction = new QAction(tr("Change Text Color..."), this);
	changeColorAction->setEnabled(false);

	settingsMenu->addAction(changeNickAction);
	settingsMenu->addAction(changeColorAction);

	mainWidget = new MainWidget(this);
	setCentralWidget(mainWidget);
	resize(600,350);
	
	trayIcon = new TrayIcon(this);
	
	// Menu connections
	connect(connectAction, SIGNAL(triggered()), mainWidget, SLOT(requestConnection()));
	connect(reconnectAction, SIGNAL(triggered()), mainWidget, SLOT(loadSettings()));
	connect(disconnectAction, SIGNAL(triggered()), mainWidget, SLOT(requestDisconnect()));
	connect(closeWindowAction, SIGNAL(triggered()), trayIcon, SLOT(showHideWindow()));
	connect(quitAction, SIGNAL(triggered()), qApp, SLOT(quit()));
	
	connect(changeNickAction, SIGNAL(triggered()), mainWidget, SLOT(requestChangeNick()));
	connect(changeColorAction, SIGNAL(triggered()), mainWidget, SLOT(requestChangeColor()));
	
	// Menu activate connections
	connect(mainWidget, SIGNAL(canConnect(bool)), this, SLOT(canConnect(bool)));
	connect(mainWidget, SIGNAL(canDisconnect(bool)), this, SLOT(canDisconnect(bool)));
	connect(mainWidget, SIGNAL(canChangeNick(bool)), this, SLOT(canChangeNick(bool)));
	connect(mainWidget, SIGNAL(canChangeColor(bool)), this, SLOT(canChangeColor(bool)));
	
	// Tray Icon connections
	connect(trayIcon, SIGNAL(requestExit()), qApp, SLOT(quit()));
	connect(trayIcon, SIGNAL(showChatWindow(bool)), this, SLOT(setVisible(bool)));	

	connect(mainWidget, SIGNAL(newMessage(QString, QString)), this, SLOT(newMessage(QString, QString)));
	
	mainWidget->loadSettings();
	show();
}

void MainWindow::newMessage(QString nick, QString msg) {
	if(isMinimized() && isVisible()) {
		flashWindow();
	} else if(!isVisible()) {
		if(msg.length() > 80) {
			msg = msg.left(80) + "...";
		}
		trayIcon->showMessage(tr("New Message"), tr("A message from") + " " + nick + " " + tr("was recived:") + "\n" + msg);
	}
}

void MainWindow::flashWindow() {
		#if defined(Q_WS_WIN)
		FlashWindow(winId(), true);
		#endif
}

void MainWindow::closeWindow() {
	hide();
	deleteLater();
}

void MainWindow::closeEvent(QCloseEvent *e) {
	trayIcon->showHideWindow();
	e->ignore();
}

void MainWindow::canConnect(bool can) {
	connectAction->setEnabled(can);
	reconnectAction->setEnabled(can);
}

void MainWindow::canDisconnect(bool can) {
	disconnectAction->setEnabled(can);
}

void MainWindow::canChangeNick(bool can) {
	changeNickAction->setEnabled(can);
}

void MainWindow::canChangeColor(bool can) {
	changeColorAction->setEnabled(can);
}
