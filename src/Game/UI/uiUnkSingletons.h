#pragma once

#include <container/seadOffsetList.h>
#include <container/seadObjList.h>
#include <prim/seadEnum.h>
#include <prim/seadRuntimeTypeInfo.h>
#include <heap/seadDisposer.h>
#include <container/seadPtrArray.h>
#include <math/seadVector.h>
#include <mc/seadCoreInfo.h>
#include <container/seadSafeArray.h>
#include <thread/seadCriticalSection.h>
#include "Game/UI/uiTimer.h"
#include "Game/UI/uiUnkTiny.h"
#include "KingSystem/Utils/Types.h"
#include "KingSystem/ActorSystem/actBaseProcLink.h"
#include "KingSystem/Utils/Thread/Task.h"
#include "KingSystem/GameData/gdtFlagHandle.h"
#include "KingSystem/GameData/gdtFlag.h"

namespace ksys::qst {
struct IndicatorActor;
class Quest;
}

namespace ksys::map {
class Object;
}

namespace ksys::act {
class Actor;
}

namespace ksys {
class TaskThread;
class TaskMgr;
class ManagedTaskHandle;
class ManagedTask;
}  // namespace ksys

namespace eui {
class LayoutEx;
class Animator;
class MassDrawPane;
}
namespace nn::ui2d {
class Pane;
}

namespace uking::ui {

// UI singletons whose classes are not identified yet. Placeholder names after the address of the
// singleton instance pointer (data_symbols.csv); only the fields used by the UI facade functions
// (uiMiscFacade.cpp) are declared, at their original offsets.

// The UI's low priority thread manager (CSV uiLowPrioThreadMgr; instance pointer 0x71025f59e0). Only the thread it
// forwards pause / resume / clearQueue to is declared.
class UiLowPrioThreadMgr {
    SEAD_SINGLETON_DISPOSER(UiLowPrioThreadMgr)
    UiLowPrioThreadMgr() = default;

public:
    // D1 0x7100a6d5bc, D0 0x7100a6d654
    virtual ~UiLowPrioThreadMgr();

    void start(const sead::SafeString& name, sead::Heap* heap, sead::CoreId core, s32 priority);

    struct Request {
        ksys::TaskDelegate* delegate;
        void* user_data;
        ksys::TaskRemoveCallback* remove_callback;
        ksys::TaskPostRunCallback* post_run_callback;
        ksys::ManagedTaskHandle* handle;
        ksys::ManagedTask* task;
    };
    ksys::ManagedTaskHandle* submitRequest(const Request& request);

    // 0x7100a6d978 / 0x7100a6d988 / 0x7100a6d998
    void pause();
    void resume();
    void clearQueue();

    /* 0x28 */ ksys::TaskThread* _28 = nullptr;
    /* 0x30 */ ksys::TaskMgr* _30 = nullptr;
    /* 0x38 */ ksys::ManagedTaskHandle* _38[100]{};
};
KSYS_CHECK_SIZE_NX150(UiLowPrioThreadMgr, 0x358);

// Instance pointer 0x71025d6ac0 (placeholder name; used by the UI facade).
class Unk_71025d6ac0 {
public:
    static Unk_71025d6ac0* instance() { return sInstance; }

    // Child m29 9C0770 passes this singleton; the native body leaves its receiver unused.
    void sub_7100968040();
    void sub_710096809C();
    void sub_71009680DC();
    bool sub_71009684B4() const;
    bool sub_71009684BC() const;
    void sub_71009684D8();
    bool get29() const;
    // Complete MainScreen and child callers pass this singleton; bodies read UiSubsys1.
    bool sub_710096828C() const;
    bool sub_71009682B4() const;
    s32 sub_71009682CC() const;
    void sub_71009685C4();
    void sub_71009682A4();
    void sub_71009684A0();
    bool sub_71009684C4() const;
    void sub_71009684CC(bool value);
    bool sub_7100968550() const;
    bool sub_7100968564() const;
    bool sub_71009685BC() const;
    void sub_710096867C(bool value);
    void sub_7100968688();
    void sub_7100968690();
    bool sub_7100968698();

    f32 sub_7100968558() const;
    bool sub_71009685AC(s32 value) const;
    bool sub_71009686E8() const;

    // 0x71009686a0: `_74 = value`, clears _80
    void sub_71009686A0(s32 value);
    // 0x71009686bc: clears _80, `_84 = value * 2`
    void sub_71009686BC(s32 value);
    void sub_71009686AC();
    void sub_71009686C8();
    bool sub_71009686D8() const;

    // Native child reset 0x71009c0310 passes this singleton to the byte accessors.
    bool get88() const;
    void clear88();

    // Full createInstance 967E78 and child consumers identify flags, scale and timer.
    u8 _0[0x28];
    /* 0x28 */ bool _28;
    /* 0x29 */ bool _29;
    /* 0x2a */ bool _2a;
    /* 0x2b */ bool _2b;
    /* 0x2c */ bool _2c;
    u8 _2d[3];
    /* 0x30 */ UiTimer _30;
    /* 0x48 */ f32 _48;
    /* 0x4c */ f32 _4c;
    /* 0x50 */ f32 _50;
    /* 0x54 */ bool _54;
    u8 _55[3];
    /* 0x58 */ UiTimer _58;
    /* 0x70 */ f32 _70;
    /* 0x74 */ s32 _74;
    u8 _78[0x80 - 0x78];
    /* 0x80 */ s32 _80;
    /* 0x84 */ s32 _84;
    /* 0x88 */ bool _88;

private:
    static Unk_71025d6ac0* sInstance;
};

// Instance pointer 0x71025d6578 (createInstance 0x7100949bbc, size 0x78; lane2 s47: the class of the vtable 0x7102475278,
// whose destructors are trivial, with a singleton disposer at 0x8; the old placeholder `Unk_7102475278` was this class).
// `_3c` is a state (initialised to 13), `_40` is initialised to 7.
// createInstance (the constructor is inlined) is m: only the order of the inlined zero stores differs (the original stores
// `_4a` / `_4c..` early and `_68` / `_70` late).
class Unk_71025d6578 {
    SEAD_SINGLETON_DISPOSER(Unk_71025d6578)
    Unk_71025d6578() = default;

public:
    virtual ~Unk_71025d6578();

    void sub_710094B844(bool a1, bool a2, bool a3);
    // 0x7100949d28 (placeholder name): sets the low nibble of the gauge flags (_63) to 0xa
    void sub_7100949D28();
    void sub_710094B8A4(bool a1);
    bool sub_710094B8D4() const;
    void sub_710094B9A0();
    void sub_710094B99C();
    void sub_710094BB9C();
    void sub_710094BCDC();
    void sub_710094BD54();
    // A2D8C4 passes its gauge singleton; native receiver fields are 28..70.
    void sub_7100949EDC();
    void sub_7100949FBC();
    u32 sub_710094C094(u32 value) const;
    u32 sub_710094C0D4(u32 value) const;
    void sub_710094BF98(u32 current_increment, u32 max_increment);
    void sub_710094BE14();
    void sub_710094BE30();
    bool sub_710094BE40();
    void sub_710094BE84();

    // Heart values copied as u32 by 0x710094b9a0 / 0x710094bcdc;
    // ScreenMainScreen reads _28 as an integer and the Ichigeki gauge reads _2c.
    /* 0x28 */ u32 _28 = 0;
    /* 0x2c */ u32 _2c = 0;
    /* 0x30 */ u32 _30 = 0;
    /* 0x34 */ u32 _34 = 0;
    /* 0x38 */ u16 _38 = 0;
    /* 0x3a */ u8 _3a = 0;
    /* 0x3c */ s32 _3c = 13;
    /* 0x40 */ s32 _40 = 7;
    /* 0x44 */ s32 _44 = 0;
    /* 0x48 */ u8 _48 = 0;
    /* 0x49 */ u8 _49 = 0;
    /* 0x4a */ u8 _4a = 0;
    u8 _4b;
    /* 0x4c */ u32 _4c = 0;
    /* 0x50 */ u32 _50 = 0;
    /* 0x54 */ u32 _54 = 0;
    /* 0x58 */ s32 _58 = 0;
    /* 0x5c */ s32 _5c = 0;
    u8 _60 = 0;
    /* 0x61 */ u8 _61 = 0;  // bit 1: ?, bits 1 / 2 are rewritten by sub_710094BE14
    u8 _62 = 0;
    /* 0x63 */ u8 _63 = 0;  // four flags (bits 0 / 1 and 2 / 3: two pairs, see sub_710094B844)
    /* 0x64 */ u16 _64 = 0;
    u8 _66[2];
    /* 0x68 */ s32 _68 = 0;
    /* 0x6c */ s32 _6c = 0;
    /* 0x70 */ u16 _70 = 0;
    u16 _72 = 0;
    u8 _74[4];

private:
    // Repeated inline sequences in 0x710094b8d4, b9a0, be84 and c0d4.
    u32 getCurrentHeartValue() const;
    u32 getMaxHeartValue() const;
    u32 getExtraHeartValue() const;
};
KSYS_CHECK_SIZE_NX150(Unk_71025d6578, 0x78);

// Instance pointer 0x71025d6550 (a large map / compass related UI object; `_b64`, `_b6c`, `_b74`
// are states).
// The index and display value select a pin; producers supply an actor's world position.
struct UiSubsys1PinArg {
    s32 index;
    s32 value;
    sead::Vector3f pos;
};

// Placeholder (0x58 bytes): the elements of the 3 x 10 table at 0xe8 of Unk_71025d6550.
struct Unk_71025d6550Entry {
    u8 _0[8];
    /* 0x08 */ s32 _8;
    /* 0x0c */ sead::Vector3f _c;
    u8 _18[0x28 - 0x18];
    /* 0x28 */ s32 _28;
    u8 _2c[0x3c - 0x2c];
    /* 0x3c */ sead::Vector3f _3c;
    /* 0x48 */ bool _48;
    u8 _49[0x50 - 0x49];
    /* 0x50 */ void* _50;
};

class Unk_71025d6550 {
public:
    static Unk_71025d6550* instance() { return sInstance; }

