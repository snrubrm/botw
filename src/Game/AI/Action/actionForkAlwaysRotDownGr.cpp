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
    auto* controller = mActor->getCharacterController();
    _34.x = mActor->getMtx().m[1][2] < 0.0f ? 1.0f : -1.0f;
    _34.y = _34.z = 0.0f;
    if (controller) {
        controller->mFlags.set(2);
        controller->_240 = _34;
    }
    _40 = true;
    _28.value = _28.prev_value = 0.0f;
    mFlags.set(Flag::Changeable);
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
