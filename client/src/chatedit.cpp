#include "chatedit.h"


ChatEdit::ChatEdit(QWidget *parent) : QTextEdit(parent) {}

void ChatEdit::keyPressEvent (QKeyEvent * e) {
	if(e->key() == Qt::Key_Return) {
		if(e->modifiers() != Qt::ShiftModifier) {
			emit send();
		} else {
			insertPlainText("\n");
		}
	} else {
		QTextEdit::keyPressEvent(e);
	}
}
