#pragma once

#include <container/seadOffsetList.h>
#include <heap/seadDisposer.h>
#include <container/seadPtrArray.h>
#include <math/seadVector.h>
#include <container/seadSafeArray.h>
#include "Game/UI/uiTimer.h"
#include "KingSystem/Utils/Types.h"

namespace ksys::act {
class Actor;
}

namespace ksys::util {
class TaskThread;
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
    // D1 0x7100a6d5bc, D0 0x7100a6d654 (not decompiled)
    virtual ~UiLowPrioThreadMgr();

    // 0x7100a6d978 / 0x7100a6d988 / 0x7100a6d998
    void pause();
    void resume();
    void clearQueue();

    /* 0x28 */ ksys::util::TaskThread* _28 = nullptr;
    /* 0x30 */ void* _30 = nullptr;
    /* 0x38 */ void* _38[100]{};
};
KSYS_CHECK_SIZE_NX150(UiLowPrioThreadMgr, 0x358);

// Instance pointer 0x71025d6ac0 (placeholder name; used by the UI facade).
class Unk_71025d6ac0 {
public:
    static Unk_71025d6ac0* instance() { return sInstance; }

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

    u8 _0[0x29];
    /* 0x29 */ bool _29;
    u8 _2a[0x74 - 0x2a];
    /* 0x74 */ s32 _74;
    u8 _78[0x80 - 0x78];
    /* 0x80 */ s32 _80;
    /* 0x84 */ s32 _84;

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
    void sub_710094B8A4(bool a1);
    void sub_710094BE14();
    void sub_710094BE30();

    /* 0x28 */ void* _28 = nullptr;
    /* 0x30 */ void** _30 = nullptr;
    /* 0x38 */ u16 _38 = 0;
    /* 0x3a */ u8 _3a = 0;
    /* 0x3c */ s32 _3c = 13;
    /* 0x40 */ s32 _40 = 7;
    /* 0x44 */ s32 _44 = 0;
    /* 0x48 */ u8 _48 = 0;
    /* 0x49 */ u8 _49 = 0;
    /* 0x4a */ u8 _4a = 0;
    u8 _4b;
    u8 _4c[0x61 - 0x4c]{};
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

    u8 _0[0x80];
    /* 0x80 */ sead::Vector3f _80;
    u8 _8c[0xe8 - 0x8c];
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
    u8 _c28[0xd38 - 0xc28];
    /* 0xd38 */ u16 _d38;
    /* 0xd3a */ u8 _d3a;
    u8 _d3b;
    /* 0xd3c */ s32 _d3c;
    /* 0xd40 */ s32 _d40;
    /* 0xd44 */ s32 _d44;
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
class Unk_71025d69f0 {
    SEAD_SINGLETON_DISPOSER(Unk_71025d69f0)
    Unk_71025d69f0() = default;

public:
    virtual ~Unk_71025d69f0();

    void sub_710094D8CC();
    void sub_710094D8DC();
    void sub_710094E0A0();
    bool sub_710094E920();
    void sub_710094E1C0(bool value);
    void sub_710094E480();
    void sub_710094D9F4(s32 a1, s32 a2, s32 a3, s32 a4);
    void sub_710094DCC4(s32 a1, s32 a2);

    /* 0x28 */ s32 _28 = 1;
    /* 0x2c */ s32 _2c = 4;
    /* 0x30 */ s32 _30 = 4;
    /* 0x34 */ u8 _34 = 0;
    /* 0x35 */ u8 _35 = 1;
    /* 0x36 */ u8 _36 = 0;
    u8 _37 = 0;
    /* 0x38 */ u8 _38 = 0;
    /* 0x3c */ s32 _3c = 0;
    /* 0x40 */ void* _40 = nullptr;
};
KSYS_CHECK_SIZE_NX150(Unk_71025d69f0, 0x48);

// Element of UiSubsys1's list at 0x280 (placeholder: the first word is compared with a key, the list node is at +8; erased
// entries are chained through the first word on a free list at 0x298).
struct UiSubsys1ListEntry {
    void* _0;
    sead::ListNode _8;
};

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

// Element of UiSubsys1's table at 0x658 (placeholder; flags at 0x3c).
struct UiSubsys1Entry {
    // 0x7100951388: sets flag 8, then forwards to the virtual control update.
    void sub_7100951388(bool enabled);
    u8 _0[0x28];
    /* 0x28 */ sead::Vector3f _28;  // map pin position (CopyMapPinPosition::oneShot_)
    u8 _34[0x3c - 0x34];
    /* 0x3c */ u32 _3c;
};

class UiSubsys1 {
public:
    static UiSubsys1* instance() { return sInstance; }

