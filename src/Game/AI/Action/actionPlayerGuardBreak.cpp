#include "Game/AI/Action/actionPlayerGuardBreak.h"
#include "KingSystem/ActorSystem/Profiles/actPlayer.h"
#include "KingSystem/ActorSystem/AS/ASList.h"
#include "KingSystem/ActorSystem/actActor.h"
#include "Game/AI/aiUnk_71005D6D10.h"
#include "Game/Actor/actWeapon.h"
#include "KingSystem/Utils/MathUtil.h"

namespace uking::action {

PlayerGuardBreak::PlayerGuardBreak(const InitArg& arg) : PlayerAction(arg) {}

void PlayerGuardBreak::enter_(ksys::act::ai::InlineParamPack* params) {
    PlayerAction::enter_(params);
    static_cast<ksys::act::Player*>(mActor)->_cf0.set(0x80);
    static_cast<ksys::act::Player*>(mActor)->_cf4.set(0x4000000);
    if (!static_cast<ksys::act::Player*>(mActor)->isSurfingOnGround())
        static_cast<ksys::act::Player*>(mActor)->_cec.set(0x2);
    if (!static_cast<ksys::act::Player*>(mActor)->_c40.isOnBit(3) &&
        static_cast<ksys::act::Player*>(mActor)->sub_7100888294()) {
        static_cast<ksys::act::Player*>(mActor)->x_7();
    }
    static_cast<ksys::act::Player*>(mActor)->sub_7100888278();
    const u32 angle = static_cast<ksys::act::Player*>(mActor)->x_5().value ^ 0x80000000;
    static_cast<ksys::act::Player*>(mActor)->_1c68 =
        ksys::util::Unk_7101EC6BAC(ksys::util::sUnk_7101EC6BA0 & angle);
    static_cast<ksys::act::Player*>(mActor)->switchToAnimSequenceMaybe("GuardBreak", true, -1.0f);
}

void PlayerGuardBreak::leave_() {}

void PlayerGuardBreak::loadParams_() {}

void PlayerGuardBreak::calc_() {
    if (static_cast<ksys::act::Player*>(mActor)->isSurfingOnGround())
        static_cast<ksys::act::Player*>(mActor)->_cec.resetBit(1);
    static_cast<ksys::act::Player*>(mActor)->sub_7100877BD8();
    m32();
    static_cast<ksys::act::Player*>(mActor)->actionCommon();
}

bool PlayerGuardBreak::isChangeable() const {
    return _1c;
}

}  // namespace uking::action