    // 0x7100948eb4 (placeholder name): element `j` of row `i` of the table at 0xe8 (an out of range index selects 0)
    Unk_71025d6550Entry* sub_7100948EB4(s32 i, s32 j);
    // 0x7100948d40 (placeholder name): whether the used entries of the first row are all in state 2..4 with a target and a flag
    bool sub_7100948D40();
    // 0x71009485ec (placeholder name): copies the value picked by the state at 0xb3c into the three values at 0xb58
    void sub_71009485EC();
    // 0x71009486f0 (placeholder name): for every entry in state 2..4 with a target, copies the position at 0x3c to 0xc
    void sub_71009486F0();
    // 0x7100948664 (placeholder name): updates _34 / _9c and the entries, then the state 3 / 4 handler
    void sub_7100948664();
    // 0x71009487c0 (declared only; 340 bytes): the state 3 counterpart of sub_7100948914
    void sub_71009487C0();
    // 0x7100948914 (placeholder name): follows the state at 0xd64 with the gear manager's flag (while screen state 27 is active)
    void sub_7100948914();
    // 0x710094852c (placeholder name): `_b38` = the index of the first entry of the first row whose pointer at 0x50 is null (10 if none)
    void sub_710094852C();
    // 0x7100948db0 (placeholder name): whether the values at 0xb58 differ from the value picked by the state at 0xb3c
    bool sub_7100948DB0();
    // 0x7100948f58 (placeholder name): a value picked by the manager's state at 0x64c38 (-1 for states 3 / > 4)
    s32 sub_7100948F58();

    void sub_71009482FC();
    void sub_7100948CC4(const void* a1);
    void sub_71009489C0(const void* a1);
    void sub_7100948E44(const void* a1);
    void sub_7100948F0C(const f32* values);
    void sub_7100948F48(f32 value);

    u8 _0[0x34];
    // set from uking::ui::sub_7100A9B800 by sub_7100948664
    /* 0x34 */ sead::Vector3f _34;
    u8 _40[0x80 - 0x40];
    /* 0x80 */ sead::Vector3f _80;
    u8 _8c[0x9c - 0x8c];
    // copy of _80 (sub_7100948664)
    /* 0x9c */ sead::Vector3f _9c;
    u8 _a8[0xe8 - 0xa8];
    /* 0xe8 */ sead::SafeArray<sead::SafeArray<Unk_71025d6550Entry, 10>, 3> _e8;
    /* 0xb38 */ s32 _b38;  // number of used entries of the first row
    /* 0xb3c */ u32 _b3c;
    u8 _b40[0xb54 - 0xb40];
    /* 0xb54 */ s32 _b54;
    /* 0xb58 */ sead::SafeArray<s32, 3> _b58;
    /* 0xb64 */ s32 _b64;
    /* 0xb68 */ f32 _b68;
    /* 0xb6c */ s32 _b6c;
    /* 0xb70 */ f32 _b70;
    /* 0xb74 */ s32 _b74;
    u8 _b78[0xb80 - 0xb78];
    // The three pins (index 0x193 - 0x195 of the pin argument) set by sub_7100948CC4 (placeholder layout).
    struct Pin {
        sead::Vector3f pos;
        u8 _c[0x18 - 0xc];
        /* 0x18 */ s32 value;
        /* 0x1c */ bool valid;
        u8 _1d[0x38 - 0x1d];
    };
    /* 0xb80 */ Pin _b80[3];
    u8 _c28[0xc60 - 0xc28];
    // Targets matching the pins (placeholder layout; sub_71009487C0 reads the position at 0x20 and the flag at 0x40)
    struct Target {
        u8 _0[0x20];
        /* 0x20 */ sead::Vector3f pos;
        u8 _2c[0x40 - 0x2c];
        /* 0x40 */ bool valid;
        u8 _41[0x48 - 0x41];
    };
    static_assert(sizeof(Target) == 0x48);
    /* 0xc60 */ Target _c60[3];
    // set once the angle from pin i to target i is stored in _d3c / _d40 / _d44 (sub_71009487C0)
    /* 0xd38 */ bool _d38;
    /* 0xd39 */ bool _d39;
    /* 0xd3a */ bool _d3a;
    u8 _d3b;
    /* 0xd3c */ f32 _d3c;
    /* 0xd40 */ f32 _d40;
    /* 0xd44 */ f32 _d44;
    /* 0xd48 */ s32 _d48;
    /* 0xd4c */ s32 _d4c;
    /* 0xd50 */ s32 _d50;
    /* 0xd54 */ sead::SafeArray<s32, 3> _d54;
    /* 0xd60 */ s32 _d60;
    /* 0xd64 */ s32 _d64;
    u8 _d68[0xd78 - 0xd68];
    /* 0xd78 */ s32 _d78;
    u8 _d7c[0xd80 - 0xd7c];
    /* 0xd80 */ sead::SafeArray<f32, 10> _d80;
    /* 0xda8 */ f32 _da8;
    /* 0xdac */ bool _dac;

    // 0x7100948ee4 / 0x7100948ef4 / 0x7100948f04 (placeholder names)
    bool isD78Zero() const;
    bool isD78One() const;
    void setD78(s32 value);
    // 0x7100948f18 / 0x7100948f30
    f32 getD80(s32 index) const;
    void clearD80();
    // 0x7100948f50 / 0x7100948fb8 / 0x7100948fc0
    f32 getDA8() const;
    bool getDAC() const;
    void setDAC(bool value);

private:
    static Unk_71025d6550* sInstance;
};

// Singleton at 0x71025d69f0 (createInstance 0x710094d7b4, size 0x48, vtable 0x7102475348 with D1 / D0 0x710094d8c4 /
// 0x710094d8c8, disposer vtable 0x7102475328; `_2c` is a state set by the facade functions).
// 0x71009f8420: sets the mode in sUnk_71025eb5b8
void sub_71009F8420(s32 a1);
// 0x71009d3fb0 (declared only)
void sub_71009D3FB0(s32 a1, s32 a2, const sead::SafeString* name);

class Unk_71025d69f0 {
    SEAD_SINGLETON_DISPOSER(Unk_71025d69f0)
    Unk_71025d69f0() = default;

public:
    virtual ~Unk_71025d69f0();

    void sub_710094D8CC();
    void sub_710094D8DC();
    // 0x710094d8ec (placeholder name): unless the home screen is open / opening or sub_7100AA8F30 holds, resets _28
    // to 1 and the app mode; true when it did
    bool sub_710094D8EC();
    void sub_710094E0A0();
    bool sub_710094E920();
    void sub_710094E1C0(bool value);
    void sub_710094E480();
    // 0x710094e488 (placeholder name): whether the open home screen allows mode _28 (sub_710094E570 succeeds without
    // setting its flag)
    bool sub_710094E488();
    // 0x710094e570 (declared only; 944 bytes): checks mode `mode` (0 .. 3) against the screens; `out` is cleared first
    bool sub_710094E570(s32 mode, bool* out);
    void sub_710094D9F4(s32 a1, s32 a2, s32 a3, s32 a4);
    void sub_710094DCC4(s32 a1, s32 a2);
    // 0x710094e064 (placeholder name): sets _28 to 3, then forwards to sub_710094DCC4 with the change
    void sub_710094E064();
    // 0x710094f6f8 (placeholder name): ScreenAppHome::sub_71009DD81C of the open home screen (false without one)
    bool sub_710094F6F8() const;
    // 0x710094f7ac (placeholder name): whether app `app` can be used: the current one (_30), the runes app with any
    // rune, app 1 always, the album / picture book apps once obtained
    bool sub_710094F7AC(s32 app) const;

