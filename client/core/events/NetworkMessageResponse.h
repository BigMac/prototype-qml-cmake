#ifndef NETWORKREQUEST_H
#define NETWORKREQUEST_H
#include "Event.h"

class NetworkMessageResponse : public EventImplementation<NetworkMessageResponse>
{
public:
    NetworkMessageResponse();
};

#endif // NETWORKREQUEST_H
