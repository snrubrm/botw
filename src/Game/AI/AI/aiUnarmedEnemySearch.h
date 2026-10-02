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
