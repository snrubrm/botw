#pragma once

#include <basis/seadTypes.h>
#include <heap/seadDisposer.h>

namespace uking::ui {

// Placeholder declaration (name from the CSV: UiShopMgr::createInstance 0x7100980794, deleteInstance
// 0x7100980910; instance pointer at 0x71025d7ae0; namespace is a guess). The shop UI manager; only
// what the AI classes use is declared.
// TODO: incomplete.
class UiShopMgr {
    SEAD_SINGLETON_DISPOSER(UiShopMgr)
    UiShopMgr();
    ~UiShopMgr();

public:
    // 0x7100985508 (declaration only; NPCClerkRoot::leave_): `_140.reset()`.
    void sub_7100985508();
};

}  // namespace uking::ui
