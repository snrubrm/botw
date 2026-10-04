#include "Game/AI/Action/actionSetImpulseDamageMin.h"
#include "Game/AI/aiUnk_71005D6D10.h"
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

// NON_MATCHING: the original tests bit 31 of the param (`tst`) and selects the first argument with the same condition
// (`csel w1, w9, w9`); ours tests `< 0`
void SetImpulseDamageMin::enter_(ksys::act::ai::InlineParamPack* params) {
    auto* actor = mActor;
    const s32 power = s32(m32());
    s32 level = sead::Mathi::min((power - 1) / 4, 2);
    if (power < -2)
        level = 0;
    const s32 reaction = *mReactionLevel_s;
    sub_71005DBC94(actor, power, reaction < 0 ? level : reaction, *mIsGuardable_s, *mIsGuarantee_s,
                   false, false);
    mFlags.set(Flag::Changeable);
}

void SetImpulseDamageMin::leave_() {
    sub_71005DC02C(mActor);
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
