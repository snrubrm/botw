#pragma once

#include "KingSystem/ActorSystem/actAiAi.h"
#include "KingSystem/System/Timer.h"

namespace uking::act {
class WolfLink;
}

namespace uking::ai {

class WolfLinkRushAttack : public ksys::act::ai::Ai {
    SEAD_RTTI_OVERRIDE(WolfLinkRushAttack, ksys::act::ai::Ai)
public:
    explicit WolfLinkRushAttack(const InitArg& arg);
    ~WolfLinkRushAttack() override;

    bool init_(sead::Heap* heap) override;
    void enter_(ksys::act::ai::InlineParamPack* params) override;
    void calc_() override;
    void leave_() override;
    void loadParams_() override;

    bool sub_710060C1E4(bool x);

protected:
    // static_param at offset 0x38
    const float* mAttackPosOffsetLength_s{};
    // static_param at offset 0x40
    const float* mAllowUpdateTimerLength_s{};
    // static_param at offset 0x48
    const bool* mCheckSafeGround_s{};
    // dynamic_param at offset 0x50
    sead::Vector3f* mTargetPos_d{};
    act::WolfLink* _58{};
    ksys::Timer _60;
    sead::Vector3f _6c;
};
KSYS_CHECK_SIZE_NX150(WolfLinkRushAttack, 0x78);

}  // namespace uking::ai
