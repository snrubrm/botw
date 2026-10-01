#include "Game/AI/Action/actionSetImpulseDamageMin.h"
#include "KingSystem/Resource/Actor/resResourceGParamList.h"
#include "KingSystem/Resource/GeneralParamList/resGParamListObjectAttack.h"
#include "KingSystem/ActorSystem/actActorParam.h"
#include "KingSystem/ActorSystem/actActor.h"

namespace uking::action {

SetImpulseDamageMin::SetImpulseDamageMin(const InitArg& arg) : ksys::act::ai::Action(arg) {}

SetImpulseDamageMin::~SetImpulseDamageMin() = default;

bool SetImpulseDamageMin::init_(sead::Heap* heap) {
    return ksys::act::ai::Action::init_(heap);
}

void SetImpulseDamageMin::enter_(ksys::act::ai::InlineParamPack* params) {
    ksys::act::ai::Action::enter_(params);
}

void SetImpulseDamageMin::leave_() {
    ksys::act::ai::Action::leave_();
}

void SetImpulseDamageMin::loadParams_() {
    getStaticParam(&mReactionLevel_s, "ReactionLevel");
    getStaticParam(&mIsGuardable_s, "IsGuardable");
    getStaticParam(&mIsGuarantee_s, "IsGuarantee");
}

void SetImpulseDamageMin::calc_() {
    ksys::act::ai::Action::calc_();
}

float SetImpulseDamageMin::m32() {
    return mActor->getParam()->getRes().mGParamList->getAttack()->mPower.ref();
}

}  // namespace uking::action
