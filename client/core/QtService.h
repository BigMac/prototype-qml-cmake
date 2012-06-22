#ifndef QTSERVICE_H
#define QTSERVICE_H
#include "Service.h"
#include "ConcurrentQueue.h"

class Dispatcher;
class QtService : public Service
{
public:
    QtService(std::weak_ptr<Dispatcher> dispatcher);

};

#endif // QTSERVICE_H
