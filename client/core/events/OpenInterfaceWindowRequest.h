#ifndef OPENINTERFACEWINDOWREQUEST_H
#define OPENINTERFACEWINDOWREQUEST_H
#include "Event.h"
#include <string>

class OpenInterfaceWindowRequest : public EventImplementation<OpenInterfaceWindowRequest>
{
public:
    OpenInterfaceWindowRequest(const std::string& requestedQml);
    const std::string& getRequestedQml() { return m_requestedQml; }

private:
    std::string m_requestedQml;
};

#endif // OPENINTERFACEWINDOWREQUEST_H
