#pragma once

#include "Game/UI/uiScreens.h"
#include <container/seadSafeArray.h>
#include "Game/UI/uiControlCreator.h"
#include <thread/seadCriticalSection.h>
#include "KingSystem/System/StringBoard.h"
#include "KingSystem/World/worldDefines.h"
#include <container/seadPtrArray.h>
#include <xlink2/xlink2HandleELink.h>

// ScreenChildEx-derived classes (their constructors call ScreenChildEx's) with their own state callback slots (105+, groups of four: void, void, void, s32).
// Placeholder names after the vtable; their destructors / RTTI are not decompiled yet.
namespace ksys {
class ManagedTaskHandle;
}

namespace eui {
class LetterAnimControl;
class MessageString;
class CapturePane;
}

namespace uking::ui {

// Temperature child: factory a1764c, full ctor 9c81cc and D1 9c8248.
class Unk_710247e0c8 : public ScreenChildEx {
public:
    explicit Unk_710247e0c8(eui::LayoutEx* layout);
    ~Unk_710247e0c8() override;

    // Initial values from the ctor 0x9c81cc.
    u8 _130[100]{};
    /* 0x198 */ void* _198 = nullptr;
    /* 0x1a0 */ void* _1a0 = nullptr;
    /* 0x1a8 */ bool _1a8 = false;
    /* 0x1ac */ sead::Vector2f _1ac{0, 0};
    /* 0x1b4 */ sead::Vector2f _1b4{0, 0};
    /* 0x1bc */ s32 _1bc = 2;
    /* 0x1c0 */ s32 _1c0 = 0;
    /* 0x1c4 */ bool _1c4 = false;
    /* 0x1c8 */ void* _1c8 = nullptr;
    /* 0x1d0 */ void* _1d0 = nullptr;
    /* 0x1d8 */ s32 _1d8 = 2;
    /* 0x1dc */ s32 _1dc = 0;
    /* 0x1e0 */ bool _1e0 = false;
    /* 0x1e4 */ s32 _1e4 = 0;
};
static_assert(sizeof(Unk_710247e0c8) == 0x1e8);

// Hero-soul child: factory a17844, full ctor 9c37f8 and D1 9c3890.
class Unk_710247d580 : public ScreenChildEx {
public:
    explicit Unk_710247d580(eui::LayoutEx* layout);
    ~Unk_710247d580() override;

    // Members from the ctor 0x9c37f8.
    /* 0x130 */ s32 _130 = 3;
    /* 0x134 */ u16 _134 = 0;
    /* 0x138 */ void* _138 = nullptr;
    /* 0x140 */ void* _140 = nullptr;
    /* 0x148 */ u16 _148 = 0;
    /* 0x14c */ u32 _14c = 0;
    /* 0x150 */ u32 _150 = 0;
    /* 0x154 */ u32 _154 = 0;
    /* 0x158 */ u32 _158 = 0;
    u8 _15c[4];
    /* 0x160 */ u8 _160[0x38]{};
    /* 0x198 */ sead::FixedPtrArray<u8, 2> _198;
    /* 0x1b8 */ void* _1b8 = nullptr;
    /* 0x1c0 */ void* _1c0 = nullptr;
    /* 0x1c8 */ f32 _1c8 = 1.0f;
    /* 0x1cc */ bool _1cc = false;
    u8 _1cd[3];
    /* 0x1d0 */ bool _1d0 = false;
};
static_assert(sizeof(Unk_710247d580) == 0x1d8);

// MainScreen arrow child: factory a17160, full ctor 985eb4 and D1 985ef0.
class Unk_7102476db8 : public ScreenChildEx {
public:
    NN_RUNTIME_TYPEINFO(ScreenChildEx)
    explicit Unk_7102476db8(eui::LayoutEx* layout);
    ~Unk_7102476db8() override;
    void m24(sead::Heap* heap) override;
    void m25() override;
    void m27() override;
    void sub_7100986268();
    void sub_7100986480(s32 count);
    void sub_7100986580();

