#include "Game/AI/AI/aiPreyNormal.h"
#include <math/seadMathCalcCommon.h>
#include "Game/AI/aiUnk_71005D6D10.h"
#include "KingSystem/ActorSystem/actActor.h"
#include "KingSystem/Physics/System/physNavMeshCharacter.h"
#include "KingSystem/ActorSystem/actAiRoot.h"
#include "KingSystem/ActorSystem/actBaseProcLink.h"
#include "KingSystem/Utils/Thread/Message.h"

namespace uking::ai {

PreyNormal::PreyNormal(const InitArg& arg) : ksys::act::ai::Ai(arg) {}

PreyNormal::~PreyNormal() = default;

bool PreyNormal::init_(sead::Heap* heap) {
    m9();
    return true;
}

void PreyNormal::enter_(ksys::act::ai::InlineParamPack* params) {
    ksys::act::ai::Ai::enter_(params);
}

void PreyNormal::leave_() {
    sub_71005DB3EC(mActor);
}

void PreyNormal::loadParams_() {
    getStaticParam(&mChangeBattleStateRadius_s, "ChangeBattleStateRadius");
    getStaticParam(&mCounterAttackRadius_s, "CounterAttackRadius");
    getStaticParam(&mCounterAttackRate_s, "CounterAttackRate");
    getStaticParam(&mAddCautionLevelVal_s, "AddCautionLevelVal");
    getStaticParam(&mAutoReduceCautionLevelVal_s, "AutoReduceCautionLevelVal");
    getStaticParam(&mLimitOverReduceCautionLevelVal_s, "LimitOverReduceCautionLevelVal");
    getStaticParam(&mAwnRangeScaleWhenAttention_s, "AwnRangeScaleWhenAttention");
    getStaticParam(&mTargetLostTime_s, "TargetLostTime");
    getStaticParam(&mAllowRoarRadius_s, "AllowRoarRadius");
    getStaticParam(&mEscapeWaterFlowLimit_s, "EscapeWaterFlowLimit");
    getStaticParam(&mNewFoodAddTime_s, "NewFoodAddTime");
    getStaticParam(&mIsUseEscapeState_s, "IsUseEscapeState");
    getStaticParam(&mIsPositiveAttacker_s, "IsPositiveAttacker");
    getStaticParam(&mIsSearchTarget_s, "IsSearchTarget");
    getStaticParam(&mIsEmitForceEscapeSignal_s, "IsEmitForceEscapeSignal");
    getStaticParam(&mIsReceivedForceEscapeSignal_s, "IsReceivedForceEscapeSignal");
    getStaticParam(&mIsCheckSandStorm_s, "IsCheckSandStorm");
    getMapUnitParam(&mIsLocatorCreate_m, "IsLocatorCreate");
    getMapUnitParam(&mEnableNoEntryAreaCheck_m, "EnableNoEntryAreaCheck");
}

bool PreyNormal::isChangeable() const {
    return !isCurrentChild("逃走") && !isCurrentChild("ダメージ逃走") && !isCurrentChild("戦闘");
}

void PreyNormal::m9() {
    _d0 = sead::DynamicCast<act::Enemy>(mActor);
    auto* root = mActor->getRootAi();
    _180 = (root && root->getI() == 4) || *mIsLocatorCreate_m;
}

bool PreyNormal::handleMessage_(const ksys::Message& message) {
    if (!_1f8._30 &&
        !mActor->getActorFlags2().isAnyOn({ksys::act::Actor::ActorFlag2::_2000000,
                                           ksys::act::Actor::ActorFlag2::_8000000}) &&
        _1f8.m2(message)) {
        return true;
    }
    if (!_2c0._30 && !mActor->getActorFlags2().isOn(ksys::act::Actor::ActorFlag2::_8000000) &&
        _2c0.m2(message)) {
        return true;
    }
    return false;
}

bool PreyNormal::m36() {
    if (m37(&_170))
        _140.value += *mNewFoodAddTime_s;
    if (_170.hasProc())
        _140.update();
    return _140.value <= sead::Mathf::epsilon();
}

bool PreyNormal::m38() {
    if (auto* nav = mActor->m45()) {
        if ((nav->_2a4 & 0xffff) != 0x17) {
            if (sub_7100500A0C(&_e0))
                return true;
        }
    }
    return false;
}

bool PreyNormal::m40() {
    return isCurrentChild("徘徊");
}

void PreyNormal::m41() {
    sub_71004FCA60();
}

// NON_MATCHING: scheduling (the original computes the clamped index before the own-target link)
ksys::act::Unk_7100d78e50* PreyNormal::m43(s32 idx, bool skip_own_target) {
    if (!_d8)
        return nullptr;

    Unk_7102410738 filter;
    if (skip_own_target) {
        const auto& own_target = _d0 ? _d0->_c48._8 : ksys::act::sUnk_71026505e0;
        while (_d8->_260[idx]) {
            auto* entry = ksys::act::sub_7100D7EEE8(&_d8->_260[idx]->_8, &filter);
            if (!entry || !(entry->_0.mLink == own_target))
                return entry;
        }
        return nullptr;
    }

    if (!_d8->_260[idx])
        return nullptr;
    return ksys::act::sub_7100D7EEE8(&_d8->_260[idx]->_8, &filter);
}

}  // namespace uking::ai
