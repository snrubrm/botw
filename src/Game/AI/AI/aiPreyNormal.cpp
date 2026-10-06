#include "Game/AI/AI/aiPreyNormal.h"
#include <math/seadMathCalcCommon.h>
#include <random/seadGlobalRandom.h>
#include "Game/AI/aiUnk_71005D6D10.h"
#include "Game/AI/aiUnk_71006F1DF0.h"
#include "Game/AI/aiUnk_7100736460.h"
#include "KingSystem/ActorSystem/actActor.h"
#include "KingSystem/ActorSystem/actActorConstDataAccess.h"
#include "KingSystem/ActorSystem/actActorUtil.h"
#include "KingSystem/ActorSystem/actAiInlineParam.h"
#include "KingSystem/ActorSystem/actActorParam.h"
#include "KingSystem/Physics/System/physInstanceSet.h"
#include "KingSystem/Resource/Actor/resResourceGParamList.h"
#include "KingSystem/Resource/GeneralParamList/resGParamListObjectPrey.h"
#include "Game/Actor/actRideable.h"
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

bool PreyNormal::handleMessage_(const ksys::Message* message) {
    if (!_1f8._30 &&
        !mActor->getActorFlags2().isAnyOn({ksys::act::Actor::ActorFlag2::_2000000,
                                           ksys::act::Actor::ActorFlag2::_8000000}) &&
        _1f8.m2(*message)) {
        return true;
    }
    if (!_2c0._30 && !mActor->getActorFlags2().isOn(ksys::act::Actor::ActorFlag2::_8000000) &&
        _2c0.m2(*message)) {
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

// 0x71004fca60
bool PreyNormal::sub_71004FCA60() {
    if (isCurrentChild("徘徊") &&
        (!isCurrentChild("徘徊") || !getCurrentChild()->isFinishedOrFailed()))
        return false;

    if (auto* enemy = _d0) {
        enemy->_c48._8.reset();
        enemy->_c48._7c = 0;
        _fc = -1;
        _100 = 0;
        _104 = 0;
        _108 = 0;
    }
    _170.reset();
    const f32 wait = sead::GlobalRandom::instance()->getF32Range(630.0f, 1050.0f);
    _11c = ksys::Timer(wait, wait);
    const auto* prey = mActor->getParam()->getRes().mGParamList->getPrey();
    if (prey) {
        const f32 time = prey->mWaitTimeForStartEat.ref();
        _140 = ksys::Timer(time, time);
    } else {
        _140 = ksys::Timer(1.0f, 1.0f, 0.0f);
    }
    _182 = *mIsReceivedForceEscapeSignal_s;
    _270 = *mIsPositiveAttacker_s;
    mActor->getActorFlags2().reset(ksys::act::Actor::ActorFlag2::_8000000);
    mActor->getActorFlags2().reset(ksys::act::Actor::ActorFlag2::_2000000);
    mActor->getActorFlags2().reset(ksys::act::Actor::ActorFlag2::_1000000);
    if (auto* physics = mActor->getPhysics()) {
        if (mActor->getHorseOptionsMaybe())
            physics->sub_7100FBACE0(ksys::phys::ContactLayer(0x28));
    }
    sead::Vector3f pos;
    mActor->getMtx().getTranslation(pos);
    ksys::act::ai::InlineParamPack params;
    params.addVec3(pos, "CentralPos", -1);
    params.addVec3(pos, "TargetPos", -1);
    changeChild("徘徊", &params);
    return true;
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

void PreyNormal::sub_7100500B50(bool a, bool b, bool c) {
    using Flag = ksys::act::Actor::ActorFlag2;
    mActor->getActorFlags2().change(Flag::_8000000, a);
    mActor->getActorFlags2().change(Flag::_2000000, b);
    mActor->getActorFlags2().change(Flag::_1000000, c);
}

// 0x71004fe2b4
bool PreyNormal::sub_71004FE2B4() {
    if (isCurrentChild("気づき") || mActor->getActorFlags2().isOn(ksys::act::Actor::ActorFlag2::_8000000))
        return false;
    mActor->getActorFlags2().reset(ksys::act::Actor::ActorFlag2::_8000000);
    mActor->getActorFlags2().set(ksys::act::Actor::ActorFlag2::_2000000);
    mActor->getActorFlags2().reset(ksys::act::Actor::ActorFlag2::_1000000);
    ksys::act::ai::InlineParamPack pack;
    changeChild("気づき", &pack);
    return true;
}

// 0x71004feac8
bool PreyNormal::sub_71004FEAC8() {
    if (isCurrentChild("注目"))
        return false;
    _134 = ksys::Timer(*mTargetLostTime_s, *mTargetLostTime_s);
    mActor->getActorFlags2().reset(ksys::act::Actor::ActorFlag2::_8000000);
    mActor->getActorFlags2().set(ksys::act::Actor::ActorFlag2::_2000000);
    mActor->getActorFlags2().set(ksys::act::Actor::ActorFlag2::_1000000);
    ksys::act::ai::InlineParamPack pack;
    pack.addVec3(_e0, "TargetPos", -1);
    changeChild("注目", &pack);
    return true;
}

// 0x7100500ba8
bool PreyNormal::sub_7100500BA8() {
    if (isCurrentChild("威嚇"))
        return false;
    mActor->getActorFlags2().reset(ksys::act::Actor::ActorFlag2::_8000000);
    mActor->getActorFlags2().set(ksys::act::Actor::ActorFlag2::_2000000);
    mActor->getActorFlags2().set(ksys::act::Actor::ActorFlag2::_1000000);
    ksys::act::ai::InlineParamPack pack;
    pack.addVec3(_e0, "TargetPos", -1);
    changeChild("威嚇", &pack);
    return true;
}

// 0x71004fc890
bool PreyNormal::sub_71004FC890() {
    if (!*mIsUseEscapeState_s)
        return sub_71004FCA60();
    if (isCurrentChild("逃走") &&
        (!isCurrentChild("逃走") || !getCurrentChild()->isFinishedOrFailed()))
        return false;
    mActor->getActorFlags2().set(ksys::act::Actor::ActorFlag2::_8000000);
    mActor->getActorFlags2().set(ksys::act::Actor::ActorFlag2::_2000000);
    mActor->getActorFlags2().reset(ksys::act::Actor::ActorFlag2::_1000000);
    _334 = ksys::Timer(900.0f, 900.0f);
    mActor->getActorFlags2().set(ksys::act::Actor::ActorFlag2::_8000);
    ksys::act::ai::InlineParamPack pack;
    pack.addVec3(_e0, "TargetPos", -1);
    changeChild("逃走", &pack);
    return true;
}

// 0x7100500cd8
bool PreyNormal::sub_7100500CD8() {
    if (!*mIsUseEscapeState_s)
        return sub_71004FCA60();
    if (isCurrentChild("ダメージ逃走") &&
        (!isCurrentChild("ダメージ逃走") || !getCurrentChild()->isFinishedOrFailed()))
        return false;
    mActor->getActorFlags2().set(ksys::act::Actor::ActorFlag2::_8000000);
    mActor->getActorFlags2().set(ksys::act::Actor::ActorFlag2::_2000000);
    mActor->getActorFlags2().reset(ksys::act::Actor::ActorFlag2::_1000000);
    _334 = ksys::Timer(900.0f, 900.0f);
    mActor->getActorFlags2().set(ksys::act::Actor::ActorFlag2::_8000);
    ksys::act::ai::InlineParamPack pack;
    pack.addVec3(_e0, "TargetPos", -1);
    changeChild("ダメージ逃走", &pack);
    return true;
}

// 0x71004fe594
bool PreyNormal::sub_71004FE594() {
    const bool is_current = isCurrentChild("ふり向き");
    if (!getCurrentChild()->isChangeable() && !getCurrentChild()->isFinishedOrFailed() && is_current)
        return false;
    _18d = is_current;
    if (auto* enemy = _d0) {
        enemy->_c48._8.reset();
        enemy->_c48._7c = 0;
        _fc = -1;
        _100 = 0;
        _104 = 0;
        _108 = 0;
    }
    _110.value += *mAddCautionLevelVal_s;
    mActor->getActorFlags2().reset(ksys::act::Actor::ActorFlag2::_8000000);
    mActor->getActorFlags2().reset(ksys::act::Actor::ActorFlag2::_2000000);
    mActor->getActorFlags2().set(ksys::act::Actor::ActorFlag2::_1000000);
    ksys::act::ai::InlineParamPack pack;
    pack.addVec3(_e0, "TargetPos", -1);
    changeChild("ふり向き", &pack);
    return true;
}

// 0x71004ff8a0
// NON_MATCHING: register allocation of the first compare only (the original loads _100 into w8 and the required hit
// count into w9)
bool PreyNormal::sub_71004FF8A0() {
    const s32 required = *mIsPositiveAttacker_s ? 2 : 1;
    if (required < s32(_100))
        return false;
    auto* link = _d0 ? &_d0->_c48._8 : &ksys::act::sUnk_71026505e0;
    const bool is_prey = ksys::act::isPreyOrSwarm(link);
    const bool is_npc = ksys::act::isNPCProfile(link);
    if (!is_prey && !is_npc)
        return false;
    if (is_npc) {
        ksys::act::ActorConstDataAccess accessor;
        if (!ksys::act::acquireActor(link, &accessor) || accessor.sub_7100022FD0())
            return false;
    }
    return (mActor->getMtx().getTranslation() - _e0).length() <= *mAllowRoarRadius_s;
}

// 0x71004ff740
// NON_MATCHING: block layout / the two distance compares are one conditional-compare chain in the original (the radius
// is loaded before the compares) and every exit is a separate `mov w0, wzr` / `orr w0, wzr, #1`
bool PreyNormal::sub_71004FF740() {
    if (!(_d0 ? _d0->_c48._8 : ksys::act::sUnk_71026505e0).hasProc())
        return false;
    const f32 x = mActor->getMtx().m[0][3];
    const f32 z = mActor->getMtx().m[2][3];
    ksys::act::ActorConstDataAccess accessor;
    ksys::act::acquireActor(_d0 ? &_d0->_c48._8 : &ksys::act::sUnk_71026505e0, &accessor);
    const f32 distance = std::sqrt((_e0.x - x) * (_e0.x - x) + (_e0.z - z) * (_e0.z - z));
    f32 threshold;
    if (*mIsPositiveAttacker_s) {
        threshold = 0.0f;
    } else {
        const sead::Vector3f& velocity = accessor.getVelocity();
        threshold = std::sqrt(velocity.x * velocity.x + velocity.z * velocity.z) * 45.0f;
    }
    if (ksys::act::isPlayerProfile(accessor) && !accessor.sub_7100D12E64()) {
        if (distance >= threshold && distance < *mChangeBattleStateRadius_s) {
            if (!m39(_e0))
                return true;
        }
    }
    return false;
}

}  // namespace uking::ai

using ksys::act::Unk_71024dc858;
using ksys::act::Unk_71024dc978;

// 0x7100501344
bool Unk_7102410710::m2(Unk_71024dc978* entry) {
    auto* target = sead::DynamicCast<Unk_71024dc858>(entry);
    if (!target)
        return false;
    return ksys::act::isPlayerProfile(&target->mLink);
}

// 0x71005013d8
// NON_MATCHING: the original combines `m5(1)` and the `_40` test without a branch
bool Unk_7102410738::m2(Unk_71024dc978* entry) {
    auto* target = sead::DynamicCast<Unk_71024dc858>(entry);
    if (!target)
        return false;
    ksys::act::ActorConstDataAccess accessor;
    if (ksys::act::acquireActor(&target->mLink, &accessor)) {
        const auto& profile = accessor.getProfile();
        return !(profile == "Prey") && !(profile == "CapturedActor");
    }
    return target->m5(1) || (target->_40 & 0x100070) == 0;
}

// 0x71005015b0
bool Unk_7102410760::m2(Unk_71024dc978* entry) {
    auto* target = sead::DynamicCast<Unk_71024dc858>(entry);
    if (!target)
        return false;
    auto* link = &target->mLink;
    ksys::act::ActorConstDataAccess accessor;
    if (ksys::act::acquireActor(link, &accessor)) {
        if (ksys::act::isPlayerProfile(accessor))
            return true;
        return ksys::act::hasTag(link, 0xf3a5f416);
    }
    return false;
}

// 0x7100501698
// NON_MATCHING: the original evaluates all three predicates (the `||` chain is not short-circuited)
bool Unk_7102410788::m2(Unk_71024dc978* entry) {
    auto* target = sead::DynamicCast<Unk_71024dc858>(entry);
    if (!target)
        return false;
    auto* link = &target->mLink;
    ksys::act::ActorConstDataAccess accessor;
    if (!ksys::act::acquireActor(link, &accessor))
        return (target->_3c & 0x1c30) != 0;
    return !(ksys::act::isNPCProfile(accessor) ||
             (ksys::act::isPreyOrSwarm(accessor) && !ksys::act::isWolfOrBear(accessor)) ||
             hasAnimalTypeWolfOrBearTags(_28, link));
}

// 0x71005017b8
// NON_MATCHING: the original evaluates both predicates (the `||` is not short-circuited)
bool Unk_71024107b0::m2(Unk_71024dc978* entry) {
    auto* target = sead::DynamicCast<Unk_71024dc858>(entry);
    if (!target)
        return false;
    ksys::act::ActorConstDataAccess accessor;
    if (!ksys::act::acquireActor(&target->mLink, &accessor))
        return (target->_3c & 0x1c30) != 0;
    return !(ksys::act::isNPCProfile(accessor) ||
             (ksys::act::isPreyOrSwarm(accessor) && !ksys::act::isWolfOrBear(accessor)));
}

// 0x71005018b8
bool Unk_71024107d8::m2(Unk_71024dc978* entry) {
    auto* target = sead::DynamicCast<Unk_71024dc858>(entry);
    if (!target)
        return false;
    ksys::act::ActorConstDataAccess accessor;
    if (!ksys::act::acquireActor(&target->mLink, &accessor))
        return (target->_3c & 0x1c30) != 0;
    return !ksys::act::isPreyOrSwarm(accessor) || ksys::act::isWolfOrBear(accessor);
}

// 0x71005019a4
bool Unk_7102410800::m2(Unk_71024dc978* entry) {
    auto* target = sead::DynamicCast<Unk_71024dc858>(entry);
    if (!target)
        return false;
    ksys::act::ActorConstDataAccess accessor;
    if (!ksys::act::acquireActor(&target->mLink, &accessor))
        return false;
    if (!accessor.sub_7100D10E6C(27) && !accessor.sub_7100D10E6C(26))
        return false;
    return ksys::act::isPreyOrSwarm(accessor);
}

// 0x7100501a94
bool Unk_7102410828::m2(Unk_71024dc978* entry) {
    auto* target = sead::DynamicCast<Unk_71024dc858>(entry);
    if (!target)
        return false;
    ksys::act::ActorConstDataAccess accessor;
    if (!ksys::act::acquireActor(&target->mLink, &accessor))
        return false;
    if (ksys::act::isNPCProfile(accessor))
        return true;
    return ksys::act::isPreyOrSwarm(accessor) && !ksys::act::isWolfOrBear(accessor);
}
