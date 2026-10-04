#include "Game/AI/Action/actionPlayerWakeBoardGoal.h"
#include "KingSystem/ActorSystem/Profiles/actPlayer.h"
#include "KingSystem/ActorSystem/AS/ASList.h"
#include "KingSystem/ActorSystem/actUnk_71024ef620.h"
#include "KingSystem/Physics/CharacterController/physCharacterController.h"

namespace uking::action {

PlayerWakeBoardGoal::PlayerWakeBoardGoal(const InitArg& arg) : PlayerAction(arg) {}

PlayerWakeBoardGoal::~PlayerWakeBoardGoal() = default;

void PlayerWakeBoardGoal::enter_(ksys::act::ai::InlineParamPack* params) {
    PlayerAction::enter_(params);
    static_cast<ksys::act::Player*>(mActor)->_cf0.set(0x800000);
    static_cast<ksys::act::Player*>(mActor)->_cec.set(0x20000);
    mActor->getASList()->sub_710115BC28(mASName_d.cstr(), -1.0f);
}

void PlayerWakeBoardGoal::leave_() {
    auto* as_list = mActor->getASList();
    if (as_list && as_list->_163 & 2)
        as_list->sub_710115C11C();
}

void PlayerWakeBoardGoal::loadParams_() {
    getDynamicParam(&mASName_d, "ASName");
}

// NON_MATCHING: actor load crosses the string termination check and compare registers differ.
void PlayerWakeBoardGoal::calc_() {
    const char* as_name = mASName_d.cstr();
    if (mActor->getASList()->x_1(0, 0) != as_name)
        mActor->getASList()->sub_710115BC28(mASName_d.cstr(), -1.0f);
    auto* player = static_cast<ksys::act::Player*>(mActor);
    player->_20bc.value = 0;
    player->_20bc.prev_value = 0;
    auto* surfing = static_cast<ksys::act::Player*>(mActor)->getAttachedTargetActor2()->_c0;
    if (surfing && surfing->_30) {
        surfing->sub_7100EBA9F0(mActor->getASList(), static_cast<ksys::act::Player*>(mActor)->_cec.isOnBit(17));
        if (auto* controller = mActor->getCharacterController()) {
            sead::Vector3f velocity;
            controller->sub_7100F5F598(&velocity);
            static_cast<ksys::act::Player*>(mActor)->_1c68 = ksys::util::Unk_7101EC6BAC(sead::Mathf::atan2Idx(velocity.x, velocity.z));
        }
    }
    setFinished();
}

bool PlayerWakeBoardGoal::isChangeable() const {
    return false;
}

}  // namespace uking::action
