#pragma once
#include "Event.h"

class DrawBufferReleased : public EventImplementation<DrawBufferReleased>
{
public:
    DrawBufferReleased(/* pointer to buffer? */);
};
