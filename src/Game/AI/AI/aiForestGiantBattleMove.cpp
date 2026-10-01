#include "Game/AI/AI/aiForestGiantBattleMove.h"
#include <random/seadGlobalRandom.h>
#include "KingSystem/ActorSystem/actActor.h"
#include "KingSystem/System/Timer.h"

namespace uking::ai {

ForestGiantBattleMove::ForestGiantBattleMove(const InitArg& arg) : WaitNearTarget(arg) {}

ForestGiantBattleMove::~ForestGiantBattleMove() = default;

bool ForestGiantBattleMove::init_(sead::Heap* heap) {
    return WaitNearTarget::init_(heap);
}

void ForestGiantBattleMove::enter_(ksys::act::ai::InlineParamPack* params) {
    _80 = 10;
    _78 = 10.0f;
    _7c = 10;
    WaitNearTarget::enter_(params);
}

void ForestGiantBattleMove::calc_() {
    f32& timer = _78;
    bool in_range = true;
    if (isCurrentChild("待機")) {
        const f32 actor_y = mActor->getMtx().m[1][3];
        const f32 height = mTargetPos_d->y - actor_y;
        in_range = *mAttackHeightMin_s < height && height <= *mAttackHeightMax_s;
    }

    if (in_range) {
        s32 time = _7c;
        if (_80 != _7c)
            time = sead::GlobalRandom::instance()->getS32Range(_7c, _80);
        timer = time;
    } else {
        ksys::Timer::update(&timer, -1.0f);
    }

    if (isCurrentChild("待機") && timer <= 0.0f && getCurrentChild()->isChangeable()) {
        setFailed();
        return;
    }

    WaitNearTarget::calc_();
}

void ForestGiantBattleMove::leave_() {
    WaitNearTarget::leave_();
}

void ForestGiantBattleMove::loadParams_() {
    WaitNearTarget::loadParams_();
    getStaticParam(&mAttackHeightMin_s, "AttackHeightMin");
    getStaticParam(&mAttackHeightMax_s, "AttackHeightMax");
}

}  // namespace uking::ai
