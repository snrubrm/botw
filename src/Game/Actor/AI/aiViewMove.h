#pragma once

#include "KingSystem/ActorSystem/actAiAi.h"
#include "KingSystem/System/Timer.h"

namespace uking::ai {

class ViewMove : public ksys::act::ai::Ai {
    SEAD_RTTI_OVERRIDE(ViewMove, ksys::act::ai::Ai)
public:
    explicit ViewMove(const InitArg& arg);
    ~ViewMove() override;

    bool isFinished() const override;

    bool isFailed() const override;

    bool init_(sead::Heap* heap) override;
    void enter_(ksys::act::ai::InlineParamPack* params) override;
    void calc_() override;
    void leave_() override;
    void loadParams_() override;

    virtual const sead::Vector3f& m34();
    virtual void m35();
    virtual void m36();
    virtual bool m37();

protected:
    // static_param at offset 0x38
    const float* mTurnStartAngle_s{};
    // static_param at offset 0x40
    const bool* mCheckOnce_s{};
    // dynamic_param at offset 0x48
    sead::Vector3f* mTargetPos_d{};
    ksys::Timer _50{};
    bool _5c = false;
};
KSYS_CHECK_SIZE_NX150(ViewMove, 0x60);

}  // namespace uking::ai
