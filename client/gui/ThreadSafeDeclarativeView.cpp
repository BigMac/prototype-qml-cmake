#include "ThreadSafeDeclarativeView.h"

ThreadSafeDeclarativeView::ThreadSafeDeclarativeView(QWidget* parent) :
    QDeclarativeView(parent)
{
}

void ThreadSafeDeclarativeView::loadResources(QUrl source)
{
    setSource(source);
    show();
}
