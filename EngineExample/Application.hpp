#pragma once

#include <string>
#include <memory>

#include <CyberEngine.hpp>

#include "BasicScene.hpp"

#include "Arg.hpp"

class Application {
public:
  Application(int argc, char *argv[]);
  ~Application();
  void run();

private:
  static constexpr unsigned int mMaxInputSize = 32; 
  
  std::unique_ptr<Window> mWindow;
  std::unique_ptr<Scene> mScene;
  Timer mGlobalTimer;
  float mFrameTime;
  bool mShowTestWindow;
  bool mShowInfoWindow;
  char mCommandText[mMaxInputSize];
  std::string mConsoleText;

  void changeScene(std::string name);
  void frame();
  void runCommand();
  void printConsole(std::string msg);
};