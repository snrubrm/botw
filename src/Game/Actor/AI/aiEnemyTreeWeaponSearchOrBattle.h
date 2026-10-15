#pragma once

#include "Game/Actor/aiUnk_7102357d20.h"
#include "KingSystem/ActorSystem/actAiAi.h"
#include "KingSystem/ActorSystem/actBaseProcLink.h"

namespace uking::ai {

class EnemyTreeWeaponSearchOrBattle : public ksys::act::ai::Ai {
    SEAD_RTTI_OVERRIDE(EnemyTreeWeaponSearchOrBattle, ksys::act::ai::Ai)
public:
    explicit EnemyTreeWeaponSearchOrBattle(const InitArg& arg);
    ~EnemyTreeWeaponSearchOrBattle() override;

    bool init_(sead::Heap* heap) override;
    void enter_(ksys::act::ai::InlineParamPack* params) override;
    void leave_() override;
    void calc_() override;
    void loadParams_() override;

protected:
    // 0x71003c1e20 (placeholder name; declared only, 1168 B): searches a tree weapon (sets _60) or a tree (sets
    // _61) into _50.
    bool sub_71003C1E20();

    // static_param at offset 0x38
    const int* mWeaponIdx_s{};
    // static_param at offset 0x40
    const float* mSearchDist_s{};
    // static_param at offset 0x48
    const float* mNoSearchDist_s{};
    ksys::act::BaseProcLink _50;
    bool _60 = false;
    bool _61 = false;
    Unk_71023ec318 _68{mActor, 0x300000c};
    Unk_71023ec340 _80{mActor, 0x300000d};
};

}  // namespace uking::ai
