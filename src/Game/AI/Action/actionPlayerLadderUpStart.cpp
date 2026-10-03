#include "Game/AI/Action/actionPlayerLadderUpStart.h"
#include "KingSystem/ActorSystem/AS/ASList.h"
#include "KingSystem/ActorSystem/Profiles/actPlayer.h"
#include "KingSystem/ActorSystem/actActor.h"
#include "Game/AI/aiUnk_7101e7c5d0.h"
#include "KingSystem/System/VFR.h"
#include "KingSystem/Utils/MathUtil.h"

namespace uking::action {

PlayerLadderUpStart::PlayerLadderUpStart(const InitArg& arg) : PlayerAction(arg) {}

void PlayerLadderUpStart::enter_(ksys::act::ai::InlineParamPack* params) {
    PlayerAction::enter_(params);
    static_cast<ksys::act::Player*>(mActor)->_cf0.set(0x200000);
    static_cast<ksys::act::Player*>(mActor)->_cec.set(0x10);
    static_cast<ksys::act::Player*>(mActor)->_cf0.set(0x200);
    static_cast<ksys::act::Player*>(mActor)->sub_71008697E4();

    auto* player = static_cast<ksys::act::Player*>(mActor);
    player->_181c = player->_1770;
    player = static_cast<ksys::act::Player*>(mActor);
    const u32 reversed = player->_1c84 ^ 0x80000000u;
    const ksys::act::Player::Unk1 angle(ksys::util::sUnk_7101EC6BA0 & reversed);
    player->x_53(angle);
    player = static_cast<ksys::act::Player*>(mActor);
    const u32 reversed2 = player->_1c84 ^ 0x80000000u;
    player->_1c68.value = ksys::util::sUnk_7101EC6BA0 & reversed2;
    player = static_cast<ksys::act::Player*>(mActor);
    player->_1810 = player->_22f4;
    player = static_cast<ksys::act::Player*>(mActor);
    ksys::util::sub_71011EEEE0(&player->_1810, player->_1c84, sUnk_7101e7c5d4);
    while (static_cast<ksys::act::Player*>(mActor)->_1810.y <
           static_cast<ksys::act::Player*>(mActor)->_1770.y) {
        static_cast<ksys::act::Player*>(mActor)->_1810.y += sUnk_7101e7c5d0;
    }
    static_cast<ksys::act::Player*>(mActor)->switchToAnimSequenceMaybe("LadderUpReadySt", true,
                                                                       -1.0f);

    const f32 time = mActor->getASList()->x_5(0, 0, &ksys::as::ASList::Unk2::sub_710116323C);
    player = static_cast<ksys::act::Player*>(mActor);
    const sead::Vector3f to_target = player->_1810 - player->_181c;
    const f32 length = sead::Mathf::sqrt(to_target.x * to_target.x + to_target.z * to_target.z);
    const sead::Vector3f velocity = to_target * (1.0f / time);
    static_cast<ksys::act::Player*>(mActor)->_1828 = velocity;
    const f32 min_length = sUnk_7101e7c5c4;
    player = static_cast<ksys::act::Player*>(mActor);
    if (length < min_length) {
        player->getASList()->x_6(9, 0, 0.0f);
        return;
    }
    sead::Vector3f axis;
    player->_1b18.getBase(axis, 0);
    axis.normalize();
    if (axis.dot(to_target) > 0.0f)
        mActor->getASList()->x_6(9, 0, -90.0f);
    else
        mActor->getASList()->x_6(9, 0, 90.0f);
}

void PlayerLadderUpStart::leave_() {}

void PlayerLadderUpStart::loadParams_() {
    getStaticParam(&mJumpHeight_s, "JumpHeight");
}

void PlayerLadderUpStart::calc_() {
    auto* player = static_cast<ksys::act::Player*>(mActor);
    player->_181c += player->_1828 * ksys::VFR::instance()->getDeltaFrame();
    player = static_cast<ksys::act::Player*>(mActor);
    player->sub_7100892100(player->_181c);
    if (mActor->getASList()->x_4(0, 0))
        setFinished();
}

bool PlayerLadderUpStart::isChangeable() const {
    return false;
}

}  // namespace uking::action
