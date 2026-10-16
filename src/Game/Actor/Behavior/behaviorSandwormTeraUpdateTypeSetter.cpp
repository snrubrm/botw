#include "Game/Actor/Behavior/behaviorSandwormTeraUpdateTypeSetter.h"
#include "Game/Actor/actSandworm.h"

namespace uking::behavior {

SandwormTeraUpdateTypeSetter::SandwormTeraUpdateTypeSetter(const InitArg& arg)
    : ksys::act::ai::Behavior(arg) {}

SandwormTeraUpdateTypeSetter::~SandwormTeraUpdateTypeSetter() = default;

bool SandwormTeraUpdateTypeSetter::init_(sead::Heap* heap) {
    return true;
}

void SandwormTeraUpdateTypeSetter::calc() {}

void SandwormTeraUpdateTypeSetter::loadParams() {
    getStaticParam(&mUpdateType_s, "UpdateType");
}

// NON_MATCHING: the original keeps one store per case (ours selects the value)
void SandwormTeraUpdateTypeSetter::enter() {
    auto* sandworm = sead::DynamicCast<uking::act::Sandworm>(mActor);
    if (!sandworm)
        return;
    switch (*mUpdateType_s) {
    case 0:
        sandworm->_1640 = 2;
        break;
    case 1:
        sandworm->_1640 = 1;
        break;
    default:
        sandworm->_1640 = 0;
        break;
    }
}

void SandwormTeraUpdateTypeSetter::leave() {
    if (auto* sandworm = sead::DynamicCast<uking::act::Sandworm>(mActor))
        sandworm->_1640 = 0;
}

}  // namespace uking::behavior