    // Setup 986068 and independent hooks 98640c / 986480 / 986580 use these controls.
    eui::Animator* mDisable = nullptr;
    eui::Animator* mZoom = nullptr;
    eui::Animator* mInvalid = nullptr;
    eui::Animator* mNumOff = nullptr;
    eui::Animator* mGanon = nullptr;
    eui::CapturePane* mCapture = nullptr;
};
static_assert(sizeof(Unk_7102476db8) == 0x160);

// Camera pointer: factory a1725c, full ctor 986868 and D1 9868f4.
// Embedded event links and control lifetimes remain undecompiled.
class Unk_7102477110 : public ScreenChildEx {
public:
    explicit Unk_7102477110(eui::LayoutEx* layout);
    ~Unk_7102477110() override;

    // One entry of the effect array at 0x1d8; the destructor kills each effect handle.
    struct EffectEntry {
        xlink2::HandleELink handle;
        u8 _10[0x10];
    };
    // 0x160 - 0x298: value-initialised by the constructor (one 0x138-byte memset).
    struct Unk160 {
        u8 _0[0x78];
        EffectEntry effects[5];
        u8 _118[0x20];
    };

    /* 0x130 */ void* _130 = nullptr;
    /* 0x138 */ void* _138 = nullptr;
    /* 0x140 */ void* _140 = nullptr;
    /* 0x148 */ bool _148 = true;
    /* 0x149 */ bool _149 = false;
    u8 _14a[0x158 - 0x14a];
    /* 0x158 */ f32 _158 = -1.0f;
    /* 0x160 */ Unk160 _160;
    /* 0x298 */ Unk_7102474bc8 _298;
    /* 0x3f0 */ sead::PtrArray<u8> _3f0;
};
static_assert(sizeof(Unk_7102477110) == 0x400);

// Player status: factory a17454, full ctor 9bc9bc and D1 9bca14.
class Unk_710247bcb8 : public ScreenChildEx {
public:
    NN_RUNTIME_TYPEINFO(ScreenChildEx)
    explicit Unk_710247bcb8(eui::LayoutEx* layout);
    ~Unk_710247bcb8() override;
    void m24(sead::Heap* heap) override;
    void m29() override;
    void sub_71009BCFF8();
    void sub_71009BD010(const eui::Animator* animator);
    eui::Animator* sub_71009BD02C() const;

    // Constructor and independent setup/update/reset consumers identify these controls.
    eui::Animator* mNumber = nullptr;
    eui::Animator* mAttention = nullptr;
    Unk_71024774c8 mEffectIcons[3];
    s32 _188 = -1;
    s32 _18c = 0;
    s32 _190 = -1;
    u8 _194[4];
};
static_assert(sizeof(Unk_710247bcb8) == 0x198);

// Full ctor 9a4330 calls the existing button-child base; factory 9e8158 allocates 0x158.
// Native vtable 2479838 shares D1 931ddc with the base and has D0 9a49e0.
class Unk_7102479838 : public Unk_71024746d0 {
public:
    explicit Unk_7102479838(eui::LayoutEx* layout);
    ~Unk_7102479838() override;
    const nn::font::detail::RuntimeTypeInfo* GetRuntimeTypeInfo() const override;
    void m24(sead::Heap* heap) override;
    void m25() override;
    void m39(void* button) override;
    void sub_71009A4588();

    /* 0x138 */ sead::Vector2f mPosition{0.0f, 0.0f};
    /* 0x140 */ f32 mAngle = 0.0f;
    u8 _144[4];
    /* 0x148 */ eui::Animator* mAngleAnimator = nullptr;
    /* 0x150 */ ScreenAppMapWidget* mMapWidget = nullptr;
};
static_assert(sizeof(Unk_7102479838) == 0x158);

// Full ctor 9c54e4/D1 9c55b8 and factory 9e8254 prove the base and 0x408 extent.
// The native embedded dc50 and d8d8 lifetimes are not defined here.
class Unk_710247d8f8 : public ScreenChildEx {
public:
    explicit Unk_710247d8f8(eui::LayoutEx* layout);
    ~Unk_710247d8f8() override;

