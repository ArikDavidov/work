#ifndef __DIGITAL_CAT_H__
#define __DIGITAL_CAT_H__

#include "SmartHomeAPI.h"

#include <string>
#include <iostream>
#include <pthread.h>
#include <unistd.h>
#include <sstream>
#include <assert.h>
#include <stdlib.h>
#include <tr1/memory>

class AgentData;


class TempEvent : public Event {
public:
    explicit TempEvent(std::string _topic, std::string _floor,
                       std::string _room, int _temp)
               : Event(_topic, _floor, _room), m_temp(_temp){}
    virtual ~TempEvent(){    std::cout << "TempEvent::DTOR" << std::endl; }    
//    const std::string& Topic() const;
//    const std::string& Floor() const;
//    const std::string& Room()  const;
    int Temp() const { return m_temp; }
private:
    TempEvent(const TempEvent&);
    TempEvent& operator=(const TempEvent&);
private:
    int m_temp;
};

class DigitalCat800 : public Sensor
{
        friend class DigitalCatFactory;
public:
    ~DigitalCat800(){
        std::cout << "DigitalCat800::~DTOR\n";
        pthread_cancel(m_thread);
        int err = pthread_join(m_thread, 0);
        if (0 != err){
            errno = err;
            perror("pthread_join");
        }
    }
private:
    DigitalCat800(AgentData* _agentData, ISubscriber* _hub)
    : Sensor(_agentData, _hub) {}
    void Start(){
        int err;
        if (0 != (err = pthread_create(&m_thread, 0, &Run, (void*)this))){
            errno = err;
            perror("pthread_create");
        }
    }
    static void* Run(void* _context){
        assert(_context);
        std::cout << "DigitalCat800::Run" << std::endl;
        DigitalCat800* pThis = (DigitalCat800*)_context;
        int temp;
        for (int i = 0; i < 1; ++i)
        {
            temp = rand() % 60 - 5;
            std::tr1::shared_ptr<TempEvent> sp(new TempEvent("Temperature", pThis->m_agentData->Floor(), pThis->m_agentData->Room(), temp));
            pThis->Publish(sp);
            usleep(1000000);
        }

        return 0;
    }
    std::string Itoa(int _i){
        std::ostringstream ss;
        ss << _i;
        return ss.str();
    }
private:
    pthread_t m_thread;
};

class DigitalCat900 : public Controller
{
    friend class DigitalCatFactory;
public:
    ~DigitalCat900()    { std::cout << "DigitalCat900::~DTOR\n"; }

private:
    DigitalCat900(AgentData* _agentData, ISubscriber* _hub)
    : Controller(_agentData, _hub) {
        EventFilter* eventFilter = new EventFilter("Temperature", "3", "42");
        ((Hub*)m_hub)->Subscribe(this, eventFilter);
    }
};

class DigitalCatFactory {
	static unsigned s_posNextGet;
	static const std::string s_supportedTypes[];
public:
    static Agent* CreateDigitalCat(AgentData* _agentData, ISubscriber* _hub);
    static std::string GetNextSupported();
    
private:
    DigitalCatFactory();
    DigitalCatFactory(const DigitalCatFactory&);
    DigitalCatFactory& operator=(const DigitalCatFactory&);
};


#endif // __DIGITAL_CAT_H__



