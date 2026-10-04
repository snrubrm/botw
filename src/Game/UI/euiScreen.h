#pragma once

#include <container/seadBuffer.h>
#include <heap/seadDisposer.h>
#include <hostio/seadHostIONode.h>
#include <math/seadBoundBox.h>
#include "KingSystem/Utils/Types.h"
#include <prim/seadRuntimeTypeInfo.h>
#include "Game/UI/euiButton.h"

namespace sead {
class Heap;
}

namespace xlink2 {
class UserInstanceSLink;
}

namespace eui {

class AnimButton;
class BoxCursorNode;
class ButtonGroup;
class ScreenMgr;

// (only the nested type is needed so far)
struct DrawInfoEx {
    struct RenderBufferInfo;
};

// The eui UI framework's screen base class (CSV: eui::Screen::*, mangled names). Only the parts that
// are needed so far are declared: the RTTI root (vtable slots 2 / 3 are checkDerivedRuntimeTypeInfo /
// getRuntimeTypeInfo) and the screen manager's screen table.
// eui::Screen derives from sead::IDisposer (offset 0) and sead::hostio::Node (offset 0x20: the vtable
// stored at 0x20 has Node::getNodeClassType first); its own data follows (0x28 - 0x108).
class Screen : public sead::IDisposer, public sead::hostio::Node {
public:
    ~Screen() override;
    SEAD_RTTI_BASE(Screen)

    virtual s32 isEnableControl() const;
    // Slots 5 / 6 (CSV Screen::open / Screen::close); the argument is an open / close option
    // (-1 / -4 are passed to close by the facade functions).
    virtual void open(s32 option);
    virtual void close(s32 option);
    // Slots 7-68 (CSV eui::Screen::* names: adjstBoxCursor, createBoxCursorNode, initialize, update, draw, ...);
    // placeholders so that the vtable layout is right.
    virtual void adjstBoxCursor(sead::BoundBox2<f32>* box, const BoxCursorNode* node) const;
    virtual void m8();
    virtual void m9();
    virtual void m10();
    virtual void draw(const DrawInfoEx::RenderBufferInfo* info);
    virtual void m12();
    virtual void m13();
    virtual void m14();
    virtual const char* m15() const;  // returns the layout name (<Name>_00) in the leaf classes
    virtual const char* getMessageName_() const;
    virtual const char* getArchiveName_() const;
    virtual bool isPlayPartsInOut_() const;  // slot 18
    virtual bool isDisallowHitLowerScreenOnButtonHit_() const;
    virtual void m20();
    virtual void m21();
    virtual void m22();
    virtual void doAfterBuildLayout_(sead::Heap* heap);
    virtual void m24();
    virtual void m25();
    virtual void m26();
    virtual void m27();
    virtual void m28();
    virtual void doLoadResource_(sead::Heap* heap);
    virtual void doInitialize_(sead::Heap* heap);
    virtual void doUpdate_();
    virtual f32 m32();
    virtual void doDraw_(const DrawInfoEx::RenderBufferInfo* info);
    virtual void doOpenStart_();
    virtual void doOpenEnd_();
    virtual void doCloseStart_();
    virtual void doCloseEnd_();
    virtual void doButtonOnStart_(AnimButton* button);
    virtual void doButtonOnEnd_(AnimButton* button);
    virtual void doButtonOffStart_(AnimButton* button);
    virtual void doButtonOffEnd_(AnimButton* button);
    virtual void doButtonDownStart_(AnimButton* button);
    virtual void doButtonDownEnd_(AnimButton* button);
    virtual void doButtonCancelStart_(AnimButton* button);
    virtual void doButtonCancelEnd_(AnimButton* button);
    virtual void* getElinkSystem_() const;
    virtual void m47();
    virtual s32 getSlink2LocalPropertyNum_() const;
    virtual void setSlink2PropertyDefinition_(xlink2::UserInstanceSLink* link);
    virtual void m50();
    virtual void m51();
    virtual void m52();
    virtual void m53();
    virtual void m54();
    virtual void m55();
    virtual void m56();
    virtual void m57();
    virtual bool isForceGlbMtxDirty_() const;
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

    // 0x7100be9908
    bool moveBoxCursorByButton(const AnimButton* button);
    // 0x7100be9fa8 (the old / new button states are ButtonBase::State values)
    void buttonStateChangeCallback(AnimButton* button, ButtonBase::State old_state, ButtonBase::State new_state);

    // eui::Screen's non-virtual update helpers (called by the overrides in uking::ui::Screen)
    void updateControl_();
    void updateAnimator_();

    /* 0x28 */ ScreenMgr* mMgr;
    u8 _30[0x38 - 0x30];
    /* 0x38 */ ButtonGroup* mButtonGroup;
    u8 _40[0xc0 - 0x40];
    /* 0xc0 */ s32 mId;
    u8 _c4[0x104 - 0xc4];
    /* 0x104 */ bool _104;  // read by AnimButton::Build / InactivateByBoxCursor (touch device?)
    u8 _105[0x108 - 0x105];
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
    f32 getAnimationStep() const { return mAnimationStep; }

    // 0x7100bec7e8
    void inactivateScreen(s32 id);

private:
    // The singleton disposer is at 0x8 (CSV: createInstance 0x7100bec0a4, object size 0xb50).
    sead::Buffer<Screen*> mScreens;
    u8 _38[0xb20 - 0x38];
    /* 0xb20 */ f32 mAnimationStep;
    u8 _b24[0xb50 - 0xb24];
};

}  // namespace eui
