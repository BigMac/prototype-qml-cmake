#ifndef QTSERVICEFSMEVENTS_H
#define QTSERVICEFSMEVENTS_H
#include <string>

// Events, in addition to common client events
struct ResourceNeeded
{
public:
    ResourceNeeded(const std::string& url) : m_url(url) {}
    const std::string& getUrl() const { return m_url; }
private:
    std::string m_url;
};

struct DrawBufferNeeded
{};

#endif // QTSERVICEFSMEVENTS_H
