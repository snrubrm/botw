#include "Game/AI/AI/aiPlayerItem.h"
#include "KingSystem/ActorSystem/Profiles/actPlayer.h"

namespace uking::ai {

PlayerItem::PlayerItem(const InitArg& arg) : ksys::act::ai::Ai(arg) {}

bool PlayerItem::isChangeable() const {
    return false;
}

bool PlayerItem::init_(sead::Heap* heap) {
    return ksys::act::ai::Ai::init_(heap);
}

void PlayerItem::enter_(ksys::act::ai::InlineParamPack* params) {
    if (hasPendingChildChange()) {
        changeChild(mPendingChildIdx);
        return;
    }
    auto* player = static_cast<ksys::act::Player*>(mActor);
    if (player->_d30 == player->getEquipmentTypeName(5))
        changeChild("マグネットグローブ");
}

void PlayerItem::calc_() {
    if (handlePendingChildChange())
        return;
    auto* player = static_cast<ksys::act::Player*>(mActor);
    if (player->_d30 == player->getEquipmentTypeName(5) && !isCurrentChild("マグネットグローブ"))
        changeChild("マグネットグローブ");
}

void PlayerItem::loadParams_() {}

}  // namespace uking::ai