    /* 0x28 */ s32 _28 = 1;
    /* 0x2c */ s32 _2c = 4;
    /* 0x30 */ s32 _30 = 4;
    /* 0x34 */ u8 _34 = 0;
    /* 0x35 */ u8 _35 = 1;
    /* 0x36 */ u8 _36 = 0;
    u8 _37 = 0;
    /* 0x38 */ u8 _38 = 0;
    /* 0x3c */ s32 _3c = 0;
    /* 0x40 */ s32 _40 = 0;
    // cleared by sub_710094D8EC
    /* 0x44 */ s32 _44 = 0;
};
KSYS_CHECK_SIZE_NX150(Unk_71025d69f0, 0x48);

// ObjList stores the pointer item before its ListNode; native queue handles address the item.
using UiSubsys1ListEntry = void*;

// Placeholder for the object UiSubsys1 keeps at 0x378 (byte 0x50 is set by sub_7100963C78).
struct UiSubsys1Unk378 {
    struct Entry {
        sead::Vector3f pos;
    };

    u8 _0[0x50];
    /* 0x50 */ bool _50;
    u8 _51[0x54 - 0x51];
    /* 0x54 */ sead::SafeArray<s32, 2> _54;
    /* 0x5c */ sead::SafeArray<s32, 2> _5c;
    /* 0x64 */ sead::SafeArray<Entry, 2> _64;
};


// Instance pointer 0x71025d6aa8 (CSV uiSubsys1, createInstance 0x710095a4bc, size 0x3920,
// polymorphic with a singleton disposer at 0x8).
// Element of UiSubsys1's marker table at 0x310 (placeholder; position at 0x28 / 0x30, index at 0x44).
struct UiSubsys1Marker {
    u8 _0[0x28];
    /* 0x28 */ f32 _28;
    u8 _2c[4];
    /* 0x30 */ f32 _30;
    u8 _34[0x44 - 0x34];
    /* 0x44 */ s32 _44;
};

// Element of UiSubsys1's table at 0x658; native base vtable 0x71024753c8.
// Virtual 25 is called by 951388, whose existing users read the position at +0x28.
class Unk_7102477fc0;

struct UiSubsys1Entry {
    SEAD_RTTI_BASE(UiSubsys1Entry)
    virtual ~UiSubsys1Entry();
    virtual void m4();
    virtual void m5();
    virtual void m6();
    virtual void m7();
    virtual void m8();
    virtual void m9();
    virtual s32 m10();
    virtual void m11() {}
    virtual void m12() {}
    virtual void m13();
    virtual void m14() {}
    virtual void m15();
    virtual void m16() {}
    virtual void m17();
    virtual void m18();
    virtual void m19();
    virtual void m20();
    virtual void m21() {}
    virtual void m22();
    virtual void updateDistrictFromPos(const sead::Vector3f* pos);
    virtual void m24(bool enabled);
    virtual void m25(bool enabled);
    virtual void m26() {}
    virtual void m27(bool enabled);
    virtual void m28(bool enabled);

    // 0x7100951388: sets flag 8, then forwards to the virtual control update.
    void sub_7100951388(bool enabled);
    void sub_710095156C(bool enabled);
    bool sub_7100951048() const;
    // 0x7100951058: whether the kind _24 is one of 0-31 other than 23 and 24
    bool sub_7100951058() const;
    // 0x7100951074: whether the kind _24 is below 18
    bool sub_7100951074() const;

    /* 0x08 */ Unk_7102477fc0* _8;
    /* 0x10 */ void* _10;
    /* 0x18 */ f32 _18;
    /* 0x1c */ s32 _1c;
    /* 0x20 */ s32 _20;
    /* 0x24 */ s32 _24;
    /* 0x28 */ sead::Vector3f _28;  // map pin position (CopyMapPinPosition::oneShot_)
    /* 0x34 */ sead::Vector2f _34;
    /* 0x3c */ u32 _3c;
    /* 0x40 */ s32 _40;
    /* 0x44 */ s32 _44;
    /* 0x48 */ const char* _48;
};
static_assert(sizeof(UiSubsys1Entry) == 0x50);

// Map pin entries (kinds 2 and 0x2b). Factory 0x710095c0a8 allocates 0x88 bytes for both; native vtables
// 0x71024755e8 / 0x7102475700. The index at 0x78 starts at -1 and is matched against Manager::_64c40.
class UiSubsys1PinEntry : public UiSubsys1Entry {
public:
    u8 _50[0x78 - 0x50];
    /* 0x78 */ s32 _78;
    /* 0x7c */ s32 _7c;
    /* 0x80 */ s32 _80;
    /* 0x84 */ s32 _84;
};
static_assert(sizeof(UiSubsys1PinEntry) == 0x88);

// Marker records referenced by native 95192C / 951A04 / 951B28.
struct Unk_710095192c {
    u8 _0[8];
    const char* _8;
    const char* _10;
    ksys::gdt::FlagHandle _18;
    s32 _1c;
    u8 _20[0x38 - 0x20];
    sead::Vector3f _38;
    s32 _44;
    s32 _48;
};
static_assert(sizeof(Unk_710095192c) == 0x50);

// Native VT24754C0 adds four slots to the marker entry interface.
class Unk_71024754c0 : public UiSubsys1Entry {
    SEAD_RTTI_OVERRIDE(Unk_71024754c0, UiSubsys1Entry)
public:
    ~Unk_71024754c0() override;
    void m4() override;
    void m5() override;
    void m9() override;
    void m11() override;
    void m12() override;
    void m13() override;
    void m22() override;
    void m26() override;
    virtual void m29(Unk_710095192c* entry);
    virtual void m30();
    virtual void m31();
    virtual void m32();

    /* 0x50 */ Unk_7102477fc0* _50;
    /* 0x58 */ Unk_710095192c* _58;
    /* 0x60 */ s32 _60;
};
static_assert(sizeof(Unk_71024754c0) == 0x68);

// Native VT24755D8 and the allocation in 95C0A8 establish the 0x88-byte layout.
class Unk_71024755d8 : public Unk_71024754c0 {
    SEAD_RTTI_OVERRIDE(Unk_71024755d8, Unk_71024754c0)
public:
    ~Unk_71024755d8() override;
    void m9() override;
    void m11() override;
    void m12() override;
    void m21() override;
    void m29(Unk_710095192c* entry) override;
    void m30() override;
    void m31() override;
    void m32() override;
    // 0x71009520d4 (CSV unnamed; not decompiled): called at the end of m29
    void sub_71009520D4();
    // 0x71009529ec (placeholder name): whether the area's dungeon has been entered
    bool isDungeonEntered() const;

    sead::SafeString _68;
    ksys::gdt::FlagHandle _78;
    ksys::gdt::FlagHandle _7c;
    ksys::gdt::FlagHandle _80;
    ksys::gdt::FlagHandle _84;
};
static_assert(sizeof(Unk_71024755d8) == 0x88);


// Factory 95C0A8 case3 allocates 0x70 bytes and installs VT2475808.
class Unk_7102475808 : public Unk_71024754c0 {
    SEAD_RTTI_OVERRIDE(Unk_7102475808, Unk_71024754c0)
public:
    ~Unk_7102475808() override;
    void m9() override;
    void m21() override;
    void m29(Unk_710095192c* entry) override;
    void m30() override;
    void m31() override;
    void m32() override;

    bool _64;
    ksys::gdt::FlagHandle _68;
};
static_assert(sizeof(Unk_7102475808) == 0x70);



// Observed prefix of the Manager record used by 955900 and factory 95C0A8.
struct Unk_7100955900 {
    const char* _0;
    ksys::gdt::FlagHandle _8;
    sead::Vector3f _c;
};

// Factory 95C0A8 allocates 0x58-byte entries and installs VT2475C68.
class Unk_7102475c68 : public UiSubsys1Entry {
    SEAD_RTTI_OVERRIDE(Unk_7102475c68, UiSubsys1Entry)
public:
    ~Unk_7102475c68() override;
    void m11() override;
    void m12() override;
    void m13() override;
    void m15() override;
    void m17() override;
    void m26() override;
    virtual void m29();
    virtual void m30();

