#include <QObject>

class NoMultiStart : public QObject {

	Q_OBJECT

	public:
	static bool start();
	static void stop();
};
