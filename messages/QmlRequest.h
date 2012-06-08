#ifndef QMLREQUEST_H
#define QMLREQUEST_H
#include "Message.h"
#include <string>

class QmlRequest : public MessageImplementation<QmlRequest>
{
public:
    QmlRequest(const std::string& url);
    const std::string& getUrl() const;
private:
    std::string m_url;
};

#endif // QMLREQUEST_H
