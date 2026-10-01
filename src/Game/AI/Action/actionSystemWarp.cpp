#include "Game/AI/Action/actionSystemWarp.h"
#include "KingSystem/Physics/System/physInstanceSet.h"
#include "KingSystem/ActorSystem/actActor.h"

namespace uking::action {

SystemWarp::SystemWarp(const InitArg& arg) : ksys::act::ai::Action(arg) {}

SystemWarp::~SystemWarp() = default;

bool SystemWarp::init_(sead::Heap* heap) {
    return ksys::act::ai::Action::init_(heap);
}

void SystemWarp::enter_(ksys::act::ai::InlineParamPack* params) {
    sead::Matrix34f mtx;
    mActor->getHomeMtx(&mtx);
    mtx.setTranslation(*mTargetPos_d);
    if (auto* physics = mActor->getPhysics())
        physics->setMtxAndScale(mtx, false, false, mActor->getScale().x);
    setFinished();
}

void SystemWarp::leave_() {
    ksys::act::ai::Action::leave_();
}

void SystemWarp::loadParams_() {
    getDynamicParam(&mTargetPos_d, "TargetPos");
}

void SystemWarp::calc_() {
    ksys::act::ai::Action::calc_();
}

}  // namespace uking::action
