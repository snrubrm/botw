#include "Game/AI/AI/aiHorseLoopTarget.h"
#include "KingSystem/ActorSystem/actActor.h"
#include "KingSystem/Map/mapObject.h"

namespace uking::ai {

HorseLoopTarget::HorseLoopTarget(const InitArg& arg) : ksys::act::ai::Ai(arg) {}

HorseLoopTarget::~HorseLoopTarget() = default;

void HorseLoopTarget::enter_(ksys::act::ai::InlineParamPack* params) {
    ksys::act::ai::Ai::enter_(params);
}

ksys::map::Rail* HorseLoopTarget::m34() {
    auto* object = mActor->getMapObject();
    if (!object)
        return nullptr;
    if (!object->getRails_0())
        return nullptr;
    return *object->getRails_0();
}

void HorseLoopTarget::loadParams_() {
    getStaticParam(&mTargetName_s, "TargetName");
    getStaticParam(&mIsFlip_s, "IsFlip");
}

}  // namespace uking::ai
