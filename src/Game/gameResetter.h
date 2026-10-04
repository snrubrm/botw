#pragma once

#include <basis/seadTypes.h>
#include <heap/seadDisposer.h>
#include <prim/seadSafeString.h>
#include "KingSystem/Utils/Types.h"

namespace uking {

// Name from the CSV (Resetter::createInstance 0x71007d20a0, startReset, finishedReset, init, calc).
// A sead singleton without vtable (size 0x390, instance 0x71025cc660). Members from createInstance
// (inlined ctor) and startReset; meanings unknown.
// TODO: incomplete (startReset / calc not decompiled).
class Resetter {
    SEAD_SINGLETON_DISPOSER(Resetter)
    Resetter() = default;

public:
    // 0x71007d21b0: declaration only.
    bool startReset(s32 state, s32 option, const sead::SafeString& additional_actor,
                    bool reset_camera, bool a5);
    // 0x71007d2310: true unless a reset is in progress (_20 is set to 1 by startReset).
    bool finishedReset() const;

private:
    s32 _20 = 0;
    s32 _24 = 0;
    sead::FixedSafeString<256> _28;
    u8 _140[0x170 - 0x140];
    u8 _170 = 0;
    bool _171 = false;
    bool _172 = false;
    s32 _174 = 0;
    sead::FixedSafeString<512> _178;
};
KSYS_CHECK_SIZE_NX150(Resetter, 0x390);

}  // namespace uking
