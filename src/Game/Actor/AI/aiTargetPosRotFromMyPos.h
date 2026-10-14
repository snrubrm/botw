#pragma once

#include "Game/Actor/AI/aiTargetActorPos.h"
#include "KingSystem/ActorSystem/actAiAi.h"

namespace uking::ai {

class TargetPosRotFromMyPos : public TargetActorPos {
    SEAD_RTTI_OVERRIDE(TargetPosRotFromMyPos, TargetActorPos)
public:
    explicit TargetPosRotFromMyPos(const InitArg& arg);
    ~TargetPosRotFromMyPos() override;

    bool init_(sead::Heap* heap) override;
    void enter_(ksys::act::ai::InlineParamPack* params) override;
    void calc_() override;
    void leave_() override;
    void loadParams_() override;

    void m35(sead::Vector3f* pos) override;

protected:
    struct Params {
        // static_param at offset 0x40
        const float* mMinDist_s{};
        // static_param at offset 0x48
        const bool* mIsRandSign_s{};
        // static_param at offset 0x50
        const sead::Vector3f* mAngle_s{};
        // dynamic_param at offset 0x58
        sead::Vector3f* mTargetPos_d{};
    };
    Params mParams;
    sead::Vector3f mAngle{0, 0, 0};
};

}  // namespace uking::ai
