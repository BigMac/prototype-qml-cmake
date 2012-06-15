#ifndef RESOURCERESPONSE_H
#define RESOURCERESPONSE_H
#include "../Message.h"
#include <vector>
#include <string>

class ResourceRequest;
class ResourceResponse : public MessageImplementation<ResourceResponse>
{
public:
    ResourceResponse();
    ResourceResponse(const ResourceRequest& request);
    void setSuccess(bool val);
    const std::string& getRequestedUrl() const;
    const std::vector<char>& getData() const;
    std::string getDataAsString() const;
    void setData(const std::vector<char>& data);
    void setData(const std::string& data);

    virtual SerializedMessage serialize() const;
    static std::shared_ptr<ResourceResponse> deserialize(SerializedMessage& serialized);
private:
    bool m_success;
    std::string m_url;
    std::vector<char> m_data;
};

#endif // RESOURCERESPONSE_H
