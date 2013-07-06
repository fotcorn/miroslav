#include "mainwidget.h"

#include <QLayout>

#include <QWidget>

#include <QLabel>
#include <QPushButton>

#include <QTextEdit>
#include <QScrollBar>

#include "chatedit.h"

#include "listview.h"
#include <QStringListModel>

#include <QMessageBox>

#include "network.h"

#include "connectwindow.h"

#include "changenickdialog.h"

#include <QColorDialog>
#include <QRgb>

#include "highlighter.h"

#include "settings.h"

#include <QDebug>

MainWidget::MainWidget(QWidget *parent) : QSplitter(parent) {
	
	network = new Network();
	
/****************************************************************************************/

	leftWidget = new QWidget(this);
	leftLayout = new QVBoxLayout();
	leftLayout->setMargin(0);
	leftWidget->setLayout(leftLayout);
	
	////////////////////////////////////////////////
	
	nickLayout = new QHBoxLayout();
	
	nickLabel = new QLabel(leftWidget);
	nickLabel->setSizePolicy(QSizePolicy::Preferred, QSizePolicy::Fixed);
	nickLayout->addWidget(nickLabel);
	
	changeNickButton = new QPushButton(tr("Change Name"), leftWidget);
	changeNickButton->setSizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);
	changeNickButton->setDisabled(true);
	nickLayout->addWidget(changeNickButton);

	leftLayout->addLayout(nickLayout);

	///////////////////////////////////////////////

	messageViewer = new QTextEdit(leftWidget);
	messageViewer->setReadOnly(true);
	leftLayout->addWidget(messageViewer);
	
	//////////////////////////////////////////////
	fontLayout = new QHBoxLayout();
	colorButton = new QPushButton(tr("Color"), leftWidget);
	colorButton->setDisabled(true);
	fontLayout->addWidget(colorButton);
	boldButton  = new QPushButton(tr("B"), leftWidget);
	boldButton->setMinimumWidth(20);
	boldButton->setMaximumWidth(20);
	boldButton->setCheckable(true);
	boldButton->setDisabled(true);
	fontLayout->addWidget(boldButton);
	italicButton = new QPushButton(tr("I"), leftWidget);
	italicButton->setMinimumWidth(20);
	italicButton->setMaximumWidth(20);
	italicButton->setCheckable(true);
	italicButton->setDisabled(true);
	fontLayout->addWidget(italicButton);
	underlineButton  = new QPushButton(tr("U"), leftWidget);
	underlineButton->setMinimumWidth(20);
	underlineButton->setMaximumWidth(20);
	underlineButton->setCheckable(true);
	underlineButton->setDisabled(true);
	fontLayout->addWidget(underlineButton);
	fontLayout->addStretch();
	
	leftLayout->addLayout(fontLayout);
	///////////////////////////////////////////////
	
	messageLayout = new QHBoxLayout();
	
	messageInput = new ChatEdit(leftWidget);
	messageInput->setMinimumHeight(70);
	messageInput->setMaximumHeight(70);
	messageInput->setSizePolicy(QSizePolicy::Preferred, QSizePolicy::Fixed);
	messageInput->setDisabled(true);
	
	messageInput->setAcceptRichText(false);

	messageInput->setFocus();
	messageLayout->addWidget(messageInput);
	
	sendButton = new QPushButton(tr("Send"), leftWidget);
	sendButton->setSizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);
	sendButton->setDisabled(true);
	messageLayout->addWidget(sendButton);
	
	leftLayout->addLayout(messageLayout);

	//////////////////////////////////////////////

