#include "Game/AI/Action/actionForkAITreeVariableMove.h"
#include "KingSystem/Physics/System/physRayCastBodyQuery.h"

namespace uking::action {

ForkAITreeVariableMove::ForkAITreeVariableMove(const InitArg& arg) : ksys::act::ai::Action(arg) {}

ForkAITreeVariableMove::~ForkAITreeVariableMove() = default;

bool ForkAITreeVariableMove::init_(sead::Heap* heap) {
    return ksys::act::ai::Action::init_(heap);
}

void ForkAITreeVariableMove::enter_(ksys::act::ai::InlineParamPack* params) {
    ksys::act::ai::Action::enter_(params);
}

void ForkAITreeVariableMove::leave_() {
    ksys::act::ai::Action::leave_();
}

void ForkAITreeVariableMove::loadParams_() {
    getStaticParam(&mArrivedRadius_s, "ArrivedRadius");
    getStaticParam(&mTargetSpeed_s, "TargetSpeed");
    getStaticParam(&mRotSlerpRate_s, "RotSlerpRate");
    getStaticParam(&mKeepDistFromGround_s, "KeepDistFromGround");
    getStaticParam(&mIsChangeable_s, "IsChangeable");
    getStaticParam(&mIsSuccessEndOnArrive_s, "IsSuccessEndOnArrive");
    getStaticParam(&mIsKeepDistFromGround_s, "IsKeepDistFromGround");
    getAITreeVariable(&mTargetSpeed_a, "TargetSpeed");
    getAITreeVariable(&mKeepDistFromGround_a, "KeepDistFromGround");
    getAITreeVariable(&mIsArrivedAtDestination_a, "IsArrivedAtDestination");
    getAITreeVariable(&mIsActive_a, "IsActive");
    getAITreeVariable(&mDestinationPos_a, "DestinationPos");
    getAITreeVariable(&mFacePos_a, "FacePos");
}

void ForkAITreeVariableMove::sub_710005BE70() {
    if (!*mIsKeepDistFromGround_s)
        return;
    const f32 dist = *(*mKeepDistFromGround_a > 0.0f ? mKeepDistFromGround_a : mKeepDistFromGround_s);
    ksys::phys::RayCastBodyQuery query(nullptr, ksys::phys::GroundHit::HitAll);
    sead::Vector3f start;
    start.x = mDestinationPos_a->x + 0.0f;
    start.y = dist + mDestinationPos_a->y;
    start.z = mDestinationPos_a->z + 0.0f;
    query.enableLayer(ksys::phys::ContactLayer::EntityGround);
    query.setStartAndDisplacementScaled(start, sead::Vector3f::ey, dist * -5.0f);
    if (query.worldRayCast(ksys::phys::ContactLayerType::Entity)) {
        query.getHitPosition(&start);
        mDestinationPos_a->y = dist + start.y;
    }
}

void ForkAITreeVariableMove::calc_() {
    ksys::act::ai::Action::calc_();
}

}  // namespace uking::action
