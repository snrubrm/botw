#pragma once

#include <math/seadVector.h>
#include "KingSystem/ActorSystem/actAiAction.h"
#include "KingSystem/Physics/CharacterController/physCharacterController.h"

namespace uking::action {

class HuntingDead : public ksys::act::ai::Action {
    SEAD_RTTI_OVERRIDE(HuntingDead, ksys::act::ai::Action)
public:
    explicit HuntingDead(const InitArg& arg);
    ~HuntingDead() override;

    void enter_(ksys::act::ai::InlineParamPack* params) override;
    void leave_() override;
    void loadParams_() override;

protected:
    // 0x71001b4afc (declared only; defining it here makes clang inline it into enter_). Sets the
    // controller motion type from the water depth (motion type compares go through stack slots in the
    // original, like CCAccessor::changeMotionType; Actor::_68f is a sead::Atomic).
    void sub_71001B4AFC(ksys::phys::CharacterController* controller);
    void calc_() override;

    // static_param at offset 0x20
    const float* mInWaterDepth_s{};
    // static_param at offset 0x28
    const bool* mIsUseOffsetY_s{};
    // static_param at offset 0x30
    sead::SafeString mOffsetBoneName_s{};
    // static_param at offset 0x40
    const sead::Vector3f* mExtraOffset_s{};
    sead::Vector3f _48;
    u8 _54[4];

};
KSYS_CHECK_SIZE_NX150(HuntingDead, 0x58);

}  // namespace uking::action
