#include "Application.hpp"

#include "filesystem.hpp"
#include "Renderer.hpp"
#include "BoxelScene/BoxelScene.hpp"

#include <imgui.h>

Application::Application(int argc, char *argv[]):
    mShowTestWindow(false),
    mShowInfoWindow(false),
    mCommandText("")
{
    Arg arg(argc, argv);

    filesystem::createFileSystem();

    mWindow.reset(new Window(arg.width, arg.height));
    mWindow->addAction(SDL_SCANCODE_F3, &mShowInfoWindow, false);

    Renderer::createRenderer();
    
    changeScene(arg.sceneName);
    mScene->addAction(*mWindow);
}

Application::~Application(){
    mScene = nullptr;
    Renderer::destroyRenderer();
    filesystem::destroyFileSystem();
}

void Application::run(){
    while (mWindow->isRunning()) {
        frame();
    }
}

void Application::changeScene(std::string name) {
    if (name == "Boxel") {
        mScene.reset(new BoxelScene);
    } else {
        mScene.reset(new BasicScene);
    }
}

void Application::frame(){
    mFrameTime = mGlobalTimer.timeInSecond();
    mGlobalTimer.restart();

    mWindow->doEvent();

    int width, height;
    if (mWindow->getSize(&width, &height)) {
        Renderer::resize(width, height);
    }

    mWindow->clear();

    if (mShowInfoWindow) {
        ImGui::SetNextWindowSize(ImVec2(400, 100), ImGuiSetCond_FirstUseEver);
        ImGui::Begin("Info", &mShowInfoWindow);
        ImGui::Text("Application average %.3f ms/frame (%.1f FPS)",
            1000.0f / ImGui::GetIO().Framerate, ImGui::GetIO().Framerate);
        if (ImGui::Button("Test Window"))
    mShowTestWindow ^= 1;

        ImGui::Text("%s", mConsoleText.c_str());
        
        ImGui::InputText("command", mCommandText, mMaxInputSize);
        if (ImGui::Button("exec")){
    runCommand();
        }
        
        ImGui::End();
    }

    if (mShowTestWindow) {
        ImGui::SetNextWindowPos(ImVec2(650, 20), ImGuiSetCond_FirstUseEver);
        ImGui::ShowTestWindow(&mShowTestWindow);
    }

    mScene->update(mFrameTime);
    Renderer::renderAllObject();

    ImGui::Render();

    mWindow->endFrame();
}


void Application::runCommand(){
    CB_LOG_INFO<<"run command : "<< mCommandText;

    std::string command = mCommandText;
    memset(mCommandText, 0, mMaxInputSize);

    if(command=="exit"){
        mWindow->close();
    }else{
        printConsole("unkown command");
    }
}


void Application::printConsole(std::string msg){
    mConsoleText += ">"+msg+"\n";
}