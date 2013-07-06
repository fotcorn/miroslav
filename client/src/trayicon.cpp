#include "trayicon.h"

#include <QMenu>
#include <QAction>

#include <QMessageBox>

TrayIcon::TrayIcon(QWidget *parent) : QSystemTrayIcon(QIcon(":/icon.png"), parent) {
	
	visible = true;
	
	menu = new QMenu();
	
	showAction = new QAction(tr("Hide"), this);
	exitAction = new QAction(tr("Exit"), this);
	
	menu->addAction(showAction);
	menu->addAction(exitAction);
	
	setContextMenu(menu);
	
	connect(this, SIGNAL(activated(QSystemTrayIcon::ActivationReason)), this, SLOT(showHideWindow(QSystemTrayIcon::ActivationReason)));
	connect(this, SIGNAL(messageClicked()), this, SLOT(showHideWindow()));

	connect(showAction, SIGNAL(triggered()), this, SLOT(showHideWindow()));
	connect(exitAction, SIGNAL(triggered()), this, SIGNAL(requestExit()));
	
	show();
}



void TrayIcon::showHideWindow(QSystemTrayIcon::ActivationReason reason) {
	if(reason == QSystemTrayIcon::Trigger) {
		if(visible == true) {
			showAction->setText(tr("Show"));
			visible = false;
			emit showChatWindow(false);
		} else {
			showAction->setText(tr("Hide"));
			visible = true;
			emit showChatWindow(true);
		}
	}
}

void TrayIcon::showHideWindow() {
		if(visible == true) {
			showAction->setText(tr("Show"));
			visible = false;
			emit showChatWindow(false);
		} else {
			showAction->setText(tr("Hide"));
			visible = true;
			emit showChatWindow(true);
		}
}
