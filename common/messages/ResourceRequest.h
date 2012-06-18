#ifndef RESOURCEREQUEST_H
#define RESOURCEREQUEST_H
#include "../Message.h"
#include <string>
#include <boost/serialization/string.hpp>

class ResourceRequest : public MessageImplementation<ResourceRequest>
{
    friend class boost::serialization::access;
    template<class Archive>
    void serialize(Archive & ar, const unsigned int)
    {
        boost::serialization::base_object<Message>(*this);
        ar & m_url;
    }
public:
    ResourceRequest(const std::string& url);
    const std::string& getUrl() const;
private:
    ResourceRequest();
    std::string m_url;
};

BOOST_CLASS_EXPORT_KEY(ResourceRequest)

#endif // RESOURCEREQUEST_H