    Unk_7100955900* _50;
};
static_assert(sizeof(Unk_7102475c68) == 0x58);

// Factory 95C0A8 retains its final 0x58-byte allocation for native VT2475D70.
class Unk_7102475d70 : public UiSubsys1Entry {
    SEAD_RTTI_OVERRIDE(Unk_7102475d70, UiSubsys1Entry)
public:
    ~Unk_7102475d70() override;
    s32 m10() override;
    void m11() override;
    void m12() override;
    void m14() override;
    void m16() override;
    void m18() override;

    bool _50;
};
static_assert(sizeof(Unk_7102475d70) == 0x58);

// Factory 0x95C0A8 allocates 0x50 bytes and installs native vtable 0x2475F60.
class Unk_7102475f60 : public UiSubsys1Entry {
    SEAD_RTTI_OVERRIDE(Unk_7102475f60, UiSubsys1Entry)
public:
    ~Unk_7102475f60() override;
    void m11() override;
    void m12() override;
    void m14() override;
    void m16() override;
};
static_assert(sizeof(Unk_7102475f60) == 0x50);

// Factory 0x95C0A8 allocates 0x50 bytes and installs native vtable 0x2476058.
class Unk_7102476058 : public UiSubsys1Entry {
    SEAD_RTTI_OVERRIDE(Unk_7102476058, UiSubsys1Entry)
public:
    ~Unk_7102476058() override;
    void m11() override;
    void m12() override;
    void m14() override;
    void m16() override;
};
static_assert(sizeof(Unk_7102476058) == 0x50);

// Factory 0x95C0A8 allocates 0x60 bytes and installs the complete 30-slot table.
class Unk_7102476150 : public UiSubsys1Entry {
    SEAD_RTTI_OVERRIDE(Unk_7102476150, UiSubsys1Entry)
public:
    ~Unk_7102476150() override;
    void m11() override;
    void m12() override;
    void m14() override;
    void m16() override;
    void m21() override;
    virtual void m29();

    const ksys::qst::IndicatorActor* _50;
    ksys::gdt::FlagHandle _58;
};
static_assert(sizeof(Unk_7102476150) == 0x60);

// Native factory 0x95C0A8 allocates 0x60 bytes and installs all 30 slots.
class Unk_7102476250 : public UiSubsys1Entry {
    SEAD_RTTI_OVERRIDE(Unk_7102476250, UiSubsys1Entry)
public:
    ~Unk_7102476250() override;
    void m11() override;
    void m12() override;
    void m14() override;
    void m16() override;
    virtual void m29();

    ksys::gdt::FlagHandle _50;
    ksys::gdt::FlagType _54;
    ksys::gdt::FlagHandle _58;
    ksys::gdt::FlagType _5c;
};
static_assert(sizeof(Unk_7102476250) == 0x60);

// Observed prefix of the Manager record used by native 0x956BAC.
struct Unk_7100956bac {
    u8 _0[0xc];
    // read by Unk_7102478be0::setMapMarkerAncientText (animation frame / name for the location marker)
    /* 0x0c */ s32 _c;
    /* 0x10 */ const char* _10;
    u8 _18[0x28 - 0x18];
    const char* _28;
    ksys::gdt::FlagHandle _30;
};

// The record behind Unk_7102476350::_50 (sub_7100956C34 tests the map-mode bit of `_8`; m26 looks up the location
// marker of the name `_10`).
struct Unk_7102476350Record {
    u8 _0[8];
    /* 0x08 */ u32 _8;
    // ancient text type (Unk_7102478be0::setMapMarkerAncientText)
    /* 0x0c */ s32 _c;
    /* 0x10 */ const char* _10;
};

// Both list loops in factory 0x95C0A8 allocate 0x60 bytes for VT 0x2476350.
class Unk_7102476350 : public UiSubsys1Entry {
    SEAD_RTTI_OVERRIDE(Unk_7102476350, UiSubsys1Entry)
public:
    ~Unk_7102476350() override;
    void m11() override;
    void m12() override;
    void m14() override;
    void m15() override;
    void m16() override;
    void m17() override;
    void m26() override;
    virtual void m29();
    bool sub_7100956C34();

    Unk_7102476350Record* _50;
    Unk_7100956bac* _58;
};
static_assert(sizeof(Unk_7102476350) == 0x60);

// Native factory 0x95C0A8 allocates 0x50 bytes for the complete 29-slot table.
class Unk_7102476450 : public UiSubsys1Entry {
    SEAD_RTTI_OVERRIDE(Unk_7102476450, UiSubsys1Entry)
public:
    ~Unk_7102476450() override;
    void m11() override;
    void m12() override;
    void m14() override;
    void m16() override;
};
static_assert(sizeof(Unk_7102476450) == 0x50);

// Factory 0x95C0A8 allocates 0x58 bytes and initializes the two added indices to -1.
class Unk_7102476548 : public UiSubsys1Entry {
    SEAD_RTTI_OVERRIDE(Unk_7102476548, UiSubsys1Entry)
public:
    ~Unk_7102476548() override;
    void m4() override;
    void m5() override;
    void m6() override;
    void m7() override;
    void m11() override;
    void m12() override;
    void m14() override;
    void m16() override;
    void m20() override;
    void m21() override;
    void updateDistrictFromPos(const sead::Vector3f* pos) override;

    s32 _50;
    s32 _54;
};
static_assert(sizeof(Unk_7102476548) == 0x58);

// Factory 0x95C0A8 allocates 0x88 bytes and constructs the actor link at 0x60.
class Unk_7102476640 : public UiSubsys1Entry {
    SEAD_RTTI_OVERRIDE(Unk_7102476640, UiSubsys1Entry)
public:
    ~Unk_7102476640() override;
    void m4() override;
    void m5() override;
    void m6() override;
    void m7() override;
    void m11() override;
    void m12() override;
    void m14() override;
    void m16() override;
    void m17() override;
    void m21() override;
    void m24(bool enabled) override;
    void m25(bool enabled) override;
    void m27(bool enabled) override;
    void m28(bool enabled) override;
    s32 sub_7100957A64();
    s32 sub_7100958408(bool enabled);
    void sub_7100958C7C();
    bool sub_7100958D38() const;
    void sub_7100958D4C();

    ksys::map::Object* _50;
    s32 _58;
    ksys::act::BaseProcLink _60;
    bool _70;
    bool _71;
    sead::Vector3f _74;
    s32 _80;
    s32 _84;
};
static_assert(sizeof(Unk_7102476640) == 0x88);

// Factory 0x95C0A8 allocates 0x50 bytes for this complete 29-slot leaf.
class Unk_7102476738 : public UiSubsys1Entry {
    SEAD_RTTI_OVERRIDE(Unk_7102476738, UiSubsys1Entry)
public:
    ~Unk_7102476738() override;
    s32 m10() override;
    void m19() override;
    void m24(bool enabled) override;
    void m25(bool enabled) override;
};
static_assert(sizeof(Unk_7102476738) == 0x50);

// Factory 0x95C0A8 allocates 0x80 bytes and initializes the two UiTimer members.
class Unk_7102476830 : public UiSubsys1Entry {
    SEAD_RTTI_OVERRIDE(Unk_7102476830, UiSubsys1Entry)
public:
    ~Unk_7102476830() override;
    void m5() override;
    s32 m10() override;
    void m19() override;
    void m24(bool enabled) override;
    void m25(bool enabled) override;

    UiTimer _50;
    UiTimer _68;
};
static_assert(sizeof(Unk_7102476830) == 0x80);

// Factory 0x95C0A8 allocates 0x50 bytes and installs this complete 29-slot leaf table.
class Unk_7102476928 : public UiSubsys1Entry {
    SEAD_RTTI_OVERRIDE(Unk_7102476928, UiSubsys1Entry)
public:
    ~Unk_7102476928() override;
    void m25(bool enabled) override;
};
static_assert(sizeof(Unk_7102476928) == 0x50);

// Native vtable 2477FC0 has fifteen slots; reset 98C7A4 establishes the 0x30-byte layout.
class Unk_7102477fc0 {
    SEAD_RTTI_BASE(Unk_7102477fc0)
public:
    virtual ~Unk_7102477fc0();
    virtual void m4();
    virtual void m5();
    virtual void m6(eui::LayoutEx* layout);
    virtual void m7();
    virtual void m8();
    virtual void m9();
    virtual void m10();
    virtual void m11();
    virtual void m12();
    virtual void m13();
    virtual s32 m14() const;
    void sub_710098CB98(bool enabled);
    void sub_710098CF9C();
    // 0x710098cfd4 (placeholder name): applies a show (1) / hide (-1) direction to the marker icon
    void sub_710098CFD4(f32 direction);

