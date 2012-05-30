#include "GuiEntryPoint.h"
#include "InventoryGUI.h"
#include "core/InventoryCore.h"
#include <QDeclarativeEngine>
#include <QDeclarativeComponent>
#include <QDeclarativeContext>
#include <QDeclarativeView>
#include <QApplication>

GuiEntryPoint::GuiEntryPoint()
{
}

int GuiEntryPoint::exec(int argc, char *argv[], std::shared_ptr<InventoryCore> core)
{
    std::shared_ptr<InventoryGUI> gui = std::make_shared<InventoryGUI>();
    gui->attachCore(core);

    QApplication app(argc, argv);
    QDeclarativeView view;
    view.setSource(QUrl::fromLocalFile("gui/main.qml"));
    view.setVisible(true);
    view.connect(view.engine(), SIGNAL(quit()), SLOT(close()));
    return app.exec();
}
