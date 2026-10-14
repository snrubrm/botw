#pragma once

#include <math/seadVector.h>
#include "KingSystem/ActorSystem/actAiAi.h"

namespace uking::ai {

class EscapeFromTargetFront : public ksys::act::ai::Ai {
    SEAD_RTTI_OVERRIDE(EscapeFromTargetFront, ksys::act::ai::Ai)
public:
    explicit EscapeFromTargetFront(const InitArg& arg);
    ~EscapeFromTargetFront() override;

    bool init_(sead::Heap* heap) override;
    void enter_(ksys::act::ai::InlineParamPack* params) override;
    void calc_() override;
    void leave_() override;
    void loadParams_() override;

    virtual int m34();

    void sub_71003C8338(sead::Vector3f* front);

protected:
    // static_param at offset 0x38
    const int* mMaxTime_s{};
    // static_param at offset 0x40
    const int* mMinTime_s{};
    // static_param at offset 0x48
    const float* mFrontAngle_s{};
    // static_param at offset 0x50
    const bool* mUseCameraFrontByTargetPlayer_s{};
    f32 _58{};
};

}  // namespace uking::ai
