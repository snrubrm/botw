#include "Game/AI/AI/aiDistanceLostCheck.h"
#include <math/seadMathCalcCommon.h>
#include <random/seadGlobalRandom.h>
#include "KingSystem/ActorSystem/Awareness/actAwarenessInstance.h"
#include "KingSystem/ActorSystem/Awareness/actAwarenessRequest.h"
#include "KingSystem/ActorSystem/actActor.h"
#include "KingSystem/ActorSystem/actAiInlineParam.h"
#include "KingSystem/System/Timer.h"

namespace uking::ai {

DistanceLostCheck::DistanceLostCheck(const InitArg& arg) : ksys::act::ai::Ai(arg) {}

DistanceLostCheck::~DistanceLostCheck() = default;

bool DistanceLostCheck::init_(sead::Heap* heap) {
    return ksys::act::ai::Ai::init_(heap);
}

// NON_MATCHING: the original builds the request objects with other store groupings (the zero stores of `_10` ..
// `_48` are merged as 8 / 16 byte stores in descending order); the layout of the requests is only partly known
void DistanceLostCheck::enter_(ksys::act::ai::InlineParamPack* params) {
    _58 = 0;
    if (auto* awareness = mActor->getAwareness()) {
        switch (*mAddAwarenessRangeType_s) {
        case 1: {
            Unk_71023e26d8 request;
            if (auto* sensor = awareness->_260[0]) {
                if (sensor->m4(&request))
                    _58 = request._8;
            }
            break;
        }
        case 2: {
            Unk_71023e2750 request;
            if (auto* sensor = awareness->_260[1]) {
                if (sensor->m4(&request))
                    _58 = request._8;
            }
            break;
        }
        case 3: {
            Unk_71023e2780 request;
            if (auto* sensor = awareness->_260[3]) {
                if (sensor->m4(&request))
                    _58 = request._8;
            }
            break;
        }
        case 4: {
            Unk_71023e26d8 request;
            if (auto* sensor = awareness->_260[0]) {
                if (sensor->m4(&request))
                    _58 = request._20;
            }
            break;
        }
        }
    }

    const s32 range = *mLostTimer_s;
    const s32 other = static_cast<s32>(range * 1.1f);
    _60 = sead::Mathi::min(range, other);
    _64 = sead::Mathi::max(range, other);
    _5c = _60 == _64 ? _60 : sead::GlobalRandom::instance()->getS32Range(_60, _64);

    ksys::act::ai::InlineParamPack pack;
    pack.addVec3(*mTargetPos_d, "TargetPos", -1);
    changeChild("発見行動", &pack);
}

bool DistanceLostCheck::isFailed() const {
    return ksys::act::ai::Ai::isFailed() || getCurrentChild()->isFailed();
}

bool DistanceLostCheck::isFinished() const {
    return getCurrentChild()->isFinished();
}

bool DistanceLostCheck::isChangeable() const {
    return getCurrentChild()->isChangeable();
}

// NON_MATCHING: the original keeps &_5c in a callee-saved register; regalloc
void DistanceLostCheck::calc_() {
    if (m34())
        ksys::Timer::update(&_5c, -1.0f);
    else
        _5c = _60 == _64 ? _60 : sead::GlobalRandom::instance()->getS32Range(_60, _64);

    auto* child = getCurrentChild();
    if (child->isChangeable() && _5c <= 0.0f)
        setFailed();
    child->setDynamicParam(*mTargetPos_d, "TargetPos");
}

void DistanceLostCheck::leave_() {
    ksys::act::ai::Ai::leave_();
}

void DistanceLostCheck::loadParams_() {
    getStaticParam(&mLostTimer_s, "LostTimer");
    getStaticParam(&mAddAwarenessRangeType_s, "AddAwarenessRangeType");
    getStaticParam(&mLostRange_s, "LostRange");
    getDynamicParam(&mTargetPos_d, "TargetPos");
}

// NON_MATCHING: regalloc (the original squares the range into s1)
bool DistanceLostCheck::sub_7100362928() {
    sead::Vector3f pos;
    mActor->getMtx().getTranslation(pos);
    return (pos - *mTargetPos_d).squaredLength() > sead::Mathf::square(*mLostRange_s + _58);
}

}  // namespace uking::ai
