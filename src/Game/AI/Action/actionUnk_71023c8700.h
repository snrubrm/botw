#pragma once

#include <math/seadVector.h>
#include "Game/AI/Action/actionUnk_71025afc58.h"

// Shoot helper (vtable 0x71023c8700; no out-of-line ctor) embedded in IgniteGrabAndShoot: once the
// AS allows it, throws the owner's connected calc child towards TargetPos (with a random blur of up
// to BlurMax per axis) using ShootAng / ShootSpd.
class Unk_71023c8700 : public Unk_71025afc58 {
    SEAD_RTTI_OVERRIDE(Unk_71023c8700, Unk_71025afc58)
public:
    explicit Unk_71023c8700(ksys::act::ai::ActionBase* owner) : Unk_71025afc58(owner) {}

    void enter_(ksys::act::ai::InlineParamPack* params) override;
    void calc_() override;
    void leave_() override {}
    void loadParams_() override;

    const float* mShootSpd_s{};
    const float* mShootAng_s{};
    const sead::Vector3f* mBlurMax_s{};
    sead::Vector3f* mTargetPos_d{};
};
KSYS_CHECK_SIZE_NX150(Unk_71023c8700, 0x38);
