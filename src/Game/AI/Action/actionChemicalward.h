#pragma once

#include "Game/AI/Action/actionActionWithPosAngReduce.h"
#include "KingSystem/ActorSystem/actAiAction.h"
#include "KingSystem/ActorSystem/actBoneHandle.h"

namespace uking::action {

class Chemicalward : public ActionWithPosAngReduce {
    SEAD_RTTI_OVERRIDE(Chemicalward, ActionWithPosAngReduce)
public:
    explicit Chemicalward(const InitArg& arg);
    ~Chemicalward() override;

    bool init_(sead::Heap* heap) override;
    void enter_(ksys::act::ai::InlineParamPack* params) override;
    void leave_() override;
    void loadParams_() override;
    bool isChangeable() const override;

protected:
    void calc_() override;

    // static_param at offset 0x30
    const int* mWeaponIdx_s{};
    // static_param at offset 0x38
    const int* mNodeAxisIdx_s{};
    // static_param at offset 0x40
    const int* mStableTime_s{};
    // static_param at offset 0x48
    const int* mKeepTime_s{};
    // static_param at offset 0x50
    const int* mTiredTime_s{};
    // static_param at offset 0x58
    const float* mTiredRadius_s{};
    // static_param at offset 0x60
    const float* mTiredAngle_s{};
    // static_param at offset 0x68
    const float* mVoltage_s{};
    // static_param at offset 0x70
    sead::SafeString mNodeName_s{};
    // dynamic_param at offset 0x80
    sead::Vector3f* mTargetPos_d{};
    // dynamic_param at offset 0x88
    ksys::act::BaseProcLink* mTargetActor_d{};
    ksys::act::BoneHandle _90;
    gsys::BoneAccessKey _138;
    sead::Matrix34f _13c;
    s32 _16c = -1;
    f32 _170 = 0.0f;
    f32 _174 = 0.0f;
    f32 _178 = 0.0f;
    s32 _17c = 0;
};
KSYS_CHECK_SIZE_NX150(Chemicalward, 0x180);

}  // namespace uking::action
