#ifndef INVENTORYGUI_H
#define INVENTORYGUI_H
#include <qdeclarative.h>
#include <memory>

class InventoryCore;

class InventoryGUI : public QObject
{
    Q_OBJECT
public:
    InventoryGUI();
    void attachCore(std::shared_ptr<InventoryCore> inventoryCore)
    {
        m_inventoryCore = inventoryCore;
    }

private:
    std::shared_ptr<InventoryCore> m_inventoryCore;
};

#endif // INVENTORYGUI_H
