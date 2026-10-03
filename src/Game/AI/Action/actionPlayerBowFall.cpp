#include "Game/AI/Action/actionPlayerBowFall.h"
#include "KingSystem/ActorSystem/Profiles/actPlayer.h"
#include "KingSystem/ActorSystem/AS/ASList.h"
#include "KingSystem/ActorSystem/actActor.h"

namespace uking::action {

PlayerBowFall::PlayerBowFall(const InitArg& arg) : PlayerFall(arg) {}

void PlayerBowFall::enter_(ksys::act::ai::InlineParamPack* params) {
    PlayerFall::enter_(params);
    static_cast<ksys::act::Player*>(mActor)->_cec.set(0x20000000);
    static_cast<ksys::act::Player*>(mActor)->_cf0.set(0x4);
}

void PlayerBowFall::leave_() {}

void PlayerBowFall::loadParams_() {
    PlayerFall::loadParams_();
}

// NON_MATCHING: the original loads the ASList and the member-function pointer in both arms of the speed selection
// (block layout / scheduling only)
void PlayerBowFall::calc_() {
    PlayerFall::calc_();
    auto* player = static_cast<ksys::act::Player*>(mActor);
    const f32 speed = player->_c40.isOnBit(13) ? player->m301() : 1.0f;
    player->getASList()->x_3(0, 0, &ksys::as::ASList::Unk2::sub_71011631BC, speed);
    player->getASList()->x_3(1, 0, &ksys::as::ASList::Unk2::sub_71011631BC, speed);
    if (static_cast<ksys::act::Player*>(mActor)->m179()) {
        if (ksys::act::playerIsReloadingOrChargingOrShootingBow(static_cast<ksys::act::Player*>(mActor))) {
            static_cast<ksys::act::Player*>(mActor)->x_37();
            static_cast<ksys::act::Player*>(mActor)->sub_71008824AC(false);
        }
        auto* p = static_cast<ksys::act::Player*>(mActor);
        if (p->_d30 == p->getEquipmentTypeName(0)) {
            if (!p->_c40.isOnBit(3)) {
                setFinished();
                return;
            }
        }
    }
    static_cast<ksys::act::Player*>(mActor)->actionCommon();
}

bool PlayerBowFall::isChangeable() const {
    return true;
}

}  // namespace uking::action