    eui::LayoutEx* _8 = nullptr;
    eui::MassDrawPane* _10 = nullptr;
    UiSubsys1Entry* _18 = nullptr;
    nn::ui2d::Pane* _20 = nullptr;
    s32 _28 = 33;
    bool _2c = false;
};
static_assert(sizeof(Unk_7102477fc0) == 0x30);

// Native VT24783A0 (address point 24783B0) overrides the marker update and pane methods.
class Unk_71024783b0 : public Unk_7102477fc0 {
    SEAD_RTTI_OVERRIDE(Unk_71024783b0, Unk_7102477fc0)
public:
    ~Unk_71024783b0() override;
    void m4() override;
    void m5() override;
    void m7() override;
    void m8() override;
    void m9() override;
    void m10() override;
    void m11() override;
    void m13() override;
    void sub_710098D2B0();

    sead::Vector2f _30;
};
static_assert(sizeof(Unk_71024783b0) == 0x38);

// RTTI 25D9170 is the intermediate parent of the 17-slot marker controls.
// Native 9998BC allocates 0x48-byte leaves and fills the animator pointers at 0x30/0x38.
class Unk_71025d9170 : public Unk_7102477fc0 {
    SEAD_RTTI_OVERRIDE(Unk_71025d9170, Unk_7102477fc0)
public:
    ~Unk_71025d9170() override;
    void m8() override;
    void m11() override;
    virtual void m15();
    virtual void m16();

    eui::Animator* _30 = nullptr;
    eui::Animator* _38 = nullptr;
    eui::Animator* _40 = nullptr;
};
static_assert(sizeof(Unk_71025d9170) == 0x48);

// Native VT2478428 has seventeen slots and RTTI 25D91A0.
class Unk_7102478428 : public Unk_71025d9170 {
    SEAD_RTTI_OVERRIDE(Unk_7102478428, Unk_71025d9170)
public:
    ~Unk_7102478428() override;
    void m8() override;
    void m11() override;
};
static_assert(sizeof(Unk_7102478428) == 0x48);

// Native VT2478EC8 uses the animator-control interface and RTTI 25D92C0.
class Unk_7102478ec8 : public Unk_71025d9170 {
    SEAD_RTTI_OVERRIDE(Unk_7102478ec8, Unk_71025d9170)
public:
    ~Unk_7102478ec8() override;
    void m8() override;
    void m11() override;
};

// Native VT24784C0, with RTTI 25D91B0; complete seventeen-slot interface.
class Unk_71024784c0 : public Unk_71025d9170 {
    SEAD_RTTI_OVERRIDE(Unk_71024784c0, Unk_71025d9170)
public:
    ~Unk_71024784c0() override;
    void m8() override;
    void m11() override;
};

// Native VT2478558, with RTTI 25D91C0; complete seventeen-slot interface.
class Unk_7102478558 : public Unk_71025d9170 {
    SEAD_RTTI_OVERRIDE(Unk_7102478558, Unk_71025d9170)
public:
    ~Unk_7102478558() override;
    void m8() override;
    void m11() override;
};

// Native VT24785F0, with RTTI 25D91D0; complete seventeen-slot interface.
class Unk_71024785f0 : public Unk_71025d9170 {
    SEAD_RTTI_OVERRIDE(Unk_71024785f0, Unk_71025d9170)
public:
    ~Unk_71024785f0() override;
    void m8() override;
    void m11() override;
};

// Native VT2478688, with RTTI 25D91E0; complete seventeen-slot interface.
class Unk_7102478688 : public Unk_71025d9170 {
    SEAD_RTTI_OVERRIDE(Unk_7102478688, Unk_71025d9170)
public:
    ~Unk_7102478688() override;
    void m8() override;
    void m11() override;
};

// Native VT2478720, with RTTI 25D91F0; complete seventeen-slot interface.
class Unk_7102478720 : public Unk_71025d9170 {
    SEAD_RTTI_OVERRIDE(Unk_7102478720, Unk_71025d9170)
public:
    ~Unk_7102478720() override;
    void m8() override;
    void m11() override;
};

// Native VT24787B8, with RTTI 25D9200; complete seventeen-slot interface.
class Unk_71024787b8 : public Unk_71025d9170 {
    SEAD_RTTI_OVERRIDE(Unk_71024787b8, Unk_71025d9170)
public:
    ~Unk_71024787b8() override;
    void m8() override;
    void m11() override;
};

// Native VT2478850, with RTTI 25D9210; complete seventeen-slot interface.
class Unk_7102478850 : public Unk_71025d9170 {
    SEAD_RTTI_OVERRIDE(Unk_7102478850, Unk_71025d9170)
public:
    ~Unk_7102478850() override;
    void m8() override;
    void m11() override;
};

// Native VT24788E8, with RTTI 25D9220; complete seventeen-slot interface.
class Unk_71024788e8 : public Unk_71025d9170 {
    SEAD_RTTI_OVERRIDE(Unk_71024788e8, Unk_71025d9170)
public:
    ~Unk_71024788e8() override;
    void m8() override;
    void m11() override;
};

// Native VT2478980, with RTTI 25D9230; complete seventeen-slot interface.
class Unk_7102478980 : public Unk_71025d9170 {
    SEAD_RTTI_OVERRIDE(Unk_7102478980, Unk_71025d9170)
public:
    ~Unk_7102478980() override;
    void m12() override;
};

// Native VT2478D98 supplies an integer marker-style index in slot fourteen.
class Unk_7102478d98 : public Unk_71025d9170 {
    SEAD_RTTI_OVERRIDE(Unk_7102478d98, Unk_71025d9170)
public:
    ~Unk_7102478d98() override;
    void m12() override;
    s32 m14() const override;
};

// Native factory 99AA18 allocates 0x50 bytes and creates the State animator at +0x48.
class Unk_7102478a18 : public Unk_71025d9170 {
    SEAD_RTTI_OVERRIDE(Unk_7102478a18, Unk_71025d9170)
public:
    ~Unk_7102478a18() override;
    void m11() override;

    eui::Animator* _48;
};
static_assert(sizeof(Unk_7102478a18) == 0x50);

// Native factory 99AE94 allocates 0x50 bytes and creates the State animator at +0x48.
class Unk_7102478ab0 : public Unk_71025d9170 {
    SEAD_RTTI_OVERRIDE(Unk_7102478ab0, Unk_71025d9170)
public:
    ~Unk_7102478ab0() override;
    void m11() override;

    eui::Animator* _48;
};
static_assert(sizeof(Unk_7102478ab0) == 0x50);

// Native factory 99B310 allocates 0x50 bytes and creates the State animator at +0x48.
class Unk_7102478b48 : public Unk_71025d9170 {
    SEAD_RTTI_OVERRIDE(Unk_7102478b48, Unk_71025d9170)
public:
    ~Unk_7102478b48() override;
    void m11() override;

    eui::Animator* _48;
};
static_assert(sizeof(Unk_7102478b48) == 0x50);

// Native factory 99C470 allocates 0x38 bytes and initializes the added animator fields.
class Unk_7102478be0 : public Unk_7102477fc0 {
    SEAD_RTTI_OVERRIDE(Unk_7102478be0, Unk_7102477fc0)
public:
    ~Unk_7102478be0() override;
    void m8() override;
    void m11() override;
    void setMapMarkerAncientText();
    void sub_710098EAB8();

    eui::Animator* _30;
};
static_assert(sizeof(Unk_7102478be0) == 0x38);

// Native factory 99DAD0 allocates 0x58 bytes and initializes the added animator fields.
class Unk_7102478e30 : public Unk_71025d9170 {
    SEAD_RTTI_OVERRIDE(Unk_7102478e30, Unk_71025d9170)
public:
    ~Unk_7102478e30() override;
    void m8() override;
    void m11() override;
    void m12() override;

    eui::Animator* _48;
    eui::Animator* _50;
};
static_assert(sizeof(Unk_7102478e30) == 0x58);

// Native factory 99CCA0 allocates 0x60 bytes; VT2478C68 has seventeen slots.
class Unk_7102478c68 : public Unk_71025d9170 {
    SEAD_RTTI_OVERRIDE(Unk_7102478c68, Unk_71025d9170)
public:
    ~Unk_7102478c68() override;
    void m6(eui::LayoutEx* layout) override;
    void m8() override;
    void m11() override;

    nn::ui2d::Pane* _48;
    nn::ui2d::Pane* _50;
    eui::Animator* _58;
};
static_assert(sizeof(Unk_7102478c68) == 0x60);

// Native factory 99D164 allocates 0x70 bytes; VT2478D00 has seventeen slots.
class Unk_7102478d00 : public Unk_71025d9170 {
    SEAD_RTTI_OVERRIDE(Unk_7102478d00, Unk_71025d9170)
public:
    ~Unk_7102478d00() override;
    void m5() override;
    void m8() override;
    void m10() override;
    void m11() override;
    void m12() override;
    void m13() override;

