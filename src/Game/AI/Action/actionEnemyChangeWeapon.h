#pragma once

#include "Game/AI/aiUnk_7100D3D3A8.h"
#include "KingSystem/ActorSystem/actAiAction.h"

namespace uking::action {

class EnemyChangeWeapon : public ksys::act::ai::Action {
    SEAD_RTTI_OVERRIDE(EnemyChangeWeapon, ksys::act::ai::Action)
public:
    explicit EnemyChangeWeapon(const InitArg& arg);
    ~EnemyChangeWeapon() override;

    bool init_(sead::Heap* heap) override;
    void enter_(ksys::act::ai::InlineParamPack* params) override;
    void leave_() override;
    void loadParams_() override;

protected:
    void calc_() override;

    // aitree_variable at offset 0x20
    int* mEquipWeaponBufIndex_a{};
    // aitree_variable at offset 0x28
    void* mPriestBossMetaAIUnit_a{};
    Unk_7100d3d3a8 _30;
    Unk_7100d3d3a8 _50;
    s32 _70 = -1;
    s32 _74 = -1;
    s32 _78 = 0;
};

}  // namespace uking::action
