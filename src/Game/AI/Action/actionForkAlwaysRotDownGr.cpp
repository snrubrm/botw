#include "Game/AI/Action/actionForkAlwaysRotDownGr.h"
#include "KingSystem/Physics/CharacterController/physCharacterController.h"
#include "KingSystem/ActorSystem/actActor.h"

namespace uking::action {

ForkAlwaysRotDownGr::ForkAlwaysRotDownGr(const InitArg& arg) : ksys::act::ai::Action(arg) {}

ForkAlwaysRotDownGr::~ForkAlwaysRotDownGr() = default;

bool ForkAlwaysRotDownGr::init_(sead::Heap* heap) {
    return ksys::act::ai::Action::init_(heap);
}

void ForkAlwaysRotDownGr::enter_(ksys::act::ai::InlineParamPack* params) {
    ksys::act::ai::Action::enter_(params);
}

void ForkAlwaysRotDownGr::leave_() {
    if (auto* controller = mActor->getCharacterController())
        controller->mFlags.reset(2);
}

void ForkAlwaysRotDownGr::loadParams_() {
    getStaticParam(&mGroundRotAngle_s, "GroundRotAngle");
}

void ForkAlwaysRotDownGr::calc_() {
    ksys::act::ai::Action::calc_();
}

}  // namespace uking::action
