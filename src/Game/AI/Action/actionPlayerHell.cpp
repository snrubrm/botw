#include "Game/AI/Action/actionPlayerHell.h"
#include "Game/E3Mgr.h"
#include "KingSystem/ActorSystem/actCCAccessor.h"
#include "KingSystem/ActorSystem/AS/ASList.h"
#include "KingSystem/ActorSystem/Profiles/actPlayer.h"
#include "KingSystem/ActorSystem/actActor.h"
#include "KingSystem/Physics/CharacterController/physCharacterController.h"
#include "KingSystem/System/StageInfo.h"

namespace uking::action {

PlayerHell::PlayerHell(const InitArg& arg) : PlayerAction(arg) {}

void PlayerHell::enter_(ksys::act::ai::InlineParamPack* params) {
    PlayerAction::enter_(params);
}

// NON_MATCHING: the original tests the result of E3Mgr::isRidDemo() with `tbz w0` directly; ours emits `eor w8, w0, #1;
// tbnz` (inverted branch) for the same nested ifs. Everything else matches (the byte global 0x71025cc26e is
// ksys::StageInfo::sIsMainField, added to data_symbols.csv).
void PlayerHell::leave_() {
    static_cast<ksys::act::Player*>(mActor)->_c48.reset(0x80000);
    static_cast<ksys::act::Player*>(mActor)->_c48.reset(0x400000);
    static_cast<ksys::act::Player*>(mActor)->_c48.reset(0x80000000);
    if (E3Mgr::instance()) {
        if (E3Mgr::instance()->isRidDemo()) {
            if (ksys::StageInfo::sIsMainField && static_cast<ksys::act::Player*>(mActor)->_d18 == 0)
                E3Mgr::instance()->setIsRidDemo(true);
        }
    }
    static_cast<ksys::act::Player*>(mActor)->_d18 = -1;
    if (mActor->getASList()->x_1(3, 0) == "FaceFallinLava")
        static_cast<ksys::act::Player*>(mActor)->sub_7100855F80("FaceDefault");
    if (auto* controller = mActor->getCharacterController()) {
        controller->mFlags.set(8);
        controller->sub_7100F6059C();
        controller->sub_7100F5EEB8(1.0f);
        controller->sub_7100F5F458(ksys::act::MotionType::_0);
    }
}

void PlayerHell::loadParams_() {
    getDynamicParam(&mIsNoDamage_d, "IsNoDamage");
}

void PlayerHell::calc_() {
    PlayerAction::calc_();
}

bool PlayerHell::isChangeable() const {
    return false;
}

}  // namespace uking::action
