#include "changenickdialog.h"

#include <QLayout>
#include <QLabel>
#include <QLineEdit>
#include <QPushButton>




ChangeNickDialog::ChangeNickDialog(QWidget *parent) : QDialog(parent) {
	
	setWindowTitle(tr("New Nick"));
	
	mainLayout = new QVBoxLayout(this);
	
	label = new QLabel(tr("Please enter a new Nick:"), this);
	edit = new QLineEdit(this);
	edit->setMaxLength(30);
	
	mainLayout->addWidget(label);
	mainLayout->addWidget(edit);
	
	
	buttonLayout = new QHBoxLayout(this);
	
	okButton = new QPushButton(tr("OK"), this);
	okButton->setDefault(true);
	cancelButton  = new QPushButton(tr("Cancel"), this);
	
	buttonLayout->addStretch();
	buttonLayout->addWidget(okButton);
	buttonLayout->addWidget(cancelButton);
	
	mainLayout->addLayout(buttonLayout);
	
	connect(okButton, SIGNAL(clicked()), this, SLOT(okClicked()));
	connect(cancelButton, SIGNAL(clicked()), this, SLOT(reject()));
}

void ChangeNickDialog::okClicked() {
	nick = edit->text();
	accept();
}
