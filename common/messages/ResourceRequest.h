#ifndef RESOURCEREQUEST_H
#define RESOURCEREQUEST_H
#include "Message.h"
#include <string>
#include <boost/serialization/string.hpp>

class ResourceRequest : public MessageImplementation<ResourceRequest>
{
    friend class boost::serialization::access;
    template<class Archive>
    void serialize(Archive & ar, const unsigned int)
    {
        ar & boost::serialization::base_object<Message>(*this);
        ar & m_resourceIsBinary;
        ar & m_url;
    }
public:
    ResourceRequest(const std::string& url, bool binary = false);
    const std::string& getUrl() const;
    bool isResourceBinary() { return m_resourceIsBinary; }
private:
    ResourceRequest();
    bool m_resourceIsBinary;
    std::string m_url;
};

#endif // RESOURCEREQUEST_H
