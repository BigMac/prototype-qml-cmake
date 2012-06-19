#ifndef RESOURCEREPOSITORY_H
#define RESOURCEREPOSITORY_H
#include "messages/MessageReceiver.h"
#include <functional>

class ResourceRepository : protected MessageReceiver
{
public:
    ResourceRepository();
    void requestResource(const std::string url,
                         std::function<void(ResourceResponse)> completionCallback);
protected:
    virtual void receive(ResourceResponse &);
};

#endif // RESOURCEREPOSITORY_H
