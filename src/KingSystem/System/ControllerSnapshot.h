#pragma once

#include <math/seadVector.h>
#include <prim/seadRuntimeTypeInfo.h>
#include "KingSystem/Utils/Types.h"

// Placeholder name: input snapshot embedded at Controller +0x38. The complete vtable at
// 0x71024dd5c8 contains root RTTI methods followed by D1/D0 (0x7100d9e140 / 0x7100d9e144).
class Unk_71024dd5c8 {
    SEAD_RTTI_BASE(Unk_71024dd5c8)
public:
    // 0x7100d9e0f4; Controller::createInstance constructs this before its next member at +0x90.
    Unk_71024dd5c8();
    virtual ~Unk_71024dd5c8();

    // 0x7100d9e148: always true.
    bool sub_7100D9E148();
    bool sub_7100D9E48C() const;
    const sead::Vector2f& sub_7100D9E498() const;

private:
    friend class Controller;

    bool _8;
    u32 _c;
    u32 _10;
    f32 _14;
    f32 _18;
    s32 _1c;
    s32 _20;
    s32 _24;
    sead::Vector2f _28;
    sead::Vector2f _30;
    sead::Vector2f _38;
    sead::Vector2f _40;
    sead::Vector2f _48;
    sead::Vector2f _50;
};
KSYS_CHECK_SIZE_NX150(Unk_71024dd5c8, 0x58);
