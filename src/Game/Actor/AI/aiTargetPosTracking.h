#pragma once

#include <math/seadVector.h>
#include "KingSystem/ActorSystem/actAiAi.h"

namespace uking::ai {

class TargetPosTracking : public ksys::act::ai::Ai {
    SEAD_RTTI_OVERRIDE(TargetPosTracking, ksys::act::ai::Ai)
public:
    explicit TargetPosTracking(const InitArg& arg);
    ~TargetPosTracking() override;

    bool isFailed() const override;
    bool isFinished() const override { return getCurrentChild()->isFinished(); }

    bool init_(sead::Heap* heap) override;
    void enter_(ksys::act::ai::InlineParamPack* params) override;
    void calc_() override;
    void leave_() override;
    void loadParams_() override;

    virtual void m34();

protected:
    struct Params {
        // static_param at offset 0x38
        const float* mTrackSpeed_s{};
        // static_param at offset 0x40
        const bool* mIsStoppedByJustAvoid_s{};
        // dynamic_param at offset 0x48
        sead::Vector3f* mTargetPos_d{};
    };
    Params mParams;
    sead::Vector3f _50;
    bool _5c = false;
};
KSYS_CHECK_SIZE_NX150(TargetPosTracking, 0x60);

}  // namespace uking::ai
