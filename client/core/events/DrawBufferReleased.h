#ifndef DRAWBUFFERRELEASED_H
#define DRAWBUFFERRELEASED_H
#include "Event.h"

class DrawBufferReleased : public EventImplementation<DrawBufferReleased>
{
public:
    DrawBufferReleased(/* pointer to buffer? */);
};
#endif // DRAWBUFFERRELEASED_H
