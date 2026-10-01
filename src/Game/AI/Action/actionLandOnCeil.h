#pragma once

#include "KingSystem/ActorSystem/actAiAction.h"

namespace uking::action {

class LandOnCeil : public ksys::act::ai::Action {
    SEAD_RTTI_OVERRIDE(LandOnCeil, ksys::act::ai::Action)
public:
    explicit LandOnCeil(const InitArg& arg);
    ~LandOnCeil() override;

    bool init_(sead::Heap* heap) override;
    void enter_(ksys::act::ai::InlineParamPack* params) override;
    void leave_() override;
    void loadParams_() override;

protected:
    void calc_() override;

    // static_param at offset 0x20
    const float* mRotRatio_s{};
    // static_param at offset 0x28
    const float* mGravityScale_s{};
    // map_unit_param at offset 0x30
    const bool* mIsCreateOnFace_m{};
    u8 _38[0x8c - 0x38];
    int _8c = 0;
    float _90 = 1.0f;
};

}  // namespace uking::action
