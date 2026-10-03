#include "Game/AI/AI/aiPreyNormal.h"
#include <math/seadMathCalcCommon.h>
#include "Game/AI/aiUnk_71005D6D10.h"
#include "Game/AI/aiUnk_71006F1DF0.h"
#include "KingSystem/ActorSystem/actActor.h"
#include "KingSystem/Physics/System/physNavMeshCharacter.h"
#include "KingSystem/ActorSystem/Profiles/actPlayerBase.h"
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

// NON_MATCHING: register allocation only (the original keeps the result in x20 across the accessor
// destructor with `this` still in x19; ours reuses x19 for the result)
bool PreyNormal::m35() {
    if (!*mIsSearchTarget_s)
        return false;

    if (*mIsPositiveAttacker_s) {
        if (!isChangeable())
            return false;
    } else if (mActor->getActorFlags2().isOn(ksys::act::Actor::ActorFlag2::_8000000)) {
        return false;
    }

    bool result = false;
    ksys::act::acc::PlayerBase player;
    if (player.getPlayerFromPlayerInfo()) {
        sead::Vector3f diff =
            mActor->getMtx().getTranslation() - player.getActorMtx().getTranslation();
        diff.y = 0.0f;
        if (diff.length() < 15.0f) {
            _1a0.forcePushBack(player.m178() ? 1.0f : 0.0f);

            f32 sum = 0.0f;
            for (s32 i = 0; i < _1a0.size(); ++i) {
                if (auto* value = _1a0.get(i))
                    sum += *value;
            }
            if (sum > f32(_1a0.capacity()) * 0.9f)
                result = true;
        }
    }
    return result;
}

bool PreyNormal::m36() {
    if (m37(&_170))
        _140.value += *mNewFoodAddTime_s;
    if (_170.hasProc())
        _140.update();
    return _140.value <= sead::Mathf::epsilon();
}

bool PreyNormal::m39(const sead::Vector3f& pos) {
    if (*mEnableNoEntryAreaCheck_m)
        return sub_71006F1DF0(mActor, pos);
    return false;
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

bool PreyNormal::m41() {
    return sub_71004FCA60();
}

// NON_MATCHING: scheduling (the original computes the clamped index before the own-target link)
ksys::act::Unk_7100d78e50* PreyNormal::sub_7100501B84(s32 idx, Unk_7102410738* filter) {
    const auto& own_target = _d0 ? _d0->_c48._8 : ksys::act::sUnk_71026505e0;
    while (_d8->_260[idx]) {
        auto* entry = ksys::act::sub_7100D7EEE8(&_d8->_260[idx]->_8, filter);
        if (!entry || !(entry->_0.mLink == own_target))
            return entry;
    }
    return nullptr;
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
