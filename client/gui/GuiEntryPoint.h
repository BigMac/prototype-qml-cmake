#ifndef GUIENTRYPOINT_H
#define GUIENTRYPOINT_H
#include <memory>

class InventoryCore;
class GuiEntryPoint
{
public:
    GuiEntryPoint();
    int exec(int argc, char *argv[], std::shared_ptr<InventoryCore> core);
};

#endif // GUIENTRYPOINT_H
