#include "Game/Actor/AI/aiOctarockServiceHideWait.h"
#include <random/seadGlobalRandom.h>
#include "KingSystem/ActorSystem/actActor.h"
#include "KingSystem/ActorSystem/actActorUtil.h"
#include "KingSystem/ActorSystem/Awareness/actAwarenessInstance.h"
#include "Game/Actor/aiUnk_71005D6D10.h"
#include "Game/Actor/aiAwarenessFilters.h"
#include "KingSystem/ActorSystem/Awareness/actAwarenessRequest.h"
#include "Game/Actor/aiUnk_7100D8C538.h"
#include "KingSystem/ActorSystem/actAiInlineParam.h"

namespace uking::ai {

OctarockServiceHideWait::OctarockServiceHideWait(const InitArg& arg) : ksys::act::ai::Ai(arg) {}

OctarockServiceHideWait::~OctarockServiceHideWait() = default;

bool OctarockServiceHideWait::init_(sead::Heap* heap) {
    return ksys::act::ai::Ai::init_(heap);
}

void OctarockServiceHideWait::enter_(ksys::act::ai::InlineParamPack* params) {
    _68 = ksys::act::isAttClientEnabled(mActor, "AutoAim");
    _69 = ksys::act::isAttClientEnabled(mActor, "AutoAimHidden");
    sub_71004EF670();
}

// NON_MATCHING: stack slot order of the target position and the param pack
void OctarockServiceHideWait::calc_() {
    auto* child = getCurrentChild();
    if (child->isFinished() || child->isFailed()) {
        if (isCurrentChild("待機")) {
            ksys::act::disableAttClient(mActor, "AutoAimHidden");
            ksys::act::enableAttClient(mActor, "AutoAim");
            changeChild("飛び出す");
        } else if (isCurrentChild("飛び出す")) {
            if (auto* awareness = mActor->getAwareness())
                awareness->sub_7100D7E9BC(0);
            changeChild("出現待機");
        } else if (isCurrentChild("出現待機") || isCurrentChild("気づき")) {
            mActor->m93(0, 0.0f);
            if (auto* awareness = mActor->getAwareness())
                awareness->sub_7100D7EAE4(0);
            changeChild("隠れる");
        } else {
            sub_71004EF670();
        }
        return;
    }

    if (!child->isChangeable())
        return;

    if (isCurrentChild("待機")) {
        if (_6c.value <= sead::Mathf::epsilon()) {
            if (sub_71005D8F28(mActor)) {
                const auto& pos = sub_71005D9330(mActor);
                const auto& mtx = mActor->getMtx();
                const f32 dx = pos.x - mtx(0, 3);
                const f32 dz = pos.z - mtx(2, 3);
                const f32 dist = sead::Mathf::sqrt(dx * dx + dz * dz);
                if (*mSafeAreaDist_s > dist || dist >= *mSafeAreaDist_s + *mSafeAreaDistRange_s)
                    return;
            }
            ksys::act::disableAttClient(mActor, "AutoAimHidden");
            ksys::act::enableAttClient(mActor, "AutoAim");
            changeChild("飛び出す");
        } else {
            _6c.update();
        }
    } else if (isCurrentChild("出現待機")) {
        if (!visibilityCheckMaybe(mActor->getMtx().getTranslation(), 1.0f))
            return;
        sead::Vector3f target;
        if (!sub_71004EFAE8(&target))
            return;
        mActor->m93(4, 0.0f);
        ksys::act::ai::InlineParamPack pack;
        pack.addVec3(target, "TargetPos", -1);
        changeChild("気づき", &pack);
    }
}

void OctarockServiceHideWait::leave_() {
    if (_68)
        ksys::act::enableAttClient(mActor, "AutoAimHidden");
    if (!_69)
        ksys::act::disableAttClient(mActor, "AutoAim");
    if (auto* awareness = mActor->getAwareness())
        awareness->sub_7100D7EAE4(0);
    mActor->m93(0, 0.0f);
}

void OctarockServiceHideWait::loadParams_() {
    getStaticParam(&mSafeAreaDist_s, "SafeAreaDist");
    getStaticParam(&mSafeAreaDistRange_s, "SafeAreaDistRange");
    getStaticParam(&mMinWaitTime_s, "MinWaitTime");
    getStaticParam(&mMinWaitTimeRand_s, "MinWaitTimeRand");
    getStaticParam(&mNoticeTerrorLevel_s, "NoticeTerrorLevel");
    getStaticParam(&mNoticeWorryRange_s, "NoticeWorryRange");
}

bool OctarockServiceHideWait::isChangeable() const {
    return isCurrentChild("待機") && getCurrentChild()->isChangeable();
}

void OctarockServiceHideWait::sub_71004EF670() {
    if (_68)
        ksys::act::enableAttClient(mActor, "AutoAimHidden");
    if (!_69)
        ksys::act::disableAttClient(mActor, "AutoAim");
    const f32 time = *mMinWaitTime_s + *mMinWaitTimeRand_s * sead::GlobalRandom::instance()->getF32();
    _6c = ksys::Timer(time, time);
    changeChild("待機");
}

// NON_MATCHING: worry-filter construction and shared return/cleanup branches.
bool OctarockServiceHideWait::sub_71004EFAE8(sead::Vector3f* out) {
    auto* awareness = mActor->getAwareness();
    if (!awareness)
        return false;

    auto* target = sub_71005D9050(mActor);
    if (target && target->hasProcInCalcState()) {
        Unk_71024514c0 filter(mActor);
        while (auto* sensor = awareness->_260[0]) {
            auto* entry = ksys::act::sub_7100D7EEE8(&sensor->_8, &filter);
            if (!entry)
                break;
            if (entry->_0.mLink == *target) {
                if (out)
                    *out = entry->_88;
                return true;
            }
        }
    } else {
        Unk_71024514c0 filter(mActor);
        if (auto* sensor = awareness->_260[0]) {
            if (auto* entry = ksys::act::sub_7100D7EEE8(&sensor->_8, &filter)) {
                if (out)
                    *out = entry->_88;
                return true;
            }
        }
    }

    if (auto* sensor = awareness->_260[2]) {
        if (sensor->_8.size() >= 1) {
            if (auto* entry = ksys::act::sub_7100D78E30(&sensor->_8, 0)) {
                if (*mNoticeTerrorLevel_s <= entry->_a4) {
                    if (out)
                        *out = entry->_88;
                    return true;
                }
            }
        }
    }

    f32 range = *mNoticeWorryRange_s;
    if (range < 0.0f) {
        auto* current_awareness = mActor->getAwareness();
        if (!current_awareness)
            return false;
        Unk_71023e2780 request;
        if (auto* sensor = current_awareness->_260[3]) {
            range = sensor->m4(&request) ? request._8 : 0.0f;
            if (!(range > 0.0f))
                return false;
        } else {
            range = 0.0f;
        }
    }
    if (!(range > 0.0f))
        return false;

    Unk_7102451510 filter;
    filter._28 = mActor;
    if (auto* sensor = awareness->_260[3]) {
        if (auto* entry = ksys::act::sub_7100D7EEE8(&sensor->_8, &filter)) {
            if (entry->_a8 <= range) {
                if (out)
                    *out = entry->_88;
                return true;
            }
        }
    }
    return false;
}

}  // namespace uking::ai
