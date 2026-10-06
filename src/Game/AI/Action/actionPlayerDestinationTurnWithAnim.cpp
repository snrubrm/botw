#include "Game/AI/Action/actionPlayerDestinationTurnWithAnim.h"
#include "KingSystem/ActorSystem/Profiles/actPlayer.h"
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

// NON_MATCHING: scheduling: the original loads the ASList and the member strings after the m35() test, calls
// assureTermination of mASName_d before x_1 and keeps `this` in x19 / `&mASName_d` in x20.
void PlayerDestinationTurnWithAnim::m33() {
    if (mASName_d == "GrabPut")
        mActor->getASList()->goLimpFromHeadShotMaybe(0x31, "Pouch", 0);
    if (!m35()) {
        if (mActor->getASList()->x_1(0, 0) != mASName_d) {
            static_cast<ksys::act::Player*>(mActor)->switchToAnimSequenceMaybe(mASName_d.cstr(), true, -1.0f);
            static_cast<ksys::act::Player*>(mActor)->sub_7100855F80(mASName_d.cstr());
        }
    } else {
        mActor->getASList()->startAnimationMaybe(-1.0f, -1.0f, sead::SafeString(mASName_d.cstr()), 0, 0, true);
    }
}

}  // namespace uking::action
