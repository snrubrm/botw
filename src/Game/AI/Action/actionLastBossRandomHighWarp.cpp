#include "Game/AI/Action/actionLastBossRandomHighWarp.h"
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
    LastBossNormalWarp::enter_(params);
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
