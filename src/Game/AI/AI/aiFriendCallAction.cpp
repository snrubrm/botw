#include "Game/AI/AI/aiFriendCallAction.h"
#include "KingSystem/ActorSystem/actAiInlineParam.h"
#include "KingSystem/ActorSystem/actActorConstDataAccess.h"

namespace uking::ai {

FriendCallAction::FriendCallAction(const InitArg& arg) : ksys::act::ai::Ai(arg) {}

FriendCallAction::~FriendCallAction() = default;

bool FriendCallAction::init_(sead::Heap* heap) {
    return ksys::act::ai::Ai::init_(heap);
}

void FriendCallAction::enter_(ksys::act::ai::InlineParamPack* params) {
    _90.x();
    sub_71003DD74C();
}

void FriendCallAction::leave_() {
    ksys::act::ai::Ai::leave_();
}

void FriendCallAction::loadParams_() {
    getStaticParam(&mWeaponIdx_s, "WeaponIdx");
    getStaticParam(&mNearDistH_s, "NearDistH");
    getStaticParam(&mNearDistVMax_s, "NearDistVMax");
    getStaticParam(&mNearDistVMin_s, "NearDistVMin");
    getDynamicParam(&mTargetActor_d, "TargetActor");
}

bool FriendCallAction::handleMessage_(const ksys::Message& message) {
    _90.m2(message);
    if (*mTargetActor_d == _90._8)
        return true;
    _90.x();
    return false;
}

bool FriendCallAction::handleAck_(const ksys::MessageAck& ack) {
    return _60.sub_710070E070(ack);
}

void FriendCallAction::sub_71003DD74C() {
    sead::Vector3f target_pos;
    ksys::act::ActorConstDataAccess accessor;
    ksys::act::acquireActor(mTargetActor_d, &accessor);
    accessor.getActorMtx().getTranslation(target_pos);
    _60._18.x(mActor);
    _60.sub_710070DBB0(*accessor.getMessageTransceiverId(), true);
    _90.x();

    ksys::act::ai::InlineParamPack params;
    params.addVec3(target_pos, "TargetPos", -1);
    changeChild("呼ぶ", &params);
}

}  // namespace uking::ai
