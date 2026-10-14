#pragma once

#include "Game/Actor/Action/actionLastBossBlowOff.h"
#include "KingSystem/ActorSystem/actAiAction.h"

namespace uking::action {

class SiteBossBowBlowOff : public LastBossBlowOff {
    SEAD_RTTI_OVERRIDE(SiteBossBowBlowOff, LastBossBlowOff)
public:
    explicit SiteBossBowBlowOff(const InitArg& arg);
    ~SiteBossBowBlowOff() override;

    bool init_(sead::Heap* heap) override;
    void enter_(ksys::act::ai::InlineParamPack* params) override;
    void leave_() override;
    void loadParams_() override;

protected:
    void calc_() override;

    bool m36() override;
    s32 m37() override;

    // 0x7100256c34 (placeholder name): the boss is back within the force recover range of its home.
    bool sub_7100256C34();

    // static_param at offset 0x170
    const int* mAddForceRecoverTime_s{};
    // static_param at offset 0x178
    const bool* mIsRemoveCharacterController_s{};
    // static_param at offset 0x180
    const sead::Vector3f* mForceRecoverDist_s{};
    // static_param at offset 0x188
    const sead::Vector3f* mForceRecoverOffset_s{};
};

}  // namespace uking::action
