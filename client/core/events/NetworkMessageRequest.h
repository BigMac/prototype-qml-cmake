#ifndef NETWORKREQUEST_H
#define NETWORKREQUEST_H
#include "Event.h"

class NetworkMessageRequest : public EventImplementation<NetworkMessageRequest>
{
public:
    NetworkMessageRequest();
};

#endif // NETWORKREQUEST_H
