#pragma once

#include "KingSystem/ActorSystem/actAiAi.h"

namespace uking::ai {

class CapturedActorReaction : public ksys::act::ai::Ai {
    SEAD_RTTI_OVERRIDE(CapturedActorReaction, ksys::act::ai::Ai)
public:
    explicit CapturedActorReaction(const InitArg& arg);
    ~CapturedActorReaction() override;

    bool init_(sead::Heap* heap) override;
    void enter_(ksys::act::ai::InlineParamPack* params) override;
    void calc_() override;
    void leave_() override;
    void loadParams_() override;

protected:
    bool _38{};
};

}  // namespace uking::ai
