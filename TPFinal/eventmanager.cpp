#include "EventManager.h"
#include "args.h"

// memory leaks
#include <crtdbg.h>
#ifdef _DEBUG 
  #define new new( _CLIENT_BLOCK, __FILE__, __LINE__)
#endif // _DEBUG

EventManager EventManager::_instance = EventManager();

EventManager::EventManager(void)
{
	
}

EventManager::~EventManager(void)
{

}

EventManager& EventManager::Instance()
{
	return _instance;
}

void EventManager::FireEvent(std::string eventName, EventArgs args)
{
	if(_eventsMap.find(eventName) != _eventsMap.end())
	{
		std::pair <std::multimap<std::string, std::function<void(EventArgs)>>::iterator, std::multimap<std::string, std::function<void(EventArgs)>>::iterator> ret;
		ret = _eventsMap.equal_range(eventName);
		for(std::multimap<std::string, std::function<void(EventArgs)>>::iterator it=ret.first; it!=ret.second; ++it)
		{
			it->second(args);
		}
	}
}

void EventManager::FireEvent(std::string eventName)
{
	if(_eventsMap.find(eventName) != _eventsMap.end())
	{
		std::pair <std::multimap<std::string, std::function<void(EventArgs)>>::iterator, std::multimap<std::string, std::function<void(EventArgs)>>::iterator> ret;
		ret = _eventsMap.equal_range(eventName);
		for(std::multimap<std::string, std::function<void(EventArgs)>>::iterator it=ret.first; it!=ret.second; ++it)
		{
			it->second(EventArgs());
		}
	}
}

void EventManager::RegisterEvent(std::string eventName, std::function<void(EventArgs)> funct)
{
	_eventsMap.insert(std::pair<std::string, std::function<void(EventArgs)>>(eventName, funct));
}

void EventManager::UnregisterEvent(std::string eventName, std::function<void(EventArgs)> funct)
{
	if(_eventsMap.find(eventName) != _eventsMap.end())
	{
		std::multimap<std::string, std::function<void(EventArgs)>>::iterator itToDelete = _eventsMap.end();
		std::pair <std::multimap<std::string, std::function<void(EventArgs)>>::iterator, std::multimap<std::string, std::function<void(EventArgs)>>::iterator> ret;
		ret = _eventsMap.equal_range(eventName);
		for(std::multimap<std::string, std::function<void(EventArgs)>>::iterator it=ret.first; it!=ret.second || itToDelete == _eventsMap.end(); ++it)
		{
			if(typeid(it->second) == typeid(funct))
			{
				itToDelete = it;
			}
		}
		if(itToDelete != _eventsMap.end())
		{
			_eventsMap.erase(itToDelete);
		}
	}
}