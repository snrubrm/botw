#pragma once

#include "KingSystem/System/VFRValue.h"
#include "KingSystem/ActorSystem/actAiAction.h"

namespace uking::action {

class GrabAndShoot : public ksys::act::ai::Action {
    SEAD_RTTI_OVERRIDE(GrabAndShoot, ksys::act::ai::Action)
public:
    explicit GrabAndShoot(const InitArg& arg);
    ~GrabAndShoot() override;

    void enter_(ksys::act::ai::InlineParamPack* params) override;
    void leave_() override;
    void loadParams_() override;
    bool isChangeable() const override;

protected:
    void calc_() override;

    struct Params {
        // static_param at offset 0x20
        const int* mGrabIdx_s{};
        // static_param at offset 0x28
        const float* mRotSpd_s{};
        // static_param at offset 0x30
        const float* mShootSpeed_s{};
        // static_param at offset 0x38
        const float* mShootAng_s{};
        // static_param at offset 0x40
        const sead::Vector3f* mBlurMax_s{};
        // dynamic_param at offset 0x48
        sead::Vector3f* mTargetPos_d{};
    };
    Params mParams;
    u8 _50[0x24];
    ksys::VFRValue _74;
    s32 _80 = -1;
    u8 _84[0x4];
};
KSYS_CHECK_SIZE_NX150(GrabAndShoot, 0x88);

}  // namespace uking::action
