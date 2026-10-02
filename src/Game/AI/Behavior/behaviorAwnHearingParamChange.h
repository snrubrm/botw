#pragma once

#include "KingSystem/ActorSystem/actAiBehavior.h"

namespace uking::behavior {

// TODO: `_38` is an awareness parameter object with vtable 0x71023e2750 (base vtable 0x71023e2708; functions in
// DistanceLostCheck's translation unit) passed to AwarenessInstance 0x7100d7e6f4; type not declared yet.
class AwnHearingParamChange : public ksys::act::ai::Behavior {
    SEAD_RTTI_OVERRIDE(AwnHearingParamChange, ksys::act::ai::Behavior)
public:
    explicit AwnHearingParamChange(const InitArg& arg);
    bool m6(sead::Heap* heap) override;
    void m7() override;
    void loadParams() override;
    void m8() override;  // not decompiled yet (0x7100618c00)
    void m9() override;  // not decompiled yet (0x7100618cac)
    ~AwnHearingParamChange() override;  // not decompiled yet

    /* 0x28 */ const float* mNoticeRatio_s{};
    /* 0x30 */ const float* mWarnRatio_s{};
    /* 0x38 */ u8 _38[0x20];
};
KSYS_CHECK_SIZE_NX150(AwnHearingParamChange, 0x58);

}  // namespace uking::behavior
