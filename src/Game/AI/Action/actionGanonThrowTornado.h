#pragma once

#include <math/seadMatrix.h>
#include "KingSystem/ActorSystem/actAiAction.h"

namespace uking::action {

class GanonThrowTornado : public ksys::act::ai::Action {
    SEAD_RTTI_OVERRIDE(GanonThrowTornado, ksys::act::ai::Action)
public:
    explicit GanonThrowTornado(const InitArg& arg);
    ~GanonThrowTornado() override;

    bool init_(sead::Heap* heap) override;
    void enter_(ksys::act::ai::InlineParamPack* params) override;
    void leave_() override;
    void loadParams_() override;
    bool isFinished() const override;

protected:
    void calc_() override;
    // 0x710017d4ac / 0x710017d550; MultiTornado passes the throw index (0 = this class's parts name / offset).
    virtual ksys::act::BaseProcLink& m32(int idx);
    virtual const sead::Vector3f* m33(int idx);
    // 0x710017cff8 (declared only, 872 B): throws tornado `idx`.
    void sub_710017CFF8(int idx);

    // static_param at offset 0x20
    const float* mInitVelocity_s{};
    // static_param at offset 0x28
    const float* mCreateHeight_s{};
    // static_param at offset 0x30
    sead::SafeString mASName_s{};
    // static_param at offset 0x40
    const sead::Vector3f* mAppearOffset_s{};
    // dynamic_param at offset 0x48
    sead::SafeString mThrowPartsName_d{};
    // dynamic_param at offset 0x58
    sead::Vector3f* mTargetPos_d{};
    // dynamic_param at offset 0x60
    ksys::act::BaseProcLink* mTargetActor_d{};
    int _68 = 0;
    sead::Matrix33f _6c;
};

}  // namespace uking::action
