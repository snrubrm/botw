#pragma once

#include "KingSystem/ActorSystem/actAiAi.h"
#include "KingSystem/ActorSystem/actUnk_7100d3bc4c.h"

namespace uking::ai {

class EnemyMoveToGround : public ksys::act::ai::Ai {
    SEAD_RTTI_OVERRIDE(EnemyMoveToGround, ksys::act::ai::Ai)
public:
    explicit EnemyMoveToGround(const InitArg& arg);
    ~EnemyMoveToGround() override;

    bool init_(sead::Heap* heap) override;
    void enter_(ksys::act::ai::InlineParamPack* params) override;
    void leave_() override;
    void loadParams_() override;

    bool sub_710039A2B8();

protected:
    // static_param at offset 0x38
    const int* mRetryTime_s{};
    // static_param at offset 0x40
    const float* mAreaThreshold_s{};
    // static_param at offset 0x48
    const float* mSearchRadius_s{};
    s32 _50 = 0;
    ksys::act::Unk_7100d3bce4 _58{mActor};
    sead::Vector3f _70;
    u32 _7c;
};
KSYS_CHECK_SIZE_NX150(EnemyMoveToGround, 0x80);

}  // namespace uking::ai
