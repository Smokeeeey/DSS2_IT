#include "event.h"
#define NULL ((void*)(0))

void Event_init(struct Event_* me)
{
    me->id = NULLEVENT;
    me->delay = 0;
    me->processEvent = NULL;
}


void Event_setPE(Event* me, processEventT processEvent)
{
    me->processEvent = processEvent;
}

processEventT Event_getPE(Event* me)
{
    return me->processEvent;
}

void Event_setId(Event* me, evIDT eventID)
{
    me->id = eventID;
}

evIDT Event_getId(Event* me)
{
    return me->id;
}

void Event_setDelay(Event* me, uint16_t delay)
{
    me->delay = delay;
}

uint16_t Event_getDelay(Event* me)
{
    return me->delay;
}