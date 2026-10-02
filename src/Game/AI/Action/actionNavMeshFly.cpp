#include "Game/AI/Action/actionNavMeshFly.h"
#include "KingSystem/ActorSystem/actActor.h"

namespace uking::action {

NavMeshFly::NavMeshFly(const InitArg& arg) : NavMeshAction(arg) {}

NavMeshFly::~NavMeshFly() = default;

bool NavMeshFly::init_(sead::Heap* heap) {
    return NavMeshAction::init_(heap);
}

void NavMeshFly::enter_(ksys::act::ai::InlineParamPack* params) {
    NavMeshAction::enter_(params);
    _b8.changeMotionType(mActor->getCharacterController(), ksys::act::MotionType::Hover);
}

void NavMeshFly::leave_() {
    _b8.resetMotionType(mActor->getCharacterController());
    NavMeshAction::leave_();
}

void NavMeshFly::loadParams_() {
    NavMeshAction::loadParams_();
    getStaticParam(&mASName_s, "ASName");
}

void NavMeshFly::calc_() {
    NavMeshAction::calc_();
}

void NavMeshFly::m34() {
    playAS(mASName_s.cstr(), true, 0, 0, -1.0f);
}

}  // namespace uking::action
