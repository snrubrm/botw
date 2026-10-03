#pragma once

#include <math/seadMatrix.h>
#include "Game/AI/aiUnk_710073EBD4.h"
#include "KingSystem/ActorSystem/actAiAction.h"

namespace uking::action {

class PredictVacuumShoot : public ksys::act::ai::Action {
    SEAD_RTTI_OVERRIDE(PredictVacuumShoot, ksys::act::ai::Action)
public:
    explicit PredictVacuumShoot(const InitArg& arg);
    ~PredictVacuumShoot() override;

    bool init_(sead::Heap* heap) override;
    void enter_(ksys::act::ai::InlineParamPack* params) override;
    void leave_() override;
    void loadParams_() override;

protected:
    void calc_() override;
    virtual void m32();
    virtual void m33(const sead::Vector3f* a1) { _78.sub_710073F14C(a1); }

    // static_param at offset 0x20
    const float* mPosReduceRatio_s{};
    // static_param at offset 0x28
    const float* mAngReduceRatio_s{};
    // static_param at offset 0x30
    const float* mRotSpd_s{};
    // static_param at offset 0x38
    const bool* mIsReuseBullet_s{};
    // static_param at offset 0x40
    sead::SafeString mASName_s{};
    /* 0x50 */ sead::Matrix33f _50;
    /* 0x78 */ Unk_710073ebd4 _78{mActor};
    /* 0x120 */ bool _120 = false;
    bool _121 = false;
    /* 0x124 */ sead::Vector3f _124;
};

}  // namespace uking::action
