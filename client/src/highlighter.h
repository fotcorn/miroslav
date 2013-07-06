#include <QSyntaxHighlighter>

#include <QColor>

class QTextCharFormat;
class QTextEdit;

class Highlighter : public QSyntaxHighlighter {

	Q_OBJECT
	
	QTextCharFormat* format;
	
	QString colorString;
	QString styleString;
	
	QColor color;
	
	QTextEdit *messageInput;
	
	protected:
	void highlightBlock(const QString &text);
	
	public:
	Highlighter(QTextEdit *parent = 0);
	QString getStyleString();
	QString getColorString();
	
	public slots:
	void setColor(QColor color);
	void setBold(bool test);
	void setItalic(bool test);
	void setUnderline(bool test);
};
