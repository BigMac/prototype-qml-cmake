#include "gui/GuiEntryPoint.h"
#include "core/InventoryCore.h"


int main(int argc, char *argv[])
{
    GuiEntryPoint entryPoint;
    std::shared_ptr<InventoryCore> core = std::make_shared<InventoryCore>();
    return entryPoint.exec(argc, argv, core);
}
