#pragma once

#include "Game/UI/uiScreens.h"
#include "Game/UI/uiControlCreator.h"
#include "KingSystem/World/worldDefines.h"

// ScreenChildEx-derived classes (their constructors call ScreenChildEx's) with their own state callback slots (105+, groups of four: void, void, void, s32).
// Placeholder names after the vtable; their destructors / RTTI are not decompiled yet.
namespace eui {
class LetterAnimControl;
class MessageString;
}

namespace uking::ui {

// Temperature child: factory a1764c, full ctor 9c81cc and D1 9c8248.
class Unk_710247e0c8 : public ScreenChildEx {
public:
    explicit Unk_710247e0c8(eui::LayoutEx* layout);
    ~Unk_710247e0c8() override;
    u8 _130[0x1e8 - 0x130];
};
static_assert(sizeof(Unk_710247e0c8) == 0x1e8);

// Hero-soul child: factory a17844, full ctor 9c37f8 and D1 9c3890.
class Unk_710247d580 : public ScreenChildEx {
public:
    explicit Unk_710247d580(eui::LayoutEx* layout);
    ~Unk_710247d580() override;
    u8 _130[0x1d8 - 0x130];
};
static_assert(sizeof(Unk_710247d580) == 0x1d8);

// MainScreen arrow child: factory a17160, full ctor 985eb4 and D1 985ef0.
class Unk_7102476db8 : public ScreenChildEx {
public:
    explicit Unk_7102476db8(eui::LayoutEx* layout);
    ~Unk_7102476db8() override;
    u8 _130[0x160 - 0x130];
};
static_assert(sizeof(Unk_7102476db8) == 0x160);

// Camera pointer: factory a1725c, full ctor 986868 and D1 9868f4.
// Embedded event links and control lifetimes remain undecompiled.
class Unk_7102477110 : public ScreenChildEx {
public:
    explicit Unk_7102477110(eui::LayoutEx* layout);
    ~Unk_7102477110() override;
    u8 _130[0x400 - 0x130];
};
static_assert(sizeof(Unk_7102477110) == 0x400);

// Player status: factory a17454, full ctor 9bc9bc and D1 9bca14.
class Unk_710247bcb8 : public ScreenChildEx {
public:
    explicit Unk_710247bcb8(eui::LayoutEx* layout);
    ~Unk_710247bcb8() override;
    u8 _130[0x198 - 0x130];
};
static_assert(sizeof(Unk_710247bcb8) == 0x198);

// Full ctor 9a4330 calls the existing button-child base; factory 9e8158 allocates 0x158.
// Native vtable 2479838 shares D1 931ddc with the base and has D0 9a49e0.
class Unk_7102479838 : public Unk_71024746d0 {
public:
    explicit Unk_7102479838(eui::LayoutEx* layout);
    ~Unk_7102479838() override;

    u8 _138[0x158 - 0x138];
};
static_assert(sizeof(Unk_7102479838) == 0x158);

// Full ctor 9c54e4/D1 9c55b8 and factory 9e8254 prove the base and 0x408 extent.
// The native embedded dc50 and d8d8 lifetimes are not defined here.
class Unk_710247d8f8 : public ScreenChildEx {
public:
    explicit Unk_710247d8f8(eui::LayoutEx* layout);
    ~Unk_710247d8f8() override;

    u8 _130[0x408 - 0x130];
};
static_assert(sizeof(Unk_710247d8f8) == 0x408);

// Full ctor 9bf770/D1 9bf7e4 and factory 9e8350 prove this 0x1a0-byte child.
class Unk_710247c368 : public ScreenChildEx {
public:
    explicit Unk_710247c368(eui::LayoutEx* layout);
    ~Unk_710247c368() override;

    u8 _130[0x1a0 - 0x130];
};
static_assert(sizeof(Unk_710247c368) == 0x1a0);

// Full ctor 98c278/D1 98c2a8 and factory 9e844c prove this child has no added storage.
class Unk_7102477c30 : public ScreenChildEx {
public:
    explicit Unk_7102477c30(eui::LayoutEx* layout);
    ~Unk_7102477c30() override;
};
static_assert(sizeof(Unk_7102477c30) == 0x130);

// Factory 9d7294 allocates 0x708 bytes; full ctor 9c69a4 and dtor 9c6a2c
// establish ScreenChildEx and native vtable 247dc90. Lifetime bodies remain undecompiled.
class Unk_710247dc90 : public ScreenChildEx {
public:
    explicit Unk_710247dc90(eui::LayoutEx* layout);
    ~Unk_710247dc90() override;

    u8 _130[0x708 - 0x130];
};
static_assert(sizeof(Unk_710247dc90) == 0x708);

// Factory 9de3f4 allocates 0x480 bytes; full ctor 9bd404 and dtor 9bd470
// establish the same base and vtable 247c010. No embedded lifetime is defined here.
class Unk_710247c010 : public ScreenChildEx {
public:
    explicit Unk_710247c010(eui::LayoutEx* layout);
    ~Unk_710247c010() override;

    u8 _130[0x480 - 0x130];
};
static_assert(sizeof(Unk_710247c010) == 0x480);

// Full ctor 9c0ebc/dtor 9c0f04 and factory 9de4f0 establish the base, vtable and size.
class Unk_710247c6c0 : public ScreenChildEx {
public:
    explicit Unk_710247c6c0(eui::LayoutEx* layout);
    ~Unk_710247c6c0() override;

