#include "Game/AI/Action/actionPlayerSpAttack.h"
#include "KingSystem/ActorSystem/Profiles/actPlayer.h"
#include "KingSystem/ActorSystem/AS/ASList.h"
#include "KingSystem/ActorSystem/actActor.h"
#include "Game/AI/aiUnk_71005D6D10.h"
#include "Game/Actor/actWeapon.h"
#include "KingSystem/Utils/MathUtil.h"

namespace uking::action {

PlayerSpAttack::PlayerSpAttack(const InitArg& arg) : PlayerAction(arg) {}

void PlayerSpAttack::enter_(ksys::act::ai::InlineParamPack* params) {
    PlayerAction::enter_(params);
}

void PlayerSpAttack::leave_() {
    static_cast<ksys::act::Player*>(mActor)->_14c0 = 0;
    if (static_cast<ksys::act::Player*>(mActor)->sub_7100888294()) {
        auto* p = static_cast<ksys::act::Player*>(mActor);
        if (p->_d30 == p->getEquipmentTypeName(1)) {
            if (static_cast<ksys::act::Player*>(mActor)->_d24 == 0)
                static_cast<ksys::act::Player*>(mActor)->x_7();
        }
    }
    auto* player = static_cast<ksys::act::Player*>(mActor);
    sub_71005D79AC(player, player->playerWeapons_return0(), act::Unk_71002edaec(1));
}

void PlayerSpAttack::loadParams_() {
    getStaticParam(&mSwordSearchFrame_s, "SwordSearchFrame");
    getStaticParam(&mSwordSearchAngle_s, "SwordSearchAngle");
}

void PlayerSpAttack::calc_() {
    PlayerAction::calc_();
}

bool PlayerSpAttack::isChangeable() const {
    return _1c;
}

}  // namespace uking::action
