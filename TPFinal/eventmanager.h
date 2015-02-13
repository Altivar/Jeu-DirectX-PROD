#pragma once

#include <map>
#include <string>
#include <functional>

class EventArgs;

class EventManager
{
public:
	//Methods
	static EventManager& Instance();
	void RegisterEvent(std::string eventName, std::function<void(EventArgs)> funct);
	void UnregisterEvent(std::string eventName, std::function<void(EventArgs)> funct);
	void FireEvent(std::string eventName, EventArgs args);
	void FireEvent(std::string eventName);
	
private:
	EventManager(void);
	~EventManager(void);

	std::multimap<std::string, std::function<void(EventArgs)>> _eventsMap;

	static EventManager _instance;
};