    u8 _130[0x160 - 0x130];
};
static_assert(sizeof(Unk_710247c6c0) == 0x160);

// Full ctor 98fc08/dtor 98fc90 and factory 9e805c prove this 0x450-byte child.
class Unk_7102478048 : public ScreenChildEx {
public:
    explicit Unk_7102478048(eui::LayoutEx* layout);
    ~Unk_7102478048() override;

    u8 _130[0x450 - 0x130];
};
static_assert(sizeof(Unk_7102478048) == 0x450);

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

// A child class of the PauseMenu screen (id 46, child group 1; the facade helpers of the 0x7100a94000 TU DynamicCast
// to it). Its typeinfo static is at 0x71025d9b08 (guard 0x71025d9b10); it was declared separately as
// ScreenChildUnk_71025d9b08 before.
class Unk_710247af10 : public ScreenChildEx {
public:
    NN_RUNTIME_TYPEINFO(ScreenChildEx)
    ~Unk_710247af10() override;
    // 0x71009b62cc (`_1a8 = a1`)
    void sub_71009B62CC(void* a1);
    void sub_71009B7A1C(Unk_710247ae28* record);
    void sub_71009B7D88();
    void sub_71009B87C8(Unk_710247ae28* record, eui::MessageString* out);

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

    // The members used so far (the state machine at 0x80 is ScreenChild's).
    // 0x71009b8b6c (not decompiled; m110 tail-calls it)
    void sub_71009B8B6C();

    u8 _130[0x148 - 0x130];
    /* 0x148 */ eui::Animator* _148;
    u8 _150[0x160 - 0x150];
    // Found by 9b5238 via 9b53f4's LetterAnimControl RTTI lookup.
    /* 0x160 */ eui::LetterAnimControl* mQuestCaption;
    u8 _168[0x1a8 - 0x168];
    /* 0x1a8 */ void* _1a8;
    u8 _1b0[0x300 - 0x1b0];
    /* 0x300 */ ScreenAppPictureBookUnk* _300;
    // Native reset uses -1; 9b6ec0 consumes this as the selected group index.
    /* 0x308 */ s32 _308;
    u8 _30c[0x32c - 0x30c];
    /* 0x32c */ s32 _32c;
};

class Unk_710247b428 : public ScreenChildEx {
public:
    explicit Unk_710247b428(eui::LayoutEx* layout);
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

    u8 _130[0x1a8 - 0x130];
    /* 0x1a8 */ eui::Animator* _1a8;  // stopped at max / min by m114 depending on the JumpButtonChange flag
    u8 _1b0[0x1c4 - 0x1b0];
    u8 _1c4[4];
    // Constructed by 0x7100a82fbc in this class' constructor.
    /* 0x1c8 */ Unk_710249d300 _1c8;
    /* 0x268 */ bool _268 = false;
};

// States of Unk_710247b428's state machine (plain StateBase objects; the transitions after the option / controller /
// DLC / system window screens close).
extern const ksys::StateBase sUnk_71025d9ec0;
extern const ksys::StateBase sUnk_71025da040;
extern const ksys::StateBase sUnk_71025da100;
extern const ksys::StateBase sUnk_71025da220;

class Unk_710247e468 : public ScreenChildEx {
public:
    // Factory a17748 and full ctor 9c96a4/D1 9c9700 establish the 0x190 extent.
    explicit Unk_710247e468(eui::LayoutEx* layout);
    ~Unk_710247e468() override;
    void m24() override;
    void m25() override;
    void m27() override;
    void m31() override;

    virtual void m105();
    virtual void m106();
    virtual void m107();
    virtual s32 m108();
    virtual void m109();
    virtual void m110();
    virtual void m111();
    virtual s32 m112();

    // Native weather-frame updater; independently called by setup and state callbacks.
    void sub_71009C9D5C(bool update);
    void sub_71009C9A88();
    bool sub_71009C9BEC();
    bool sub_71009C9F20();

    /* 0x130 */ eui::Animator* _130;
    /* 0x138 */ eui::Animator* _138;
    /* 0x140 */ eui::Animator* _140;
    /* 0x148 */ eui::Animator* _148;
    /* 0x150 */ eui::Animator* _150;
    // Native frame updater indexes these five animators at +158 with an 8-byte stride.
    /* 0x158 */ eui::Animator* mTexPatterns[5];
    /* 0x180 */ ksys::world::Climate _180;
    /* 0x184 */ ksys::world::Climate _184;
    /* 0x188 */ bool _188;
    /* 0x189 */ bool _189;
    /* 0x18a */ bool _18a;
    /* 0x18b */ bool _18b;
    u8 _18c[0x190 - 0x18c];
};
static_assert(sizeof(Unk_710247e468) == 0x190);

// Native state descriptors initialized by 9ca8ac with this child's member callbacks.
extern ksys::StateTemplate<Unk_710247e468> sUnk_71025dbb28;
extern ksys::StateTemplate<Unk_710247e468> sUnk_71025dbb88;

// 9ca8ac initializes this Buffer with nine records at 247e420. Both 9c9bec
// and 9c9d5c compare the byte with WeatherMgr::x_6 and read the float at +4.
struct WeatherAnimationFrame {
    u8 weather;
    u8 _pad[3];
    f32 frame;
};
static_assert(sizeof(WeatherAnimationFrame) == 8);
extern sead::Buffer<WeatherAnimationFrame> sUnk_71025dbcc8;

}  // namespace uking::ui
