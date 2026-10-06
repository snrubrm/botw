#include "Game/AI/Action/actionPlayerBackJump.h"
#include "Game/AI/Action/actionPlayerSubjectWait.h"
#include "Game/Actor/actCameraUtil.h"
#include "KingSystem/ActorSystem/Profiles/actPlayer.h"

namespace uking::action {

PlayerSubjectWait::PlayerSubjectWait(const InitArg& arg) : PlayerAction(arg) {}

void PlayerSubjectWait::enter_(ksys::act::ai::InlineParamPack* params) {
    PlayerAction::enter_(params);
    static_cast<ksys::act::Player*>(mActor)->_cec.set(0x1);
    static_cast<ksys::act::Player*>(mActor)->_cf0.set(0x4);
    static_cast<ksys::act::Player*>(mActor)->_cf0.set(0x80000);
    static_cast<ksys::act::Player*>(mActor)->_cf4.set(0x400000);
    static_cast<ksys::act::PlayerBase*>(mActor)->_c44.setBit(15);
    auto* player = static_cast<ksys::act::Player*>(mActor);
    player->_20bc.value = 0;
    player->_20bc.prev_value = 0;
    if (static_cast<ksys::act::Player*>(mActor)->x_21())
        static_cast<ksys::act::Player*>(mActor)->x_8(false, false);
    if (static_cast<ksys::act::PlayerBase*>(mActor)->_d11)
        static_cast<ksys::act::Player*>(mActor)->m228(false);
    if (sub_71007D86B4(static_cast<ksys::act::Player*>(mActor)))
        static_cast<ksys::act::Player*>(mActor)->x_18(true);
    static_cast<ksys::act::Player*>(mActor)->x_23("ItemScopeReady", false, -1.0f);
}

void PlayerSubjectWait::leave_() {
    static_cast<ksys::act::PlayerBase*>(mActor)->_c44.resetBit(15);
    static_cast<ksys::act::Player*>(mActor)->_1c68 = static_cast<ksys::act::Player*>(mActor)->x_5();
    if (!static_cast<ksys::act::PlayerBase*>(mActor)->_d11)
        static_cast<ksys::act::Player*>(mActor)->x_18(true);
}

void PlayerSubjectWait::calc_() {
    auto* player = static_cast<ksys::act::Player*>(mActor);
    const auto angle = sub_710092DBA4();
    player->x_53(angle);
    if (static_cast<ksys::act::Player*>(mActor)->_c40.isOnBit(1) &&
        static_cast<ksys::act::Player*>(mActor)->_20bc.value != 0.0f) {
        setFinished();
    }
    static_cast<ksys::act::Player*>(mActor)->sub_71008911F0();
    static_cast<ksys::act::Player*>(mActor)->x_4();
    static_cast<ksys::act::Player*>(mActor)->sub_7100877E2C();
    static_cast<ksys::act::Player*>(mActor)->actionCommon();
    static_cast<ksys::act::Player*>(mActor)->sub_7100888D24();
    static_cast<ksys::act::Player*>(mActor)->sub_71008893B8(false);
    if (!static_cast<ksys::act::Player*>(mActor)->sub_710088873C()) {
        auto* p = static_cast<ksys::act::Player*>(mActor);
        if (p->_d30 == p->getEquipmentTypeName(0)) {
            p = static_cast<ksys::act::Player*>(mActor);
            if (p->_d68 == p->getEquipmentTypeName(0))
                return;
        }
        setFinished();
    }
}

bool PlayerSubjectWait::isChangeable() const {
    return true;
}

}  // namespace uking::action
