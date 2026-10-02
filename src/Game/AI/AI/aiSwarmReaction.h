#pragma once

#include "KingSystem/ActorSystem/actAiAi.h"

namespace uking::ai {

class SwarmReaction : public ksys::act::ai::Ai {
    SEAD_RTTI_OVERRIDE(SwarmReaction, ksys::act::ai::Ai)
public:
    explicit SwarmReaction(const InitArg& arg);
    ~SwarmReaction() override;

    bool init_(sead::Heap* heap) override;
    void enter_(ksys::act::ai::InlineParamPack* params) override;
    void leave_() override;
    void loadParams_() override;

    virtual bool m34();
    virtual void m35();
    virtual void m36();

protected:
    bool _38 = false;
};

}  // namespace uking::ai
