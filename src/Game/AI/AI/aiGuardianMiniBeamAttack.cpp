#include "Game/AI/AI/aiGuardianMiniBeamAttack.h"
#include "Game/AI/aiUnk_71005D6D10.h"
#include "KingSystem/ActorSystem/AS/ASList.h"

namespace uking::ai {

GuardianMiniBeamAttack::GuardianMiniBeamAttack(const InitArg& arg) : MiniBeamAttack(arg) {}

// The SafeString members make the original keep the vtable store that a defaulted destructor drops;
// written as upstream's GameDataFlagSelector::~GameDataFlagSelector() { ; } (commit 96101229).
GuardianMiniBeamAttack::~GuardianMiniBeamAttack() { ; }

void GuardianMiniBeamAttack::enter_(ksys::act::ai::InlineParamPack* params) {
    MiniBeamAttack::enter_(params);
    _2c4 = ksys::Timer(*mAttackInterval_s, *mAttackInterval_s);
    if (*mAttackInterval_s >= 0)
        sub_710033F27C(0);
    if (isCurrentChild("戦闘準備")) {
        if (auto* as_list = mActor->getASList()) {
            if (!mLoopShaderASName_s.isEmpty())
                as_list->startAnimationMaybe(-1.0f, -1.0f, mLoopShaderASName_s.cstr(), 0, 1, true);
        }
    }
}

void GuardianMiniBeamAttack::leave_() {
    sub_71005DB498(mActor);
    MiniBeamAttack::leave_();
}

bool GuardianMiniBeamAttack::isChangeable() const {
    if (!*mIsChangeable_s)
        return false;
    return getCurrentChild()->isChangeable();
}

void GuardianMiniBeamAttack::loadParams_() {
    MiniBeamAttack::loadParams_();
    getStaticParam(&mHeadNodeName_s, "HeadNodeName");
    getStaticParam(&mAttackInterval_s, "AttackInterval");
    getStaticParam(&mEndShaderASFrame_s, "EndShaderASFrame");
    getStaticParam(&mLoopShaderASName_s, "LoopShaderASName");
    getStaticParam(&mEndShaderASName_s, "EndShaderASName");
    getStaticParam(&mPreLaunchEffectName_s, "PreLaunchEffectName");
    getStaticParam(&mIsChangeable_s, "IsChangeable");
    getStaticParam(&mIsFinalBattle_s, "IsFinalBattle");
    getStaticParam(&mInDirAngle_s, "InDirAngle");
}

}  // namespace uking::ai
