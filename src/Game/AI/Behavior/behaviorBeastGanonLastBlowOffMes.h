#pragma once

#include <gsys/gsysModelAccessKey.h>
#include <prim/seadSafeString.h>
#include "Game/AI/Behavior/behaviorSimpleAtvUnitOpenDlgRnd3.h"

namespace uking::behavior {

class BeastGanonLastBlowOffMes : public SimpleAtvUnitOpenDlgRnd3 {
    SEAD_RTTI_OVERRIDE(BeastGanonLastBlowOffMes, SimpleAtvUnitOpenDlgRnd3)
public:
    explicit BeastGanonLastBlowOffMes(const InitArg& arg);
    ~BeastGanonLastBlowOffMes() override;
    bool m6(sead::Heap* heap) override;
    void m8() override;
    void m9() override;
    void loadParams() override;
    void m7() override;  // not decompiled yet (0x7100619868)
    bool m15() override;  // not decompiled yet (0x710061997c)

    /* 0xb0 */ const int* mDistXZ_s{};
    /* 0xb8 */ const float* mSubsY_s{};
    /* 0xc0 */ const float* mFrontAngle_s{};
    /* 0xc8 */ sead::SafeString mXZBaseNode_s{};
    /* 0xd8 */ gsys::BoneAccessKeyEx _d8;
};
KSYS_CHECK_SIZE_NX150(BeastGanonLastBlowOffMes, 0x110);

}  // namespace uking::behavior
