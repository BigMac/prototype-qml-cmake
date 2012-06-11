#ifndef QMLREQUEST_H
#define QMLREQUEST_H
#include "Message.h"
#include <boost/serialization/export.hpp>
#include <string>

class QmlRequest : public MessageImplementation<QmlRequest>
{
    friend class boost::serialization::access;
    template<class Archive>
    void serialize(Archive & ar, const unsigned int file_version)
    {
        boost::serialization::base_object<MessageImplementation<QmlRequest>>(*this);
        ar & m_url;
    }
public:
    QmlRequest(const std::string& url);
    const std::string& getUrl() const;
private:
    std::string m_url;
};

#endif // QMLREQUEST_H
