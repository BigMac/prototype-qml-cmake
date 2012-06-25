#ifndef IRESOURCEHANDLER_H
#define IRESOURCEHANDLER_H
#include <string>
#include <functional>
#include <vector>

typedef std::function<void(const std::string& url, std::vector<char> data)>
RequestArrivedCallback;

class IResourceHandler
{
public:
    virtual void resourceNeeded(const std::string& url,
                                RequestArrivedCallback callback) = 0;
};

#endif // IRESOURCEHANDLER_H
