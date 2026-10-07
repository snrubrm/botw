#pragma once

#include "KingSystem/ActorSystem/Awareness/actAwarenessRequest.h"
#include "KingSystem/ActorSystem/actAiBehavior.h"

namespace uking::behavior {

class AwnHearingParamChange : public ksys::act::ai::Behavior {
    SEAD_RTTI_OVERRIDE(AwnHearingParamChange, ksys::act::ai::Behavior)
public:
    explicit AwnHearingParamChange(const InitArg& arg);
    ~AwnHearingParamChange() override;
    bool m6(sead::Heap* heap) override;
    void m7() override;
    void loadParams() override;
    void m8() override;
    void m9() override;

    /* 0x28 */ const float* mNoticeRatio_s{};
    /* 0x30 */ const float* mWarnRatio_s{};
    /* 0x38 */ Unk_71023e2750 _38;
};
KSYS_CHECK_SIZE_NX150(AwnHearingParamChange, 0x58);

}  // namespace uking::behavior
