#include "Game/AI/AI/aiPlayerBeetle.h"
#include "KingSystem/ActorSystem/Profiles/actPlayer.h"
#include "Game/UI/uiUtils.h"
#include "KingSystem/ActorSystem/AS/ASList.h"

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

// NON_MATCHING: the flag and VFR resets are combined and scheduled differently.
void PlayerBeetle::calc_() {
    if (handlePendingChildChange())
        return;
    if (isCurrentChild("ビートル操作")) {
        uking::ui::sub_7100A9BAEC(10);
        setFinished();
    }

    auto* child = getCurrentChild();
    if (!(child->isFinished() || child->isFailed()) || !isCurrentChild("構え"))
        return;

    auto* player = static_cast<ksys::act::Player*>(mActor);
    player->_cf4.makeAllZero();
    player->_cf8.makeAllZero();
    player->_cec.makeAllZero();
    player->_cf0.makeAllZero();
    player->_ce8 = 0;
    player->_cf0.setBit(20);
    player->_20bc.value = 0.0f;
    player->_20bc.prev_value = 0.0f;
    changeChild("ビートル操作");

    player = static_cast<ksys::act::Player*>(mActor);
    if (player->_cec.isOnBit(27) || player->_cf0.isOnBit(2) || player->_c50.isOnBit(26))
        return;
    if (player->getASList()->x_7(1, 1, &ksys::as::ASList::Unk2::sub_710002E82C))
        static_cast<ksys::act::Player*>(mActor)->x_18(true);
}

void PlayerBeetle::leave_() {
    const auto& name = static_cast<ksys::act::Player*>(mActor)->getEquipmentTypeName(0);
    static_cast<ksys::act::Player*>(mActor)->_d30.copy(name);
    static_cast<ksys::act::Player*>(mActor)->x_18(true);
}

}  // namespace uking::ai