    eui::Animator* _48;
    s32 _50;
    u8 _54[0xc];
    s32 _60;
    f32 _64;
    bool _68;
    u8 _69[3];
    bool _6c;
};
static_assert(sizeof(Unk_7102478d00) == 0x70);

// Native VT2479050 has seventeen slots; its factory allocates 0x48 bytes.
class Unk_7102479050 : public Unk_71025d9170 {
    SEAD_RTTI_OVERRIDE(Unk_7102479050, Unk_71025d9170)
public:
    ~Unk_7102479050() override;
};
static_assert(sizeof(Unk_7102479050) == 0x48);

// Native VT24790E8 has seventeen slots; its factory allocates 0x48 bytes.
class Unk_71024790e8 : public Unk_71025d9170 {
    SEAD_RTTI_OVERRIDE(Unk_71024790e8, Unk_71025d9170)
public:
    ~Unk_71024790e8() override;
};
static_assert(sizeof(Unk_71024790e8) == 0x48);

// Native VT2479180 has seventeen slots; its factory allocates 0x48 bytes.
class Unk_7102479180 : public Unk_71025d9170 {
    SEAD_RTTI_OVERRIDE(Unk_7102479180, Unk_71025d9170)
public:
    ~Unk_7102479180() override;
};
static_assert(sizeof(Unk_7102479180) == 0x48);

// Native VT2479218 has seventeen slots; its factory allocates 0x48 bytes.
class Unk_7102479218 : public Unk_71025d9170 {
    SEAD_RTTI_OVERRIDE(Unk_7102479218, Unk_71025d9170)
public:
    ~Unk_7102479218() override;
};
static_assert(sizeof(Unk_7102479218) == 0x48);

// Native VT24792B0 has seventeen slots; its factory allocates 0x48 bytes.
class Unk_71024792b0 : public Unk_71025d9170 {
    SEAD_RTTI_OVERRIDE(Unk_71024792b0, Unk_71025d9170)
public:
    ~Unk_71024792b0() override;
};
static_assert(sizeof(Unk_71024792b0) == 0x48);

// Native VT2479348 has seventeen slots; its factory allocates 0x48 bytes.
class Unk_7102479348 : public Unk_71025d9170 {
    SEAD_RTTI_OVERRIDE(Unk_7102479348, Unk_71025d9170)
public:
    ~Unk_7102479348() override;
};
static_assert(sizeof(Unk_7102479348) == 0x48);

// Native VT24793E0 has seventeen slots; its factory allocates 0x48 bytes.
class Unk_71024793e0 : public Unk_71025d9170 {
    SEAD_RTTI_OVERRIDE(Unk_71024793e0, Unk_71025d9170)
public:
    ~Unk_71024793e0() override;
};
static_assert(sizeof(Unk_71024793e0) == 0x48);

// Native VT2479478 has seventeen slots; its factory allocates 0x48 bytes.
class Unk_7102479478 : public Unk_71025d9170 {
    SEAD_RTTI_OVERRIDE(Unk_7102479478, Unk_71025d9170)
public:
    ~Unk_7102479478() override;
};
static_assert(sizeof(Unk_7102479478) == 0x48);

// Native VT2479510 has seventeen slots; its factory allocates 0x48 bytes.
class Unk_7102479510 : public Unk_71025d9170 {
    SEAD_RTTI_OVERRIDE(Unk_7102479510, Unk_71025d9170)
public:
    ~Unk_7102479510() override;
};
static_assert(sizeof(Unk_7102479510) == 0x48);

class UiSubsys1 {
    // Native singleton forwarders 96828C / 9682B4 / 9682CC read these UI fields directly.
    friend class Unk_71025d6ac0;
    friend struct UiSubsys1Entry;
    // Native 955964/9559D8/955BE4 read the map mode at 0x848 directly.
    friend class Unk_7102475c68;
    friend class Unk_7102476350;
    friend class Unk_7102476640;
    friend class Unk_7102476830;
    friend class Unk_7102476738;
    friend class Unk_7102476928;
    friend class Unk_7102478048;  // m16 / m34 walk _5d8
    // Native 9A99F0 reads the map view object at 0x850 and its scale at +0x38 directly.
    friend class ScreenAppMapWidget;
    // Native 9F05C0 reads the map view offsets (+0x30) and scale (+0x28) directly.
    friend class ScreenAppMap;
public:
    static UiSubsys1* instance() { return sInstance; }

    // Marker factory hooks at 0x7100964bac / 0x71009675d0; bodies remain undecompiled.
    void sub_7100964BAC(sead::Heap* heap);
    void sub_71009675D0(sead::Heap* heap, Unk_7102477fc0* marker);
    bool sub_7100960DF8();
    // 0x7100960a1c: resets the map marker timer from the selected mode
    void sub_7100960A1C();
    // 0x7100965eec: clamps the negated map cursor position for the supplied scale
    void sub_7100965EEC(f32 scale, sead::Vector2f* out);
    // 0x7100960758 (placeholder name): copies the Sheikah Sensor+ target name (ActorName_SeakSensor_Slot0) to `out`
    void sub_7100960758(sead::BufferedSafeString* out);
    bool sub_7100956C10(u32 index) const;
    Unk_7102476640** sub_71009580A4(Unk_7102476640* key);
    bool sub_71009580E4(Unk_7102476640** entry);
    bool sub_7100958134(Unk_7102476640* entry);
    // 0x7100958fcc / 0x710095900c (placeholder names): find / erase an entry of the list at 0x620
    UiSubsys1Entry** sub_7100958FCC(UiSubsys1Entry* key);
    bool sub_710095900C(UiSubsys1Entry** entry);
    // 0x710095f584 (declared only; 960 bytes): resets the marker and entry tables; `a1` selects the full reset
    void sub_710095F584(bool a1);
    // 0x71009595fc: find the element of the list at 0x668 whose stored pointer is `key`
    UiSubsys1Entry** sub_71009595FC(UiSubsys1Entry* key);
    // 0x710095963c: erase the element found by sub_71009595FC and return it to the list's free list
    bool sub_710095963C(UiSubsys1Entry** entry);
    // 0x7100963724: the full reset of sub_710095F584
    void sub_7100963724();
    // 0x71009635dc (declared only; 296 bytes): whether the selected map mode's state allows a change
    bool sub_71009635DC();
    // 0x7100963598: the mask at 0x120 without the bit selected at 0x128 when sub_71009635DC allows it
    u32 sub_7100963598();
    bool sub_7100958D18() const;
    void sub_71009637D4();
    // 0x710096023c (CSV uiSubsys1::__auto3; placeholder name): ends the timer at 0x6f0 and clears the flag at 0x6ec
    void sub_710096023C();
    // 0x71009512f8 / 0x7100951338 (CSV uiSubsys1::__auto41 / __auto42; placeholder names)
    UiSubsys1ListEntry* findListEntry(void* key);
    bool freeListEntry(UiSubsys1ListEntry* entry);
    // 0x7100963704 / 0x7100968af8 / 0x7100968bd8 (placeholder names)
    void set128(s32 value);
    void sub_7100968AF8(s32 index);
    bool sub_7100968BD8();
    // 0x7100960dac (CSV uiSubsys1::__auto39; placeholder name): `index` is the lowest set bit of `_3860` (6: none)
    bool sub_7100960DAC(s32 index) const;
    // 0x710096101c / 0x7100961058 / 0x710096106c / 0x710096107c (placeholder names)
    // ScreenAppMap::m101 passes this even though the method only clears TU-local flags.
    void sub_7100961008();
    void sub_710096101C();
    void copy38b8To38b9();
    void set38b8();
    void clear38b8();
    void sub_710095B1BC();
    // 0x7100968844 (CSV unnamed; not decompiled; ScreenAppMap::demoLeave)
    void sub_7100968844();
    void set3885() { _3885 = true; }
    void clear3885() { _3885 = false; }
    void set4cc(bool value) { _4cc = value; }
    // 0x71009644e8: entry `index` of the table at 0x658 (null if out of range).
    UiSubsys1Entry* sub_71009644E8(s32 index);
    void sub_71009645D0(const void* a1);
    void sub_710096372C(const void* a1);
    void* sub_71009648A8();
    bool sub_7100964A0C(s32 a1);
    // 0x7100964b24 (placeholder name): the number of entries of the table at 0x610 whose flag (bit 4 of the byte at 0x3c) is clear
    s32 sub_7100964B24();
    void sub_7100963CE8(ksys::act::Actor* actor);
    bool sub_71009661DC(const void* a1, s32* out);
    void sub_7100963C8C(const UiSubsys1PinArg* arg);
    // 0x7100961e48 (CSV uiSubsys1::__auto0; declared only): called by GameSceneSubsys13::setGameOverPosition.
    void sub_7100961E48(const sead::Vector3f* pos);
    // 0x71008b43cc (CSV uiSubsys1::__auto43; not decompiled)
    bool sub_71008B43CC();
    void sub_7100963C78(bool a1);
    bool sub_710096310C(s32* out_index, const sead::Vector3f* pos, f32 radius);

