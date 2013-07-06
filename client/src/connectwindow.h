#include <QDialog>

class QGridLayout;

class QLabel;
class QLineEdit;
class QRadioButton;
class QCheckBox;
class QPushButton;

class ConnectWindow : public QDialog {

	
	Q_OBJECT
	
	QGridLayout *mainLayout;
	
	
	QLabel *nickLabel;
	QLineEdit *nickEdit;
	
	QLabel *passwordLabel;
	QLineEdit *passwordEdit;
	
	QRadioButton *hostRadio;
	QLineEdit *hostEdit;
	
	QRadioButton *ipRadio;
	QLineEdit *ipEdit;
	
	QLabel *portLabel;
	QLineEdit *portEdit;
	
	QCheckBox *settingsBox;
	//QCheckBox *passwordBox;
	
	QPushButton *cancelButton;
	QPushButton *okButton;
	
	public:
	ConnectWindow();
	
	QString nick;
	QString password;
	
	bool host;
	QString hostip;
	int port;
	
	bool saveSettings;
	//bool savePassword;
	
	private slots:
	void okClicked();
	void cancelClicked();

	//void settingsBoxChanged(int state);
};