    bool sub_7100960DF8();
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
    void sub_710096101C();
    void copy38b8To38b9();
    void set38b8();
    void clear38b8();
    void sub_710095B1BC();
    // 0x7100968844 (CSV unnamed; not decompiled; ScreenAppMap::demoLeave)
    void sub_7100968844();
    void set3885() { _3885 = true; }
    void clear3885() { _3885 = false; }
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
    void sub_7100963C78(bool a1);
    bool sub_710096310C(s32* out_index, const sead::Vector3f* pos, f32 radius);

    // Accessors (uiSubsys1.cpp). Placeholder names after the offsets of the fields they use.
    bool is848Zero() const;
    bool returnTrue() const;
    bool is848EqualTo1() const;
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
    u8 get29() const;
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
    u8 get88() const;
    void clear88();
    sead::Vector2f* getVec3868();
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
    // 0x7100965e68 / 0x7100965e78 / 0x7100965e88 / 0x7100965e98 (placeholder names)
    bool is898Zero() const;
    bool is898EqualTo3() const;
    bool is898Below3() const;
    bool is898Positive() const;
    // 0x7100965fec (placeholder name): 6.0 / 7.5 / 8.5 / 9.5 for `_898` 0 .. 3 (6.0 otherwise)
    f32 sub_7100965FEC() const;
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
    u8* sub_710096357C() const;
    s32 returnFF() const;
    u8 get12c() const;
    void set6e4(s32 value);
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
    s32 get7c4(s32 index) const;

private:
    static UiSubsys1* sInstance;

    u8 _0[0x29];
    /* 0x29 */ u8 _29;
    u8 _2a[0x88 - 0x2a];
    /* 0x88 */ u8 _88;
    u8 _89[0x120 - 0x89];
    /* 0x120 */ u16 _120;
    u8 _122[0x128 - 0x122];
    /* 0x128 */ s32 _128;
    /* 0x12c */ u8 _12c;
    u8 _12d[0x280 - 0x12d];
    /* 0x280 */ sead::OffsetList<UiSubsys1ListEntry> _280;
    /* 0x298 */ UiSubsys1ListEntry* _298;
    u8 _2a0[0x310 - 0x2a0];
    /* 0x310 */ sead::PtrArray<UiSubsys1Marker> _310;
    u8 _320[0x378 - 0x320];
    /* 0x378 */ UiSubsys1Unk378* _378;
    u8 _380[0x478 - 0x380];
    /* 0x478 */ UiSubsys1Entry* _478;
    u8 _480[0x4bc - 0x480];
    /* 0x4bc */ sead::Vector3f _4bc;
    /* 0x4c8 */ bool _4c8;
    u8 _4c9[0x610 - 0x4c9];
    /* 0x610 */ sead::PtrArray<UiSubsys1Entry> _610;
    u8 _620[0x650 - 0x620];
    /* 0x650 */ UiSubsys1Entry* _650;
    /* 0x658 */ sead::PtrArray<UiSubsys1Entry> _658;
    u8 _668[0x6e4 - 0x668];
    /* 0x6e4 */ s32 _6e4;
    u8 _6e8[0x6ec - 0x6e8];
    /* 0x6ec */ bool _6ec;
    /* 0x6f0 */ UiTimer _6f0;
    u8 _708[0x7c4 - 0x708];
    /* 0x7c4 */ sead::SafeArray<s32, 15> _7c4;
    u8 _800[0x848 - 0x800];
    /* 0x848 */ s32 _848;
    u8 _84c[0x880 - 0x84c];
    /* 0x880 */ sead::Vector2f _880;
    u8 _888[0x898 - 0x888];
    /* 0x898 */ s32 _898;
    u8 _89c[0x3820 - 0x89c];
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

}  // namespace uking::ui
