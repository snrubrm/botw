#pragma once

#include <container/seadBuffer.h>
#include <heap/seadDisposer.h>
#include <prim/seadRuntimeTypeInfo.h>

namespace eui {

// The eui UI framework's screen base class (CSV: eui::Screen::*, mangled names). Only the parts that
// are needed so far are declared: the RTTI root (vtable slots 2 / 3 are checkDerivedRuntimeTypeInfo /
// getRuntimeTypeInfo) and the screen manager's screen table.
class Screen {
public:
    virtual ~Screen();
    SEAD_RTTI_BASE(Screen)
};

// The screen manager singleton (CSV: eui::ScreenMgr::*, sInstance 0x71025fcc68). The table of loaded
// screens is a sead::Buffer (count at 0x28, pointer at 0x30) indexed by the screen id of
// uking::ui::ScreenFactory::create.
class ScreenMgr {
    SEAD_SINGLETON_DISPOSER(ScreenMgr)
    ScreenMgr();

public:
    virtual ~ScreenMgr();

    Screen* getScreen(s32 id) { return mScreens[id]; }

private:
    // The singleton disposer is at 0x8 (CSV: createInstance 0x7100bec0a4, object size 0xb50).
    sead::Buffer<Screen*> mScreens;
};

}  // namespace eui
