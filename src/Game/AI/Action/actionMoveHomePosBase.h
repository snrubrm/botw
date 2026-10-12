#pragma once

#include "KingSystem/ActorSystem/actAiAction.h"
#include <math/seadVector.h>

namespace ksys::phys {
class RigidBody;
}

namespace uking::action {

class MoveHomePosBase : public ksys::act::ai::Action {
    SEAD_RTTI_OVERRIDE(MoveHomePosBase, ksys::act::ai::Action)
public:
    explicit MoveHomePosBase(const InitArg& arg);
    ~MoveHomePosBase() override;

    bool init_(sead::Heap* heap) override;
    void enter_(ksys::act::ai::InlineParamPack* params) override;
    void leave_() override;
    void loadParams_() override;

protected:
    void calc_() override;
    virtual ksys::phys::RigidBody* m32();

    // static_param at offset 0x20
    const bool* mIsReturn_s{};
    // dynamic_param at offset 0x28
    float* mDynMoveDis_d{};
    // dynamic_param at offset 0x30
    float* mDynMoveSpeed_d{};
    sead::Vector3f _38 = sead::Vector3f::zero;
    sead::Vector3f _44 = sead::Vector3f::zero;
};

KSYS_CHECK_SIZE_NX150(MoveHomePosBase, 0x50);

}  // namespace uking::action
