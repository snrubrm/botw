#pragma once

#include <math/seadMatrix.h>
#include "Game/AI/Action/actionUnk_71023c8600.h"
#include "Game/AI/Action/actionUnk_71023c8700.h"
#include "KingSystem/ActorSystem/actAiAction.h"

namespace uking::action {

class IgniteGrabAndShoot : public ksys::act::ai::Action {
    SEAD_RTTI_OVERRIDE(IgniteGrabAndShoot, ksys::act::ai::Action)
public:
    explicit IgniteGrabAndShoot(const InitArg& arg);
    ~IgniteGrabAndShoot() override;

    bool init_(sead::Heap* heap) override;
    void enter_(ksys::act::ai::InlineParamPack* params) override;
    void leave_() override;
    void loadParams_() override;

protected:
    void calc_() override;

    // static_param at offset 0x20
    const float* mRotSpd_s{};
    Unk_71023c8700 _28{this};
    Unk_71023c8600 _60{this};
    /// 0: grabbing (_60), 1: shooting (_28).
    int _a0 = 0;
    sead::Matrix33f _a4;
};

}  // namespace uking::action
