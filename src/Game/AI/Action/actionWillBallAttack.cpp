#include "Game/AI/Action/actionWillBallAttack.h"
#include "Game/AI/aiUnk_71005D6D10.h"
#include "KingSystem/ActorSystem/actActor.h"
#include "KingSystem/ActorSystem/actActorParam.h"
#include "KingSystem/Resource/Actor/resResourceGParamList.h"
#include "KingSystem/Resource/GeneralParamList/resGParamListObjectAttack.h"

namespace uking::action {

WillBallAttack::WillBallAttack(const InitArg& arg) : WillBallAction(arg) {}

WillBallAttack::~WillBallAttack() = default;

bool WillBallAttack::init_(sead::Heap* heap) {
    return WillBallAction::init_(heap);
}

// NON_MATCHING: the original tests bit 31 of the reaction param (`tst`) and selects the first argument with the same
// condition (`csel w1, w11, w11`); ours tests `< 0` (same shape as SetImpulseDamageMin::enter_)
void WillBallAttack::enter_(ksys::act::ai::InlineParamPack* params) {
    WillBallAction::enter_(params);
    const s32 power = s32(f32(mActor->getParam()->getRes().mGParamList->getAttack()->mPower.ref()));
    s32 level = sead::Mathi::min((power - 1) / 4, 2);
    if (power < -2)
        level = 0;
    const s32 reaction = *mReactionLevel_s;
    sub_71005DBC94(mActor, power, reaction < 0 ? level : reaction, *mIsAbleGuard_s, false, true,
                   false);
}

void WillBallAttack::leave_() {
    WillBallAction::leave_();
    sub_71005DC02C(mActor);
}

void WillBallAttack::loadParams_() {
    WillBallAction::loadParams_();
    getStaticParam(&mReactionLevel_s, "ReactionLevel");
    getStaticParam(&mIsAbleGuard_s, "IsAbleGuard");
}

void WillBallAttack::calc_() {
    WillBallAction::calc_();
}

}  // namespace uking::action
