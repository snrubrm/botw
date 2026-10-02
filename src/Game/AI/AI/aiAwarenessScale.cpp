#include "Game/AI/AI/aiAwarenessScale.h"
#include "KingSystem/ActorSystem/Awareness/actAwarenessInstance.h"
#include "KingSystem/ActorSystem/actActor.h"

namespace uking::ai {

AwarenessScale::AwarenessScale(const InitArg& arg) : ksys::act::ai::Ai(arg) {}

AwarenessScale::~AwarenessScale() = default;

bool AwarenessScale::isFailed() const {
    return getCurrentChild()->isFailed();
}

bool AwarenessScale::isFinished() const {
    return getCurrentChild()->isFinished();
}

bool AwarenessScale::isChangeable() const {
    return getCurrentChild()->isChangeable();
}

bool AwarenessScale::init_(sead::Heap* heap) {
    return ksys::act::ai::Ai::init_(heap);
}

void AwarenessScale::enter_(ksys::act::ai::InlineParamPack* params) {
    if (auto* awareness = mActor->getAwareness()) {
        _40 = awareness->sub_7100D7EC34(0);
        _44 = awareness->sub_7100D7EC34(1);
        _48 = awareness->sub_7100D7EC34(2);
        _4c = awareness->sub_7100D7EC34(3);
        awareness->sub_7100D7EBE0(*mScale_s);
    }
    changeChild("行動", params);
}

void AwarenessScale::calc_() {}

void AwarenessScale::leave_() {
    if (auto* awareness = mActor->getAwareness()) {
        awareness->sub_7100D7EC14(0, _40);
        awareness->sub_7100D7EC14(1, _44);
        awareness->sub_7100D7EC14(2, _48);
        awareness->sub_7100D7EC14(3, _4c);
    }
}

void AwarenessScale::loadParams_() {
    getStaticParam(&mScale_s, "Scale");
}

}  // namespace uking::ai
