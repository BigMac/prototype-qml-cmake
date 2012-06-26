#ifndef QTSERVICEFACTORY_H
#define QTSERVICEFACTORY_H
#include <memory>

class QtService;
class Dispatcher;
class QtServiceFactory
{
public:
    static std::shared_ptr<QtService> create(
            std::shared_ptr<Dispatcher> dispatcher,
            int& argc,
            char**& argv);
};

#endif // QTSERVICEFACTORY_H
