#include "Game/AI/Action/actionSwarmAreaDamaged.h"
#include "KingSystem/ActorSystem/actChemical.h"
#include "KingSystem/Physics/CharacterController/physCharacterController.h"
#include "KingSystem/ActorSystem/actActor.h"
#include "Game/AI/aiUnk_71007377D4.h"

namespace uking::action {

SwarmAreaDamaged::SwarmAreaDamaged(const InitArg& arg) : SwarmDamagedBase(arg) {}

SwarmAreaDamaged::~SwarmAreaDamaged() = default;

bool SwarmAreaDamaged::init_(sead::Heap* heap) {
    return SwarmDamagedBase::init_(heap);
}

void SwarmAreaDamaged::enter_(ksys::act::ai::InlineParamPack* params) {
    SwarmDamagedBase::enter_(params);
}

void SwarmAreaDamaged::leave_() {
    if (auto* chemical = mActor->getChemicalStuff())
        chemical->_14c = 1.0f;
    SwarmDamagedBase::leave_();
}

void SwarmAreaDamaged::loadParams_() {
    SwarmDamagedBase::loadParams_();
    getStaticParam(&mDeadSubActorMax_s, "DeadSubActorMax");
}

void SwarmAreaDamaged::calc_() {
    SwarmDamagedBase::calc_();
    if (auto* controller = mActor->getCharacterController())
        sub_7100737C0C(controller, 0.2f, -sead::Vector3f::ey);
}

}  // namespace uking::action
