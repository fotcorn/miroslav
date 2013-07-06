#include "connectwindow.h"

#include <QLayout>
#include <QLabel>
#include <QLineEdit>
#include <QRadioButton>
#include <QPushButton>
#include <QCheckBox>
#include <QIntValidator>

ConnectWindow::ConnectWindow() : QDialog(0, Qt::Tool) {
	
	mainLayout = new QGridLayout();
	
	mainLayout->setMargin(3);
	mainLayout->setSpacing(3);
	
	nickLabel = new QLabel(tr("Nickname:"), this);
	mainLayout->addWidget(nickLabel , 0, 0);
	nickEdit = new QLineEdit(this);
	nickEdit->setMaxLength(30);
	mainLayout->addWidget(nickEdit, 0, 1);
	
	passwordLabel = new QLabel(tr("Password:"), this);
	mainLayout->addWidget(passwordLabel , 1, 0);
	passwordEdit = new QLineEdit(this);
	passwordEdit->setEchoMode(QLineEdit::Password);
	mainLayout->addWidget(passwordEdit, 1, 1);
	
	hostRadio = new QRadioButton(tr("Hostname:"), this);
	hostRadio->toggle();
	mainLayout->addWidget(hostRadio, 2, 0);
	hostEdit = new QLineEdit(this);
	mainLayout->addWidget(hostEdit, 2, 1);
	
	ipRadio = new QRadioButton(tr("IP Address:"), this);
	mainLayout->addWidget(ipRadio, 3, 0);
	ipEdit = new QLineEdit(this);
	ipEdit->setInputMask("000.000.000.000;");
	ipEdit->setDisabled(true);
	mainLayout->addWidget(ipEdit,3,1);
	
	portLabel = new QLabel(tr("Port:"),this);
	mainLayout->addWidget(portLabel, 4, 0);
	portEdit = new QLineEdit(this);
	portEdit->setValidator(new QIntValidator(0,65535, this));
	mainLayout->addWidget(portEdit, 4, 1);
	
	settingsBox = new QCheckBox(tr("Save Settings"), this);
	mainLayout->addWidget(settingsBox, 5, 1);
	settingsBox->setCheckState(Qt::Checked);
	//passwordBox = new QCheckBox(tr("Save Password"), this);
	//mainLayout->addWidget(passwordBox, 5, 1);
	
	cancelButton = new QPushButton(tr("Cancel"), this);
	mainLayout->addWidget(cancelButton, 6, 0);
	okButton = new QPushButton(tr("OK"), this);
	okButton->setDefault(true);
	mainLayout->addWidget(okButton, 6, 1);
	
	setLayout(mainLayout);
	
	connect(okButton, SIGNAL(clicked()), this, SLOT(okClicked()));
	connect(cancelButton, SIGNAL(clicked()), this, SLOT(cancelClicked()));
	
	connect(hostRadio, SIGNAL(toggled(bool)), ipEdit, SLOT(setDisabled(bool)));
	connect(ipRadio, SIGNAL(toggled(bool)), hostEdit, SLOT(setDisabled(bool)));
	
	//connect(settingsBox, SIGNAL(stateChanged(int)), this, SLOT(settingsBoxChanged(int)));
}

/*
void ConnectWindow::settingsBoxChanged(int state) {
	if(state == Qt::Unchecked) {
		passwordBox->setDisabled(true);
	} else {
		passwordBox->setDisabled(false);
	}
}
*/
void ConnectWindow::okClicked() {
	
	nick = nickEdit->text();
	password = passwordEdit->text();
	
	if(hostEdit->isEnabled()) {
		host = true;
		hostip = hostEdit->text();
	} else {
		host = false;
		hostip = ipEdit->text();
	}
	
	port = portEdit->text().toInt();
	
	if(settingsBox->checkState() == Qt::Checked) {
		saveSettings = true;
	} else {
		saveSettings = false;
	}
	/*
	if(passwordBox->checkState() == Qt::Checked) {
		savePassword = true;
	} else {
		savePassword = false;
	}
	*/
	accept();
}

void ConnectWindow::cancelClicked() {
	reject();
}
