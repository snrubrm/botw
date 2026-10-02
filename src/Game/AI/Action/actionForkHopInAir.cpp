#include "Game/AI/Action/actionForkHopInAir.h"
#include "Game/AI/aiUnk_71005D6D10.h"
#include "KingSystem/ActorSystem/actActorSensorUtil.h"
#include "KingSystem/ActorSystem/actActor.h"
#include "KingSystem/Physics/CharacterController/physCharacterController.h"

namespace uking::action {

ForkHopInAir::ForkHopInAir(const InitArg& arg) : Fork(arg) {}

ForkHopInAir::~ForkHopInAir() = default;

bool ForkHopInAir::init_(sead::Heap* heap) {
    return Fork::init_(heap);
}

void ForkHopInAir::enter_(ksys::act::ai::InlineParamPack* params) {
    Fork::enter_(params);
    if (auto* cc = mActor->getCharacterController()) {
        cc->sub_7100F5EF08(true);
        cc->sub_7100F62B70(*mHopHeight_s);
    }
}

void ForkHopInAir::leave_() {
    Fork::leave_();
}

void ForkHopInAir::loadParams_() {
    Fork::loadParams_();
    getStaticParam(&mHopHeight_s, "HopHeight");
}

void ForkHopInAir::calc_() {
    Fork::calc_();
}

bool ForkHopInAir::isFinished() const {
    if (ksys::act::ai::Action::isFinished())
        return true;
    if (*mEndState_s != 0)
        return false;
    return isBgGroundHit(mActor, false) || sub_71005E1064(mActor);
}

bool ForkHopInAir::isFailed() const {
    if (ksys::act::ai::Action::isFailed())
        return true;
    if (*mEndState_s != 1)
        return false;
    return isBgGroundHit(mActor, false) || sub_71005E1064(mActor);
}

bool ForkHopInAir::isChangeable() const {
    if (ksys::act::ai::Action::isChangeable())
        return true;
    if (*mEndState_s != 2)
        return false;
    return isBgGroundHit(mActor, false) || sub_71005E1064(mActor);
}

}  // namespace uking::action
