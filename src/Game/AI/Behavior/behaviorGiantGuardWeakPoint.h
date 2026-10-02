#pragma once

#include <prim/seadSafeString.h>
#include "Game/AI/aiUnk_7102357d20.h"
#include "Game/AI/aiUnk_71025afb58.h"
#include "KingSystem/ActorSystem/actAiBehavior.h"
#include "KingSystem/System/Timer.h"

namespace uking::behavior {

class GiantGuardWeakPoint : public ksys::act::ai::Behavior {
    SEAD_RTTI_OVERRIDE(GiantGuardWeakPoint, ksys::act::ai::Behavior)
public:
    explicit GiantGuardWeakPoint(const InitArg& arg);
    ~GiantGuardWeakPoint() override;
    void m8() override;
    void loadParams() override;
    bool m6(sead::Heap* heap) override;  // not decompiled yet (0x71006253f0)
    void m7() override;  // not decompiled yet (0x71006256a4)
    void m9() override;  // not decompiled yet (0x7100625af0)

    /* 0x28 */ const int* mTargetBone_s{};
    /* 0x30 */ const int* mDelayTime_s{};
    /* 0x38 */ const int* mWeakPointArmorIdx_s{};
    /* 0x40 */ const float* mGuardAngleRange_s{};
    /* 0x48 */ const float* mRestLifeRate_s{};
    /* 0x50 */ sead::SafeString mGuardStartAS_s{};
    /* 0x60 */ sead::SafeString mGuardLoopAS_s{};
    /* 0x70 */ sead::SafeString mGuardEndAS_s{};
    /* 0x80 */ sead::SafeString mGuardTgName_s{};
    /* 0x90 */ sead::SafeString mPartialBoneName_s{};
    /* 0xa0 */ void* mGiantPartBoneUnit_a{};
    /* 0xa8 */ Unk_710001bf60 _a8{mActor};
    /* 0x128 */ ksys::Timer _128{0.0f, 0.0f};
    /* 0x134 */ bool _134 = false;
    /* 0x135 */ bool _135 = false;
    /* 0x138 */ Unk_71025afb58** _138 = nullptr;
};
KSYS_CHECK_SIZE_NX150(GiantGuardWeakPoint, 0x140);

}  // namespace uking::behavior
