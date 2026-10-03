#include "Game/AI/AI/aiTrolleyRoot.h"
#include "KingSystem/ActorSystem/Profiles/actDynamicActor.h"
#include "KingSystem/ActorSystem/actActor.h"
#include "KingSystem/Physics/Constraint/physConstraint.h"
#include "KingSystem/Physics/Constraint/physFixedCs.h"
#include "KingSystem/Physics/RigidBody/physRigidBody.h"
#include "KingSystem/Physics/System/physInstanceSet.h"

namespace uking::ai {

TrolleyRoot::TrolleyRoot(const InitArg& arg) : ksys::act::ai::Ai(arg) {}

TrolleyRoot::~TrolleyRoot() {
    if (_d0) {
        ksys::phys::Constraint::destroy(_d0);
        _d0 = nullptr;
    }
}

bool TrolleyRoot::init_(sead::Heap* heap) {
    auto* actor = sead::DynamicCast<ksys::act::DynamicActor>(mActor);
    if (!actor)
        return false;
    auto* physics = actor->getPhysics();
    actor->_a70 = &_d8;
    if (!physics)
        return false;
    auto* main_body = actor->getMainBody();
    if (!main_body)
        return false;
    auto* body = physics->findRigidBody("Barrier");
    if (!body)
        return false;
    ksys::phys::FixedCs::Param param;
    param.body_a = main_body;
    param.body_b = body;
    _d0 = ksys::phys::FixedCs::make(param, heap);
    return true;
}

void TrolleyRoot::enter_(ksys::act::ai::InlineParamPack* params) {
    changeChild("転がり");
    if (_d0)
        _d0->sub_7100F69FF0();
}

void TrolleyRoot::leave_() {
    ksys::act::ai::Ai::leave_();
}

void TrolleyRoot::loadParams_() {
    getStaticParam(&mNearGoalDist_s, "NearGoalDist");
    getStaticParam(&mNearGoalLimitSpd_s, "NearGoalLimitSpd");
    getStaticParam(&mNearGoalReduceRate_s, "NearGoalReduceRate");
}

bool TrolleyRoot::handleMessage_(const ksys::Message& message) {
    if (!_70._30)
        _70.m2(message);
    return false;
}

}  // namespace uking::ai
