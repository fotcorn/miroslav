#include <QListView>
#include <QMouseEvent>


class ListView : public QListView {
	
	public:
	ListView(QWidget *parent) : QListView(parent) {}
	
	protected:
	void mouseDoubleClickEvent(QMouseEvent *e) {
		e->accept();
	}
};