    // Members from the ctor 0x9c54e4 and D1 0x9c55b8.
    /* 0x130 */ void* _130 = nullptr;
    /* 0x138 */ bool _138 = false;
    /* 0x140 */ Unk_710247dc50 _140;
    /* 0x158 */ sead::SafeArray<Unk_710247d8d8, 14> _158;
    /* 0x388 */ u8 _388[0x80]{};
};
static_assert(sizeof(Unk_710247d8f8) == 0x408);

// Full ctor 9bf770/D1 9bf7e4 and factory 9e8350 prove this 0x1a0-byte child.
class Unk_710247c368 : public ScreenChildEx {
public:
    NN_RUNTIME_TYPEINFO(ScreenChildEx)
    explicit Unk_710247c368(eui::LayoutEx* layout);
    ~Unk_710247c368() override;
    void m14() override;
    void m24(sead::Heap* heap) override;
    void m25() override;
    void m27() override;
    void m29() override;
    void m30() override;
    void sub_71009C0310();
    void sub_71009C07FC(s32 state);
    void sub_71009C082C();

    // Full setup and independent callbacks identify eight animators and their current selection.
    // Initial values from the ctor 0x9bf770.
    /* 0x130 */ f32 _130 = 1.0f;
    /* 0x134 */ f32 _134 = 0.4f;
    /* 0x138 */ f32 _138 = 2.0f;
    /* 0x13c */ f32 _13c = 0.0f;
    /* 0x140 */ f32 _140 = 0.0f;
    /* 0x144 */ f32 _144 = 0.0f;
    /* 0x148 */ f32 _148 = 0.0f;
    /* 0x14c */ s32 _14c = 0;
    /* 0x150 */ s32 _150 = 0;
    /* 0x154 */ u8 _154 = 0;
    /* 0x158 */ eui::Animator* mAnimators[8]{};
    /* 0x198 */ eui::Animator* mCurrentAnimator = nullptr;
};
static_assert(sizeof(Unk_710247c368) == 0x1a0);

// Full ctor 98c278/D1 98c2a8 and factory 9e844c prove this child has no added storage.
class Unk_7102477c30 : public ScreenChildEx {
public:
    // Native 98c694 follows the ControlBase / ScreenChild / ScreenChildEx RTTI chain.
    NN_RUNTIME_TYPEINFO(ScreenChildEx)
    explicit Unk_7102477c30(eui::LayoutEx* layout);
    ~Unk_7102477c30() override;
    void m24(sead::Heap* heap) override;
    void m25() override;
};
static_assert(sizeof(Unk_7102477c30) == 0x130);

// Polymorphic loader embedded in Unk_71009cb0c8 at 0x80 (vtable 0x710247e990; ctor 9cc648 and D1 9cc7c4 are not
// decompiled). Queue count/state are consumed by 9cc3a0 / 9cc970; 9cbcc0 reads the task handle at 0x200 under the
// owner's lock.
class Unk_710247e990 {
public:
    Unk_710247e990();
    virtual ~Unk_710247e990();

    /* 0x08 */ s32 mQueueCount;
    u8 _c[0x48 - 0xc];
    /* 0x48 */ s32 mQueueState;
    u8 _4c[0x200 - 0x4c];
    /* 0x200 */ ksys::ManagedTaskHandle* mTaskHandle;
};
static_assert(sizeof(Unk_710247e990) == 0x208);

// Native ctor 9cb0c8 and D1 9cbcc0 establish this non-polymorphic 0x2e8-byte controller.
// Queue count/state are also initialized by inner ctor 9cc648 and consumed by 9cc3a0 / 9cc970.
class Unk_71009cb0c8 {
public:
    Unk_71009cb0c8();
    ~Unk_71009cb0c8();
    void sub_71009CC3A0();
    void sub_71009CC970();
    bool sub_71009CBFA4() const;
    bool sub_71009CBEAC() const;
    void sub_71009CBE38();
    // Full 216-byte native returns one of the resource's two texture records under the controller lock.
    // Declaration only: resource access remains with its owner.
    nn::ui2d::TextureInfo* sub_71009CBECC();
    void sub_71009CBD48(sead::Heap* heap, eui::LayoutEx* layout, const sead::SafeString& name);
    void sub_71009CBDE8(eui::LayoutEx* layout, const sead::SafeString& name);

