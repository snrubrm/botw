#include "Game/AI/AI/aiViewWait.h"
#include <cmath>
#include <random/seadGlobalRandom.h>
#include "Game/AI/aiUnk_71007377D4.h"
#include "KingSystem/ActorSystem/actActor.h"
#include "KingSystem/Physics/CharacterController/physCharacterController.h"
#include "KingSystem/Utils/MathUtil.h"
#include "KingSystem/ActorSystem/actAiInlineParam.h"

namespace uking::ai {

ViewWait::ViewWait(const InitArg& arg) : ksys::act::ai::Ai(arg) {}

ViewWait::~ViewWait() = default;

bool ViewWait::m38() {
    sead::Vector3f front;
    mActor->getMtx().getBase(front, 2);
    front.y = 0;
    front.normalize();

    sead::Vector3f up;
    if (auto* controller = mActor->getCharacterController())
        up = getUpDir(controller->get70());
    else
        up = sead::Vector3f::ey;

    const sead::Vector3f pos = mActor->getMtx().getTranslation();
    sead::Vector3f dir = m34();
    dir -= pos;
    ksys::util::sub_71011EFA00(&dir, dir, up);
    dir.y = 0;
    if (sead::Mathf::equalsEpsilon(dir.normalize(), 0.0f))
        return true;
    return front.dot(dir) >= std::cos(*mTurnStartAngle_s);
}

void ViewWait::enter_(ksys::act::ai::InlineParamPack* params) {
    if (m38())
        m36();
    else
        m37();
}

// NON_MATCHING: the two Timer float stores are not paired into an stp
void ViewWait::calc_() {
    mTimer.update();
    if (m35())
        return;

    auto* child = getCurrentChild();
    if (!*mCheckOnce_s && isCurrentChild("待機")) {
        if (m38()) {
            _5c = false;
        } else if (_5c) {
            mTimer.update();
        } else {
            _5c = true;
            const s32 time = 4 + sead::GlobalRandom::instance()->getU32(3);
            mTimer = ksys::Timer(time, time);
        }

        if (child->isChangeable() && _5c && mTimer.value <= sead::Mathf::epsilon()) {
            m37();
            return;
        }
    }

    child->setDynamicParam(m34(), "TargetPos");
}

bool ViewWait::isFinished() const {
    if (mFlags.isOn(Flag::Finished))
        return true;
    if (isCurrentChild("待機"))
        return getCurrentChild()->isFinished();
    return false;
}

bool ViewWait::m35() {
    auto* child = getCurrentChild();
    if (!child->isFinished() && !child->isFailed())
        return false;

    if (isCurrentChild("待機")) {
        setFinished();
        return false;
    }
    if (isCurrentChild("回転")) {
        m36();
        return true;
    }
    return false;
}

void ViewWait::m36() {
    _5c = false;
    ksys::act::ai::InlineParamPack params;
    params.addVec3(m34(), "TargetPos", -1);
    m39(&params);
    changeChild("待機", &params);
}

void ViewWait::m37() {
    _5c = false;
    ksys::act::ai::InlineParamPack params;
    params.addVec3(m34(), "TargetPos", -1);
    m39(&params);
    changeChild("回転", &params);
}

void ViewWait::loadParams_() {
    getStaticParam(&mTurnStartAngle_s, "TurnStartAngle");
    getStaticParam(&mCheckOnce_s, "CheckOnce");
    getDynamicParam(&mTargetPos_d, "TargetPos");
}

}  // namespace uking::ai
