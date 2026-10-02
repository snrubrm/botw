#include "Game/AI/AI/aiWolfLinkNormalRoot.h"
#include "Game/Actor/actWolfLink.h"
#include "KingSystem/ActorSystem/actActorParam.h"
#include "KingSystem/Resource/Actor/resResourceGParamList.h"
#include "KingSystem/Resource/GeneralParamList/resGParamListObjectWolfLink.h"
#include "KingSystem/Utils/MathUtil.h"

namespace uking::ai {

// NON_MATCHING: store pairing/scheduling (_140's MesTransceiverId, _198/_1a8/_1b0)
WolfLinkNormalRoot::WolfLinkNormalRoot(const InitArg& arg) : ksys::act::ai::Ai(arg) {}

WolfLinkNormalRoot::~WolfLinkNormalRoot() = default;

bool WolfLinkNormalRoot::init_(sead::Heap* heap) {
    _1b8 = 0;
    _70 = sead::DynamicCast<act::WolfLink>(mActor);
    if (!_70)
        return false;

    const auto* param = _70->getParam();
    if (!param)
        return false;
    const auto* gparams = param->getRes().mGParamList;
    if (!gparams)
        return false;
    _78 = gparams->getWolfLink();
    if (!_78)
        return false;

    _80 = mActor->getAwareness();
    return _80 != nullptr;
}

void WolfLinkNormalRoot::enter_(ksys::act::ai::InlineParamPack* params) {
    ksys::act::ai::Ai::enter_(params);
}

void WolfLinkNormalRoot::leave_() {
    using Idx = act::WolfLink::Idx14f8;
    _70->_14f8[Idx(Idx::_1)].rate = 0;
    _70->_14f8[Idx(Idx::_0)].rate = 0;
    _70->_14f8[Idx(Idx::_3)].rate = 0;
    _1b0 = _1a8;
    _70->_1698 &= ~0x400;
    _70->_1698 &= ~0x800;
}

// NON_MATCHING: regalloc (w8/w9 swapped around the timer index computation)
bool WolfLinkNormalRoot::handleMessage_(const ksys::Message& message) {
    bool reset;
    switch (_1a8) {
    case 0:
    case 3:
    case 5:
    case 6:
    case 13:
    case 14:
    case 15:
        reset = true;
        break;
    default:
        reset = false;
        break;
    }

    if (_88.m2(message)) {
        if (reset)
            _88.x();
        return true;
    }
    if (_c8.m2(message)) {
        if (reset)
            _c8.x();
        return true;
    }
    if (_108.m2(message)) {
        if (reset)
            _108.x();
        return true;
    }
    if (!_140.m2(message))
        return false;

    if (reset) {
        _140.x();
        return true;
    }

    const s32 delay = _78->mCallDelayMinLength.ref() +
                      sead::Mathf::sqrt(ksys::util::sqXZDistance(_19c, _190)) / 11.0f;
    using Idx = act::WolfLink::Idx14f8;
    auto& timer = _70->_14f8[Idx(Idx::_11)];
    timer.value = delay;
    timer.previous_value = delay;
    _70->_14f8[Idx(Idx::_11)].rate = -1.0f;
    _70->_1698 |= 0x4000;
    return true;
}

void WolfLinkNormalRoot::loadParams_() {
    getStaticParam(&mShiekSensorLeadDistance_s, "ShiekSensorLeadDistance");
    getStaticParam(&mShiekSensorGoalTolerance_s, "ShiekSensorGoalTolerance");
    getStaticParam(&mShiekSensorTargetFowardOffset_s, "ShiekSensorTargetFowardOffset");
    getStaticParam(&mBattleAggressionRange_s, "BattleAggressionRange");
    getStaticParam(&mHowlAtEnemyRange_s, "HowlAtEnemyRange");
    getStaticParam(&mUtilityWantsToHunt_s, "UtilityWantsToHunt");
    getStaticParam(&mWarpToPlayerDistance_s, "WarpToPlayerDistance");
}

}  // namespace uking::ai
