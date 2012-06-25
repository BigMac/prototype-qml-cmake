#include "GuiEntryPoint.h"
#include "NetworkAccessManager.h"
#include <QDeclarativeEngine>
#include <QDeclarativeComponent>
#include <QDeclarativeContext>
#include <QDeclarativeView>
#include <QtNetwork/QNetworkAccessManager>
#include <QApplication>
#include <QDebug>

GuiEntryPoint::GuiEntryPoint()
{
}

int GuiEntryPoint::exec(int argc, char *argv[], std::shared_ptr<InventoryCore> core)
{
//    QApplication app(argc, argv);
//    QDeclarativeView view;
//    view.engine()->setNetworkAccessManagerFactory(new NetworkAccessManagerFactory(*this));
//    view.setSource(QUrl("dupa://gui/qml/main.qml"));
//    view.setVisible(true);
//    view.connect(view.engine(), SIGNAL(quit()), SLOT(close()));

    /*QDeclarativeView view_sub(&view);
    view_sub.setSource(QUrl::fromLocalFile("http://gui/qml/sub.qml"));
    view_sub.setVisible(true);
    view_sub.connect(view_sub.engine(), SIGNAL(quit()), SLOT(close()));*/
    return 0;//app.exec();
}
