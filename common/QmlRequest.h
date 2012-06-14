#ifndef QMLREQUEST_H
#define QMLREQUEST_H
#include "Message.h"
#include <string>

class QmlRequest : public MessageImplementation<QmlRequest>
{
public:
    QmlRequest();
    QmlRequest(const std::string& url);
    const std::string& getUrl() const;
    virtual SerializedMessage serialize() const;
    static std::shared_ptr<QmlRequest> deserialize(SerializedMessage& serialized);
private:
    std::string m_url;
};

#include "MessageRegistry.h"
REGISTER_BUILDER("QmlRequest", &QmlRequest::deserialize)

#endif // QMLREQUEST_H