    u8 _0[8];
    /* 0x8 */ bool mApplied;
    u8 _9[7];
    /* 0x10 */ ksys::res::Handle* mTextureHandle;
    /* 0x18 */ nn::ui2d::Material* mMaterial;
    /* 0x20 */ nn::ui2d::ExternalTextureInfo mTexInfo;
    /* 0x38 */ eui::Animator* mAnimator;
    /* 0x40 */ sead::CriticalSection mCS;
    /* 0x80 */ Unk_710247e990 mLoader;
    // Member delegates set up by the ctor 9cb0c8 (trivially destroyed).
    u8 _288[0x2e8 - 0x288];
};
static_assert(sizeof(Unk_71009cb0c8) == 0x2e8);

// Factory 9d7294 allocates 0x708 bytes; full ctor 9c69a4 and dtor 9c6a2c
// establish ScreenChildEx and native vtable 247dc90. Lifetime bodies remain undecompiled.
class Unk_710247dc90 : public ScreenChildEx {
public:
    explicit Unk_710247dc90(eui::LayoutEx* layout);
    ~Unk_710247dc90() override;

    // Members from the ctor 0x9c69a4 and D1 0x9c6a2c.
    u8 _130[0x188 - 0x130]{};
    /* 0x188 */ nn::ui2d::ExternalTextureInfo _188;
    /* 0x1a0 */ nn::ui2d::ExternalTextureInfo _1a0;
    /* 0x1b8 */ agl::TextureData _1b8;
    /* 0x2e0 */ agl::TextureData _2e0;
    /* 0x408 */ Unk_71009cb0c8 _408;
    /* 0x6f0 */ u16 _6f0 = 0;
    /* 0x6f8 */ void* _6f8 = nullptr;
    /* 0x700 */ void* _700 = nullptr;
};
static_assert(sizeof(Unk_710247dc90) == 0x708);


// Factory 9de3f4 and full ctor/D1 9bd404 / 9bd470 place the controller at 0x198.
class Unk_710247c010 : public ScreenChildEx {
public:
    NN_RUNTIME_TYPEINFO(ScreenChildEx)
    explicit Unk_710247c010(eui::LayoutEx* layout);
    ~Unk_710247c010() override;
    void m30() override;
    void m34() override;
    void m82() override;

    void m39(void* button) override;
    void sub_71009BE260(eui::ButtonBase* button);
    void sub_71009BE4E8(eui::ButtonBase* button);

    /* 0x130 */ eui::Animator* mModeAnimator;
    /* 0x138 */ eui::Animator* mStateAnimator;
    /* 0x140 */ sead::SafeArray<Unk_7102477488, 3> mButtons;
    /* 0x188 */ eui::Animator* mThirdButtonAnimator = nullptr;
    /* 0x190 */ eui::ButtonBase* mDescriptionButton = nullptr;
    /* 0x198 */ Unk_71009cb0c8 mController;
};
static_assert(sizeof(Unk_710247c010) == 0x480);

// The factory placeholder and existing map controller describe the same native child.
using Unk_710247c6c0 = ScreenAppMapUnk3c90;

// Full ctor 98fc08/dtor 98fc90 and factory 9e805c prove this 0x450-byte child.
class Unk_7102478048 : public ScreenChildEx {
public:
    explicit Unk_7102478048(eui::LayoutEx* layout);
    ~Unk_7102478048() override;
    // 0x710098fd5c (declared only; the destructor calls it first)
    void sub_710098FD5C();

    // Members from the ctor 0x98fc08.
    u8 _130[0x211]{};
    /* 0x344 */ u32 _344[2]{};
    /* 0x34c */ bool _34c = false;
    /* 0x350 */ void* _350 = nullptr;
    /* 0x358 */ f32 _358 = 1.0f;
    /* 0x35c */ u8 _35c[0x428 - 0x35c]{};
    /* 0x428 */ ksys::StringBoard _428[5];
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
    void sub_71009B30F0();

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
    void m35(void* a1) override {}
    void m37(void* a1) override {}

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
    void m24(sead::Heap* heap) override;
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
    void m33() override {}
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
