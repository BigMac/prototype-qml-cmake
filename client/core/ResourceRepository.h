#ifndef RESOURCEREPOSITORY_H
#define RESOURCEREPOSITORY_H
#include <functional>
#include <map>
#include <string>
#include "messages/Message.h"

class ResourceResponse;
class ResourceRepository
{
public:
    ResourceRepository();

    typedef std::function<void(const ResourceResponse&)> CompletionCallback_t;
    void requestResource(const std::string url,
                         CompletionCallback_t completionCallback);

    void receive(const ResourceResponse &);
protected:
    std::map<transactionId_t, CompletionCallback_t> m_callbacks;
    transactionId_t m_nextTransactionId;
};

#endif // RESOURCEREPOSITORY_H
