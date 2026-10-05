#include "Game/AI/AI/aiWolfLinkBattleRoot.h"
#include <random/seadGlobalRandom.h>
#include "Game/Actor/actWolfLink.h"
#include "KingSystem/ActorSystem/actAiInlineParam.h"
#include "KingSystem/ActorSystem/actActorParam.h"
#include "KingSystem/Resource/Actor/resResourceGParamList.h"
#include "KingSystem/Resource/GeneralParamList/resGParamListObjectWolfLink.h"

namespace uking::ai {

WolfLinkBattleRoot::WolfLinkBattleRoot(const InitArg& arg) : ksys::act::ai::Ai(arg) {}

WolfLinkBattleRoot::~WolfLinkBattleRoot() = default;

bool WolfLinkBattleRoot::init_(sead::Heap* heap) {
    _60 = sead::DynamicCast<act::WolfLink>(mActor);
    if (!_60)
        return false;

    const auto* params = mActor->getParam()->getRes().mGParamList->getWolfLink();
    const f32 min = params->mAttackCounterLength.ref();
    const f32 max = min + params->mAttackCounterRand.ref();
    const s32 time = sead::GlobalRandom::instance()->getF32Range(min, max);
    _60->_e68 = ksys::Timer(time, time);
    return true;
}

void WolfLinkBattleRoot::enter_(ksys::act::ai::InlineParamPack* params) {
    ksys::act::ai::Ai::enter_(params);
}

// NON_MATCHING: parameter-pack frame layout and random-range arithmetic scheduling differ.
void WolfLinkBattleRoot::calc_() {
    if (!sub_7100601F84()) {
        setFinished();
        return;
    }
    if (!sub_7100602654() || !isCurrentChild("戦闘準備"))
        return;
    _60->sub_71002F3234(*mKeepTargetRange_d, 1337, 1, 3);
    if (!(_60->_e68.value <= sead::Mathf::epsilon()))
        return;
    if (sub_7100602CCC()) {
        if (sub_7100602E40()) {
            changeChild("戦闘連鎖攻撃", nullptr);
        } else {
            // The original constructs this actual pack despite passing no parameters.
            ksys::act::ai::InlineParamPack pack;
            changeChild("戦闘攻撃対地", nullptr);
        }
        return;
    }
    if (_60->sub_71002F420C())
        _5c += *mChanceToBarkOnAttackFail_s;
    if (sead::GlobalRandom::instance()->getF32Range(0.0f, 1.0f) <=
        *mChanceToBarkOnAttackFail_s + _5c) {
        _5c = 0;
        ksys::act::ai::InlineParamPack pack;
        pack.addVec3(_60->_c48._18, "TargetPos", -1);
        changeChild("戦闘攻撃できない", &pack);
    } else {
        const auto* params = mActor->getParam()->getRes().mGParamList->getWolfLink();
        const f32 min = params->mAttackCounterLength.ref();
        const s32 time = sead::GlobalRandom::instance()->getF32Range(
            min, min + params->mAttackCounterRand.ref());
        _60->_e68.reset(time);
    }
}

void WolfLinkBattleRoot::leave_() {
    _60->_e68.rate = 0;
    using Idx = act::WolfLink::Idx14f8;
    _60->_14f8[Idx(Idx::_6)].rate = 0;
}

void WolfLinkBattleRoot::loadParams_() {
    if (getStaticParam(&mAttackIntiationRange_s, "AttackIntiationRange"))
        _58 = *mAttackIntiationRange_s * *mAttackIntiationRange_s;
    getStaticParam(&mChanceToBarkOnAttackFail_s, "ChanceToBarkOnAttackFail");
    getStaticParam(&mUseChainAttack_s, "UseChainAttack");
    getDynamicParam(&mKeepTargetRange_d, "KeepTargetRange");
}

}  // namespace uking::ai
