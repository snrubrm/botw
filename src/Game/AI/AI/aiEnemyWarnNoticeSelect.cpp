#include "Game/AI/AI/aiEnemyWarnNoticeSelect.h"
#include <algorithm>
#include <random/seadGlobalRandom.h>
#include "Game/DLC/aocHardModeManager.h"
#include "Game/AI/aiAwarenessFilters.h"
#include "KingSystem/ActorSystem/actActor.h"
#include "KingSystem/ActorSystem/actActorConstDataAccess.h"
#include "KingSystem/ActorSystem/actActorUtil.h"
#include "KingSystem/ActorSystem/actAiInlineParam.h"
#include "KingSystem/System/Timer.h"

namespace uking::ai {

EnemyWarnNoticeSelect::EnemyWarnNoticeSelect(const InitArg& arg) : ksys::act::ai::Ai(arg) {}

EnemyWarnNoticeSelect::~EnemyWarnNoticeSelect() = default;

bool EnemyWarnNoticeSelect::init_(sead::Heap* heap) {
    return ksys::act::ai::Ai::init_(heap);
}

void EnemyWarnNoticeSelect::sub_71003C4CB4(bool a1) {
    _134 = 0;
    if (ksys::act::isPlayerProfile(mTargetActor_d)) {
        if ((mActor->m94() | 1) == 3 || a1 || _138) {
            mActor->m93(4, 0.0f);
            f32 duration = 20.0f;
            if (auto* manager = aoc::HardModeManager::instance()) {
                if (manager->checkFlag(aoc::HardModeManager::Flag::EnableHardMode) &&
                    manager->isHardModeChangeOn(
                        aoc::HardModeManager::HardModeChange::EnableShorterEnemyNotice)) {
                    manager->modifyEnemyNoticeDuration(&duration);
                }
            }
            _130 = duration;
        }
    }
    mActor->getActorFlags2().reset(ksys::act::Actor::ActorFlag2::_1000000);
    ksys::act::ai::InlineParamPack pack;
    pack.addActor(*mTargetActor_d, "TargetActor", -1);
    sead::Vector3f pos;
    ksys::act::ActorConstDataAccess accessor;
    ksys::act::acquireActor(mTargetActor_d, &accessor);
    accessor.getActorMtx().getTranslation(pos);
    pack.addVec3(pos, "TargetPos", -1);
    changeChild("発見", &pack);
}

void EnemyWarnNoticeSelect::sub_71003C56A8() {
    const bool is_player = ksys::act::isPlayerProfile(mTargetActor_d);
    const int level = sub_71003C4EA4();
    const bool noticed = level != 0;
    f32 duration;
    if (isCurrentChild("発見")) {
        if (!(_130 <= 0.0f)) {
            ksys::Timer::update(&_130, -1.0f);
            if (_130 <= 0.0f) {
                mActor->m94();
                mActor->m93(0, 0.0f);
            }
        }
    } else {
        if (!_139 && noticed) {
            ++_134;
            duration = sead::Mathf::min(f32(*mWarnBlinkTime_s), _130);
            if (auto* manager = aoc::HardModeManager::instance()) {
                if (manager->checkFlag(aoc::HardModeManager::Flag::EnableHardMode) &&
                    manager->isHardModeChangeOn(
                        aoc::HardModeManager::HardModeChange::EnableShorterEnemyNotice)) {
                    manager->modifyEnemyNoticeDuration(&duration);
                }
            }
            _130 = duration;
            _139 = noticed;
        }
        if (is_player) {
            if (_130 < f32(*mWarnBlinkTime_s))
                mActor->m93(3, sead::Mathf::clamp((f32(*mWarnBlinkTime_s) - _130) /
                                                      f32(*mWarnBlinkTime_s),
                                                  0.0f, 1.0f));
        }
    }
    if (!is_player) {
        mActor->m94();
        mActor->m93(0, 0.0f);
    }
}

void EnemyWarnNoticeSelect::sub_71003C5028() {
    _a0.reset();
    ksys::act::ai::InlineParamPack pack;
    pack.addActor(*mTargetActor_d, "TargetActor", -1);
    sead::Vector3f pos;
    ksys::act::ActorConstDataAccess accessor;
    ksys::act::acquireActor(mTargetActor_d, &accessor);
    accessor.getActorMtx().getTranslation(pos);
    pack.addVec3(pos, "TargetPos", -1);
    changeChild("警戒", &pack);
}

void EnemyWarnNoticeSelect::sub_71003C5B04(sead::Vector3f* position) {
    ksys::act::ActorConstDataAccess accessor;
    ksys::act::acquireActor(mTargetActor_d, &accessor);
    accessor.getActorMtx().getTranslation(*position);
}

bool EnemyWarnNoticeSelect::sub_71003C5418(s32 condition) {
    if (condition == 2)
        return true;
    if (_138)
        return true;
    return *mForceNotice_d;
}

// NON_MATCHING: Initial flag stores and enum temporaries differ; the compiler removes the range minimum.
void EnemyWarnNoticeSelect::enter_(ksys::act::ai::InlineParamPack* params) {
    _138 = false;
    _139 = true;
    _134 = 0;
    const f32 notice_time = f32(*mWarnNoticeTime_s);
    const f32 notice_random = f32(*mWarnNoticeTimeRnd_s);
    f32 duration = notice_time + notice_random * sead::GlobalRandom::instance()->getF32();
    if (auto* manager = aoc::HardModeManager::instance()) {
        if (manager->checkFlag(aoc::HardModeManager::Flag::EnableHardMode) &&
            manager->isHardModeChangeOn(
                aoc::HardModeManager::HardModeChange::EnableShorterEnemyNotice)) {
            manager->modifyEnemyNoticeDuration(&duration);
        }
    }
    _130 = duration;
    const s32 lost_counter = *mLostCounter_s;
    const s32 maximum = lost_counter + sead::GlobalRandom::instance()->getS32Range(0, 10);
    _a0.min = std::min(lost_counter, maximum);
    _a0.max = maximum;
    _ac.min = 3;
    _ac.max = 3;
    if (*mIsTrgChangeUnderWaterState_a) {
        sub_71003C4CB4(false);
        return;
    }
    auto* actor = mActor;
    if (actor->getActorFlags2().isOn(ksys::act::Actor::ActorFlag2::_2000000)) {
        sub_71003C4CB4(false);
        return;
    }
    if (*mForceNotice_d || sub_71003C4EA4() == 2) {
        sub_71003C4CB4(true);
        return;
    }
    if (ksys::act::isPlayerProfile(mTargetActor_d))
        actor->m93(2, 0.0f);
    actor->getActorFlags2().set(ksys::act::Actor::ActorFlag2::_1000000);
    sub_71003C5028();
}

void EnemyWarnNoticeSelect::calc_() {
    const int state = sub_71003C4EA4();
    if (state) {
        _a0.reset();
        _ac.reset();
    } else {
        _a0.update();
        _ac.update();
    }
    ksys::act::isPlayerProfile(mTargetActor_d);

    auto* child = getCurrentChild();
    if (child->isFinished() || child->isFailed()) {
        if (isCurrentChild("警戒"))
            m34();
        else if (child->isFinished())
            setFinished();
        else
            setFailed();
    } else if (child->isChangeable()) {
        if (isCurrentChild("警戒")) {
            if (state == 2 || _138 || *mForceNotice_d || sub_71003C544C())
                sub_71003C4CB4(false);
            else if (_a0.value <= 0.0f && _130 > f32(*mWarnBlinkTime_s))
                m34();
        }
    }

    sead::Vector3f pos;
    ksys::act::ActorConstDataAccess accessor;
    ksys::act::acquireActor(mTargetActor_d, &accessor);
    accessor.getActorMtx().getTranslation(pos);
    child->setDynamicParam(pos, "TargetPos");
    sub_71003C56A8();
}

bool EnemyWarnNoticeSelect::isFailed() const {
    return ksys::act::ai::Ai::isFailed() || getCurrentChild()->isFailed();
}

// NON_MATCHING: register allocation / block layout of the filter temporaries (the original rematerialises &filter
// for the destructor call and shares the `return 2` block)
int EnemyWarnNoticeSelect::sub_71003C4EA4() {
    if (mActor->getActorFlags2().isOn(ksys::act::Actor::ActorFlag2::_2000000))
        return 2;
    auto* awareness = mActor->getAwareness();
    if (!awareness)
        return 0;

    u32 level = 0;
    if (*mIsSight_s) {
        auto* target = mTargetActor_d;
        Unk_7102451740 filter;
        if (target)
            filter._28 = *target;
        auto* sensor = awareness->_260[0];
        if (sensor) {
            if (auto* entry = ksys::act::sub_7100D7EEE8(&sensor->_8, &filter))
                level = entry->_a0;
        }
        if (level == 2)
            return 2;
    }
    if (*mIsWorry_s) {
        auto* target = mTargetActor_d;
        Unk_7102451740 filter;
        if (target)
            filter._28 = *target;
        auto* sensor = awareness->_260[3];
        if (sensor) {
            if (auto* entry = ksys::act::sub_7100D7EEE8(&sensor->_8, &filter)) {
                if (u32(entry->_a0) > level)
                    level = entry->_a0;
            }
        }
    }
    return level;
}

bool EnemyWarnNoticeSelect::isFinished() const {
    return ksys::act::ai::Ai::isFinished() || getCurrentChild()->isFinished();
}

bool EnemyWarnNoticeSelect::isChangeable() const {
    return getCurrentChild()->isChangeable();
}

void EnemyWarnNoticeSelect::leave_() {
    mActor->m93(0, 0.0f);
    mActor->getActorFlags2().reset(ksys::act::Actor::ActorFlag2::_1000000);
}

void EnemyWarnNoticeSelect::loadParams_() {
    getStaticParam(&mWarnNoticeTime_s, "WarnNoticeTime");
    getStaticParam(&mWarnNoticeTimeRnd_s, "WarnNoticeTimeRnd");
    getStaticParam(&mWarnBlinkTime_s, "WarnBlinkTime");
    getStaticParam(&mLostCounter_s, "LostCounter");
    getStaticParam(&mIsSight_s, "IsSight");
    getStaticParam(&mIsWorry_s, "IsWorry");
    getDynamicParam(&mForceNotice_d, "ForceNotice");
    getDynamicParam(&mTargetActor_d, "TargetActor");
    getStaticParam(&mPenaltyStair2Num_s, "PenaltyStair2Num");
    getStaticParam(&mMaxCountUp_s, "MaxCountUp");
    getStaticParam(&mPenalty_s, "Penalty");
    getStaticParam(&mNoPenaltyNum_s, "NoPenaltyNum");
    getAITreeVariable(&mIsTrgChangeUnderWaterState_a, "IsTrgChangeUnderWaterState");
}

void EnemyWarnNoticeSelect::m34() {
    setFinished();
}

bool EnemyWarnNoticeSelect::handleMessage_(const ksys::Message* message) {
    if (_b8.m2(*message) && _b8._38.mData._0 == *mTargetActor_d && _b8._38.mData._24 == 2) {
        _138 = true;
        return true;
    }
    return false;
}

}  // namespace uking::ai
