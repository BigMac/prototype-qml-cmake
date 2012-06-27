#ifndef THREADSAFEDECLARATIVEVIEW_H
#define THREADSAFEDECLARATIVEVIEW_H
#include <QDeclarativeView>

class ThreadSafeDeclarativeView : public QDeclarativeView
{
    Q_OBJECT
public:
    ThreadSafeDeclarativeView(QWidget* parent = NULL);
public Q_SLOTS:
    void loadResources(QUrl source);
};

#endif // THREADSAFEDECLARATIVEVIEW_H
