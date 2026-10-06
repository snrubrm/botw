#include "Game/AI/AI/aiWillBallFollowAttack.h"
#include <math/seadMathCalcCommon.h>
#include <random/seadGlobalRandom.h>
#include "KingSystem/ActorSystem/Profiles/actBullet.h"
#include "KingSystem/ActorSystem/actActor.h"
#include "KingSystem/ActorSystem/actChemical.h"
#include "KingSystem/ActorSystem/actAiInlineParam.h"
#include "KingSystem/Utils/MathUtil.h"
#include "KingSystem/System/Timer.h"
#include "KingSystem/World/worldManager.h"
#include "KingSystem/World/worldWeatherMgr.h"

namespace uking::ai {

WillBallFollowAttack::WillBallFollowAttack(const InitArg& arg) : ksys::act::ai::Ai(arg) {}

WillBallFollowAttack::~WillBallFollowAttack() = default;

bool WillBallFollowAttack::init_(sead::Heap* heap) {
    return ksys::act::ai::Ai::init_(heap);
}

void WillBallFollowAttack::enter_(ksys::act::ai::InlineParamPack* params) {
    _78 = 0;
    _80 = _84 = *mDelayTimer_s;
    _7c = _80;
    _88 = false;

    sead::Vector3f target = *mTargetPos_d;
    const f32 freq = sead::Mathf::pi2() / *mCycleY_s;
    target.y += *mAmplitudeY_s * sead::Mathf::sin(_78 * freq);
    const sead::Vector3f pos = mActor->getMtx().getTranslation();
    if (sead::Mathf::sqrt(ksys::util::sqXZDistance(target, pos)) < *mImmidiateLightningXZ_s &&
        sead::Mathf::abs(pos.y - target.y) < *mImmidiateLightningY_s) {
        sub_71005F34A0();
    } else {
        sub_71005F35E4();
    }
}

// NON_MATCHING: everything but the address CSE matches: the original keeps &_7c in a register (store after the random
// roll, the `_7c > 0` load) and recomputes &_78 for the Timer call; ours keeps &_78 (hoisted pre-indexed first load)
// and uses [this, #0x7c] directly, which shifts x20 / x21 and the load scheduling of the first block
void WillBallFollowAttack::calc_() {
    sead::Vector3f target = *mTargetPos_d;
    const f32 freq = sead::Mathf::pi2() / *mCycleY_s;
    target.y += *mAmplitudeY_s * sead::Mathf::sin(_78 * freq);
    const sead::Vector3f pos = mActor->getMtx().getTranslation();
    bool near = false;
    if (sead::Mathf::sqrt(ksys::util::sqXZDistance(target, pos)) < *mImmidiateLightningXZ_s &&
        sead::Mathf::abs(pos.y - target.y) < *mImmidiateLightningY_s) {
        near = true;
        _7c = _80 == _84 ? _80 : sead::GlobalRandom::instance()->getS32Range(_80, _84);
    } else {
        ksys::Timer::update(&_7c, -1.0f);
    }
    ksys::Timer::update(&_78, 1.0f);

    if (auto* chemical = mActor->getChemicalStuff(); chemical && chemical->sub_7100D9472C()) {
        if (near && !_88) {
            sead::DynamicCast<ksys::act::Bullet>(mActor);
            if (auto* wm = ksys::world::Manager::instance()) {
                auto* weather = wm->getWeatherMgr();
                if (weather && !_88)
                    weather->sub_71010EDEBC(weather->x() + *mImmidiateLightningTime_s);
            }
            _88 = true;
        }
    } else {
        _88 = false;
    }

    auto* child = getCurrentChild();
    if (child->isFinishedOrFailed()) {
        if (isCurrentChild("追尾"))
            sub_71005F34A0();
        else
            setFinished();
    } else if (child->isChangeable()) {
        if (isCurrentChild("待機")) {
            if (_7c <= 0) {
                sub_71005F35E4();
                return;
            }
        } else if (isCurrentChild("追尾")) {
            sead::Vector3f target2 = *mTargetPos_d;
            const f32 freq2 = sead::Mathf::pi2() / *mCycleY_s;
            target2.y += *mAmplitudeY_s * sead::Mathf::sin(_78 * freq2);
            const sead::Vector3f pos2 = mActor->getMtx().getTranslation();
            if (sead::Mathf::sqrt(ksys::util::sqXZDistance(target2, pos2)) < *mImmidiateLightningXZ_s &&
                sead::Mathf::abs(pos2.y - target2.y) < *mImmidiateLightningY_s) {
                sub_71005F34A0();
                return;
            }
        }
    }

    sead::Vector3f target3 = *mTargetPos_d;
    const f32 freq3 = sead::Mathf::pi2() / *mCycleY_s;
    target3.y += *mAmplitudeY_s * sead::Mathf::sin(_78 * freq3);
    child->setDynamicParam(target3, "TargetPos");
}

void WillBallFollowAttack::sub_71005F34A0() {
    sead::Vector3f target = *mTargetPos_d;
    const f32 amp = *mAmplitudeY_s;
    const f32 rate = sead::Mathf::pi2() / *mCycleY_s;
    target.y += amp * sead::Mathf::sin(rate * _78);
    ksys::act::ai::InlineParamPack params;
    params.addVec3(target, "TargetPos", -1);
    params.addVec3(*mCenterPos_d, "CenterPos", -1);
    changeChild("待機", &params);
}

void WillBallFollowAttack::sub_71005F35E4() {
    sead::Vector3f target = *mTargetPos_d;
    const f32 amp = *mAmplitudeY_s;
    const f32 rate = sead::Mathf::pi2() / *mCycleY_s;
    target.y += amp * sead::Mathf::sin(rate * _78);
    ksys::act::ai::InlineParamPack params;
    params.addVec3(target, "TargetPos", -1);
    params.addVec3(*mCenterPos_d, "CenterPos", -1);
    m34(&params);
    changeChild("追尾", &params);
}

void WillBallFollowAttack::leave_() {
    ksys::act::ai::Ai::leave_();
}

void WillBallFollowAttack::loadParams_() {
    getStaticParam(&mImmidiateLightningTime_s, "ImmidiateLightningTime");
    getStaticParam(&mCycleY_s, "CycleY");
    getStaticParam(&mDelayTimer_s, "DelayTimer");
    getStaticParam(&mImmidiateLightningXZ_s, "ImmidiateLightningXZ");
    getStaticParam(&mImmidiateLightningY_s, "ImmidiateLightningY");
    getStaticParam(&mAmplitudeY_s, "AmplitudeY");
    getDynamicParam(&mTargetPos_d, "TargetPos");
    getDynamicParam(&mCenterPos_d, "CenterPos");
}

}  // namespace uking::ai
