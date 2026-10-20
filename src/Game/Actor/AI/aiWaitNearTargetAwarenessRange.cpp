#include "Game/Actor/AI/aiWaitNearTargetAwarenessRange.h"
#include <math/seadMathCalcCommon.h>
#include "Game/Actor/actEnemy.h"
#include "KingSystem/ActorSystem/Awareness/actAwarenessRequest.h"
#include "KingSystem/ActorSystem/Awareness/actAwarenessInstance.h"
#include "KingSystem/ActorSystem/actAiInlineParam.h"
#include "KingSystem/Physics/System/physNavMeshCharacter.h"

namespace uking::ai {

WaitNearTargetAwarenessRange::WaitNearTargetAwarenessRange(const InitArg& arg)
    : ksys::act::ai::Ai(arg) {}

WaitNearTargetAwarenessRange::~WaitNearTargetAwarenessRange() = default;

bool WaitNearTargetAwarenessRange::init_(sead::Heap* heap) {
    return ksys::act::ai::Ai::init_(heap);
}

void WaitNearTargetAwarenessRange::enter_(ksys::act::ai::InlineParamPack* params) {
    _68 = ksys::Timer(30.0f, 30.0f);
    const auto& pos = mActor->getMtx().getTranslation();
    const sead::Vector2f diff(pos.x - mTargetPos_d->x, pos.z - mTargetPos_d->z);
    const f32 dist = diff.length();
    if (!(*mStartCloseDist_s + sub_71005EA1AC() <= dist)) {
        ksys::act::ai::InlineParamPack pack;
        pack.addVec3(*mTargetPos_d, "TargetPos", -1);
        changeChild("待機", &pack);
    } else if (*mUseNavMeshRequest_s) {
        if (auto* enemy = sead::DynamicCast<act::Enemy>(mActor)) {
            if (auto* state = enemy->_12d0; state && state->_0) {
                state->_0->sub_7100F75F8C(*mTargetPos_d);
                state->_8 = 0;
            }
        }
        ksys::act::ai::InlineParamPack pack;
        pack.addVec3(*mTargetPos_d, "TargetPos", -1);
        changeChild("待機", &pack);
    } else {
        ksys::act::ai::InlineParamPack pack;
        pack.addVec3(*mTargetPos_d, "TargetPos", -1);
        changeChild("近づき", &pack);
    }
}

void WaitNearTargetAwarenessRange::calc_() {
    const auto& pos = mActor->getMtx().getTranslation();
    const sead::Vector2f diff(pos.x - mTargetPos_d->x, pos.z - mTargetPos_d->z);
    const f32 dist = diff.length();
    auto* child = getCurrentChild();
    child->setDynamicParam(*mTargetPos_d, "TargetPos");
    if (child->isFinished() || child->isFailed()) {
        if (*mOutDist_s + sub_71005EA1AC() <= dist ||
            (isCurrentChild("待機") && child->isFailed())) {
            setFailed();
        } else {
            ksys::act::ai::InlineParamPack pack;
            pack.addVec3(*mTargetPos_d, "TargetPos", -1);
            changeChild("待機", &pack);
        }
    } else if (child->isChangeable()) {
        if (*mOutDist_s + sub_71005EA1AC() <= dist) {
            setFailed();
            return;
        }
        if (isCurrentChild("待機")) {
            if (*mStartCloseDist_s + sub_71005EA1AC() <= dist) {
                if (*mUseNavMeshRequest_s) {
                    if (auto* enemy = sead::DynamicCast<act::Enemy>(mActor)) {
                        if (enemy->_12d0 && enemy->_12d0->_8 == 1) {
                            ksys::act::ai::InlineParamPack pack;
                            pack.addVec3(*mTargetPos_d, "TargetPos", -1);
                            changeChild("近づき", &pack);
                            return;
                        }
                    }
                } else {
                    ksys::act::ai::InlineParamPack pack;
                    pack.addVec3(*mTargetPos_d, "TargetPos", -1);
                    changeChild("近づき", &pack);
                    return;
                }
            }
        } else if (*mEndCloseDist_s + sub_71005EA1AC() > dist) {
            ksys::act::ai::InlineParamPack pack;
            pack.addVec3(*mTargetPos_d, "TargetPos", -1);
            changeChild("待機", &pack);
        }
    }
    if (*mUseNavMeshRequest_s) {
        if (_68.value <= sead::Mathf::epsilon()) {
            if (auto* enemy = sead::DynamicCast<act::Enemy>(mActor)) {
                if (auto* state = enemy->_12d0; state && state->_8 != 1 && state->_0) {
                    state->_0->sub_7100F75F8C(*mTargetPos_d);
                    state->_8 = 0;
                }
            }
            _68 = ksys::Timer(30.0f, 30.0f);
        } else {
            _68.update();
        }
    }
}

// NON_MATCHING: request zero-store grouping and shared query branches.
f32 WaitNearTargetAwarenessRange::sub_71005EA1AC() {
    f32 range = 0.0f;
    if (auto* awareness = mActor->getAwareness()) {
        switch (*mAddAwarenessRangeType_s) {
        case 1: {
            Unk_71023e26d8 request{};
            if (auto* sensor = awareness->_260[0]; sensor && sensor->m4(&request))
                range = request.params.sight.radius;
            break;
        }
        case 2: {
            Unk_71023e2750 request{};
            if (auto* sensor = awareness->_260[1]; sensor && sensor->m4(&request))
                range = request._8;
            break;
        }
        case 3: {
            Unk_71023e2780 request;
            if (auto* sensor = awareness->_260[3]; sensor && sensor->m4(&request))
                range = request._8;
            break;
        }
        case 4: {
            Unk_71023e26d8 request{};
            if (auto* sensor = awareness->_260[0]; sensor && sensor->m4(&request))
                range = request.params.alert.radius;
            break;
        }
        }
    }
    return range;
}

void WaitNearTargetAwarenessRange::leave_() {
    ksys::act::ai::Ai::leave_();
}

void WaitNearTargetAwarenessRange::loadParams_() {
    getStaticParam(&mAddAwarenessRangeType_s, "AddAwarenessRangeType");
    getStaticParam(&mStartCloseDist_s, "StartCloseDist");
    getStaticParam(&mOutDist_s, "OutDist");
    getStaticParam(&mEndCloseDist_s, "EndCloseDist");
    getStaticParam(&mUseNavMeshRequest_s, "UseNavMeshRequest");
    getDynamicParam(&mTargetPos_d, "TargetPos");
}

}  // namespace uking::ai
