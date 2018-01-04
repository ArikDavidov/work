#ifndef __EVENT_H__
#define __EVENT_H__

#include <tr1/memory>   // std::tr1::shared_ptr
#include <string>


class Event
{
public:
//    typedef std::tr1::shared_ptr<Event> sp;
    
    explicit Event(std::string _topic, std::string _floor, 
                   std::string _room);
    virtual ~Event();
    
    const std::string& Topic() const;
    const std::string& Floor() const;
    const std::string& Room()  const;

private:	
    Event(const Event&);
    Event& operator=(const Event&);
     
private:
    std::string m_topic;
    std::string m_floor;
    std::string m_room;
//    std::string m_timestamp;
};


inline const std::string& Event::Topic() const
{
    return m_topic;
}

inline const std::string& Event::Floor() const
{
    return m_floor;
}

inline const std::string& Event::Room() const
{
    return m_room;
}


#endif    // __EVENT_H__


