#pragma once
#include "Event.h"

class GuiResourceResponse : public EventImplementation<GuiResourceResponse>
{
public:
    GuiResourceResponse(const std::string& url);
    const std::string& getUrl() const { return m_url; }
    const std::vector<char>& getData() const { return data; }
private:
    std::string m_url;
    std::vector<char> data;
};

