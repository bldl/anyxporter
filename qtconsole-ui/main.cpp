#include "engine.hpp"
#include <QtCore/QCoreApplication>

int main(int argc, char *argv[])
{
  // Not sure if this is of any use when we do not require an event
  // loop for the main thread.
  QCoreApplication app(argc, argv);
  
  engine::exportData();

  //return app.exec();
  return 0;
}
