#pragma once

#include "KingSystem/ActorSystem/actAiAi.h"

namespace uking::ai {

class PlayerCaught : public ksys::act::ai::Ai {
    SEAD_RTTI_OVERRIDE(PlayerCaught, ksys::act::ai::Ai)
public:
    explicit PlayerCaught(const InitArg& arg);

    bool isFinished() const override;
    bool isChangeable() const override;
    bool init_(sead::Heap* heap) override;
    void enter_(ksys::act::ai::InlineParamPack* params) override;
    void calc_() override;
    void leave_() override;

protected:
};

}  // namespace uking::ai
