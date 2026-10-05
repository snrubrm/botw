#pragma once

#include <container/seadObjList.h>
#include "Game/AI/AI/aiUnarmedEnemySearch.h"
#include "KingSystem/ActorSystem/Awareness/actAwarenessInstance.h"
#include "KingSystem/ActorSystem/actBaseProcLink.h"
#include "KingSystem/ActorSystem/actAiAi.h"
#include "KingSystem/System/Timer.h"

namespace uking::ai {

class UnarmedEnemySearchWeapon : public UnarmedEnemySearch {
    SEAD_RTTI_OVERRIDE(UnarmedEnemySearchWeapon, UnarmedEnemySearch)
public:
    explicit UnarmedEnemySearchWeapon(const InitArg& arg);
    ~UnarmedEnemySearchWeapon() override;

    void enter_(ksys::act::ai::InlineParamPack* params) override;
    void calc_() override;
    void leave_() override;
    void m35(const sead::Vector3f& target) override;

    bool m34() override;
    void m36() override {}
    virtual void m44();
    virtual void m45();
    virtual bool m46(ksys::act::BaseProcLink& target) { return true; }
    void loadParams_() override;

protected:
    bool sub_71003B6888();
    void sub_71003B8780();
    /* 0x68 */ ksys::act::BaseProcLink _68;
    // 0x7100d772d4 is the element destructor (Unk_71024dc858's D1 at the element start).
    /* 0x78 */ sead::FixedObjList<ksys::act::Unk_7100d78e50, 8> _78;
    /* 0x6a8 */ ksys::Timer _6a8{0, 0};
    /* 0x6b4 */ u8 _6b4[4];
    // static_param at offset 0x6b8
    const int* mEquipItemSearchIdx_s{};
    // static_param at offset 0x6c0
    const int* mRepathTime_s{};
    // static_param at offset 0x6c8
    const float* mSearchDist_s{};
    // static_param at offset 0x6d0
    const float* mSearchAng_s{};
    // static_param at offset 0x6d8
    const bool* mIsUseSight_s{};
    // static_param at offset 0x6e0
    const float* mLineReachableWeaponDist_s{};
};

}  // namespace uking::ai
