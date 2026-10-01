#pragma once

#include "KingSystem/ActorSystem/actAiAction.h"
#include <math/seadVector.h>

namespace uking::action {

class BeamMove : public ksys::act::ai::Action {
    SEAD_RTTI_OVERRIDE(BeamMove, ksys::act::ai::Action)
public:
    explicit BeamMove(const InitArg& arg);
    ~BeamMove() override;

    bool init_(sead::Heap* heap) override;
    void enter_(ksys::act::ai::InlineParamPack* params) override;
    void leave_() override;
    void loadParams_() override;

protected:
    void calc_() override;

    // static_param at offset 0x20
    const int* mAtMinDamage_s{};
    // static_param at offset 0x28
    const int* mShieldDamage_s{};
    // static_param at offset 0x30
    const float* mForceExplodeFrame_s{};
    // aitree_variable at offset 0x38
    bool* mIsReflectThrownBullet_a{};
    sead::Vector3f _40 = sead::Vector3f::ez;
    f32 _4c = 0;
    void* _50 = nullptr;
    void* _58 = nullptr;
    void* _60 = nullptr;
    u8 _68 = 0;
    u8 _69 = 0;
    bool _6a = false;
    bool _6b = false;
    u32 _6c = 0;
};

KSYS_CHECK_SIZE_NX150(BeamMove, 0x70);

}  // namespace uking::action
