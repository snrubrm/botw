#include "Game/AI/Action/actionPlayerCutHorseJumpLand.h"
#include "KingSystem/ActorSystem/AS/ASList.h"
#include "Game/Actor/actWeapon.h"
#include "Game/AI/aiUnk_71005D6D10.h"
#include "KingSystem/ActorSystem/Profiles/actPlayer.h"

namespace uking::action {

PlayerCutHorseJumpLand::PlayerCutHorseJumpLand(const InitArg& arg) : PlayerAction(arg) {}

void PlayerCutHorseJumpLand::enter_(ksys::act::ai::InlineParamPack* params) {
    PlayerAction::enter_(params);
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
