#include "KingSystem/Sound/Actor/Action/actionEnvSeEmitPointBirdPlayAction.h"
#include "Game/Actor/actEnvSeEmitPoint.h"
#include "KingSystem/ActorSystem/actActor.h"
#include "KingSystem/Sound/sndSound.h"
#include "KingSystem/Utils/InitTimeInfo.h"
#include <math/seadMathCalcCommon.h>
#include <random/seadGlobalRandom.h>

namespace ksys::snd {

namespace {
ksys::util::InitConstants sInitConstants;
ksys::util::InitTimeInfo sInitTimeInfo;
}  // namespace

EnvSeEmitPointBirdPlayAction::EnvSeEmitPointBirdPlayAction(const InitArg& arg)
    : ksys::act::ai::Action(arg) {}

EnvSeEmitPointBirdPlayAction::~EnvSeEmitPointBirdPlayAction() = default;

// NON_MATCHING: only the first case stores 0 directly in the original; we emit mov + the shared
// store (4 bytes more).
bool EnvSeEmitPointBirdPlayAction::init_(sead::Heap* heap) {
    const sead::SafeString& name = getActor()->getName();
    if (name == "EnvSeEmitPointBirdTemperate") {
        _38 = 0;
        return true;
    } else if (name == "EnvSeEmitPointBirdSubTropic")
        _38 = 1;
    else if (name == "EnvSeEmitPointBirdTropical")
        _38 = 2;
    else if (name == "EnvSeEmitPointBirdSubarctic")
        _38 = 3;
    else if (name == "EnvSeEmitPointBirdArctic")
        _38 = 4;
    else if (name == "EnvSeEmitPointBirdArd")
        _38 = 5;
    else if (name == "EnvSeEmitPointBirdWet")
        _38 = 6;
    else if (name == "EnvSeEmitPointBirdWetSubtropic")
        _38 = 7;
    return true;
}

void EnvSeEmitPointBirdPlayAction::enter_(ksys::act::ai::InlineParamPack* params) {
    _20.setNow();
    f32 rate = sub_7100FEA4E4();
    s64 milliseconds;
    if (rate > 0.0f) {
        rate = sead::Mathf::clampMin(rate, 0.2f);
        milliseconds = static_cast<s64>(
            sead::GlobalRandom::instance()->getF32Range(0.5f / rate, 8.0f / rate) * 1000.0f);
    } else {
        milliseconds = -1000;
    }
    _28.setMilliSeconds(milliseconds);
    _30.setNow();
}

void EnvSeEmitPointBirdPlayAction::leave_() {
    ksys::act::ai::Action::leave_();
}

void EnvSeEmitPointBirdPlayAction::loadParams_() {}

// NON_MATCHING: the mgr null test is placed before the IsDerivedFrom result test (branch order).
void EnvSeEmitPointBirdPlayAction::calc_() {
    auto* mgr = SoundMgr::instance()->_38;
    if (mgr && mgr->_a0) {
        _30.setNow();
        _28 = 0;
        _30 += sead::TickSpan::makeFromSeconds(6);
    }

    if (_20.diffToNow().toS64() <= _28.toS64())
        return;

    if (_28.toS64() > 0) {
        auto* actor = mActor;
        if (sead::IsDerivedFrom<uking::act::EnvSeEmitPoint>(actor)) {
            auto* point = static_cast<uking::act::EnvSeEmitPoint*>(actor);
            if (mgr && !point->_844) {
                if (auto* birds = mgr->_58) {
                    sead::Vector3f pos = mActor->getMtx().getTranslation();
                    pos.x += sead::GlobalRandom::instance()->getF32Range(-10.0f, 10.0f);
                    pos.z += sead::GlobalRandom::instance()->getF32Range(-10.0f, 10.0f);
                    birds->sub_71010289D0(point->_848, _38, &pos);
                }
            }
        }
    }

    _20.setNow();
    f32 rate = sub_7100FEA4E4();
    s64 milliseconds;
    if (rate > 0.0f) {
        rate = sead::Mathf::clampMin(rate, 0.2f);
        milliseconds = static_cast<s64>(
            sead::GlobalRandom::instance()->getF32Range(0.5f / rate, 8.0f / rate) * 1000.0f);
    } else {
        milliseconds = -1000;
    }
    _28.setMilliSeconds(milliseconds);
}

}  // namespace ksys::snd
