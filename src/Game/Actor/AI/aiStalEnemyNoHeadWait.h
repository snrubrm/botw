#pragma once

#include "KingSystem/ActorSystem/actAiAi.h"
#include "KingSystem/ActorSystem/actUnk_7100d3bc4c.h"

namespace uking::ai {

class StalEnemyNoHeadWait : public ksys::act::ai::Ai {
    SEAD_RTTI_OVERRIDE(StalEnemyNoHeadWait, ksys::act::ai::Ai)
public:
    explicit StalEnemyNoHeadWait(const InitArg& arg);
    ~StalEnemyNoHeadWait() override;

    bool init_(sead::Heap* heap) override;
    void enter_(ksys::act::ai::InlineParamPack* params) override;
    void calc_() override;
    void leave_() override;
    void loadParams_() override;

    void sub_710059E790();
    void sub_710059ED70();

protected:
    // static_param at offset 0x38
    const float* mRebootDistance_s{};
    // static_param at offset 0x40
    const float* mRebootTimer_s{};
    // dynamic_param at offset 0x48
    bool* mIsExistLivingHead_d{};
    // dynamic_param at offset 0x50
    bool* mIsExistActiveActor_d{};
    // dynamic_param at offset 0x58
    sead::Vector3f* mTargetPos_d{};
    ksys::act::Unk_7100d3bce4 _60{mActor};
};
KSYS_CHECK_SIZE_NX150(StalEnemyNoHeadWait, 0x78);

}  // namespace uking::ai
