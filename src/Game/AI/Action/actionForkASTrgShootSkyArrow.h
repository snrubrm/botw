#pragma once

#include "KingSystem/ActorSystem/actAiAction.h"

namespace uking::action {

class ForkASTrgShootSkyArrow : public ksys::act::ai::Action {
    SEAD_RTTI_OVERRIDE(ForkASTrgShootSkyArrow, ksys::act::ai::Action)
public:
    explicit ForkASTrgShootSkyArrow(const InitArg& arg);
    ~ForkASTrgShootSkyArrow() override;

    bool init_(sead::Heap* heap) override;
    void enter_(ksys::act::ai::InlineParamPack* params) override;
    void leave_() override;
    void loadParams_() override;

protected:
    void calc_() override;

    // 0x7100144cb4: the point 100 units along FrontDirOfBaseBone from the base bone (the actor's matrix if
    // there is no such bone), in world space.
    void sub_7100144CB4(sead::Vector3f* out);

    // static_param at offset 0x20
    const int* mWeaponIdx_s{};
    // static_param at offset 0x28
    const int* mSeqBank_s{};
    // static_param at offset 0x30
    const int* mTargetBone_s{};
    // static_param at offset 0x38
    sead::SafeString mBaseBoneName_s{};
    // static_param at offset 0x48
    const sead::Vector3f* mFrontDirOfBaseBone_s{};
    // dynamic_param at offset 0x50
    ksys::act::BaseProcLink* mTargetActor_d{};
    bool _58 = false;
};

}  // namespace uking::action
