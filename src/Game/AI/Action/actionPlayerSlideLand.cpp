#include "Game/AI/Action/actionPlayerSlideLand.h"
#include "KingSystem/ActorSystem/Profiles/actPlayer.h"
#include "KingSystem/ActorSystem/AS/ASList.h"
#include "KingSystem/ActorSystem/actActor.h"

namespace uking::action {

PlayerSlideLand::PlayerSlideLand(const InitArg& arg) : PlayerAction(arg) {}

void PlayerSlideLand::enter_(ksys::act::ai::InlineParamPack* params) {
    PlayerAction::enter_(params);
    static_cast<ksys::act::Player*>(mActor)->_cec.set(0x8000000);
    static_cast<ksys::act::Player*>(mActor)->_cf0.set(0x80);
    static_cast<ksys::act::Player*>(mActor)->switchToAnimSequenceMaybe("SlideLand", true, -1.0f);
    auto* player = static_cast<ksys::act::Player*>(mActor);
    player->_20bc.value *= 0.5f;
    player->_20bc.prev_value = player->_20bc.value;
}

void PlayerSlideLand::leave_() {
    static_cast<ksys::act::Player*>(mActor)->_1c68 = static_cast<ksys::act::Player*>(mActor)->x_5();
}

void PlayerSlideLand::calc_() {
    static_cast<ksys::act::Player*>(mActor)->_20bc.chase(0.0f, 0.04f);
    if (mActor->getASList()->x_4(0, 0)) {
        static_cast<ksys::act::Player*>(mActor)->_1c68 = static_cast<ksys::act::Player*>(mActor)->x_5();
        setFinished();
    } else if (mActor->getASList()->x(2, nullptr, 0, 0, &ksys::as::ASList::Unk2::sub_710116383C, true)) {
        _1c = true;
    }
    static_cast<ksys::act::Player*>(mActor)->actionCommon();
}

bool PlayerSlideLand::isChangeable() const {
    return _1c;
}

}  // namespace uking::action
