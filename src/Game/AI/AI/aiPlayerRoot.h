#pragma once

#include "KingSystem/ActorSystem/actAiAi.h"

namespace uking::ai {

class PlayerRoot : public ksys::act::ai::Ai {
    SEAD_RTTI_OVERRIDE(PlayerRoot, ksys::act::ai::Ai)
public:
    explicit PlayerRoot(const InitArg& arg);

    bool isChangeable() const override { return false; }

    void enter_(ksys::act::ai::InlineParamPack* params) override;
    void calc_() override;

protected:
};

}  // namespace uking::ai