    // Accessors (uiSubsys1.cpp). Placeholder names after the offsets of the fields they use.
    bool is848Zero() const;
    bool returnTrue() const;
    // 0x7100966a74 (CSV uiSubsys1::__auto13; not decompiled)
    void sub_7100966A74();
    bool is848EqualTo1() const;
    // 0x7100961cd4 (declared only; 372 bytes): the position to centre the map on for the current UI Manager state
    // (_64c38: the Master Sword position in state 6, sub_7100957500 in states 0 .. 4 and 7, otherwise
    // sub_7100A9B800 or _478's position)
    void sub_7100961CD4(sead::Vector3f* out);
    // 0x7100957500 (placeholder name): the position of the marker for the current manager state
    // (Divine Beast / Final Trial / selected pin; sead::Vector3f::zero when there is none)
    const sead::Vector3f* getMapMarkerPosition() const;
    bool get38b8() const;
    bool is128EqualTo6() const;
    void set848(s32 value);
    void set38c8();
    void clear38c8();
    void set3884(bool value);
    s32 get38a8() const;
    bool get38ac() const;
    // 0x71009674e8 (placeholder name; does not use `this`): the byte at 0x29 of the 0x71025d6ac0 object.
    bool sub_71009674E8() const;
    void set38e4(s32 value);
    s32 get38f8() const;
    s32 get3900() const;
    // 0x7100966de0 / 0x7100966e8c / 0x71009674fc / 0x7100967514 - 0x7100967594 / 0x710096876c (placeholder names)
    void set3888(s32 value);
    s32 get38a4() const;
    s32 get38e0() const;
    void set38e0(s32 value);
    s32 get38e8() const;
    void set38e8(s32 value);
    s32 get38f4() const;
    void set38f4(s32 value);
    s32 get38fc() const;
    void set3820(s32 value);
    void set3904(bool value);
    bool return0A() const;
    // 0x7100967504 / 0x7100967524 / 0x7100967570 / 0x71009675a4 / 0x71009675c0 / 0x71009675d4 / 0x71009675dc (placeholder names)
    bool isValid38e0() const;
    bool is38e4Equal(s32 value) const;
    void set38ec(s32 a, s32 b);
    u8 get3904() const;
    u8 get3905() const;
    bool return0C() const;
    // 0x7100961114 (CSV uiSubsys1::__auto26, declared only): the per-frame map hint step; 0x7100968900
    // (CSV uiSubsys1::__auto2, declared only) takes 1 / 2 and returns whether the map mode accepts it
    void sub_7100961088();
    void sub_7100961114();
    bool sub_7100968900(s32 value);
    // 0x7100966300 / 0x7100966e20 (placeholder names)
    void start388c();
    void sub_7100966E2C();
    bool sub_7100968D04();
    void updateCompletionCount();
    void sub_7100962638();
    // 0x7100968d5c / 0x7100968d68 / 0x7100968d70 / 0x7100968d78 / 0x7100966ce4 / 0x7100966d90 / 0x7100966db0 / 0x7100966d9c /
    // 0x7100966dbc / 0x7100966cd4 / 0x7100966dd0 / 0x7100966d00 / 0x7100966330 / 0x7100966e9c / 0x7100967478 / 0x710096633c /
    // 0x7100967484 / 0x7100966e14 / 0x7100966e64 / 0x7100967498 / 0x71009674c0 (placeholder names)
    bool has3864Bit0() const;
    void clear3864();
    sead::Vector2f* getVec3868();
    // 0x7100964174 / 0x7100968d10 / 0x7100966d0c / 0x7100966350 (placeholder names): whether an entry is selected
    // (or the cursor state 0 .. 5 / 11 .. 13 is active); updates the change bits of _3864 (2: set, 4: cleared);
    // set `_3868` / `_3870` to the given vector clamped to half the extent of the map bounds when `_848` is set
    bool sub_7100964174() const;
    void sub_7100968D10(bool set);

    // A 4-byte SEAD_ENUM-like id (the argument is spilled to the stack and reloaded; placeholder name and no enumerators)
    SEAD_ENUM(Pin, _0)
    // 0x710096349c (placeholder name): maps the ids 0x1b .. 0x20 to 0 .. 5, 0x21 .. 0x23 to 11 .. 13 and 0x25 .. 0x29 to
    // 6 .. 10 (-1 for the others)
    s32 sub_710096349C(Pin pin) const;
    void sub_7100966D0C(const sead::Vector2f& value);
    void sub_7100966350(const sead::Vector2f& value);
    sead::Vector2f* getVec3870();
    sead::Vector2f* getVec3878();
    void set880(const sead::Vector2f& value);
    void set3878(const sead::Vector2f& value);
    bool isLessOrEqual3880(f32 value) const;
    bool is3888Equal(s32 value) const;
    bool get3884() const;
    u8 get38c8() const;
    bool get38d8() const;
    u8 get38d9() const;
    void copy38c8To38c9();
    void copy38d8To38d9();
    void update388c();
    bool sub_7100966E64() const;
    // 0x7100966894 (480 bytes) / 0x71009666c0 (424 bytes): declared only
    void sub_7100966894();
    void sub_71009666C0(const sead::Vector2f* pos);
    // 0x7100966684 (CSV uiSubsys1::__auto10; placeholder name): scales the (x, z) of `pos` into the map view and forwards it
    void sub_7100966684(const sead::Vector3f* pos);
    // 0x7100965e58 / 0x7100965d10 / 0x71009659a4 (placeholder names)
    Unk_7102475368* sub_7100965E58();
    // The position of the map view in map units (scaled by 1 / _8b0 and _878, rotated by _87c degrees)
    void sub_7100965D10(sead::Vector2f* out) const;
    // Sets _880 and _890 to the negated `view` size scaled by (_8b0, _8b4) (zero when both are zero)
    void sub_71009659A4(const sead::Vector2f* view);
    // 0x710095f944 (placeholder name): clears the map icon / district state (ScreenAppMap's destructor calls it)
    void sub_710095F944();
    // 0x7100965e68 / 0x7100965e78 / 0x7100965e88 / 0x7100965e98 (placeholder names)
    bool is898Zero() const;
    bool is898EqualTo3() const;
    bool is898Below3() const;
    // 0x7100965ea8 (placeholder name): _84c
    s32 sub_7100965EA8() const;
    // 0x710096603c (placeholder name): the screen size divided by _878
    void sub_710096603C(sead::Vector2f* out) const;
    // 0x7100966064 (placeholder name): the screen size divided by _888
    void sub_7100966064(sead::Vector2f* out) const;
    // 0x7100959438 (placeholder name; defined in uiMapMarker.cpp next to its address neighbours): whether `entry` is _698
    bool sub_7100959438(const UiSubsys1Entry* entry) const;
    bool is898Positive() const;
    // 0x7100965fec (placeholder name): 6.0 / 7.5 / 8.5 / 9.5 for `_898` 0 .. 3 (6.0 otherwise)
    f32 sub_7100965FEC() const;
    f32 sub_7100965EE0(f32 angle) const;
    // 0x7100966de8 (placeholder name): the group of the s32 `value` (0-5 and 11-13: 5, 6-10: 4, else -1)
    s32 sub_7100966DE8(s32 value) const;
    bool sub_7100967498() const;
    bool sub_71009674C0() const;
    bool checkEnded388c();
    bool return0D() const;
    bool return0B() const;
    bool return0() const;
    s32 get3820() const;
    sead::Vector3f* getVec3834();
    void resetVec3834();
    u8 get3858() const;
    bool is38b8And38b9Clear() const;
    // 0x7100963538 / 0x7100963560 (placeholder names): range tests of an s32 (6..10 / <6 or 11..13)
    bool sub_7100963538(s32 value) const;
    bool sub_7100963560(s32 value) const;
    // 0x710096357c / 0x7100963590 / 0x710096371c / 0x71009638e8 (placeholder names)
    sead::Vector2f* sub_710096357C() const;
    s32 returnFF() const;
    u8 get12c() const;
    void set6e4(s32 value);
    // 0x71009638f0 / 0x7100963c70 (placeholder names): set / clear the quest at _3a0, then sub_71009638F8
    void sub_71009638F0(ksys::qst::Quest* quest);
    void sub_7100963C70();
    // 0x71009638f8 (CSV unnamed; not decompiled)
    void sub_71009638F8();
    // 0x7100960ad8 (CSV unnamed; not decompiled; called by Unk_7102478048::m31)
    void sub_7100960AD8();
    // 0x710095b530 (CSV uiSubsys1::x_0; not decompiled; called by ScreenAppMapWidget::m31)
    void sub_710095B530();
    // 0x71009641d4 / 0x71009641e4 / 0x71009645a0 / 0x7100964a40 / 0x7100964ba4 (placeholder names)
    bool is38e0Equal(s32 value) const;
    s32 sub_71009641E4() const;
    void sub_71009645A0();
    void sub_7100964A40(const sead::Vector3f& pos);
    s32 get614() const;
    // 0x7100965938 / 0x7100965994 / 0x710096599c / 0x7100965cf0 (placeholder names)
    s32 sub_7100965938() const;
    void set898(s32 value);
    bool returnTrue2() const;
    // 0x7100965e60 (placeholder name): always false
    bool returnFalse() const;
    s32 get7c4(s32 index) const;

private:
    static UiSubsys1* sInstance;

