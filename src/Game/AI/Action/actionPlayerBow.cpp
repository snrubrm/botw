#include "Game/AI/Action/actionPlayerBow.h"
#include <gfx/seadCamera.h>
#include "KingSystem/ActorSystem/Profiles/actPlayer.h"
#include "KingSystem/System/CameraMgr.h"

namespace uking::action {

PlayerBow::PlayerBow(const InitArg& arg) : PlayerAction(arg) {}

void PlayerBow::enter_(ksys::act::ai::InlineParamPack* params) {
    PlayerAction::enter_(params);
    static_cast<ksys::act::Player*>(mActor)->_cec.set(0x20000000);
    static_cast<ksys::act::Player*>(mActor)->_cec.set(0x10000000);
    static_cast<ksys::act::Player*>(mActor)->_cec.set(0x8000000);
    static_cast<ksys::act::Player*>(mActor)->_cf0.set(0x4);
    static_cast<ksys::act::Player*>(mActor)->_cf4.set(0x400000);
    static_cast<ksys::act::Player*>(mActor)->_1844 = ksys::Timer(0, 0);
    static_cast<ksys::act::Player*>(mActor)->_17f0 = 0;
}

void PlayerBow::leave_() {}

// NON_MATCHING: the original keeps the discarded `(at - pos).length()` of the look-at camera (loads, subtractions and the
// sqrtf fallback call); the dead computation is removed from ours
void PlayerBow::calc_() {
    auto* player = static_cast<ksys::act::Player*>(mActor);
    const f32 time = player->_1844.value;
    if ((time <= 15.0f && time > 12.0f) || (time <= 9.0f && time > 6.0f) ||
        (time <= 3.0f && time > 0.0f)) {
        // Both the camera lookup and the distance are unused in the original (the sqrtf call is kept).
        auto* camera = ksys::CameraMgr::instance()->getLookAtCamera();
        (camera->getAt() - camera->getPos()).length();
    }
    static_cast<ksys::act::Player*>(mActor)->_1844.update();
    static_cast<ksys::act::Player*>(mActor)->sub_71008824AC(false);
    static_cast<ksys::act::Player*>(mActor)->_c50.setBit(15);
    if (static_cast<ksys::act::Player*>(mActor)->_1f88 != 5)
        static_cast<ksys::act::Player*>(mActor)->x_4();
    auto* p = static_cast<ksys::act::Player*>(mActor);
    if (p->_17f0) {
        if (p->sub_7100848F5C() || !static_cast<ksys::act::Player*>(mActor)->m179())
            setFinished();
    } else {
        p->_17f0 = 1;
    }
    static_cast<ksys::act::Player*>(mActor)->actionCommon();
}

bool PlayerBow::isChangeable() const {
    return true;
}

}  // namespace uking::action
