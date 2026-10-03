#include "Game/AI/AI/aiEnemyNoticeTerror.h"
#include <math/seadMathCalcCommon.h>
#include <random/seadGlobalRandom.h>
#include "Game/AI/aiUnk_71005D6D10.h"
#include "KingSystem/ActorSystem/actActor.h"
#include "KingSystem/ActorSystem/actActorConstDataAccess.h"
#include "KingSystem/ActorSystem/actActorUtil.h"
#include "KingSystem/ActorSystem/actAiInlineParam.h"
#include "KingSystem/ActorSystem/Awareness/actAwarenessInstance.h"
#include "Game/Actor/actUnk_71002dccbc.h"

namespace uking::ai {

EnemyNoticeTerror::EnemyNoticeTerror(const InitArg& arg) : ksys::act::ai::Ai(arg) {}

EnemyNoticeTerror::~EnemyNoticeTerror() = default;

bool EnemyNoticeTerror::init_(sead::Heap* heap) {
    return ksys::act::ai::Ai::init_(heap);
}

void EnemyNoticeTerror::enter_(ksys::act::ai::InlineParamPack* params) {
    m34(&_60);
    _80 = _60;

    const int wait_time = *mWaitTime_s;
    const int wait_time_max = wait_time * 1.1f;
    _a4 = sead::Mathi::min(wait_time, wait_time_max);
    _a8 = sead::Mathi::max(wait_time, wait_time_max);
    int time = _a4;
    if (_a8 != _a4)
        time = sead::GlobalRandom::instance()->getS32Range(_a4, _a8);
    _a0 = time;
    m36();
}

// NON_MATCHING: the original keeps `&_a0` in a callee-saved register (computed once before the first
// branch) and loads the XZ positions in a different order; same logic and calls
void EnemyNoticeTerror::calc_() {
    if (_60._1c & 1) {
        if (!(_60._0 == _80._0) && _60._1c != _80._1c)
            _80 = _60;
    }
    m34(&_60);

    if (!(_60._1c & 1) && sub_71003A7A88()) {
        ksys::Timer::update(&_a0, -1.0f);
    } else {
        int time = _a4;
        if (_a8 != _a4)
            time = sead::GlobalRandom::instance()->getS32Range(_a4, _a8);
        _a0 = time;
    }

    auto* child = getCurrentChild();
    sead::Vector3f target;
    if (sub_71003A7B64(&target))
        child->setDynamicParam(target, "TargetPos");

    if (child->isFinished() || child->isFailed()) {
        if (_a0 <= 0) {
            if (auto* unk = sub_71005D9D68(mActor))
                unk->sub_71002DC8A0(_60._0, 2);
            setFinished();
        } else {
            if (isCurrentChild("気づき")) {
                m35();
                return;
            }
            if (isCurrentChild("逃走")) {
                sub_71003A7C44();
                return;
            }
            setFinished();
        }
    } else if (child->isChangeable()) {
        if (_a0 <= 0) {
            if (auto* unk = sub_71005D9D68(mActor))
                unk->sub_71002DC8A0(_60._0, 2);
            setFinished();
        } else if (isCurrentChild("眺める")) {
            const auto& pos = mActor->getMtx().getTranslation();
            const f32 dx = target.x - pos.x;
            const f32 dz = target.z - pos.z;
            const f32 dy = target.y - pos.y;
            if (sead::Mathf::sqrt(dx * dx + dz * dz) < *mNoWarnDist_s &&
                *mNoWarnHeightMin_s < dy && dy < *mNoWarnHeightMax_s) {
                m35();
            }
        }
    }
}

bool EnemyNoticeTerror::sub_71003A7A88() {
    auto* awareness = mActor->getAwareness();
    if (awareness && awareness->_8.size() >= 1) {
        const s32 count = awareness->_8.size();
        for (s32 i = 0; i < count; ++i) {
            if (i < awareness->_8.size()) {
                auto* entry = ksys::act::sub_7100D78E30(&awareness->_8, i);
                if (entry) {
                    if (!(entry->_a8 <= *mNoTerrorDist_s))
                        return true;
                    if (entry->_0.mLink == _80._0)
                        return false;
                    if (_80._1c & 2) {
                        if (entry->_0.m5(3) || entry->_0.m5(4))
                            return false;
                    }
                }
            }
        }
    }
    return true;
}

bool EnemyNoticeTerror::sub_71003A7B64(sead::Vector3f* out) {
    if (_60._1c & 1) {
        if (_60._0.hasProcInCalcState()) {
            ksys::act::ActorConstDataAccess accessor;
            ksys::act::acquireActor(&_60._0, &accessor);
            accessor.getActorMtx().getTranslation(*out);
        } else {
            *out = _60._10;
        }
        return true;
    }
    if (_80._1c & 1) {
        if (_80._0.hasProcInCalcState()) {
            ksys::act::ActorConstDataAccess accessor;
            ksys::act::acquireActor(&_80._0, &accessor);
            accessor.getActorMtx().getTranslation(*out);
        } else {
            *out = _80._10;
        }
        return true;
    }
    return false;
}

void EnemyNoticeTerror::sub_71003A7C44() {
    sead::Vector3f target;
    sub_71003A7B64(&target);
    ksys::act::ai::InlineParamPack params;
    params.addVec3(target, "TargetPos", -1);
    changeChild("眺める", &params);
}

void EnemyNoticeTerror::leave_() {
    ksys::act::ai::Ai::leave_();
}

void EnemyNoticeTerror::loadParams_() {
    getStaticParam(&mWaitTime_s, "WaitTime");
    getStaticParam(&mNoWarnDist_s, "NoWarnDist");
    getStaticParam(&mNoWarnHeightMin_s, "NoWarnHeightMin");
    getStaticParam(&mNoWarnHeightMax_s, "NoWarnHeightMax");
    getStaticParam(&mNoTerrorDist_s, "NoTerrorDist");
}

void EnemyNoticeTerror::sub_71003A7DD4() {
    sead::Vector3f target;
    sub_71003A7B64(&target);
    ksys::act::ai::InlineParamPack params;
    params.addVec3(target, "TargetPos", -1);
    changeChild("気づき", &params);
}

void EnemyNoticeTerror::m35() {
    sead::Vector3f target;
    sub_71003A7B64(&target);
    ksys::act::ai::InlineParamPack params;
    params.addVec3(target, "TargetPos", -1);
    changeChild("逃走", &params);
}

void EnemyNoticeTerror::m36() {
    auto* unk = sub_71005D9D68(mActor);
    auto* link = sub_71005D9050(mActor);
    if ((link && *link == _60._0) || (unk && unk->sub_71002DC9E8(_60._0, 2, false))) {
        m35();
        return;
    }
    if (unk)
        unk->sub_71002DC628(_60._0, 2);
    sub_71003A7DD4();
}

bool EnemyNoticeTerror::m34(Unk* out) {
    out->_0.reset();
    out->_1c = 0;
    auto* awareness = mActor->getAwareness();
    if (!awareness)
        return false;
    auto* sensor = awareness->_260[2];
    if (!sensor || sensor->_8.size() < 1)
        return false;
    auto* entry = ksys::act::sub_7100D78E30(&sensor->_8, 0);
    if (!entry)
        return false;
    out->_0 = entry->_0.mLink;
    out->_10 = entry->_88;
    out->_1c |= 1;
    if (entry->_0.m5(3) || entry->_0.m5(4))
        out->_1c |= 2;
    return true;
}

}  // namespace uking::ai
