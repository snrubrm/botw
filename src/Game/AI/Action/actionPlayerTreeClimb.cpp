#include "Game/AI/Action/actionPlayerTreeClimb.h"
#include "Game/Actor/actCameraUtil.h"
#include "KingSystem/ActorSystem/AS/ASList.h"
#include "KingSystem/ActorSystem/Profiles/actPlayer.h"
#include "KingSystem/ActorSystem/actActor.h"
#include "KingSystem/Utils/MathUtil.h"

namespace uking::action {

PlayerTreeClimb::PlayerTreeClimb(const InitArg& arg) : PlayerAction(arg) {}

// NON_MATCHING: stack slots of the x_5() result and `angle` are swapped (matches with a dummy
// `Unk1 angle(0);` declared before the x_5() call and assigned afterwards)
void PlayerTreeClimb::enter_(ksys::act::ai::InlineParamPack* params) {
    const bool flag = static_cast<ksys::act::Player*>(mActor)->m186();
    PlayerAction::enter_(params);
    static_cast<ksys::act::Player*>(mActor)->_cf4.set(0x2);
    static_cast<ksys::act::Player*>(mActor)->_cec.set(0x1);
    static_cast<ksys::act::Player*>(mActor)->_cf0.set(0x200);
    if (auto* info = static_cast<ksys::act::Player*>(mActor)->getAttachedTargetActor2()->mAttachInfo) {
        auto* player = static_cast<ksys::act::Player*>(mActor);
        player->_1810 = info->_140;
        player = static_cast<ksys::act::Player*>(mActor);
        player->_181c = player->_1770;
        static_cast<ksys::act::Player*>(mActor)->_17f0 = 0;
        static_cast<ksys::act::Player*>(mActor)->_1834 = sub_710092DBA4();
    }
    static_cast<ksys::act::Player*>(mActor)->switchToAnimSequenceMaybe("ClimbTreeTopSharp", true,
                                                                       -1.0f);
    if (flag) {
        auto* player = static_cast<ksys::act::Player*>(mActor);
        const u32 reversed = player->x_5().value ^ 0x80000000u;
        const ksys::act::Player::Unk1 angle(ksys::util::sUnk_7101EC6BA0 & reversed);
        player->x_53(angle);
        auto* as_list = mActor->getASList();
        const f32 value = as_list->sub_710115EC98(6, nullptr, 0);
        as_list->x_6(6, 0, value + 180.0f);
    }
    static_cast<ksys::act::Player*>(mActor)->x_8(false, false);
    auto* player = static_cast<ksys::act::Player*>(mActor);
    player->_20bc.value = 0;
    player->_20bc.prev_value = 0;
    static_cast<ksys::act::Player*>(mActor)->getAttachedTargetActor2()->sub_7100EB5634();
}

void PlayerTreeClimb::leave_() {
    static_cast<ksys::act::Player*>(mActor)->getAttachedTargetActor2()->sub_7100EB5644();
}

void PlayerTreeClimb::calc_() {
    PlayerAction::calc_();
}

bool PlayerTreeClimb::isChangeable() const {
    return _1c;
}

}  // namespace uking::action
