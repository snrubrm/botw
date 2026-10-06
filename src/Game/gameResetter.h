#pragma once

#include <basis/seadTypes.h>
#include <heap/seadDisposer.h>
#include <math/seadVector.h>
#include <prim/seadSafeString.h>
#include "KingSystem/Utils/Types.h"

namespace uking {

// The option of the reset functions: a 4-byte class passed by value (it travels in a full 64-bit register:
// `mov x2, x22` in the callers, `mov x20, x2` in startReset). Placeholder type; the values are the
// SystemResetOption dynamic params of the Reset/Warp gimmick actions.
struct ResetOption {
    s32 value;
};

// The first parameter of startReset has the same shape (`mov x1, xzr` for a constant 0 in ResetGimmick; stored
// to Resetter::_24 as a 32-bit value).
struct ResetType {
    s32 value;
};

// Name from the CSV (Resetter::createInstance 0x71007d20a0, startReset, finishedReset, init, calc).
// A sead singleton without vtable (size 0x390, instance 0x71025cc660). Members from createInstance
// (inlined ctor) and startReset; meanings unknown.
// TODO: incomplete (startReset / calc not decompiled).
class Resetter {
    SEAD_SINGLETON_DISPOSER(Resetter)
    Resetter() = default;

public:
    // 0x71007d21b0: declaration only.
    bool startReset(ResetType state, ResetOption option, const sead::SafeString& additional_actor,
                    bool reset_camera, bool a5);
    // 0x71007d2310: true unless a reset is in progress (_20 is set to 1 by startReset).
    bool finishedReset() const;
    // 0x71007d2320 (declaration only, lane5 s3; the first parameter is null in WarpPLAndResetGimmick): starts a
    // reset to the map position `pos_name` (SceneMgr::getMapPosition). The parameter meanings are guesses.
    bool sub_71007D2320(void* a1, ResetOption option, const sead::SafeString& pos_name,
                        const sead::SafeString& additional_actor, bool a5);
    // 0x71007d25a4 (declaration only, lane5 s3; WarpPLToPosAndResetGimmick): starts a reset to the given position
    // and rotation (the player's scale vector is passed along). The parameter meanings are guesses.
    bool sub_71007D25A4(void* a1, ResetOption option, const sead::Vector3f* pos, const sead::Vector3f* rotation,
                        const sead::Vector3f* scale, const sead::SafeString& additional_actor, bool a7);

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
