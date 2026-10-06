#include "Game/AI/Action/actionPlayerAtnMove.h"
#include "KingSystem/ActorSystem/Profiles/actPlayer.h"
#include "KingSystem/ActorSystem/AS/ASList.h"
#include "KingSystem/ActorSystem/actActor.h"

namespace uking::action {

PlayerAtnMove::PlayerAtnMove(const InitArg& arg) : PlayerAction(arg) {}

void PlayerAtnMove::enter_(ksys::act::ai::InlineParamPack* params) {
    const bool a = static_cast<ksys::act::Player*>(mActor)->m188();
    PlayerAction::enter_(params);
    static_cast<ksys::act::Player*>(mActor)->_cec.set(0x8000000);
    static_cast<ksys::act::Player*>(mActor)->_cec.set(0x10000000);
    static_cast<ksys::act::Player*>(mActor)->_cf0.set(0x4);
    static_cast<ksys::act::Player*>(mActor)->_cf4.set(0x10);
    static_cast<ksys::act::Player*>(mActor)->_cf0.set(0x200);
    static_cast<ksys::act::Player*>(mActor)->_cf4.set(0x400000);
    static_cast<ksys::act::Player*>(mActor)->_cf4.set(0x2000);
    static_cast<ksys::act::Player*>(mActor)->_cf4.set(0x4000);
    auto* player = static_cast<ksys::act::Player*>(mActor);
    auto& chase_speed = player->_20bc;
    const f32 limit = player->sub_71008901D0();
    chase_speed.setToMin(limit);
    if (!a) {
        auto* p = static_cast<ksys::act::Player*>(mActor);
        if (p->_1dd0.value < 2.0f)
            p->_1dd0 = ksys::Timer(2.0f, 2.0f, -1.0f);
    }
    static_cast<ksys::act::Player*>(mActor)->_1810 = sead::Vector3f(0.0f, 1.0f, 0.0f);
    auto* p2 = static_cast<ksys::act::Player*>(mActor);
    if (p2->_c50.isOnBit(34)) {
        p2->_1e6c = 15.0f;
        p2->_1e70 = 15.0f;
    }
}

void PlayerAtnMove::leave_() {
    if (mActor->getASList()->x_1(1, 1) == "MoveAttentionUpper")
        static_cast<ksys::act::Player*>(mActor)->x_18(true);
    if (mActor->getASList()->x_1(1, 1) == "MoveUnsteadyUpper")
        static_cast<ksys::act::Player*>(mActor)->x_18(true);
}

void PlayerAtnMove::loadParams_() {}

void PlayerAtnMove::calc_() {
    PlayerAction::calc_();
}

bool PlayerAtnMove::isChangeable() const {
    return true;
}

}  // namespace uking::action
