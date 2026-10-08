#pragma once

#include "Game/UI/uiScreens.h"

// ScreenChildEx-derived classes (their constructors call ScreenChildEx's) with their own state callback slots (105+, groups of four: void, void, void, s32).
// Placeholder names after the vtable; their destructors / RTTI are not decompiled yet.
namespace uking::ui {

// A list unit of the Unk_710247af10 TU (vtable 0x710247ae48, 0x58 bytes; created by 0x71009b951c, which allocates
// them into a PtrArray). Only the overridden slots are declared.
class Unk_710247ae48 : public Unk_7102474e38 {
public:
    SEAD_RTTI_OVERRIDE(Unk_710247ae48, Unk_7102474e38)
    Unk_710247ae48() = default;
    ~Unk_710247ae48() override;
    // 0x71009b3054 / 0x71009b30ec / 0x71009b328c / 0x71009b3840 / 0x71009b40dc (not decompiled)
    void m4(sead::Heap* heap) override;
    void m7() override;
    void m13() override;
    void m15(eui::AnimButton* button) override;
    void m19(eui::AnimButton* button) override;

    /* 0x48 */ void* _48{};
    /* 0x50 */ void* _50{};
};
static_assert(sizeof(Unk_710247ae48) == 0x58);

class Unk_710247af10 : public ScreenChildEx {
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
    u8 _130[0x148 - 0x130];
    /* 0x148 */ eui::Animator* _148;
};

class Unk_710247b428 : public ScreenChildEx {
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

class Unk_710247e468 : public ScreenChildEx {
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

    // The members used so far (state callbacks m109 / m111 play the animator, m110 waits for it to stop).
    u8 _130[0x138 - 0x130];
    /* 0x138 */ eui::Animator* _138;
};

}  // namespace uking::ui
