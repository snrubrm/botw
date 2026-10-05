#pragma once

#include <container/seadOffsetList.h>
#include <container/seadPtrArray.h>
#include <math/seadVector.h>
#include <container/seadSafeArray.h>
#include "KingSystem/Utils/Types.h"

namespace ksys::act {
class Actor;
}

namespace uking::ui {

// UI singletons whose classes are not identified yet. Placeholder names after the address of the
// singleton instance pointer (data_symbols.csv); only the fields used by the UI facade functions
// (uiMiscFacade.cpp) are declared, at their original offsets.

// Instance pointer 0x71025d6578 (createInstance 0x7100949bbc, size 0x78, polymorphic with a
// singleton disposer at 0x8). `_3c` is a state (initialised to 13), `_40` is initialised to 7.
class Unk_71025d6578 {
public:
    static Unk_71025d6578* instance() { return sInstance; }

    void sub_710094B844(bool a1, bool a2, bool a3);
    void sub_710094B8A4(bool a1);
    void sub_710094BE14();

    u8 _0[0x3c];
    /* 0x3c */ s32 _3c;
    u8 _40[0x49 - 0x40];
    /* 0x49 */ u8 _49;
    u8 _4a[0x61 - 0x4a];
    /* 0x61 */ u8 _61;  // bit 1: ?, bits 1 / 2 are rewritten by sub_710094BE14
    u8 _62;
    /* 0x63 */ u8 _63;  // four flags (bits 0 / 1 and 2 / 3: two pairs, see sub_710094B844)
    u8 _64[0x78 - 0x64];

private:
    static Unk_71025d6578* sInstance;
};

// Instance pointer 0x71025d6550 (a large map / compass related UI object; `_b64`, `_b6c`, `_b74`
// are states).
class Unk_71025d6550 {
public:
    static Unk_71025d6550* instance() { return sInstance; }

    void sub_71009482FC();
    void sub_7100948CC4(const void* a1);
    void sub_71009489C0(const void* a1);
    void sub_7100948E44(const void* a1);
    void sub_7100948F0C(const f32* values);
    void sub_7100948F48(f32 value);

    u8 _0[0x80];
    /* 0x80 */ sead::Vector3f _80;
    u8 _8c[0xb64 - 0x8c];
    /* 0xb64 */ s32 _b64;
    /* 0xb68 */ f32 _b68;
    /* 0xb6c */ s32 _b6c;
    /* 0xb70 */ f32 _b70;
    /* 0xb74 */ s32 _b74;
    u8 _b78[0xd38 - 0xb78];
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

// Instance pointer 0x71025d69f0 (`_2c` is a state set by the facade functions).
class Unk_71025d69f0 {
public:
    static Unk_71025d69f0* instance() { return sInstance; }

    void sub_710094E0A0();
    bool sub_710094E920();
    void sub_710094D9F4(s32 a1, s32 a2, s32 a3, s32 a4);
    void sub_710094DCC4(s32 a1, s32 a2);

    u8 _0[0x2c];
    /* 0x2c */ s32 _2c;

private:
    static Unk_71025d69f0* sInstance;
};

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

// The index and display value select a pin; producers supply an actor's world position.
struct UiSubsys1PinArg {
    s32 index;
    s32 value;
    sead::Vector3f pos;
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

// Element of UiSubsys1's table at 0x658 (placeholder; bit 4 of the byte at 0x3c is tested).
struct UiSubsys1Entry {
    u8 _0[0x28];
    /* 0x28 */ sead::Vector3f _28;  // map pin position (CopyMapPinPosition::oneShot_)
    u8 _34[0x3c - 0x34];
    /* 0x3c */ u8 _3c;
};

class UiSubsys1 {
public:
    static UiSubsys1* instance() { return sInstance; }

