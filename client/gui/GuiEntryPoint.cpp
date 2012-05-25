#include "GuiEntryPoint.h"
#include "InventoryGUI.h"
#include "core/InventoryCore.h"

GuiEntryPoint::GuiEntryPoint()
{
}

int GuiEntryPoint::exec(int argc, char *argv[], std::shared_ptr<InventoryCore> core)
{
    std::shared_ptr<InventoryGUI> gui = std::make_shared<InventoryGUI>();
    gui->attachCore(core);

    return 0;
}
