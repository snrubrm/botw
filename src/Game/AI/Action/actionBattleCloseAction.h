#pragma once
#include "KingSystem/System/Timer.h"
#include <math/seadMatrix.h>

#include <math/seadVector.h>
#include "KingSystem/ActorSystem/actAiAction.h"

namespace ksys::act {
class Unk_71024dc858;
}

namespace ksys::phys {
class CharacterController;
}

namespace uking::action {

class BattleCloseAction : public ksys::act::ai::Action {
    SEAD_RTTI_OVERRIDE(BattleCloseAction, ksys::act::ai::Action)
public:
    explicit BattleCloseAction(const InitArg& arg);
    ~BattleCloseAction() override;

    bool init_(sead::Heap* heap) override;
    void enter_(ksys::act::ai::InlineParamPack* params) override;
    void leave_() override;
    void loadParams_() override;

protected:
    void calc_() override;

    virtual void m32(sead::Vector3f* target_pos);
    virtual ksys::act::Unk_71024dc858* m33(int idx);
    virtual bool m34(ksys::act::Unk_71024dc858* entry);
    virtual f32 m35();
    virtual void m36(const sead::Matrix34f& mtx);
    virtual bool m37(ksys::phys::CharacterController* controller, f32 speed,
                     const sead::Vector3f& dir);
    virtual int m38(f32 x);
    virtual bool m39();

    // static_param at offset 0x20
    const int* mWeaponIdx_s{};
    // static_param at offset 0x28
    const float* mSpeed_s{};
    // static_param at offset 0x30
    const float* mRotSpd_s{};
    // static_param at offset 0x38
    const float* mFinRadius_s{};
    // static_param at offset 0x40
    const float* mFinRotate_s{};
    // static_param at offset 0x48
    const float* mBaseRotRatio_s{};
    // dynamic_param at offset 0x50
    sead::Vector3f* mTargetPos_d{};
    sead::Vector3f _58;
    sead::Matrix33f _64;
    float _88 = 0.0f;
    ksys::Timer _8c{0, 0};
};

}  // namespace uking::action
