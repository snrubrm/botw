#pragma once

#include "KingSystem/ActorSystem/actAiAi.h"

namespace uking::ai {

class LastBossDemoWarpMove : public ksys::act::ai::Ai {
    SEAD_RTTI_OVERRIDE(LastBossDemoWarpMove, ksys::act::ai::Ai)
public:
    explicit LastBossDemoWarpMove(const InitArg& arg);
    ~LastBossDemoWarpMove() override;

    bool init_(sead::Heap* heap) override;
    void enter_(ksys::act::ai::InlineParamPack* params) override;
    void leave_() override;
    void loadParams_() override;
    void calc_() override;
    virtual void m34();
    virtual void m35();

protected:
};

}  // namespace uking::ai
