#include "Game/AI/AI/aiEnemyWarnNoticeSelect.h"
#include "Game/AI/aiAwarenessFilters.h"
#include "KingSystem/ActorSystem/actActor.h"
#include "KingSystem/ActorSystem/actActorConstDataAccess.h"
#include "KingSystem/ActorSystem/actActorUtil.h"

namespace uking::ai {

EnemyWarnNoticeSelect::EnemyWarnNoticeSelect(const InitArg& arg) : ksys::act::ai::Ai(arg) {}

EnemyWarnNoticeSelect::~EnemyWarnNoticeSelect() = default;

bool EnemyWarnNoticeSelect::init_(sead::Heap* heap) {
    return ksys::act::ai::Ai::init_(heap);
}

void EnemyWarnNoticeSelect::enter_(ksys::act::ai::InlineParamPack* params) {
    ksys::act::ai::Ai::enter_(params);
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
