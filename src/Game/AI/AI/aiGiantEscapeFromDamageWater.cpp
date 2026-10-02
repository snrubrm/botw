#include "Game/AI/AI/aiGiantEscapeFromDamageWater.h"
#include "Game/AI/aiUnk_71005D6D10.h"
#include "KingSystem/ActorSystem/actActor.h"
#include "KingSystem/Physics/System/physNavMeshCharacter.h"

namespace uking::ai {

GiantEscapeFromDamageWater::GiantEscapeFromDamageWater(const InitArg& arg)
    : ksys::act::ai::Ai(arg) {}

GiantEscapeFromDamageWater::~GiantEscapeFromDamageWater() = default;

bool GiantEscapeFromDamageWater::init_(sead::Heap* heap) {
    sub_71005E2C58(mActor);
    return true;
}

void GiantEscapeFromDamageWater::enter_(ksys::act::ai::InlineParamPack* params) {
    sub_71003F6CF0();
    _38 = ksys::Timer(60, 60);
    changeChild("初回探索");
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
