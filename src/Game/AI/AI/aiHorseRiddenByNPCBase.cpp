#include "Game/AI/AI/aiHorseRiddenByNPCBase.h"
#include "KingSystem/ActorSystem/Awareness/actAwarenessInstance.h"
#include "KingSystem/ActorSystem/actActor.h"

namespace uking::ai {

HorseRiddenByNPCBase::HorseRiddenByNPCBase(const InitArg& arg) : ksys::act::ai::Ai(arg) {}

bool HorseRiddenByNPCBase::init_(sead::Heap* heap) {
    return ksys::act::ai::Ai::init_(heap);
}

void HorseRiddenByNPCBase::enter_(ksys::act::ai::InlineParamPack* params) {
    ksys::act::ai::Ai::enter_(params);
}

void HorseRiddenByNPCBase::leave_() {
    auto* awareness = mActor->getAwareness();
    if (!awareness || _40)
        return;
    awareness->disable();
}

void HorseRiddenByNPCBase::loadParams_() {
    getStaticParam(&mIsEscapeFromSameActorType_s, "IsEscapeFromSameActorType");
}

}  // namespace uking::ai
