#include "Game/AI/Action/actionPlayerGrabPut.h"
#include "Game/AI/aiUnk_71005D6D10.h"
#include "KingSystem/ActorSystem/AS/ASList.h"
#include "KingSystem/ActorSystem/Profiles/actPlayer.h"
#include "KingSystem/ActorSystem/actActor.h"

namespace uking::action {

PlayerGrabPut::PlayerGrabPut(const InitArg& arg) : PlayerAction(arg) {}

void PlayerGrabPut::enter_(ksys::act::ai::InlineParamPack* params) {
    PlayerAction::enter_(params);
}

void PlayerGrabPut::leave_() {
    static_cast<ksys::act::Player*>(mActor)->_14c0 = false;
    static_cast<ksys::act::Player*>(mActor)->x_19(-1.0f);
}

void PlayerGrabPut::loadParams_() {
    getStaticParam(&mPutStartFrmae_s, "PutStartFrmae");
}

void PlayerGrabPut::calc_() {
    auto* player = static_cast<ksys::act::Player*>(mActor);
    player->_20bc.value = 0;
    player->_20bc.prev_value = 0;
    if (!_28) {
        player = static_cast<ksys::act::Player*>(mActor);
        if (!(player->_1844.value <= sead::Mathf::epsilon())) {
            player->_1844.update();
            if (static_cast<ksys::act::Player*>(mActor)->_1844.value <= sead::Mathf::epsilon()) {
                if (auto* actor = sead::DynamicCast<ksys::act::Actor>(mActor->getConnectedCalcChild()))
                    sub_71005DC3CC(actor);
            }
        }
    }
    if (static_cast<ksys::act::Player*>(mActor)->_17f0) {
        if (static_cast<ksys::act::Player*>(mActor)->sub_7100857014(
                -1.0f, &static_cast<ksys::act::Player*>(mActor)->_1834, -1, -1)) {
            static_cast<ksys::act::Player*>(mActor)->x_19(-1.0f);
            static_cast<ksys::act::Player*>(mActor)->_17f0 = 0;
        }
    }
    static_cast<ksys::act::Player*>(mActor)->actionCommon();
    if (!_28) {
        if (mActor->getASList()->sub_710115FBC8(70, nullptr, &ksys::as::ASList::Unk2::sub_71011637EC,
                                                true)) {
            if (auto* actor = sead::DynamicCast<ksys::act::Actor>(mActor->getConnectedCalcChild()))
                sub_71005DC394(actor);
        }
    }
    if (mActor->getASList()->x_4(0, 0)) {
        static_cast<ksys::act::Player*>(mActor)->m228(false);
        setFinished();
    }
}

bool PlayerGrabPut::isChangeable() const {
    return false;
}

}  // namespace uking::action