    u8 _0[0x29];
    /* 0x29 */ u8 _29;
    u8 _2a[0x88 - 0x2a];
    /* 0x88 */ bool _88;
    u8 _89[0x120 - 0x89];
    /* 0x120 */ u32 _120;
    /* 0x124 */ u32 _124;
    /* 0x128 */ s32 _128;
    /* 0x12c */ u8 _12c;
    u8 _12d[0x250 - 0x12d];
    /* 0x250 */ sead::ObjList<void*> _250;
    /* 0x280 */ sead::ObjList<void*> _280;
    /* 0x2b0 */ sead::ObjList<void*> _2b0;
    // Marker lists filled by factory 0x710095c0a8: the filtered entries, then kinds 2 and 0x2b.
    /* 0x2e0 */ sead::PtrArray<UiSubsys1Entry> _2e0;
    /* 0x2f0 */ sead::PtrArray<UiSubsys1PinEntry> _2f0;
    /* 0x300 */ sead::PtrArray<UiSubsys1PinEntry> _300;
    /* 0x310 */ sead::PtrArray<UiSubsys1Marker> _310;
    // The current Divine Beast / Final Trial marker (kinds 8, 9, 7, 10), stored by the same factory.
    /* 0x320 */ UiSubsys1Entry* _320;
    /* 0x328 */ UiSubsys1Entry* _328;
    /* 0x330 */ UiSubsys1Entry* _330;
    /* 0x338 */ UiSubsys1Entry* _338;
    u8 _340[0x378 - 0x340];
    /* 0x378 */ UiSubsys1Unk378* _378;
    u8 _380[0x3a0 - 0x380];

public:
    // the quest picked for the map (passed to sub_7100A9AC84 by sub_71009F2204)
    /* 0x3a0 */ ksys::qst::Quest* _3a0;

private:
    u8 _3a8[0x478 - 0x3a8];
    /* 0x478 */ Unk_7102476548* _478;
    u8 _480[0x4bc - 0x480];
    /* 0x4bc */ sead::Vector3f _4bc;
    /* 0x4c8 */ bool _4c8;
    u8 _4c9[0x4cc - 0x4c9];
    /* 0x4cc */ bool _4cc = false;  // set by S7EventFlow::m9
    u8 _4cd[0x598 - 0x4cd];
    /* 0x598 */ sead::PtrArray<Unk_7102476640> _598;
    /* 0x5a8 */ sead::ObjList<Unk_7102476640*> _5a8;
    /* 0x5d8 */ sead::ObjList<Unk_7102476640*> _5d8;
    /* 0x608 */ bool _608;
    u8 _609[0x610 - 0x609];
    /* 0x610 */ sead::PtrArray<UiSubsys1Entry> _610;
    /* 0x620 */ sead::ObjList<UiSubsys1Entry*> _620;
    /* 0x650 */ UiSubsys1Entry* _650;
    /* 0x658 */ sead::PtrArray<UiSubsys1Entry> _658;
    /* 0x668 */ sead::ObjList<UiSubsys1Entry*> _668;
    /* 0x698 */ UiSubsys1Entry* _698;
    /* 0x6a0 */ sead::ObjList<UiSubsys1Entry*> _6a0;
    /* 0x6d0 */ s32 _6d0;
    /* 0x6d4 */ f32 _6d4;
    /* 0x6d8 */ f32 _6d8;
    /* 0x6dc */ f32 _6dc;
    /* 0x6e0 */ f32 _6e0;
    /* 0x6e4 */ s32 _6e4;
    u8 _6e8[0x6ec - 0x6e8];
    /* 0x6ec */ bool _6ec;
    /* 0x6f0 */ UiTimer _6f0;
    u8 _708[0x7c4 - 0x708];
    /* 0x7c4 */ sead::SafeArray<s32, 15> _7c4;
    /* 0x800 */ s32 _800;
    u8 _804[0x808 - 0x804];
    /* 0x808 */ sead::CriticalSection _808;
    /* 0x848 */ s32 _848;
    /* 0x84c */ s32 _84c;  // read by sub_7100965EA8
    // 0x850: the map view parameters (position +0x20, scale +0x28, rotation +0x2c, offsets +0x30, a second
    // scale +0x38, view size +0x40, mode +0x48, scale factors +0x60); sub_7100965E58 returns its address
    /* 0x850 */ Unk_7102475368 _850;
    u8 _8b8[0x8c0 - 0x8b8];
    // The bounds of the map view (min / max corner)
    /* 0x8c0 */ sead::Vector2f _8c0;
    /* 0x8c8 */ sead::Vector2f _8c8;
    u8 _8d0[0xd88 - 0x8d0];
    // The map mode table: 5 groups of 0x888 bytes, 12 entries of 0xa8 (indexed in sub_71009635DC).
    /* 0xd88 */ s32 _d88[0xa57];
    u8 _36e4[0x3820 - 0x36e4];
    /* 0x3820 */ s32 _3820;
    u8 _3824[0x3830 - 0x3824];
    /* 0x3830 */ s32 _3830;
    /* 0x3834 */ sead::Vector3f _3834;
    /* 0x3840 */ UiTimer _3840;
    /* 0x3858 */ u8 _3858;
    u8 _3859[0x3860 - 0x3859];
    /* 0x3860 */ u16 _3860;
    u8 _3862[0x3864 - 0x3862];
    /* 0x3864 */ u32 _3864;
    /* 0x3868 */ sead::Vector2f _3868;
    /* 0x3870 */ sead::Vector2f _3870;
    /* 0x3878 */ sead::Vector2f _3878;
    /* 0x3880 */ f32 _3880;
    /* 0x3884 */ bool _3884;
    /* 0x3885 */ bool _3885;
    u8 _3886[0x3888 - 0x3886];
    /* 0x3888 */ s32 _3888;
    /* 0x388c */ UiTimer _388c;
    /* 0x38a4 */ s32 _38a4;
    /* 0x38a8 */ s32 _38a8;
    /* 0x38ac */ bool _38ac;
    /* 0x38ad */ u8 _38ad;
    u8 _38ae[0x38b8 - 0x38ae];
    /* 0x38b8 */ bool _38b8;
    /* 0x38b9 */ u8 _38b9;
    u8 _38ba[0x38c8 - 0x38ba];
    /* 0x38c8 */ u8 _38c8;
    /* 0x38c9 */ u8 _38c9;
    u8 _38ca[0x38d8 - 0x38ca];
    /* 0x38d8 */ bool _38d8;
    /* 0x38d9 */ u8 _38d9;
    u8 _38da[0x38e0 - 0x38da];
    /* 0x38e0 */ s32 _38e0;
    /* 0x38e4 */ s32 _38e4;
    /* 0x38e8 */ s32 _38e8;
    /* 0x38ec */ s32 _38ec;
    /* 0x38f0 */ s32 _38f0;
    /* 0x38f4 */ s32 _38f4;
    /* 0x38f8 */ s32 _38f8;
    /* 0x38fc */ s32 _38fc;
    /* 0x3900 */ s32 _3900;
    /* 0x3904 */ bool _3904;
    /* 0x3905 */ u8 _3905;
    u8 _3906[0x3920 - 0x3906];
};

// 0x7100965960: entry 0-3 of the float buffer at 0x71025d6e58, -1 otherwise
f32 sub_7100965960(s32 index);

// 0x7100966008 / 0x7100966018 (placeholder names): the layout screen size (1280 x 720) / half of it
const sead::Vector2f* sub_7100966008();
void sub_7100966018(sead::Vector2f* out);

}  // namespace uking::ui