/****************************************************************************************/
	addWidget(leftWidget);

	onlineUserView = new ListView(leftWidget);
	//onlineUserView->setMinimumWidth(100);
	
	QSizePolicy policy = onlineUserView->sizePolicy();
	policy.setHorizontalStretch(1);
	onlineUserView->setSizePolicy(policy);
	
	model = new QStringListModel();
	onlineUserView->setModel(model);
	addWidget(onlineUserView);
	
	

	
	highlighter = new Highlighter(messageInput);
	
	settings = new Settings();
	
	/////////////////////////////////////////////////////////
	// Connections
	////////////////////////////////////////////////////////
	
	connect(sendButton, SIGNAL(clicked()), this, SLOT(sendMSG()));
	connect(messageInput, SIGNAL(send()), this, SLOT(sendMSG()));
	connect(changeNickButton, SIGNAL(clicked()), this, SLOT(requestChangeNick()));
	
	connect(colorButton, SIGNAL(clicked()), this, SLOT(requestChangeColor()));
	
	connect(boldButton, SIGNAL(clicked(bool)), highlighter, SLOT(setBold(bool)));
	connect(italicButton, SIGNAL(clicked(bool)), highlighter, SLOT(setItalic(bool)));
	connect(underlineButton, SIGNAL(clicked(bool)), highlighter, SLOT(setUnderline(bool)));
	
	connect(boldButton, SIGNAL(clicked(bool)), settings, SLOT(writeBold(bool)));
	connect(italicButton, SIGNAL(clicked(bool)), settings, SLOT(writeItalic(bool)));
	connect(underlineButton, SIGNAL(clicked(bool)), settings, SLOT(writeUnderline(bool)));
	
	connect(network, SIGNAL(errorMessage(QString)), this, SLOT(errorMessage(QString)));
	connect(network, SIGNAL(connected(QStringList)), this, SLOT(connected(QStringList)));
	connect(network, SIGNAL(wrongPW()), this, SLOT(wrongPW()));
	connect(network, SIGNAL(newMessage(QString, QString, QString, QString)), this, SLOT(addMessage(QString, QString, QString, QString)));
	
	connect(network, SIGNAL(nickAdded(QString)), this, SLOT(addNick(QString)));
	connect(network, SIGNAL(nickRemoved(QString)), this, SLOT(removeNick(QString)));
	connect(network, SIGNAL(nickChanged(QString, QString)), this, SLOT(changeNick(QString, QString)));

	connect(this, SIGNAL(sendMessage(QString, QString, QString)), network, SLOT(sendMessage(QString, QString, QString)));
	
	
	QList<int> list;
	list<<420<<180;
	setSizes(list);
}

// private slots
void MainWidget::sendMSG() {
	QString message = messageInput->toPlainText();
	if(message != "") {
		message = message.left(1000);
		emit sendMessage(message, highlighter->getColorString(), highlighter->getStyleString());
		messageInput->clear();
		messageViewer->textCursor().movePosition(QTextCursor::End);
	}
}

// public slots
void MainWidget::requestConnection() {
	ConnectWindow connectWindow;
	if(connectWindow.exec() == QDialog::Accepted) {		
		if(connectWindow.saveSettings) {
			//save Settings
			settings->writeSettings(connectWindow.nick, connectWindow.password, connectWindow.host, connectWindow.hostip, connectWindow.port);
		}
		network->connectTo(connectWindow.nick, connectWindow.password, connectWindow.host, connectWindow.hostip, connectWindow.port);
		nickLabel->setText(connectWindow.nick);
		emit canConnect(false);
		emit canDisconnect(true);
	}
}

void MainWidget::requestDisconnect() {
	network->disconnectFrom();
	emit canConnect(true);
	emit canDisconnect(false);
	emit canChangeNick(false);
	emit canChangeColor(false);
	
	nickLabel->clear();
	messageViewer->clear();
	model->setStringList(QStringList());
	changeNickButton->setDisabled(true);
	messageInput->setDisabled(true);
	sendButton->setDisabled(true);
	
	colorButton->setDisabled(true);
	boldButton->setDisabled(true);
	italicButton->setDisabled(true);
	underlineButton->setDisabled(true);
}

