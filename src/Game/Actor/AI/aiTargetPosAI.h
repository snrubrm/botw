#pragma once

#include "KingSystem/ActorSystem/actAiAi.h"

namespace uking::ai {

class TargetPosAI : public ksys::act::ai::Ai {
    SEAD_RTTI_OVERRIDE(TargetPosAI, ksys::act::ai::Ai)
public:
    explicit TargetPosAI(const InitArg& arg);
    ~TargetPosAI() override;

    bool isFailed() const override { return getCurrentChild()->isFailed(); }
    bool isFinished() const override { return getCurrentChild()->isFinished(); }

    bool init_(sead::Heap* heap) override;
    void enter_(ksys::act::ai::InlineParamPack* params) override;
    void calc_() override;
    void leave_() override;
    void loadParams_() override;

    virtual bool m34() const { return getCurrentChild()->isChangeable(); }
    virtual void m35(sead::Vector3f* pos) = 0;

protected:
    // static_param at offset 0x38
    const bool* mOnEnterOnly_s{};
};

}  // namespace uking::ai
