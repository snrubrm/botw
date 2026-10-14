#pragma once

#include <math/seadMatrix.h>
#include <math/seadVector.h>
#include "KingSystem/ActorSystem/actAiAction.h"
#include "KingSystem/System/Timer.h"

namespace ksys::phys {
class CharacterController;
}

namespace uking::action {

class ForkFollowGround : public ksys::act::ai::Action {
    SEAD_RTTI_OVERRIDE(ForkFollowGround, ksys::act::ai::Action)
public:
    explicit ForkFollowGround(const InitArg& arg);
    ~ForkFollowGround() override;

    bool init_(sead::Heap* heap) override;
    void enter_(ksys::act::ai::InlineParamPack* params) override;
    void leave_() override;
    void loadParams_() override;

protected:
    void calc_() override;
    virtual void m32(ksys::phys::CharacterController* controller);
    virtual void m33(ksys::phys::CharacterController* controller);

    struct Params {
        // static_param at offset 0x20
        const int* mUpdateFrameCountAfterNoMove_s{};
        // static_param at offset 0x28
        const float* mRotSpd_s{};
        // static_param at offset 0x30
        const float* mBaseRotRatio_s{};
        // static_param at offset 0x38
        const float* mUpdateTargetUpDirMinAngle_s{};
        // static_param at offset 0x40
        const float* mUpdateTargetUpDirRatio_s{};
    };
    Params mParams;
    sead::Vector3f _48;
    sead::Vector3f _54;
    ksys::Timer _60;
    sead::Matrix33f _6c;
    f32 _90 = 0.0f;
    u8 _94[0x4];
};
KSYS_CHECK_SIZE_NX150(ForkFollowGround, 0x98);

}  // namespace uking::action
