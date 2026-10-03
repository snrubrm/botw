#include "Game/AI/Action/actionForkWaitGroundHit.h"
#include "KingSystem/Physics/CharacterController/physCharacterController.h"
#include "KingSystem/ActorSystem/actActorSensorUtil.h"
#include "KingSystem/ActorSystem/actActor.h"

namespace uking::action {

ForkWaitGroundHit::ForkWaitGroundHit(const InitArg& arg) : ksys::act::ai::Action(arg) {}

ForkWaitGroundHit::~ForkWaitGroundHit() = default;

bool ForkWaitGroundHit::init_(sead::Heap* heap) {
    return ksys::act::ai::Action::init_(heap);
}

void ForkWaitGroundHit::enter_(ksys::act::ai::InlineParamPack* params) {
    if (*mIsChangeable_s)
        mFlags.set(Flag::Changeable);
}

void ForkWaitGroundHit::leave_() {
    ksys::act::ai::Action::leave_();
}

void ForkWaitGroundHit::loadParams_() {
    getStaticParam(&mInWaterDepth_s, "InWaterDepth");
    getStaticParam(&mIsChangeable_s, "IsChangeable");
}

void ForkWaitGroundHit::calc_() {
    ksys::act::ai::Action::calc_();
}

bool ForkWaitGroundHit::isFinished() const {
    auto* actor = mActor;
    if (isBgGroundHit(actor, false))
        return true;
    if (*mInWaterDepth_s >= 0.0f) {
        f32 depth;
        if (actor->getCharacterController() && (actor->getCharacterController()->_116 & 4)) {
            depth = actor->getCharacterController()->_210;
        } else if (actor->get68f()) {
            const f32 y = actor->getMtx().m[1][3];
            depth = actor->get6f0() - y;
        } else {
            return false;
        }
        return depth >= *mInWaterDepth_s;
    }
    return false;
}

}  // namespace uking::action
