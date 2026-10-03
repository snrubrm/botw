#pragma once

#include <math/seadVector.h>
#include <container/seadSafeArray.h>
#include "KingSystem/Utils/Types.h"

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
    u8 _b78[0xd54 - 0xb78];
    /* 0xd54 */ sead::SafeArray<s32, 3> _d54;

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

}  // namespace uking::ui
