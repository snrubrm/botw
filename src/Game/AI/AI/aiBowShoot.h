#pragma once

#include "KingSystem/ActorSystem/actAiAi.h"

namespace uking::ai {

class BowShoot : public ksys::act::ai::Ai {
    SEAD_RTTI_OVERRIDE(BowShoot, ksys::act::ai::Ai)
public:
    explicit BowShoot(const InitArg& arg);
    ~BowShoot() override;
    bool isChangeable() const override;

    void enter_(ksys::act::ai::InlineParamPack* params) override;
    void leave_() override;

protected:
};

}  // namespace uking::ai
