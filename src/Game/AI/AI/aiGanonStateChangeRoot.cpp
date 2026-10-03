#include "Game/AI/AI/aiGanonStateChangeRoot.h"
#include "Game/AI/aiUnk_71005D6D10.h"
#include "KingSystem/ActorSystem/actActor.h"
#include "KingSystem/Physics/CharacterController/physCharacterController.h"

namespace uking::ai {

GanonStateChangeRoot::GanonStateChangeRoot(const InitArg& arg) : ksys::act::ai::Ai(arg) {}

GanonStateChangeRoot::~GanonStateChangeRoot() = default;

bool GanonStateChangeRoot::init_(sead::Heap* heap) {
    return ksys::act::ai::Ai::init_(heap);
}

void GanonStateChangeRoot::enter_(ksys::act::ai::InlineParamPack* params) {
    if (auto* controller = mActor->getCharacterController()) {
        const sead::Vector3f up = sead::Vector3f::ey;
        controller->sub_7100F5EE1C(up * -29.0f);
        controller->sub_7100F5EDE8(up);
    }
    sub_71003EEE18();
    _40 = 600.0f;
}

void GanonStateChangeRoot::leave_() {
    sub_71005DB434(mActor);
}

void GanonStateChangeRoot::loadParams_() {
    getDynamicParam(&mTargetPos_d, "TargetPos");
}

}  // namespace uking::ai
