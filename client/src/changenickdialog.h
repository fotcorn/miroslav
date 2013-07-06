#include <QDialog>

class QVBoxLayout;
class QHBoxLayout;

class QLabel;
class QLineEdit;
class QPushButton;


class ChangeNickDialog : public QDialog {
	
	Q_OBJECT
	
	QVBoxLayout *mainLayout;
	
	QLabel *label;
	QLineEdit *edit;
	
	QHBoxLayout *buttonLayout;
	
	QPushButton *okButton;
	QPushButton *cancelButton;
	
	public:
	ChangeNickDialog(QWidget *parent = 0);
	QString nick;
	
	public slots:
	void okClicked();
	
};
