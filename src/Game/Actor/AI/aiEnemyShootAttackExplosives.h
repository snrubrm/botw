#pragma once

#include "Game/Actor/AI/aiEnemyBaseArrowAttack.h"
#include "Game/Actor/aiUnk_71007377D4.h"
#include "KingSystem/ActorSystem/actActor.h"
#include "KingSystem/ActorSystem/actAiAi.h"

namespace uking::ai {

class EnemyShootAttackExplosives : public EnemyBaseArrowAttack {
    SEAD_RTTI_OVERRIDE(EnemyShootAttackExplosives, EnemyBaseArrowAttack)
public:
    explicit EnemyShootAttackExplosives(const InitArg& arg);
    ~EnemyShootAttackExplosives() override;

    void enter_(ksys::act::ai::InlineParamPack* params) override;
    void calc_() override;
    void loadParams_() override;

protected:
    // inline-only in the original; name is a guess. enter_ and calc_ repeat this normalized
    // horizontal backstep destination and probe block before constructing their parameter packs.
    bool canBackstep() {
        if (auto* actor = mActor) {
            const sead::Vector3f target = *mTargetPos_d;
            sead::Vector3f direction = actor->getMtx().getTranslation() - target;
            direction.y = 0.0f;
            direction.normalize();
            sead::Vector3f destination = target;
            destination += direction * *mExplosivesAvoidDist_s;
            return sub_710072FAB0(actor, destination, nullptr, -1, -1.0f, -1.0f);
        }
        return false;
    }
    // static_param at offset 0x50
    const float* mExplosivesAvoidDist_s{};
    // static_param at offset 0x58
    const float* mTurnStartAng_s{};
};

}  // namespace uking::ai
