#include "Game/AI/Action/actionLastBossDemoWarp.h"
#include "KingSystem/ActorSystem/actActor.h"
#include "KingSystem/Physics/CharacterController/physCharacterController.h"
#include "KingSystem/Physics/RigidBody/physRigidBody.h"
#include "KingSystem/Physics/System/physInstanceSet.h"

namespace uking::action {

LastBossDemoWarp::LastBossDemoWarp(const InitArg& arg) : ksys::act::ai::Action(arg) {}

LastBossDemoWarp::~LastBossDemoWarp() = default;

bool LastBossDemoWarp::init_(sead::Heap* heap) {
    return ksys::act::ai::Action::init_(heap);
}

void LastBossDemoWarp::enter_(ksys::act::ai::InlineParamPack* params) {
    ksys::act::ai::Action::enter_(params);
}

void LastBossDemoWarp::leave_() {
    auto* controller = mActor->getCharacterController();
    if (!controller)
        return;
    controller->sub_7100F5F6FC(sead::Vector3f::zero);
    controller->sub_7100F5FB24(sead::Vector3f::zero);
    if (auto* body = controller->sub_7100F61A34()) {
        if (auto* physics = mActor->getPhysics())
            body->setContactLayerAndHandler(ksys::phys::ContactLayer::EntityHitOnlyGround,
                                            physics->get188(0));
    }
}

void LastBossDemoWarp::loadParams_() {
    getStaticParam(&mWarpTime_s, "WarpTime");
    getStaticParam(&mIsUpdateHomePos_s, "IsUpdateHomePos");
    getStaticParam(&mWarpAnchorUniqName_s, "WarpAnchorUniqName");
}

void LastBossDemoWarp::calc_() {
    ksys::act::ai::Action::calc_();
}

}  // namespace uking::action
