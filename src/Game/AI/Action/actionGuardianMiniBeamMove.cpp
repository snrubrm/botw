#include "Game/AI/Action/actionGuardianMiniBeamMove.h"
#include "KingSystem/XLink/xlinkActorUtil.h"
#include "KingSystem/Physics/RigidBody/physRigidBody.h"
#include "KingSystem/ActorSystem/actActor.h"

namespace uking::action {

// `_78()`: value-initialisation zero-fills the whole 0x20-byte handle pair incl. padding (as WeaponRootAI's `_c8()`)
GuardianMiniBeamMove::GuardianMiniBeamMove(const InitArg& arg) : BeamMove(arg), _78() {}

GuardianMiniBeamMove::~GuardianMiniBeamMove() = default;

void GuardianMiniBeamMove::enter_(ksys::act::ai::InlineParamPack* params) {
    BeamMove::enter_(params);
    _98 = 0;
    if (auto* body = mActor->getMainBody())
        body->setGravityFactor(0.0f);
    xlinkSearchAndEmit(mActor, "Beam", 2, &_78);
}

void GuardianMiniBeamMove::leave_() {
    BeamMove::leave_();
}

void GuardianMiniBeamMove::loadParams_() {
    BeamMove::loadParams_();
    getStaticParam(&mReboundDeccel_s, "ReboundDeccel");
}

void GuardianMiniBeamMove::calc_() {
    BeamMove::calc_();
}

}  // namespace uking::action
