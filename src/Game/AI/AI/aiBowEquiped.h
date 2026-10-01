#pragma once

#include "KingSystem/ActorSystem/actAiAi.h"
#include "KingSystem/ActorSystem/actBaseProcHandle.h"
#include "KingSystem/ActorSystem/actBaseProcLink.h"

namespace uking::ai {

class BowEquiped : public ksys::act::ai::Ai {
    SEAD_RTTI_OVERRIDE(BowEquiped, ksys::act::ai::Ai)
public:
    explicit BowEquiped(const InitArg& arg);
    ~BowEquiped() override;
    bool isChangeable() const override;

    void enter_(ksys::act::ai::InlineParamPack* params) override;
    void leave_() override;

protected:
    ksys::act::BaseProcHandle _38;
    bool _48{};
    bool _49{};
    ksys::act::BaseProcLink _50;
};

}  // namespace uking::ai
