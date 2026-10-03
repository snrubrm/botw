#pragma once

#include <container/seadBuffer.h>
#include <heap/seadDisposer.h>
#include <hostio/seadHostIONode.h>
#include "KingSystem/Utils/Types.h"
#include <prim/seadRuntimeTypeInfo.h>

namespace eui {

// The eui UI framework's screen base class (CSV: eui::Screen::*, mangled names). Only the parts that
// are needed so far are declared: the RTTI root (vtable slots 2 / 3 are checkDerivedRuntimeTypeInfo /
// getRuntimeTypeInfo) and the screen manager's screen table.
// eui::Screen derives from sead::IDisposer (offset 0) and sead::hostio::Node (offset 0x20: the vtable
// stored at 0x20 has Node::getNodeClassType first); its own data follows (0x28 - 0x108).
class Screen : public sead::IDisposer, public sead::hostio::Node {
public:
    ~Screen() override;
    SEAD_RTTI_BASE(Screen)

    virtual s32 m4();
    // Slots 5 / 6 (CSV Screen::open / Screen::close); the argument is an open / close option
    // (-1 / -4 are passed to close by the facade functions).
    virtual void open(s32 option);
    virtual void close(s32 option);
    // Slots 7-68 (CSV eui::Screen::* names: adjstBoxCursor, createBoxCursorNode, initialize, update, draw, ...);
    // placeholders so that the vtable layout is right.
    virtual void m7();
    virtual void m8();
    virtual void m9();
    virtual void m10();
    virtual void m11();
    virtual void m12();
    virtual void m13();
    virtual void m14();
    virtual void m15();
    virtual void m16();
    virtual void m17();
    virtual void m18();
    virtual void m19();
    virtual void m20();
    virtual void m21();
    virtual void m22();
    virtual void m23();
    virtual void m24();
    virtual void m25();
    virtual void m26();
    virtual void m27();
    virtual void m28();
    virtual void m29();
    virtual void m30();
    virtual void m31();
    virtual void m32();
    virtual void m33();
    virtual void m34();
    virtual void m35();
    virtual void m36();
    virtual void m37();
    virtual void m38();
    virtual void m39();
    virtual void m40();
    virtual void m41();
    virtual void m42();
    virtual void m43();
    virtual void m44();
    virtual void m45();
    virtual void m46();
    virtual void m47();
    virtual void m48();
    virtual void m49();
    virtual void m50();
    virtual void m51();
    virtual void m52();
    virtual void m53();
    virtual void m54();
    virtual void m55();
    virtual void m56();
    virtual void m57();
    virtual void m58();
    virtual void m59();
    virtual void m60();
    virtual void m61();
    virtual void m62();
    virtual void m63();
    virtual void m64();
    virtual void m65();
    virtual void m66();
    virtual void m67();
    virtual void m68();

    // 0x7100be9768 / 0x7100be978c / 0x7100be934c / 0x7100be97c4 (CSV; the last two are named
    // Screen::isClosed / isClosedOrClosing there)
    bool isOpened() const;
    bool isOpening() const;
    bool isClosed() const;
    bool isClosedOrClosing() const;

    u8 _28[0x108 - 0x28];
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
