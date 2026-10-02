#pragma once

#include "Game/AI/Action/actionUnk_7102451ba0.h"
#include "KingSystem/ActorSystem/actAiAction.h"

namespace uking::action {

class FallAttack : public ksys::act::ai::Action {
    SEAD_RTTI_OVERRIDE(FallAttack, ksys::act::ai::Action)
public:
    explicit FallAttack(const InitArg& arg);
    ~FallAttack() override;

    bool init_(sead::Heap* heap) override;
    void enter_(ksys::act::ai::InlineParamPack* params) override;
    void leave_() override;
    void loadParams_() override;
    bool isFinished() const override;

protected:
    void calc_() override;
    virtual int m32();
    virtual int m33();

    // static_param at offset 0x20
    const int* mWeaponIdx_s{};
    // static_param at offset 0x28
    const float* mGravity_s{};
    // static_param at offset 0x30
    const float* mJustAvoidDist_s{};
    // static_param at offset 0x38
    sead::SafeString mASName_s{};
    // static_param at offset 0x48
    sead::SafeString mAtkBodyName_s{};
    f32 _58 = -29.4f;
    Unk_7102451ba0 _60;
};

}  // namespace uking::action