    bool sub_7100960DF8();
    // 0x71009512f8 / 0x7100951338 (CSV uiSubsys1::__auto41 / __auto42; placeholder names)
    UiSubsys1ListEntry* findListEntry(void* key);
    bool freeListEntry(UiSubsys1ListEntry* entry);
    // 0x7100963704 / 0x7100968af8 / 0x7100968bd8 (placeholder names; the last is declared only)
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
    // 0x71009644e8 (declared only; lane3 s22): entry `index` of the table at 0x658 (null if out of range).
    UiSubsys1Entry* sub_71009644E8(s32 index);
    void sub_71009645D0(const void* a1);
    void sub_710096372C(const void* a1);
    void* sub_71009648A8();
    bool sub_7100964A0C(s32 a1);
    void sub_7100963CE8(ksys::act::Actor* actor);
    void sub_71009661DC(const void* a1, s32* out);
    void sub_7100963C8C(const UiSubsys1PinArg* arg);
    void sub_7100963C78(bool a1);
    bool sub_710096310C(s32* out_index, const sead::Vector3f* pos, f32 radius);

    // Accessors (uiSubsys1.cpp). Placeholder names after the offsets of the fields they use.
    bool is848Zero() const;
    bool returnTrue() const;
    bool is848EqualTo1() const;
    u8 get38b8() const;
    bool is128EqualTo6() const;
    void set848(s32 value);
    void set38c8();
    void clear38c8();
    void set3884(bool value);
    s32 get38a8() const;
    u8 get38ac() const;
    void set38e4(s32 value);
    s32 get38f8() const;
    s32 get3900() const;
    void set3904(bool value);
    bool return0A() const;
    bool return0B() const;
    bool return0() const;
    s32 get3820() const;
    sead::Vector3f* getVec3834();
    void resetVec3834();
    u8 get3858() const;
    bool is38b8And38b9Clear() const;

private:
    static UiSubsys1* sInstance;

    u8 _0[0x128];
    /* 0x128 */ s32 _128;
    u8 _12c[0x280 - 0x12c];
    /* 0x280 */ sead::OffsetList<UiSubsys1ListEntry> _280;
    /* 0x298 */ UiSubsys1ListEntry* _298;
    u8 _2a0[0x310 - 0x2a0];
    /* 0x310 */ sead::PtrArray<UiSubsys1Marker> _310;
    u8 _320[0x378 - 0x320];
    /* 0x378 */ UiSubsys1Unk378* _378;
    u8 _380[0x658 - 0x380];
    /* 0x658 */ sead::PtrArray<UiSubsys1Entry> _658;
    u8 _668[0x848 - 0x668];
    /* 0x848 */ s32 _848;
    u8 _84c[0x3820 - 0x84c];
    /* 0x3820 */ s32 _3820;
    u8 _3824[0x3830 - 0x3824];
    /* 0x3830 */ s32 _3830;
    /* 0x3834 */ sead::Vector3f _3834;
    u8 _3840[0x3858 - 0x3840];
    /* 0x3858 */ u8 _3858;
    u8 _3859[0x3860 - 0x3859];
    /* 0x3860 */ u16 _3860;
    u8 _3862[0x3884 - 0x3862];
    /* 0x3884 */ bool _3884;
    /* 0x3885 */ bool _3885;
    u8 _3886[0x38a8 - 0x3886];
    /* 0x38a8 */ s32 _38a8;
    /* 0x38ac */ u8 _38ac;
    u8 _38ad[0x38b8 - 0x38ad];
    /* 0x38b8 */ u8 _38b8;
    /* 0x38b9 */ u8 _38b9;
    u8 _38ba[0x38c8 - 0x38ba];
    /* 0x38c8 */ u8 _38c8;
    u8 _38c9[0x38e4 - 0x38c9];
    /* 0x38e4 */ s32 _38e4;
    u8 _38e8[0x38f8 - 0x38e8];
    /* 0x38f8 */ s32 _38f8;
    u8 _38fc[0x3900 - 0x38fc];
    /* 0x3900 */ s32 _3900;
    /* 0x3904 */ bool _3904;
    u8 _3905[0x3920 - 0x3905];
};

}  // namespace uking::ui
