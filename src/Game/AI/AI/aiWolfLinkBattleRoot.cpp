#include "Game/AI/AI/aiWolfLinkBattleRoot.h"
#include <random/seadGlobalRandom.h>
#include "Game/Actor/actWolfLink.h"
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