void MainWidget::addMessage(QString nick, QString msgColor, QString style, QString msg) {

	emit newMessage(nick, msg);
	
	msg = msg.replace("<", "&lt;");
	msg = msg.replace(">", "&gt;");
	msg = msg.replace("\n", "<br>");
	
	messageViewer->moveCursor(QTextCursor::End);
	messageViewer->insertHtml(nick + " " + tr("says:"));
	
	QString css = "color: " + msgColor + ";";
	QString htmlStyle1 = "<font color=\"" + msgColor + "\">";
	QString htmlStyle2 = "</font>";
	
	if(style.contains("b")) {
		htmlStyle1.append("<b>");
		htmlStyle2.prepend("</b>");
	}
	if(style.contains("i")) {
		htmlStyle1.append("<i>");
		htmlStyle2.prepend("</i>");
	}
	if(style.contains("u")) {
		htmlStyle1.append("<u>");
		htmlStyle2.prepend("</u>");
	}
	
	messageViewer->insertHtml("<table width=\"100%\"><tr><td width=\"10\"></td><td>" + htmlStyle1 + msg + htmlStyle2 + "</td></tr></table>\n");
	messageViewer->verticalScrollBar()->setValue(messageViewer->verticalScrollBar()->maximum());
}

void MainWidget::wrongPW() {
	QMessageBox::critical(this, tr("Error"), tr("Wrong Password!"));
	requestDisconnect();
}

void MainWidget::connected(QStringList nicks) {
	nicks.sort();
	model->setStringList(nicks);
	changeNickButton->setDisabled(false);
	messageInput->setDisabled(false);
	sendButton->setDisabled(false);
	
	colorButton->setDisabled(false);
	boldButton->setDisabled(false);
	italicButton->setDisabled(false);
	underlineButton->setDisabled(false);
	
	emit canChangeNick(true);
	emit canChangeColor(true);
}

void MainWidget::errorMessage(QString errorStr) {
	QMessageBox::critical(this, tr("Error"), errorStr);
	requestDisconnect();
}


void MainWidget::addNick(QString nick) {
	QStringList list = model->stringList();
	list.push_back(nick);
	list.sort();
	model->setStringList(list);
}

void MainWidget::removeNick(QString nick) {
	QStringList list = model->stringList();
	int index = list.indexOf(nick);
	list.removeAt(index);
	list.sort();
	model->setStringList(list);
}

void MainWidget::changeNick(QString oldNick, QString newNick) {
	QStringList list = model->stringList();
	int index = list.indexOf(oldNick);
	list.replace(index, newNick);
	list.sort();
	model->setStringList(list);
}

void MainWidget::requestChangeNick() {
	/*
	bool ok = false;
	QString newNick = QInputDialog::getText(0, tr("New Nick"), tr("Please enter a new Nick:"), QLineEdit::Normal, QString(), &ok);
	if(ok && !newNick.isEmpty()) {
		network->changeNick(newNick);
		nickLabel->setText(newNick);
		settings->writeNick(newNick);
	}
	*/
	ChangeNickDialog dialog(this);
	if(dialog.exec() == QDialog::Accepted && !dialog.nick.isEmpty()) {
		QString newNick = dialog.nick;
		network->changeNick(newNick);
		nickLabel->setText(newNick);
		settings->writeNick(newNick);
	}
}


void MainWidget::requestChangeColor() {
	QColor newColor = QColorDialog::getColor(Qt::white, this);
	
	if(newColor.isValid()) {	
		highlighter->setColor(newColor);
		settings->writeColor(highlighter->getColorString());
	}
}

void MainWidget::loadSettings() {
	if(settings->exists()) {
		network->connectTo(settings->nick(), settings->password(), settings->host(), settings->hostip(), settings->port());
		nickLabel->setText(settings->nick());
		
		boldButton->setChecked(settings->bold());
		italicButton->setChecked(settings->italic());
		underlineButton->setChecked(settings->underline());
		
		highlighter->setBold(settings->bold());
		highlighter->setItalic(settings->italic());
		highlighter->setUnderline(settings->underline());
		
		highlighter->setColor(QColor(settings->color()));
		
		emit canConnect(false);
		emit canDisconnect(true);
	}
}
