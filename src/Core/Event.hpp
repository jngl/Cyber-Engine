#pragma once

#include <list>
#include <functional>

namespace core
{
    template<class Event>
    class EventManager
    {
    public:
        typedef std::function<void(Event)> Listener;
        
        void send(Event e){
            for(Listener l : mListeners){
                l(e);
            }
        }
        
        void addListener(Listener l){
            mListeners.push_back(l);
        }
           
    private:
        std::list<Listener> mListeners;
    };
}
