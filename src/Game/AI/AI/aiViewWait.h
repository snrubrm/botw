#pragma once

#include "KingSystem/ActorSystem/actAiAi.h"
#include "KingSystem/System/Timer.h"

namespace uking::ai {

class ViewWait : public ksys::act::ai::Ai {
    SEAD_RTTI_OVERRIDE(ViewWait, ksys::act::ai::Ai)
public:
    explicit ViewWait(const InitArg& arg);
    ~ViewWait() override;

    void enter_(ksys::act::ai::InlineParamPack* params) override;
    void calc_() override;
    void loadParams_() override;

    bool isFinished() const override;
    bool isChangeable() const override { return getCurrentChild()->isChangeable(); }

    virtual const sead::Vector3f& m34() { return *mTargetPos_d; }
    virtual bool m35();
    virtual void m36();
    virtual void m37();
    virtual bool m38();
    virtual void m39(ksys::act::ai::InlineParamPack* params) {}

protected:
    // static_param at offset 0x38
    const float* mTurnStartAngle_s{};
    // static_param at offset 0x40
    const bool* mCheckOnce_s{};
    // dynamic_param at offset 0x48
    sead::Vector3f* mTargetPos_d{};
    ksys::Timer mTimer;
    bool _5c{};
};

}  // namespace uking::ai
