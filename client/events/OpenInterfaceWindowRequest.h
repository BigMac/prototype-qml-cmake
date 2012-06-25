#pragma once
#include "Event.h"
#include <string>

class OpenInterfaceWindowRequest : public EventImplementation<OpenInterfaceWindowRequest>
{
public:
    OpenInterfaceWindowRequest(const std::string& requestedQml);
    const std::string& getUrl() const { return m_requestedQml; }

private:
    std::string m_requestedQml;
};

