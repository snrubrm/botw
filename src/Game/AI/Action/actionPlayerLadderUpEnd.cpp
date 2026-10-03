#include "Game/AI/Action/actionPlayerLadderUpEnd.h"
#include <cmath>
#include "Game/AI/aiUnk_7101e7c5d0.h"
#include "KingSystem/ActorSystem/AS/ASList.h"
#include "KingSystem/ActorSystem/Profiles/actPlayer.h"
#include "KingSystem/ActorSystem/actActor.h"
#include "KingSystem/System/VFR.h"
#include "KingSystem/Utils/MathUtil.h"

namespace uking::action {

PlayerLadderUpEnd::PlayerLadderUpEnd(const InitArg& arg) : PlayerAction(arg) {}

void PlayerLadderUpEnd::enter_(ksys::act::ai::InlineParamPack* params) {
    PlayerAction::enter_(params);
    static_cast<ksys::act::Player*>(mActor)->_cf0.set(0x200000);
    static_cast<ksys::act::Player*>(mActor)->_cf0.set(0x200);
    static_cast<ksys::act::Player*>(mActor)->sub_71008697E4();
    static_cast<ksys::act::Player*>(mActor)->switchToAnimSequenceMaybe("LadderUpEd", true, -1.0f);
    auto* player = static_cast<ksys::act::Player*>(mActor);
    player->_181c.y = player->_2100 + sUnk_7101e7c5d0 * -4.0f;
}

void PlayerLadderUpEnd::leave_() {}

void PlayerLadderUpEnd::calc_() {
    const auto& mtx = static_cast<ksys::act::Player*>(mActor)->_1b18;
    sead::Vector3f dir;
    mtx.getBase(dir, 2);
    dir.normalize();
    const f32 angle = std::atan2(dir.x, dir.z);
    sead::Vector3f move = mActor->getASList()->sub_710115D2D4();
    ksys::util::sub_71011EF010(&move, angle);
    auto* player = static_cast<ksys::act::Player*>(mActor);
    player->_181c += move * ksys::VFR::instance()->getDeltaFrame();
    player = static_cast<ksys::act::Player*>(mActor);
    player->sub_7100892100(player->_181c);
    m32();
}

bool PlayerLadderUpEnd::isChangeable() const {
    return _1c;
}

}  // namespace uking::action
