#include "Game/AI/Action/actionPlayerWakeBoardReady.h"
#include "KingSystem/ActorSystem/Profiles/actPlayer.h"
#include "KingSystem/ActorSystem/actActorConstDataAccess.h"
#include "KingSystem/ActorSystem/actUnk_71024ef620.h"

namespace uking::action {

PlayerWakeBoardReady::PlayerWakeBoardReady(const InitArg& arg) : PlayerAction(arg) {}

PlayerWakeBoardReady::~PlayerWakeBoardReady() = default;

// NON_MATCHING: boolean helper result and actor pointer use exchanged registers in the final store.
void PlayerWakeBoardReady::enter_(ksys::act::ai::InlineParamPack* params) {
    PlayerAction::enter_(params);
    static_cast<ksys::act::Player*>(mActor)->switchToAnimSequenceMaybe("WakeBoarding", true, -1);
    if (!mActor->getConnectedCalcChild()) {
        ksys::act::ActorConstDataAccess accessor;
        ksys::act::acquireActor(&static_cast<ksys::act::Player*>(mActor)->_2c38, &accessor);
        accessor.setThisActorAsChild(mActor, false);
        static_cast<ksys::act::Player*>(mActor)->_1870->_c0->_8 = mActor;
    }
    static_cast<ksys::act::Player*>(mActor)->_17f0 = sub_7100822E7C();
    static_cast<ksys::act::Player*>(mActor)->_17f1 = false;
    auto* player = static_cast<ksys::act::Player*>(mActor);
    player->_20bc.value = 0;
    player->_20bc.prev_value = 0;
}

void PlayerWakeBoardReady::leave_() {}

void PlayerWakeBoardReady::loadParams_() {
    getDynamicParam(&mCreateSelf_d, "CreateSelf");
    getDynamicParam(&mUniqueName_d, "UniqueName");
}

// NON_MATCHING: boolean helper result and actor pointer use exchanged registers in the fallback store.
void PlayerWakeBoardReady::calc_() {
    if (static_cast<ksys::act::Player*>(mActor)->_17f0) {
        if (!static_cast<ksys::act::Player*>(mActor)->_17f1) {
            if (mActor->getConnectedCalcChild()) {
                auto* surfing = static_cast<ksys::act::Player*>(mActor)->getAttachedTargetActor2()->_c0;
                if (surfing && !surfing->_60.isOn(1))
                    surfing->sub_7100EBA4C0();
                static_cast<ksys::act::Player*>(mActor)->_17f1 = true;
            }
        } else {
            static_cast<ksys::act::Player*>(mActor)->_cf0.set(0x800000);
            static_cast<ksys::act::Player*>(mActor)->_cec.set(0x20000);
            if (static_cast<ksys::act::Player*>(mActor)->sub_7100888294()) {
                static_cast<ksys::act::Player*>(mActor)->x_7();
                static_cast<ksys::act::Player*>(mActor)->_c40.reset(8);
            }
            auto* surfing = static_cast<ksys::act::Player*>(mActor)->getAttachedTargetActor2()->_c0;
            if (surfing) {
                if (!surfing->_60.isOn(4))
                    surfing->_60.set(8);
                surfing->sub_7100EBA9F0(mActor->getASList(), false);
            }
        }
        static_cast<ksys::act::Player*>(mActor)->actionCommon();
        setFinished();
    } else {
        static_cast<ksys::act::Player*>(mActor)->_17f0 = sub_7100822E7C();
    }
}

bool PlayerWakeBoardReady::isChangeable() const {
    return false;
}

}  // namespace uking::action
