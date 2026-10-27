#pragma once

#include <heap/seadDisposer.h>
#include <prim/seadTypedBitFlag.h>
#include "KingSystem/Utils/Types.h"

namespace ksys::act {

class ActorDebug {
    SEAD_SINGLETON_DISPOSER(ActorDebug)
    ActorDebug();
    virtual ~ActorDebug();

public:
    enum class Flag {
        _100 = 0x100,
        // Set while the mass-renderer draw request is skipped (byte +0x31 bit 6).
        _4000 = 0x4000,
        // Failure flag of the quest / world frame step 0x7100f41bac: it runs the grass core step
        // unless a debug instance exists without it.
        _100000 = 0x100000,
        _200000 = 0x200000,  // enables the UI handler call of ksys::sub_7100F3ED50
        _10000000 = 0x10000000,
        _20000000 = 0x20000000,
        _40000000 = 0x40000000,  // the MCMgr frame jobs run the quest / world calc unless a debug instance has it clear
    };

    struct HashUnused {
        u32 hash = 0;
        u32 b;
    };

    const char* getNullStr(HashUnused* u);
    // 0x7100d29da0: clears the pointer at +0x28.
    void sub_7100D29DA0();
    bool hasFlag(Flag flag) const { return mFlags.isOn(flag); }

    void* _28;
    sead::TypedBitFlag<Flag> mFlags;
    u8 TEMP1[0x2DC];
    f32 mDispDistanceMultiplier;
    u8 TEMP2[0x11c];
};
KSYS_CHECK_SIZE_NX150(ActorDebug, 0x430);

}  // namespace ksys::act
