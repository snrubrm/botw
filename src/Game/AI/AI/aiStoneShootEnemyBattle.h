#pragma once

#include "Game/AI/AI/aiEnemyBattle.h"
#include "KingSystem/ActorSystem/actAiAi.h"
#include "KingSystem/ActorSystem/actBaseProcHandle.h"

namespace uking::ai {

class StoneShootEnemyBattle : public EnemyBattle {
    SEAD_RTTI_OVERRIDE(StoneShootEnemyBattle, EnemyBattle)
public:
    explicit StoneShootEnemyBattle(const InitArg& arg);
    ~StoneShootEnemyBattle() override;

    bool init_(sead::Heap* heap) override;
    void enter_(ksys::act::ai::InlineParamPack* params) override;
    void calc_() override;
    void leave_() override;
    void loadParams_() override;

    bool m41() override;
    void m43(ksys::act::ai::InlineParamPack* params) override;
    virtual void m44(ksys::act::BaseProcHandle* handle, ksys::act::InstParamPack* params);

protected:
    // static_param at offset 0x90
    sead::SafeString mShootItemName_s{};
    ksys::act::BaseProcHandle _a0;
};
KSYS_CHECK_SIZE_NX150(StoneShootEnemyBattle, 0xb0);

}  // namespace uking::ai
