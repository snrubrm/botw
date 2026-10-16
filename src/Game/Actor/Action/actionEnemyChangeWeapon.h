#pragma once

#include <container/seadSafeArray.h>
#include "Game/Actor/aiUnk_7100D3D3A8.h"
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
    void sub_71001066EC();
    void sub_71001068DC();
    void sub_7100106AF8();
    void sub_7100106D24(s32 index);

    // aitree_variable at offset 0x20
    int* mEquipWeaponBufIndex_a{};
    // aitree_variable at offset 0x28
    void* mPriestBossMetaAIUnit_a{};
    // indexed by weapon slot (sub_7100106D24 clamps the index to 0 when it is out of range)
    sead::SafeArray<Unk_7100d3d3a8, 2> _30;
    s32 _70 = -1;
    s32 _74 = -1;
    s32 _78 = 0;
};

}  // namespace uking::action
