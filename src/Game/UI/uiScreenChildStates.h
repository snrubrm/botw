#pragma once

#include "Game/UI/uiScreens.h"

// ScreenChild-derived classes with their own state callback slots (105+, groups of four: void, void, void, s32).
// Placeholder names after the vtable; their destructors / RTTI are not decompiled yet.
namespace uking::ui {

class Unk_710247af10 : public ScreenChild {
public:
    ~Unk_710247af10() override;

    virtual void m105();
    virtual void m106();
    virtual void m107();
    virtual s32 m108();
    virtual void m109();
    virtual void m110();
    virtual void m111();
    virtual s32 m112();
    virtual void m113();
    virtual void m114();
    virtual void m115();
    virtual s32 m116();

    // The members used so far (the child has a state machine at 0x80, like ScreenChildUnk_71025d9b08).
    u8 _28[0x80 - 0x28];
    /* 0x80 */ ksys::StateMachine mStateMachine;
    u8 _a8[0x128 - 0xa8];
    /* 0x128 */ eui::Screen* _128;
    u8 _130[0x148 - 0x130];
    /* 0x148 */ eui::Animator* _148;
};

class Unk_710247b428 : public ScreenChild {
public:
    ~Unk_710247b428() override;

    virtual void m105();
    virtual void m106();
    virtual void m107();
    virtual s32 m108();
    virtual void m109();
    virtual void m110();
    virtual void m111();
    virtual s32 m112();
    virtual void m113();
    virtual void m114();
    virtual void m115();
    virtual s32 m116();
    virtual void m117();
    virtual void m118();
    virtual void m119();
    virtual s32 m120();
    virtual void m121();
    virtual void m122();
    virtual void m123();
    virtual s32 m124();
    virtual void m125();
    virtual void m126();
    virtual void m127();
    virtual s32 m128();
    virtual void m129();
    virtual void m130();
    virtual void m131();
    virtual s32 m132();
    virtual void m133();
    virtual void m134();
    virtual void m135();
    virtual s32 m136();
    virtual void m137();
    virtual void m138();
    virtual void m139();
    virtual s32 m140();
    virtual void m141();
    virtual void m142();
    virtual void m143();
    virtual s32 m144();
    virtual void m145();
    virtual void m146();
    virtual void m147();
    virtual s32 m148();
    virtual void m149();
    virtual void m150();
    virtual void m151();
    virtual s32 m152();
};

class Unk_710247e468 : public ScreenChild {
public:
    ~Unk_710247e468() override;

    virtual void m105();
    virtual void m106();
    virtual void m107();
    virtual s32 m108();
    virtual void m109();
    virtual void m110();
    virtual void m111();
    virtual s32 m112();
};

}  // namespace uking::ui
