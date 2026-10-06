#pragma once

#include <math/seadMatrix.h>
#include <math/seadVector.h>
#include "KingSystem/ActorSystem/actAiAction.h"
#include "KingSystem/System/Timer.h"

namespace uking::action {

class BeeDamaged : public ksys::act::ai::Action {
    SEAD_RTTI_OVERRIDE(BeeDamaged, ksys::act::ai::Action)
public:
    explicit BeeDamaged(const InitArg& arg);
    ~BeeDamaged() override;

    bool init_(sead::Heap* heap) override;
    void enter_(ksys::act::ai::InlineParamPack* params) override;
    void leave_() override;
    void loadParams_() override;

protected:
    void calc_() override;

    struct Params {
        // static_param at offset 0x20
        const int* mTime_s{};
        // static_param at offset 0x28
        const float* mSubActorSpeed_s{};
        // static_param at offset 0x30
        const float* mAddYSpeed_s{};
    };
    Params mParams;
    sead::Matrix33f _38;
    ksys::Timer mTimer;
    sead::Vector3f mTargetPos;
    u8 _74[4];
};
KSYS_CHECK_SIZE_NX150(BeeDamaged, 0x78);

}  // namespace uking::action
