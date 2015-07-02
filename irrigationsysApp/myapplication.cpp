#include "myapplication.h"

#include <exception>
#include <QDebug>
#include <typeinfo>
MyApplication::MyApplication(int& argc, char** argv) :
  QApplication(argc, argv) {}

bool MyApplication::notify(QObject* receiver, QEvent* event) {
    try {
           return QApplication::notify(receiver, event);
       } catch (std::exception &e) {
           qFatal("Error %s sending event %s to object %s (%s)",
               e.what(), typeid(*event).name(), qPrintable(receiver->objectName()),
               typeid(*receiver).name());
       } catch (...) {
           qFatal("Error <unknown> sending event %s to object %s (%s)",
               typeid(*event).name(), qPrintable(receiver->objectName()),
               typeid(*receiver).name());
       }

       // qFatal aborts, so this isn't really necessary
       // but you might continue if you use a different logging lib
       return false;
}
