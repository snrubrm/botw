#pragma once

#include "KingSystem/ActorSystem/actAiAction.h"

namespace uking::action {

class SwimEnemyAnmBackBlownOffBase : public ksys::act::ai::Action {
    SEAD_RTTI_OVERRIDE(SwimEnemyAnmBackBlownOffBase, ksys::act::ai::Action)
public:
    explicit SwimEnemyAnmBackBlownOffBase(const InitArg& arg);
    ~SwimEnemyAnmBackBlownOffBase() override;

    bool init_(sead::Heap* heap) override;
    // NON_MATCHING: matches (as the in-class definition emitted for the derived class's vtable, where
    // the two helpers are not inlined) only if actionSwimEnemyAnmBackBlownOff.cpp is linked before
    // actionSwimEnemyAnmBackBlownOffBase.cpp (CMake source order); the Base TU's inlined copy wins now.
    bool isFinished() const override {
        if (_68)
            return false;
        return sub_7100289410() || sub_7100289460();
    }
    void enter_(ksys::act::ai::InlineParamPack* params) override;
    void leave_() override;
    void loadParams_() override;

protected:
    void calc_() override;
    bool sub_7100289410() const;
    bool sub_7100289460() const;
    virtual void m32(sead::Vector3f* out);
    virtual void m33();

    // static_param at offset 0x20
    const float* mSpeed_s{};
    // static_param at offset 0x28
    const float* mBlownHeight_s{};
    // static_param at offset 0x30
    const float* mPosReduceRatio_s{};
    // static_param at offset 0x38
    const float* mRotReduceRatio_s{};
    // static_param at offset 0x40
    const float* mInWaterDepth_s{};
    // static_param at offset 0x48
    const float* mFloatDepth_s{};
    // static_param at offset 0x50
    const bool* mUseKnockbackDir_s{};
    // static_param at offset 0x58
    sead::SafeString mAS_s{};
    bool _68 = true;
};

KSYS_CHECK_SIZE_NX150(SwimEnemyAnmBackBlownOffBase, 0x70);

}  // namespace uking::action
