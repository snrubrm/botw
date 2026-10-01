#pragma once

#include "Game/AI/AI/aiEnemyNoticeTerror.h"
#include "KingSystem/ActorSystem/actAiAi.h"

namespace uking::ai {

class EnemyNoticeFearfulLastAttacker : public EnemyNoticeTerror {
    SEAD_RTTI_OVERRIDE(EnemyNoticeFearfulLastAttacker, EnemyNoticeTerror)
public:
    explicit EnemyNoticeFearfulLastAttacker(const InitArg& arg);
    ~EnemyNoticeFearfulLastAttacker() override;

    bool m34(Unk* out) override;

    bool init_(sead::Heap* heap) override;
    void enter_(ksys::act::ai::InlineParamPack* params) override;
    void calc_() override;
    void leave_() override;
    void loadParams_() override;

protected:
};

}  // namespace uking::ai
