#include "Game/AI/Action/actionPlayerGuardJust.h"
#include "KingSystem/ActorSystem/Profiles/actPlayer.h"
#include "Game/AI/aiUnk_71005D6D10.h"
#include "Game/Actor/actWeapon.h"
#include "KingSystem/ActorSystem/AS/ASList.h"
#include "KingSystem/ActorSystem/actActor.h"

namespace uking::action {

PlayerGuardJust::PlayerGuardJust(const InitArg& arg) : PlayerAction(arg) {}

void PlayerGuardJust::enter_(ksys::act::ai::InlineParamPack* params) {
    PlayerAction::enter_(params);
    static_cast<ksys::act::Player*>(mActor)->_cec.set(0x10000000);
    static_cast<ksys::act::Player*>(mActor)->_cf4.set(0x4000000);
    static_cast<ksys::act::Player*>(mActor)->switchToAnimSequenceMaybe("GuardJust", true, -1.0f);
}

void PlayerGuardJust::leave_() {
    auto* player = static_cast<ksys::act::Player*>(mActor);
    sub_71005D79AC(player, player->playerWeapons_return1(), act::Unk_71002edaec(1));
    static_cast<ksys::act::Player*>(mActor)->_c40.reset(0x20);
    static_cast<ksys::act::Player*>(mActor)->_c40.reset(0x10000);
    auto* p2 = static_cast<ksys::act::Player*>(mActor);
    p2->_20bc.value = 0;
    p2->_20bc.prev_value = 0;
    static_cast<ksys::act::Player*>(mActor)->_1d70 = ksys::Timer(0, 0);
}

void PlayerGuardJust::loadParams_() {
    getStaticParam(&mForceSlowTime_s, "ForceSlowTime");
}

// NON_MATCHING: the actor reload of the first two ASList queries is hoisted in ours (not in the original), and the
// stack slot of the `query` object is above the request object (below it in the original)
void PlayerGuardJust::calc_() {
    static_cast<ksys::act::Player*>(mActor)->sub_7100877BD8();
    if (mActor->getASList()->x(14, nullptr, 0, 0, &ksys::as::ASList::Unk2::sub_710116383C, true)) {
        static_cast<ksys::act::Player*>(mActor)->_c40.set(0x20);
    } else if (mActor->getASList()->x(14, nullptr, 0, 0, &ksys::as::ASList::Unk2::sub_710116388C, true)) {
        static_cast<ksys::act::Player*>(mActor)->_c40.reset(0x20);
    }
    ksys::as::ASList::Unk4 query;
    if (mActor->getASList()->x(3, &query, 0, 0, &ksys::as::ASList::Unk2::sub_710116383C, true)) {
        auto* player = static_cast<ksys::act::Player*>(mActor);
        sub_71005D7F4C(player, player->playerWeapons_return1(), 0, &query.name, nullptr, 1, 1.0f, 1.0f);
    } else if (mActor->getASList()->x(3, nullptr, 0, 0, &ksys::as::ASList::Unk2::sub_710116388C, true)) {
        auto* player = static_cast<ksys::act::Player*>(mActor);
        sub_71005D79AC(player, player->playerWeapons_return1(), act::Unk_71002edaec(1));
    }
    m32();
    static_cast<ksys::act::Player*>(mActor)->actionCommon();
}

bool PlayerGuardJust::isChangeable() const {
    return _1c;
}

}  // namespace uking::action
