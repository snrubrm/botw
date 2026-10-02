#include "Game/AI/Action/actionPlayerCutHorseJumpLand.h"
#include "KingSystem/ActorSystem/AS/ASList.h"
#include "Game/Actor/actWeapon.h"
#include "Game/AI/aiUnk_71005D6D10.h"
#include "KingSystem/ActorSystem/Profiles/actPlayer.h"

namespace uking::action {

PlayerCutHorseJumpLand::PlayerCutHorseJumpLand(const InitArg& arg) : PlayerAction(arg) {}

// NON_MATCHING: block order of the two switchToAnimSequenceMaybe calls
void PlayerCutHorseJumpLand::enter_(ksys::act::ai::InlineParamPack* params) {
    PlayerAction::enter_(params);
    static_cast<ksys::act::Player*>(mActor)->_cec.set(0x1);
    const auto* life = mActor->getLife();
    if (life && *life <= 0)
        static_cast<ksys::act::Player*>(mActor)->switchToAnimSequenceMaybe("LandDamage", true, -1.0f);
    else
        static_cast<ksys::act::Player*>(mActor)->switchToAnimSequenceMaybe("CutJumpLandHorseRide", true,
                                                                       -1.0f);
    auto* player = static_cast<ksys::act::Player*>(mActor);
    player->_20bc.value = 0;
    player->_20bc.prev_value = 0;
    static_cast<ksys::act::Player*>(mActor)->actionCommon();
    static_cast<ksys::act::Player*>(mActor)->_c50.set(1);
}

void PlayerCutHorseJumpLand::leave_() {
    sub_71005D79AC(mActor, static_cast<ksys::act::Player*>(mActor)->playerWeapons_return0(), act::Unk_71002edaec(1));
}

void PlayerCutHorseJumpLand::calc_() {
    if (mActor->getASList()->x_4(0, 0)) {
        setFinished();
        return;
    }
    if (mActor->getASList()->x(2, nullptr, 0, 0, &ksys::as::ASList::Unk2::sub_710116383C, true)) {
        static_cast<ksys::act::Player*>(mActor)->_cec.set(0x8000000);
        _1c = true;
    }
}

bool PlayerCutHorseJumpLand::isChangeable() const {
    return _1c;
}

}  // namespace uking::action
