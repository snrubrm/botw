#include "Game/AI/AI/aiGiantEscapeFromDamageWater.h"
#include "KingSystem/ActorSystem/actActor.h"
#include "KingSystem/Physics/System/physNavMeshCharacter.h"

namespace uking::ai {

GiantEscapeFromDamageWater::GiantEscapeFromDamageWater(const InitArg& arg)
    : ksys::act::ai::Ai(arg) {}

GiantEscapeFromDamageWater::~GiantEscapeFromDamageWater() = default;

bool GiantEscapeFromDamageWater::init_(sead::Heap* heap) {
    return ksys::act::ai::Ai::init_(heap);
}

void GiantEscapeFromDamageWater::enter_(ksys::act::ai::InlineParamPack* params) {
    ksys::act::ai::Ai::enter_(params);
}

void GiantEscapeFromDamageWater::leave_() {
    ksys::act::ai::Ai::leave_();
}

void GiantEscapeFromDamageWater::loadParams_() {}

bool GiantEscapeFromDamageWater::isChangeable() const {
    if (isCurrentChild("移動")) {
        if (auto* nav = mActor->m45())
            return ksys::act::ai::Ai::isChangeable() && (nav->_2a4 & 0xffff) != 0x17;
    }
    return ksys::act::ai::Ai::isChangeable();
}

}  // namespace uking::ai
