#include "Game/AI/Action/actionPlayerStoleOpenBase.h"
#include "KingSystem/ActorSystem/actActor.h"
#include "KingSystem/ActorSystem/actPlayerInfo.h"

namespace uking::action {

PlayerStoleOpenBase::PlayerStoleOpenBase(const InitArg& arg) : ActionEx(arg) {}

// NON_MATCHING: the original loads the three rotation angles before the sinf/cosf calls (as if
// copied to a local first); ours reloads them between the calls
void PlayerStoleOpenBase::enter_(ksys::act::ai::InlineParamPack* params) {
    m32();
    mFlags.set(Flag::Changeable);
    _38.x(ksys::act::PlayerInfo::getSomeProcLink());
    _38._28 = mBoneName_s;
    _38._30.getKey().reset();
    _38._68.makeRT(*mRotOffsetXyz_s, *mPosOffset_s);
    mActor->sub_71011DA824(&_38);
}

void PlayerStoleOpenBase::leave_() {
    mActor->sub_71011DA834(&_38);
}

void PlayerStoleOpenBase::loadParams_() {
    getStaticParam(&mBoneName_s, "BoneName");
    getStaticParam(&mPosOffset_s, "PosOffset");
    getStaticParam(&mRotOffsetXyz_s, "RotOffsetXyz");
}

void PlayerStoleOpenBase::calc_() {
    if (isFinishedAS(0, 0))
        setFinished();
}

}  // namespace uking::action
