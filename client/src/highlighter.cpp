#include "highlighter.h"

#include <QBrush>
#include <QTextEdit>

Highlighter::Highlighter(QTextEdit *parent) : QSyntaxHighlighter(parent) {
	messageInput = parent;
	format = new QTextCharFormat();
	format->setFontWeight(QFont::Normal);
	format->setFontItalic(false);
	format->setFontUnderline(false);
	format->setForeground(QBrush(QColor(0,0,0)));
	color = QColor(0,0,0);
}

QString Highlighter::getStyleString() {
	QString styleString = "";
	if(format->fontWeight() == QFont::Bold) {
		styleString += "b";
	}
	if(format->fontItalic()) {
		styleString += "i";
	}
	
	if(format->fontUnderline()) {
		styleString += "u";
	}
	return styleString;
}

QString Highlighter::getColorString() {
	QString colorString = "#";
	
	QString cs = QString::number(color.red(),16);
	if(cs.length() == 1) {
		cs.prepend("0");
	}
	colorString += cs;
	
	cs = QString::number(color.green(),16);
	if(cs.length() == 1) {
		cs.prepend("0");
	}
	colorString += cs;
	
	cs = QString::number(color.blue(),16);
	if(cs.length() == 1) {
		cs.prepend("0");
	}
	colorString += cs;
	
	return colorString;
}

// slots
void Highlighter::setColor(QColor newColor) {
	color = newColor;
	format->setForeground(QBrush(color));
	QString text = messageInput->toPlainText();
	messageInput->setPlainText(text);
}
void Highlighter::setBold(bool test) {
	if(test) {
		format->setFontWeight(QFont::Bold);
	} else {
		format->setFontWeight(QFont::Normal);
	}
	QString text = messageInput->toPlainText();
	messageInput->setPlainText(text);
}
void Highlighter::setItalic(bool test) {
	format->setFontItalic(test);
	QString text = messageInput->toPlainText();
	messageInput->setPlainText(text);
}
void Highlighter::setUnderline(bool test) {
	format->setFontUnderline(test);
	QString text = messageInput->toPlainText();
	messageInput->setPlainText(text);
}

void Highlighter::highlightBlock(const QString &text) {
	setFormat(0, text.length(), *format);
}
