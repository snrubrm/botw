#pragma once

#include <math/seadMatrix.h>
#include "KingSystem/ActorSystem/actAiAction.h"

namespace uking::action {

class AirOctaReactionKorog : public ksys::act::ai::Action {
    SEAD_RTTI_OVERRIDE(AirOctaReactionKorog, ksys::act::ai::Action)
public:
    explicit AirOctaReactionKorog(const InitArg& arg);
    ~AirOctaReactionKorog() override;

    bool init_(sead::Heap* heap) override;
    void enter_(ksys::act::ai::InlineParamPack* params) override;
    void leave_() override;
    void loadParams_() override;

protected:
    void calc_() override;

    // static_param at offset 0x20
    const int* mEndState_s{};
    // static_param at offset 0x28
    const float* mSpeed_s{};
    // static_param at offset 0x30
    sead::SafeString mAS_s{};
    sead::Vector3f _40 = sead::Vector3f::zero;
    sead::Matrix33f _4c;

};
KSYS_CHECK_SIZE_NX150(AirOctaReactionKorog, 0x70);

}  // namespace uking::action
