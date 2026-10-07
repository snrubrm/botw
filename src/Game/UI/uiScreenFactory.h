#pragma once

#include "Game/UI/euiScreen.h"

namespace uking::ui {

// The screen factory (CSV ScreenFactory::*, vtable 0x710249ce60; no RTTI): the object at eui::ScreenMgr + 0x48.
// `create` (0x7100a81f34, 2.3 KB: the jump table over the screen ids) is not decompiled.
class ScreenFactory : public eui::ScreenTargetMgr {
public:
    ~ScreenFactory() override;
    // 0x7100a81f34 (CSV ScreenFactory::create; not decompiled)
    void m2() override;
    // 0x7100a82830 (CSV ScreenFactory::getName): the layout name of screen `id` (ids above 98 give the last name)
    const char* m3(s32 id) override;
    // 0x7100a82840 (CSV ScreenFactory::getCount)
    s32 m4() override;
    // 0x7100a82850 (CSV ScreenFactory::a)
    eui::DrawTarget getDrawTarget(u8 index) const override;
};

}  // namespace uking::ui
