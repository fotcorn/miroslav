/********************************************************************************
** Form generated from reading ui file 'connectionwindow.ui'
**
** Created: Tue 23. Jan 11:27:50 2007
**      by: Qt User Interface Compiler version 4.2.2
**
** WARNING! All changes made in this file will be lost when recompiling ui file!
********************************************************************************/

#ifndef UI_CONNECTIONWINDOW_H
#define UI_CONNECTIONWINDOW_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtGui/QApplication>
#include <QtGui/QButtonGroup>
#include <QtGui/QCheckBox>
#include <QtGui/QGridLayout>
#include <QtGui/QLabel>
#include <QtGui/QLineEdit>
#include <QtGui/QPushButton>
#include <QtGui/QRadioButton>
#include <QtGui/QWidget>

class Ui_Form
{
public:
    QGridLayout *gridLayout;
    QCheckBox *checkBox;
    QLabel *label;
    QLabel *label_2;
    QRadioButton *radioButton;
    QLineEdit *lineEdit;
    QLineEdit *lineEdit_2;
    QLineEdit *lineEdit_3;
    QPushButton *pushButton;
    QPushButton *pushButton_2;
    QLineEdit *lineEdit_5;
    QLabel *label_3;
    QRadioButton *radioButton_2;
    QLineEdit *lineEdit_4;

    void setupUi(QWidget *Form)
    {
    Form->setObjectName(QString::fromUtf8("Form"));
    gridLayout = new QGridLayout(Form);
    gridLayout->setSpacing(6);
    gridLayout->setMargin(9);
    gridLayout->setObjectName(QString::fromUtf8("gridLayout"));
    checkBox = new QCheckBox(Form);
    checkBox->setObjectName(QString::fromUtf8("checkBox"));

    gridLayout->addWidget(checkBox, 5, 1, 1, 1);

    label = new QLabel(Form);
    label->setObjectName(QString::fromUtf8("label"));

    gridLayout->addWidget(label, 0, 0, 1, 1);

    label_2 = new QLabel(Form);
    label_2->setObjectName(QString::fromUtf8("label_2"));

    gridLayout->addWidget(label_2, 1, 0, 1, 1);

    radioButton = new QRadioButton(Form);
    radioButton->setObjectName(QString::fromUtf8("radioButton"));

    gridLayout->addWidget(radioButton, 2, 0, 1, 1);

    lineEdit = new QLineEdit(Form);
    lineEdit->setObjectName(QString::fromUtf8("lineEdit"));

    gridLayout->addWidget(lineEdit, 0, 1, 1, 1);

    lineEdit_2 = new QLineEdit(Form);
    lineEdit_2->setObjectName(QString::fromUtf8("lineEdit_2"));

    gridLayout->addWidget(lineEdit_2, 1, 1, 1, 1);

    lineEdit_3 = new QLineEdit(Form);
    lineEdit_3->setObjectName(QString::fromUtf8("lineEdit_3"));

    gridLayout->addWidget(lineEdit_3, 2, 1, 1, 1);

    pushButton = new QPushButton(Form);
    pushButton->setObjectName(QString::fromUtf8("pushButton"));

    gridLayout->addWidget(pushButton, 6, 0, 1, 1);

    pushButton_2 = new QPushButton(Form);
    pushButton_2->setObjectName(QString::fromUtf8("pushButton_2"));

    gridLayout->addWidget(pushButton_2, 6, 1, 1, 1);

    lineEdit_5 = new QLineEdit(Form);
    lineEdit_5->setObjectName(QString::fromUtf8("lineEdit_5"));

    gridLayout->addWidget(lineEdit_5, 4, 1, 1, 1);

    label_3 = new QLabel(Form);
    label_3->setObjectName(QString::fromUtf8("label_3"));

    gridLayout->addWidget(label_3, 4, 0, 1, 1);

    radioButton_2 = new QRadioButton(Form);
    radioButton_2->setObjectName(QString::fromUtf8("radioButton_2"));

    gridLayout->addWidget(radioButton_2, 3, 0, 1, 1);

    lineEdit_4 = new QLineEdit(Form);
    lineEdit_4->setObjectName(QString::fromUtf8("lineEdit_4"));

    gridLayout->addWidget(lineEdit_4, 3, 1, 1, 1);


    retranslateUi(Form);

    QSize size(235, 204);
    size = size.expandedTo(Form->minimumSizeHint());
    Form->resize(size);


    QMetaObject::connectSlotsByName(Form);
    } // setupUi

    void retranslateUi(QWidget *Form)
    {
    Form->setWindowTitle(QApplication::translate("Form", "Form", 0, QApplication::UnicodeUTF8));
    checkBox->setText(QApplication::translate("Form", "Einstellungen Speichern", 0, QApplication::UnicodeUTF8));
    label->setText(QApplication::translate("Form", "Nickname:", 0, QApplication::UnicodeUTF8));
    label_2->setText(QApplication::translate("Form", "Password:", 0, QApplication::UnicodeUTF8));
    radioButton->setText(QApplication::translate("Form", "Hostname:", 0, QApplication::UnicodeUTF8));
    pushButton->setText(QApplication::translate("Form", "Abbrechen", 0, QApplication::UnicodeUTF8));
    pushButton_2->setText(QApplication::translate("Form", "OK", 0, QApplication::UnicodeUTF8));
    label_3->setText(QApplication::translate("Form", "Port:", 0, QApplication::UnicodeUTF8));
    radioButton_2->setText(QApplication::translate("Form", "IP", 0, QApplication::UnicodeUTF8));
    Q_UNUSED(Form);
    } // retranslateUi

};

namespace Ui {
    class Form: public Ui_Form {};
} // namespace Ui

#endif // UI_CONNECTIONWINDOW_H
