#pragma once
#include "Event.h"
#include <string>

class GuiResourceRequest : public EventImplementation<GuiResourceRequest>
{
public:
    GuiResourceRequest(const std::string& url);
private:
    std::string m_url;
};
