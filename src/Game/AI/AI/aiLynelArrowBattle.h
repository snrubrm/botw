#pragma once

#include "Game/AI/AI/aiEnemyBattle.h"
#include "KingSystem/ActorSystem/actAiAi.h"

namespace uking::ai {

class LynelArrowBattle : public EnemyBattle {
    SEAD_RTTI_OVERRIDE(LynelArrowBattle, EnemyBattle)
public:
    explicit LynelArrowBattle(const InitArg& arg);
    ~LynelArrowBattle() override;

    bool init_(sead::Heap* heap) override;
    void enter_(ksys::act::ai::InlineParamPack* params) override;
    void calc_() override;
    void leave_() override;
    void loadParams_() override;
    void m37() override;
    void m38() override;
    bool m40() override;
    bool m41() override;
    bool isFinished() const override;

protected:
    // static_param at offset 0x90
    const int* mWeaponIdx_s{};
    // static_param at offset 0x98
    const int* mAttackCount_s{};
    // static_param at offset 0xa0
    sead::SafeString mFrontCheckBoneName_s{};
    // static_param at offset 0xb0
    const sead::Vector3f* mFrontDirFromBone_s{};
    int _b8{};
};

}  // namespace uking::ai
