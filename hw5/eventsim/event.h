#ifndef EVENT_H
#define EVENT_H
#include <vector>

static int const SCALE_FACTOR = 1000;
typedef unsigned int TimeStamp;

// forward declaration so we can create EventList typedef
class Event;
typedef std::vector<Event*> EventList;

class Event
{
public:
    /**
     * Event constructor
     *
     * @param[in] ts
     *   Timestamp the event should be processed
     */
    Event(const TimeStamp& ts) : ts_(ts) {}

    /**
     * Virtual destructor
     */
    virtual ~Event() {}

    /**
     * Process the event
     *
     * @return
     *   list of new events generated by processing this event
     */
    virtual EventList process() = 0;

    /**
     * Returns the timestamp for this event
     */
    const TimeStamp& timeStamp() const {
        return ts_;
    }

    /**
     * Returns the sub priority for a given event (in the case that
     * timestamps are equal, the subpriorities will determine which
     * event is processed first)
     *
     */
    virtual unsigned int getSubPriority() const = 0 ;

private:
    TimeStamp ts_;
};
#endif
