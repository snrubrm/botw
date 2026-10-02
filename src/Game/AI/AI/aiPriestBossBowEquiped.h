#pragma once

#include <prim/seadSafeString.h>
#include "Game/AI/AI/aiBowEquiped.h"
#include "KingSystem/ActorSystem/actAiAi.h"

namespace uking::ai {

class PriestBossBowEquiped : public BowEquiped {
    SEAD_RTTI_OVERRIDE(PriestBossBowEquiped, BowEquiped)
public:
    explicit PriestBossBowEquiped(const InitArg& arg);
    ~PriestBossBowEquiped() override;

    bool init_(sead::Heap* heap) override;
    void enter_(ksys::act::ai::InlineParamPack* params) override;
    void calc_() override;
    void leave_() override;
    void loadParams_() override;

protected:
    sead::FixedSafeString<32> _60;
};
KSYS_CHECK_SIZE_NX150(PriestBossBowEquiped, 0x98);

}  // namespace uking::ai
