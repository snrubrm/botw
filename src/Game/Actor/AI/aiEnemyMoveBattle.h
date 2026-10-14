#pragma once

#include "Game/Actor/AI/aiEnemyBattle.h"
#include "KingSystem/ActorSystem/actAiAi.h"
#include "KingSystem/System/Timer.h"

namespace uking::ai {

class EnemyMoveBattle : public EnemyBattle {
    SEAD_RTTI_OVERRIDE(EnemyMoveBattle, EnemyBattle)
public:
    explicit EnemyMoveBattle(const InitArg& arg);
    ~EnemyMoveBattle() override;
    bool isFinished() const override;
    bool isChangeable() const override;

    void enter_(ksys::act::ai::InlineParamPack* params) override;
    void calc_() override;
    void leave_() override;
    void loadParams_() override;

protected:
    // 0x7100399bc8 (placeholder name): the point `MoveDist` to the side of the actor (the side that is nearer to its
    // front) and half a unit back from `dir`; the result is also checked with sub_710072F99C.
    void sub_7100399BC8(sead::Vector3f* out, const sead::Vector3f& dir);
    // 0x710039997c (placeholder name): for a DynamicActor, whether the way to the target is blocked: without `normal`,
    // !sub_710072E1B4(actor, false); with it, true when the target is behind the actor (dot <= -0.5), else a ground ray
    // cast from the actor (at the awareness height) to the target whose hit normal is written to `normal`.
    bool sub_710039997C(sead::Vector3f* normal);

    // dynamic_param at offset 0x90
    sead::Vector3f* mTargetPos_d{};
    // static_param at offset 0x98
    const int* mLimitMoveTime_s{};
    // static_param at offset 0xa0
    const float* mMoveDist_s{};
    ksys::Timer _a8{0, 0};
    ksys::Timer _b4{0, 0};
};

}  // namespace uking::ai
