#include <CyberBase.hpp>

#include "Application.hpp"

int main(int argc, char *argv[]) {
  cb::addDefaultLogOutput();
  Application app(argc, argv);
  CB_LOG_INFO<<"begin main loop";
  app.run();
  CB_LOG_INFO<<"end main loop";
  return 0;
}
