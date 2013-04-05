#include <QtCore/QCoreApplication>

int main(int argc, char *argv[])
{
  // Not sure if this is of any use when we do not require an event
  // loop for the main thread.
  QCoreApplication a(argc, argv);
  
  //return a.exec();
  return 0;
}
