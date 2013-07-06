#include <QTextEdit>
#include <QKeyEvent>

class ChatEdit : public QTextEdit {

	Q_OBJECT
	
	public:
	ChatEdit(QWidget *parent = 0);
	
	protected:
	void keyPressEvent (QKeyEvent *e);
	
	signals:
	void send();
	
};
