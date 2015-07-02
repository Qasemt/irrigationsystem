#include <QApplication>
class MyApplication : public QApplication {
public:
    MyApplication(int& argc, char** argv);
    bool notify(QObject* receiver, QEvent* event);
};
