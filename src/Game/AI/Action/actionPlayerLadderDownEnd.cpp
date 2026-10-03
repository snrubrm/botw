#include "Game/AI/Action/actionPlayerLadderDownEnd.h"
#include <cmath>
#include "KingSystem/ActorSystem/AS/ASList.h"
#include "KingSystem/System/VFR.h"
#include "KingSystem/Utils/MathUtil.h"
#include "KingSystem/ActorSystem/actCCAccessor.h"
#include "KingSystem/Physics/CharacterController/physCharacterController.h"
#include "KingSystem/ActorSystem/actActor.h"
#include "KingSystem/ActorSystem/Profiles/actPlayer.h"

namespace uking::action {

PlayerLadderDownEnd::PlayerLadderDownEnd(const InitArg& arg) : PlayerAction(arg) {}

void PlayerLadderDownEnd::enter_(ksys::act::ai::InlineParamPack* params) {
    PlayerAction::enter_(params);
    static_cast<ksys::act::Player*>(mActor)->_cf0.set(0x200000);
    static_cast<ksys::act::Player*>(mActor)->_cec.set(0x10);
    static_cast<ksys::act::Player*>(mActor)->_cec.set(0x2);
    static_cast<ksys::act::Player*>(mActor)->_cf0.set(0x200);
    static_cast<ksys::act::Player*>(mActor)->sub_71008697E4();
    static_cast<ksys::act::Player*>(mActor)->switchToAnimSequenceMaybe("LadderDownEd", true, -1.0f);
}

void PlayerLadderDownEnd::leave_() {
    if (auto* controller = mActor->getCharacterController()) {
        controller->sub_7100F5F458(ksys::act::MotionType::_1);
        controller->sub_7100F5F6FC(sead::Vector3f::zero);
    }
}

void PlayerLadderDownEnd::calc_() {
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
}

bool PlayerLadderDownEnd::isChangeable() const {
    return true;
}

bool PlayerLadderDownEnd::isFinished() const {
    return static_cast<ksys::act::Player*>(mActor)->isSurfingOnGround();
}

}  // namespace uking::action
