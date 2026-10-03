#pragma once

#include <container/seadObjList.h>
#include <math/seadVector.h>
#include "Game/Actor/actEnemy.h"
#include "KingSystem/ActorSystem/actAiAi.h"

namespace uking::ai {

class UnarmedEnemySearch : public ksys::act::ai::Ai {
    SEAD_RTTI_OVERRIDE(UnarmedEnemySearch, ksys::act::ai::Ai)
public:
    explicit UnarmedEnemySearch(const InitArg& arg);
    ~UnarmedEnemySearch() override;

    bool isChangeable() const override { return getCurrentChild()->isChangeable(); }

    bool init_(sead::Heap* heap) override;
    void enter_(ksys::act::ai::InlineParamPack* params) override;
    void calc_() override;
    void leave_() override;
    void loadParams_() override;

    virtual bool m34();
    virtual void m35(const sead::Vector3f& target);
    virtual void m36() {}
    virtual void m37();
    virtual void m38() {}
    virtual void m39();
    virtual bool m40(const sead::ObjList<sead::Vector3f>& points, sead::Vector3f* out);
    virtual void m41(const sead::ObjList<sead::Vector3f>& points);
    virtual void m42();
    virtual bool m43(sead::Vector3f* out);

    // Small out-of-line helpers over `_50` (the Enemy's navmesh state: `_0` navmesh character, `_8`
    // search state); names are placeholders (lane1 s22).
    // 0x71004b5fb8: changeChild("見まわす").
    void sub_71004B5FB8();
    // 0x71004b62e4 (CSV sead::ControllerMgr::getFramework, misnamed): `_50->_8`, -1 without `_50`.
    int sub_71004B62E4() const;
    // 0x71004b62fc: if the state is 1 or 3: copies navmesh `_1a0` (under its lock) to `out`.
    bool sub_71004B62FC(sead::Vector3f* out) const;
    // 0x71004b6370: if the state is not -1: copies navmesh `_194` (under its lock) to `out`.
    bool sub_71004B6370(sead::Vector3f* out) const;
    // 0x71004b63e4: `_50->_8 = -1` (if `_50`).
    void sub_71004B63E4();
    // 0x71004b6bc0: ReachTargetArea plus the weapon range.
    f32 sub_71004B6BC0() const;

protected:
    // static_param at offset 0x38
    const int* mWeaponIdx_s{};
    // static_param at offset 0x40
    const float* mReachTargetArea_s{};
    // static_param at offset 0x48
    const float* mTurnStartAng_s{};
    act::Enemy::Unk_12d0* _50 = nullptr;
    sead::Vector3f _58{0, 0, 0};
};
KSYS_CHECK_SIZE_NX150(UnarmedEnemySearch, 0x68);

}  // namespace uking::ai
