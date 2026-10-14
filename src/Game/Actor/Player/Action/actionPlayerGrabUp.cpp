#include "Game/Actor/Player/Action/actionPlayerGrabUp.h"
#include "KingSystem/ActorSystem/Profiles/actPlayer.h"
#include "KingSystem/ActorSystem/AS/ASList.h"
#include "KingSystem/ActorSystem/Attention/actAttentionSingleton.h"
#include "KingSystem/ActorSystem/actActorLinkConstDataAccess.h"

namespace uking::action {

PlayerGrabUp::PlayerGrabUp(const InitArg& arg) : PlayerAction(arg) {}

void PlayerGrabUp::enter_(ksys::act::ai::InlineParamPack* params) {
    const bool flag = static_cast<ksys::act::Player*>(mActor)->m199();
    PlayerAction::enter_(params);
    static_cast<ksys::act::Player*>(mActor)->_cec.set(1);
    static_cast<ksys::act::Player*>(mActor)->_cec.set(0x20);
    if (flag) {
        static_cast<ksys::act::Player*>(mActor)->_c4c.set(0x4000);
        static_cast<ksys::act::Player*>(mActor)->_17f0 = 0;
        static_cast<ksys::act::Player*>(mActor)->_17f2 = true;
        static_cast<ksys::act::Player*>(mActor)->sub_710088755C();
        ksys::act::ActorLinkConstDataAccess accessor;
        ksys::act::Attention::instance()->sub_7100D7482C(&accessor);
        const f32 y = accessor.getActorMtx()(1, 3);
        mActor->getASList()->x_6(0x10, 0, y - static_cast<ksys::act::Player*>(mActor)->_1770.y);
    } else {
        static_cast<ksys::act::Player*>(mActor)->_17f0 = 1;
        static_cast<ksys::act::Player*>(mActor)->_17f2 = false;
    }
    static_cast<ksys::act::Player*>(mActor)->_17f1 = false;
    static_cast<ksys::act::Player*>(mActor)->switchToAnimSequenceMaybe("GrabUp", true, -1.0f);
    static_cast<ksys::act::Player*>(mActor)->_c40.set(0x20000);
}

void PlayerGrabUp::leave_() {
    static_cast<ksys::act::Player*>(mActor)->_c4c.reset(0x4000);
}

void PlayerGrabUp::calc_() {
    PlayerAction::calc_();
}

bool PlayerGrabUp::isChangeable() const {
    return false;
}

}  // namespace uking::action
