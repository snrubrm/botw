#pragma once

#include "Game/AI/aiUnkDamageCallbacks.h"
#include "KingSystem/ActorSystem/actAiAi.h"

namespace uking::ai {

class PillarCrack : public ksys::act::ai::Ai {
    SEAD_RTTI_OVERRIDE(PillarCrack, ksys::act::ai::Ai)
public:
    explicit PillarCrack(const InitArg& arg);
    ~PillarCrack() override;

    bool init_(sead::Heap* heap) override;
    void enter_(ksys::act::ai::InlineParamPack* params) override;
    void calc_() override;
    void leave_() override;
    void loadParams_() override;

protected:
    Unk_7102451d08 _38;
};
KSYS_CHECK_SIZE_NX150(PillarCrack, 0x70);

}  // namespace uking::ai
