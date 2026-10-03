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
    if (hasPendingChildChange()) {
        changeChild(mPendingChildIdx);
        return;
    }
    changeChild("構え");
}

void PlayerBeetle::leave_() {
    const auto& name = static_cast<ksys::act::Player*>(mActor)->getEquipmentTypeName(0);
    static_cast<ksys::act::Player*>(mActor)->_d30.copy(name);
    static_cast<ksys::act::Player*>(mActor)->x_18(true);
}

}  // namespace uking::ai
