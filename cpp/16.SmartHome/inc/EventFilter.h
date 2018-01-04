#ifndef __EVENT_FILTER_H__
#define __EVENT_FILTER_H__

#include <string>

class EventFilter
{
public:
    explicit EventFilter(std::string _topic = 0, std::string _floor = 0,
                         std::string _room = 0);
    virtual ~EventFilter();
    
    const std::string& Topic() const;
    const std::string& Floor() const;
    const std::string& Room()  const;    
    
    friend std::ostream& operator<<(std::ostream& _os, EventFilter* _filter);

private:
    std::string m_topic;
    std::string m_floor;
    std::string m_room;
};


inline const std::string& EventFilter::Topic() const
{
    return m_topic;
}

inline const std::string& EventFilter::Floor() const
{
    return m_floor;
}

inline const std::string& EventFilter::Room() const
{
    return m_room;
}


#endif    // __EVENT_FILTER_H__

//    EventFilter(Event::sp _event);
//    bool operator<(const EventFilter& _eventFilter);
//    bool operator==(const EventFilter& _eventFilter);



