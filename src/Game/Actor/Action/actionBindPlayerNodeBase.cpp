#include "Game/Actor/Action/actionBindPlayerNodeBase.h"
#include "KingSystem/ActorSystem/actActor.h"
#include "Game/Actor/Player/actPlayerInfo.h"

namespace uking::action {

BindPlayerNodeBase::BindPlayerNodeBase(const InitArg& arg) : ActionEx(arg) {}

void BindPlayerNodeBase::enter_(ksys::act::ai::InlineParamPack* params) {
    m32();
    mFlags.set(Flag::Changeable);
    _38.x(uking::act::PlayerInfo::getSomeProcLink());
    _38._28 = mBoneName_s;
    _38._30.getKey().reset();
    const sead::Vector3f rot = *mRotOffsetXyz_s;
    _38._68.makeRT(rot, *mPosOffset_s);
    mActor->sub_71011DA824(&_38);
}

void BindPlayerNodeBase::leave_() {
    mActor->sub_71011DA834(&_38);
}

void BindPlayerNodeBase::loadParams_() {
    getStaticParam(&mBoneName_s, "BoneName");
    getStaticParam(&mPosOffset_s, "PosOffset");
    getStaticParam(&mRotOffsetXyz_s, "RotOffsetXyz");
}

void BindPlayerNodeBase::calc_() {
    if (isFinishedAS(0, 0))
        setFinished();
}

}  // namespace uking::action
