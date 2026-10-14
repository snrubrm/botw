#pragma once

#include "KingSystem/ActorSystem/actAiAction.h"
#include "KingSystem/System/Timer.h"

namespace ksys::act {
class AttackSensor;
}

namespace ksys::phys {
class SphereRigidBody;
}

namespace uking::action {

class Explode : public ksys::act::ai::Action {
    SEAD_RTTI_OVERRIDE(Explode, ksys::act::ai::Action)
public:
    explicit Explode(const InitArg& arg);
    ~Explode() override;

    bool init_(sead::Heap* heap) override;
    void enter_(ksys::act::ai::InlineParamPack* params) override;
    void leave_() override;
    void loadParams_() override;

protected:
    void calc_() override;

    virtual ksys::phys::SphereRigidBody* m32();
    virtual void m33();
    virtual void m34(ksys::act::AttackSensor* sensor);

    u32 sub_710012B058();

    // static_param at offset 0x20
    const int* mSizeUpTime_s{};
    // static_param at offset 0x28
    const int* mExplodeTime_s{};
    // static_param at offset 0x30
    const int* mAttackIntensity_s{};
    // static_param at offset 0x38
    const bool* mUseDefaultEffect_s{};
    // static_param at offset 0x40
    const bool* mIsDelete_s{};
    // static_param at offset 0x48
    const bool* mIsDamageGuarantee_s{};
    // static_param at offset 0x50
    const bool* mIsVanish_s{};
    ksys::phys::SphereRigidBody* _58{};
    ksys::act::AttackSensor* _60{};
    ksys::Timer _68{0, 0};
    f32 _74 = 0;
    f32 _78 = 0;
    f32 _7c = 0;
};

KSYS_CHECK_SIZE_NX150(Explode, 0x80);

}  // namespace uking::action
