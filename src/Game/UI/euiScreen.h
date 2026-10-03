#pragma once

#include <container/seadBuffer.h>
#include <heap/seadDisposer.h>
#include "KingSystem/Utils/Types.h"
#include <prim/seadRuntimeTypeInfo.h>

namespace eui {

// The eui UI framework's screen base class (CSV: eui::Screen::*, mangled names). Only the parts that
// are needed so far are declared: the RTTI root (vtable slots 2 / 3 are checkDerivedRuntimeTypeInfo /
// getRuntimeTypeInfo) and the screen manager's screen table.
// The secondary base of eui::Screen at offset 0x20 (vptr + 3 words; unknown, placeholder).
class ScreenBase0x20 {
public:
    virtual void x0();
    u8 _8[0x18];
};

class Screen : public sead::IDisposer, public ScreenBase0x20 {
public:
    ~Screen() override;
    SEAD_RTTI_BASE(Screen)

    virtual s32 m4();
    // Slots 5 / 6 (CSV Screen::open / Screen::close); the argument is an open / close option
    // (-1 / -4 are passed to close by the facade functions).
    virtual void open(s32 option);
    virtual void close(s32 option);

    // 0x7100be9768 / 0x7100be978c / 0x7100be934c / 0x7100be97c4 (CSV; the last two are named
    // Screen::isClosed / isClosedOrClosing there)
    bool isOpened() const;
    bool isOpening() const;
    bool isClosed() const;
    bool isClosedOrClosing() const;

    u8 _40[0x108 - 0x40];
};
KSYS_CHECK_SIZE_NX150(Screen, 0x108);

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
