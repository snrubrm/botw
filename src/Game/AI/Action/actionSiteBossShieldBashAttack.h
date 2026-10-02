#pragma once
#include "KingSystem/System/VFRValue.h"
#include <math/seadMatrix.h>

#include "KingSystem/ActorSystem/actAiAction.h"

namespace ksys::phys {
class RigidBody;
}

namespace uking::action {

class SiteBossShieldBashAttack : public ksys::act::ai::Action {
    SEAD_RTTI_OVERRIDE(SiteBossShieldBashAttack, ksys::act::ai::Action)
public:
    explicit SiteBossShieldBashAttack(const InitArg& arg);
    ~SiteBossShieldBashAttack() override;

    bool init_(sead::Heap* heap) override;
    void enter_(ksys::act::ai::InlineParamPack* params) override;
    void leave_() override;
    void loadParams_() override;

protected:
    void calc_() override;
    bool isChangeable() const override;
    virtual void m32();
    virtual void m33();
    virtual void m34();
    virtual void m35();

    // static_param at offset 0x20
    const int* mAtMinDamage_s{};
    // static_param at offset 0x28
    const float* mInitSpeed_s{};
    // static_param at offset 0x30
    const float* mKeepDist_s{};
    // static_param at offset 0x38
    const float* mMoveSpeed_s{};
    // dynamic_param at offset 0x40
    sead::Vector3f* mTargetPos_d{};
    ksys::phys::RigidBody* _48{};
    ksys::VFRValue _50;
    sead::Matrix33f _5c;
    bool _80 = false;
    bool _81 = false;
};

}  // namespace uking::action
