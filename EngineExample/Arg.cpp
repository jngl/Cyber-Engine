#include "Arg.hpp"

#include <cmdline.h>
#include <CyberBase.hpp>

Arg::Arg(int argc, char *argv[]){
    cmdline::parser a;

    a.add<int>("width", 'w', "width of the window", false, 1024,
                cmdline::range(1, 65535));
    a.add<int>("height", 'h', "height of the window", false, 768,
                cmdline::range(1, 65535));
    a.add<std::string>("scene", 's', "the scene to run", false, "Boxel",
                        cmdline::oneof<std::string>("Boxel", "Basic"));

    a.parse_check(argc, argv);
    
    width = a.get<int>("width");
    height = a.get<int>("height");
    sceneName = a.get<std::string>("scene");

    CB_LOG_INFO<<"Width="<<width<<" ; Height="<<height<<" ; scene="<<sceneName;
}