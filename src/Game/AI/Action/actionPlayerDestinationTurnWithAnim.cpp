#include "Game/AI/Action/actionPlayerDestinationTurnWithAnim.h"
#include "KingSystem/ActorSystem/actActor.h"
#include "KingSystem/ActorSystem/AS/ASList.h"

namespace uking::action {

PlayerDestinationTurnWithAnim::PlayerDestinationTurnWithAnim(const InitArg& arg)
    : PlayerDestinationTurn(arg) {}

PlayerDestinationTurnWithAnim::~PlayerDestinationTurnWithAnim() = default;

bool PlayerDestinationTurnWithAnim::init_(sead::Heap* heap) {
    return PlayerDestinationTurn::init_(heap);
}

void PlayerDestinationTurnWithAnim::enter_(ksys::act::ai::InlineParamPack* params) {
    PlayerDestinationTurn::enter_(params);
}

void PlayerDestinationTurnWithAnim::leave_() {
    PlayerDestinationTurn::leave_();
}

void PlayerDestinationTurnWithAnim::loadParams_() {
    PlayerDestinationTurn::loadParams_();
    getDynamicParam(&mIsWaitASFinish_d, "IsWaitASFinish");
    getDynamicParam(&mUsePartBind_d, "UsePartBind");
    getDynamicParam(&mASName_d, "ASName");
}

void PlayerDestinationTurnWithAnim::calc_() {
    PlayerDestinationTurn::calc_();
}

bool PlayerDestinationTurnWithAnim::m35() {
    return *mUsePartBind_d;
}

bool PlayerDestinationTurnWithAnim::m34() {
    if (*mIsWaitASFinish_d)
        return mActor->getASList()->x_4(0, 0);
    return true;
}

}  // namespace uking::action
