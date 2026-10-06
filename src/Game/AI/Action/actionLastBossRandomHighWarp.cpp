#include "Game/AI/Action/actionLastBossRandomHighWarp.h"
#include <random/seadGlobalRandom.h>
#include "Game/AI/aiUnk_71002C52DC.h"
#include "KingSystem/Physics/System/physInstanceSet.h"
#include "KingSystem/Physics/RigidBody/physRigidBody.h"
#include "KingSystem/Physics/CharacterController/physCharacterController.h"
#include "KingSystem/ActorSystem/actActor.h"

namespace uking::action {

LastBossRandomHighWarp::LastBossRandomHighWarp(const InitArg& arg) : LastBossNormalWarp(arg) {}

LastBossRandomHighWarp::~LastBossRandomHighWarp() = default;

bool LastBossRandomHighWarp::init_(sead::Heap* heap) {
    if (!LastBossNormalWarp::init_(heap))
        return false;
    _11c = 0;
    return true;
}

void LastBossRandomHighWarp::enter_(ksys::act::ai::InlineParamPack* params) {
    sub_71001D7104(params);
    LastBossNormalWarp::enter_(params);
}

// NON_MATCHING: register allocation only (the original keeps the constant 1 in a callee-saved register shared by
// `1 - lo` and the `_118 = true` store).
void LastBossRandomHighWarp::sub_71001D7104(ksys::act::ai::InlineParamPack* params) {
    ++_11c;
    const s32 rate = *mHighPosWarpRate_s;
    const f32 life = *mLifeCondition_s;
    const s32 random_range = *mRandomRate_s;
    if (sub_71002C52DC(mActor, life)) {
        _118 = false;
        _11c = 0;
        return;
    }
    if (_11c < rate - random_range) {
        _118 = false;
        return;
    }
    if (_11c >= rate + random_range) {
        _118 = true;
        _11c = 0;
        return;
    }
    const s32 probability = 100 / (2 * *mRandomRate_s + 1) * (1 - (rate - random_range) + _11c);
    if (sead::GlobalRandom::instance()->getS32Range(0, 100) < probability) {
        _118 = true;
        _11c -= *mHighPosWarpRate_s;
    } else {
        _118 = false;
    }
}

void LastBossRandomHighWarp::leave_() {
    LastBossNormalWarp::leave_();
    if (auto* controller = mActor->getCharacterController()) {
        if (auto* body = controller->sub_7100F61A34()) {
            if (auto* physics = mActor->getPhysics())
                body->setContactLayerAndHandler(ksys::phys::ContactLayer::EntityHitOnlyGround,
                                                physics->get188(0));
        }
    }
}

void LastBossRandomHighWarp::loadParams_() {
    LastBossNormalWarp::loadParams_();
    getStaticParam(&mHighPosWarpRate_s, "HighPosWarpRate");
    getStaticParam(&mRandomRate_s, "RandomRate");
    getStaticParam(&mHighOffsetY_s, "HighOffsetY");
    getStaticParam(&mLifeCondition_s, "LifeCondition");
}

void LastBossRandomHighWarp::calc_() {
    LastBossNormalWarp::calc_();
}

bool LastBossRandomHighWarp::m32() {
    if (_118)
        return false;
    return *mIsWarpAtGround_s;
}

// NON_MATCHING: register choice of the two member addresses of the select (x9/x10 swapped)
float LastBossRandomHighWarp::m33() {
    return *(_118 == 0 ? mOffsetY_s : mHighOffsetY_s);
}

}  // namespace uking::action
