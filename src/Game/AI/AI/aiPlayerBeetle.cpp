#include "Game/AI/AI/aiPlayerBeetle.h"
#include "KingSystem/ActorSystem/Profiles/actPlayer.h"

namespace uking::ai {

PlayerBeetle::PlayerBeetle(const InitArg& arg) : ksys::act::ai::Ai(arg) {}

bool PlayerBeetle::isChangeable() const {
    return false;
}

bool PlayerBeetle::init_(sead::Heap* heap) {
    return ksys::act::ai::Ai::init_(heap);
}

void PlayerBeetle::enter_(ksys::act::ai::InlineParamPack* params) {
    ksys::act::ai::Ai::enter_(params);
}

// NON_MATCHING: the original calls getEquipmentTypeName before loading mActor for _d30 (lane2 log)
void PlayerBeetle::leave_() {
    static_cast<ksys::act::Player*>(mActor)->_d30.copy(
        static_cast<ksys::act::Player*>(mActor)->getEquipmentTypeName(0));
    static_cast<ksys::act::Player*>(mActor)->x_18(true);
}

}  // namespace uking::ai
