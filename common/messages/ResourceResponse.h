#ifndef RESOURCERESPONSE_H
#define RESOURCERESPONSE_H
#include "../Message.h"
#include <vector>
#include <string>
#include <boost/serialization/vector.hpp>
#include <boost/serialization/string.hpp>

class ResourceRequest;
class ResourceResponse : public MessageImplementation<ResourceResponse>
{
    friend class boost::serialization::access;
    template<class Archive>
    void serialize(Archive & ar, const unsigned int)
    {
        boost::serialization::base_object<Message>(*this);
        ar & m_success;
        ar & m_url;
        ar & m_data;
    }

public:
    ResourceResponse();
    ResourceResponse(const ResourceRequest& request);
    void setSuccess(bool val);
    const std::string& getRequestedUrl() const;
    const std::vector<char>& getData() const;
    std::string getDataAsString() const;
    void setData(const std::vector<char>& data);
    void setData(const std::string& data);
private:
    bool m_success;
    std::string m_url;
    std::vector<char> m_data;
};

BOOST_CLASS_EXPORT_KEY(ResourceResponse)

#endif // RESOURCERESPONSE_H
