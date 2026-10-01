#pragma once

#include "Game/AI/AI/aiHorseRideChaseBattleMoveBase.h"
#include "Game/AI/aiUnk_7102357d20.h"
#include "KingSystem/ActorSystem/actAiAi.h"

namespace uking::ai {

class HorseRideChaseBattleAttackMove : public HorseRideChaseBattleMoveBase {
    SEAD_RTTI_OVERRIDE(HorseRideChaseBattleAttackMove, HorseRideChaseBattleMoveBase)
public:
    explicit HorseRideChaseBattleAttackMove(const InitArg& arg);
    ~HorseRideChaseBattleAttackMove() override;

    bool init_(sead::Heap* heap) override;
    void enter_(ksys::act::ai::InlineParamPack* params) override;
    void leave_() override;
    void loadParams_() override;
    void calc_() override;

    void m34(int gear) override;
    void m35() override;
    bool m36() override;

protected:
    Unk_710239c018 _90{mActor, 0x380000b};
    Unk_710239c040 _b0{mActor, 0x380000c};
};

}  // namespace uking::ai
