#pragma once

#include <container/seadObjList.h>
#include "Game/Actor/AI/aiNavMove.h"
#include "KingSystem/ActorSystem/Awareness/actAwarenessInstance.h"
#include "KingSystem/ActorSystem/actBaseProcLink.h"
#include "KingSystem/ActorSystem/actAiAi.h"
#include "KingSystem/System/Timer.h"

namespace uking::ai {

class EnemySearch : public NavMove {
    SEAD_RTTI_OVERRIDE(EnemySearch, NavMove)
public:
    explicit EnemySearch(const InitArg& arg);
    ~EnemySearch() override;

    void enter_(ksys::act::ai::InlineParamPack* params) override;
    void calc_() override;
    void leave_() override;
    void m35(const sead::Vector3f& target) override;

    bool m34() override;
    void m36(sead::FixedObjList<sead::Vector3f, 8>* points) override {}
    void m37() override;
    void m38() override;
    void m39() override;
    virtual void m44();
    virtual void m45();
    virtual bool m46(ksys::act::BaseProcLink& target) { return true; }
    void loadParams_() override;

protected:
    // 0x71003b8020: the twin of LandHumEnemyUnarmedBattle::sub_7100470ED4: whether `link` is reachable (sub_7100739030) or within the reach distance
    bool sub_71003B8020(ksys::act::BaseProcLink& link) const;
    bool sub_71003B6888();
    bool sub_71003B80F8();
    bool sub_71003B8B64();
    bool sub_71003B884C();
    // 0x71003b8e70: the link of the entry of _78 nearest to the position of the navmesh character (the dummy link if none)
    ksys::act::BaseProcLink* sub_71003B8E70();
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
