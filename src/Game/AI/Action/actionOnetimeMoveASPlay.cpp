#include "Game/AI/Action/actionOnetimeMoveASPlay.h"
#include <math/seadMathCalcCommon.h>
#include <prim/seadStringUtil.h>
#include "Game/AI/aiUnk_71005D6D10.h"
#include "Game/AI/aiUnk_71007377D4.h"
#include "KingSystem/ActorSystem/AS/ASList.h"
#include "KingSystem/ActorSystem/actActor.h"
#include "KingSystem/Physics/CharacterController/physCharacterController.h"

namespace uking::action {

OnetimeMoveASPlay::OnetimeMoveASPlay(const InitArg& arg) : OnetimeStopASPlay(arg) {}

OnetimeMoveASPlay::~OnetimeMoveASPlay() = default;

void OnetimeMoveASPlay::enter_(ksys::act::ai::InlineParamPack* params) {
    OnetimeStopASPlay::enter_(params);
    _50.value = 0;
    _50.prev_value = 0;
    mActor->getMtx().getBase(_5c, 2);
    if (*mIsChangable_s)
        mFlags.set(Flag::Changeable);
}

void OnetimeMoveASPlay::leave_() {
    OnetimeStopASPlay::leave_();
}

void OnetimeMoveASPlay::loadParams_() {
    OnetimeStopASPlay::loadParams_();
    getStaticParam(&mIsChangable_s, "IsChangable");
}

// NON_MATCHING: the original keeps `&_50` in a callee-saved register (pre-indexed store) and does not merge the
// value / prev_value stores into one stp.
void OnetimeMoveASPlay::calc_() {
    ksys::as::ASList::Unk4 query;
    ksys::phys::CharacterController* controller;
    if (sub_71005DD5B0(mActor, 47, &query, 0, 0)) {
        const f32 rate =
            sead::StringUtil::parseF32(query.name) / sead::Mathf::clampMin(query._10, 1.0f);
        _50.value = rate;
        _50.prev_value = rate;
        controller = mActor->getCharacterController();
    } else if (sub_71005DD798(mActor, 47, nullptr, 0, 0)) {
        controller = mActor->getCharacterController();
    } else {
        OnetimeStopASPlay::calc_();
        return;
    }
    if (controller) {
        _50.updateStats();
        controller->sub_7100F5E7F0(_50.value * 30.0f);
        sub_710072C1B4(controller, _5c);
    }
    if (auto* cc = mActor->getCharacterController())
        sub_7100738660(cc, 0.1f);
}

}  // namespace uking::action
