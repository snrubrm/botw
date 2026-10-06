#pragma once

#include "Game/AI/Action/actionActionEx.h"
#include "KingSystem/ActorSystem/actAiAction.h"
#include "KingSystem/System/Timer.h"

namespace ksys::phys {
class RigidBody;
class SphereRigidBody;
}

namespace uking::action {

class BombExplode : public ActionEx {
    SEAD_RTTI_OVERRIDE(BombExplode, ActionEx)
public:
    explicit BombExplode(const InitArg& arg);
    ~BombExplode() override;

    void enter_(ksys::act::ai::InlineParamPack* params) override;
    void leave_() override;
    void loadParams_() override;

protected:
    void calc_() override;
    ksys::Timer _1c{0.0f, 0.0f};
    // static_param at offset 0x28
    const int* mSizeUpTime_s{};
    // static_param at offset 0x30
    const int* mExplodeTime_s{};
    // static_param at offset 0x38
    const float* mShockPower_s{};
    // static_param at offset 0x40
    const bool* mUseDefaultEffect_s{};
    ksys::phys::SphereRigidBody* _48{};
    float _50 = 0.0f;
    float _54 = 0.0f;
    float _58 = 0.0f;
};

}  // namespace uking::action
