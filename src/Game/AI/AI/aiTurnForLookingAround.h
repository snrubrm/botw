#pragma once

#include <math/seadVector.h>
#include "KingSystem/ActorSystem/actAiAi.h"

namespace uking::ai {

class TurnForLookingAround : public ksys::act::ai::Ai {
    SEAD_RTTI_OVERRIDE(TurnForLookingAround, ksys::act::ai::Ai)
public:
    explicit TurnForLookingAround(const InitArg& arg);
    ~TurnForLookingAround() override;

    bool init_(sead::Heap* heap) override;
    void enter_(ksys::act::ai::InlineParamPack* params) override;
    void calc_() override;
    void leave_() override;
    void loadParams_() override;

protected:
    // static_param at offset 0x38
    const float* mAngle_s{};
    int _40 = 0;
    sead::Vector3f _44;

private:
    void sub_71005D2384();
    void sub_71005D26A8();
    void sub_71005D27A8();
    void sub_71005D28DC();
};

}  // namespace uking::ai
