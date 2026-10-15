#pragma once

#include "KingSystem/ActorSystem/actAiAction.h"
#include <math/seadMatrix.h>

namespace ksys::phys {
class CharacterController;
}

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
    bool isFinished() const override;

protected:
    void calc_() override;

    void sub_71001CD210(ksys::act::Actor* actor, ksys::phys::CharacterController* controller);

    // static_param at offset 0x20
    const float* mRotRatio_s{};
    // static_param at offset 0x28
    const float* mGravityScale_s{};
    // map_unit_param at offset 0x30
    const bool* mIsCreateOnFace_m{};
    sead::Vector3f _38;
    sead::Vector3f _44;
    sead::Vector3f _50;
    sead::Matrix33f _5c;
    sead::Vector3f _80;
    int _8c = 0;
    float _90 = 1.0f;
};

}  // namespace uking::action
