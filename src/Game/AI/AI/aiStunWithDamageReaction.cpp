#include "Game/AI/AI/aiStunWithDamageReaction.h"
#include "Game/Actor/actEnemy.h"
#include "Game/Damage/dmgDamageManagerBase.h"
#include "KingSystem/ActorSystem/actActor.h"
#include "KingSystem/System/Timer.h"

namespace uking::ai {

StunWithDamageReaction::StunWithDamageReaction(const InitArg& arg) : ksys::act::ai::Ai(arg) {}

StunWithDamageReaction::~StunWithDamageReaction() = default;

bool StunWithDamageReaction::init_(sead::Heap* heap) {
    return ksys::act::ai::Ai::init_(heap);
}

void StunWithDamageReaction::enter_(ksys::act::ai::InlineParamPack* params) {
    _48 = *mTimer_s;
    if (auto* enemy = sead::DynamicCast<act::Enemy>(mActor))
        enemy->_e84.set(8);
    changeChild("気絶", params);
    _4c = true;
}

void StunWithDamageReaction::calc_() {
    ksys::Timer::update(&_48, -1.0f);
    auto* child = getCurrentChild();

    if (isCurrentChild("気絶")) {
        auto* life = mActor->getLife();
        const f32 current = life ? f32(*life) : 1.0f;
        if (current < f32(mActor->getMaxLife()) * *mForceEndLifeRatio_s) {
            setFinished();
            return;
        }
        if (!_4c) {
            auto* mgr = mActor->getDamageMgr();
            if (mgr && mgr->getField54() >= 16) {
                changeChild("ダメージ");
                return;
            }
        }
    } else if (_48 > 0.0f && !_4c) {
        auto* mgr = mActor->getDamageMgr();
        if (mgr && mgr->getField54() >= 16) {
            changeChild("ダメージ");
            return;
        }
    }

    _4c = false;
    if (child->isFinished() || child->isFailed()) {
        if (isCurrentChild("ダメージ") && !(_48 <= 0.0f))
            changeChild("気絶");
        else
            setFinished();
    } else if (child->isChangeable() && _48 <= 0.0f) {
        setFinished();
    }
}

void StunWithDamageReaction::leave_() {
    if (auto* enemy = sead::DynamicCast<act::Enemy>(mActor))
        enemy->_e84.reset(8);
}

void StunWithDamageReaction::loadParams_() {
    getStaticParam(&mTimer_s, "Timer");
    getStaticParam(&mForceEndLifeRatio_s, "ForceEndLifeRatio");
}

}  // namespace uking::ai
