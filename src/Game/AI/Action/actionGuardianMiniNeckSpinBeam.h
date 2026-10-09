#pragma once

#include "Game/AI/Action/actionNeckSpinBeam.h"
#include "KingSystem/ActorSystem/actAiAction.h"

namespace uking::action {

class GuardianMiniNeckSpinBeam : public NeckSpinBeam {
    SEAD_RTTI_OVERRIDE(GuardianMiniNeckSpinBeam, NeckSpinBeam)
public:
    explicit GuardianMiniNeckSpinBeam(const InitArg& arg);
    ~GuardianMiniNeckSpinBeam() override;

    void enter_(ksys::act::ai::InlineParamPack* params) override;
    void loadParams_() override;

protected:
    void calc_() override;
    void m33() override;
    const sead::SafeString& m34() override;
    const sead::SafeString& m35() override;
    bool sub_7100197BE4(sead::Vector3f* direction);
    int m36() override { return *mMaxLengthTime_s; }

    // static_param at offset 0x178
    const int* mSpinNum_s{};
    // static_param at offset 0x180
    const int* mMaxLengthTime_s{};
    // static_param at offset 0x188
    const bool* mIsStraight_s{};
    f32 _190 = 0;
    f32 _194 = 0;
    f32 _198 = 0;
    sead::Vector3f _19c;
};
KSYS_CHECK_SIZE_NX150(GuardianMiniNeckSpinBeam, 0x1a8);

}  // namespace uking::action
