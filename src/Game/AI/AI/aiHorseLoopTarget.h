#pragma once

#include "KingSystem/ActorSystem/actAiAi.h"

namespace ksys::map {
class Rail;
}

namespace uking::ai {

class HorseLoopTarget : public ksys::act::ai::Ai {
    SEAD_RTTI_OVERRIDE(HorseLoopTarget, ksys::act::ai::Ai)
public:
    explicit HorseLoopTarget(const InitArg& arg);
    ~HorseLoopTarget() override;

    void enter_(ksys::act::ai::InlineParamPack* params) override;
    void calc_() override;
    void loadParams_() override;

    virtual ksys::map::Rail* m34();

protected:
    // static_param at offset 0x38
    sead::SafeString mTargetName_s{};
    // static_param at offset 0x48
    const bool* mIsFlip_s{};
};

}  // namespace uking::ai
