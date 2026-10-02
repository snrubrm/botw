#include "Game/AI/AI/aiViewMove.h"
#include <random/seadGlobalRandom.h>
#include "KingSystem/ActorSystem/actAiInlineParam.h"

namespace uking::ai {

ViewMove::ViewMove(const InitArg& arg) : ksys::act::ai::Ai(arg) {}

ViewMove::~ViewMove() = default;

bool ViewMove::init_(sead::Heap* heap) {
    return ksys::act::ai::Ai::init_(heap);
}

void ViewMove::enter_(ksys::act::ai::InlineParamPack* params) {
    if (m37())
        m35();
    else
        m36();
}

void ViewMove::calc_() {
    _50.update();

    auto* child = getCurrentChild();
    if (child->isFinished() || child->isFailed()) {
        if (isCurrentChild("移動")) {
            if (child->isFinished())
                setFinished();
            else
                setFailed();
        } else if (isCurrentChild("回転")) {
            m35();
            return;
        }
    }

    if (!*mCheckOnce_s && isCurrentChild("移動")) {
        if (m37()) {
            _5c = false;
        } else if (_5c) {
            _50.update();
        } else {
            _5c = true;
            const s32 time = 4 + sead::GlobalRandom::instance()->getU32(3);
            _50 = ksys::Timer(time, time);
        }

        if (child->isChangeable() && _5c && _50.value <= sead::Mathf::epsilon()) {
            m36();
            return;
        }
    }

    child->setDynamicParam(m34(), "TargetPos");
}

void ViewMove::leave_() {
    ksys::act::ai::Ai::leave_();
}

void ViewMove::loadParams_() {
    getStaticParam(&mTurnStartAngle_s, "TurnStartAngle");
    getStaticParam(&mCheckOnce_s, "CheckOnce");
    getDynamicParam(&mTargetPos_d, "TargetPos");
}

bool ViewMove::isFailed() const {
    return ksys::act::ai::Ai::isFailed() || getCurrentChild()->isFailed();
}

bool ViewMove::isFinished() const {
    return ksys::act::ai::Ai::isFinished() ||
           (isCurrentChild("移動") && getCurrentChild()->isFinished());
}

const sead::Vector3f& ViewMove::m34() {
    return *mTargetPos_d;
}

void ViewMove::m35() {
    _5c = false;
    ksys::act::ai::InlineParamPack pack;
    pack.addVec3(m34(), "TargetPos", -1);
    changeChild("移動", &pack);
}

void ViewMove::m36() {
    _5c = false;
    ksys::act::ai::InlineParamPack pack;
    pack.addVec3(m34(), "TargetPos", -1);
    changeChild("回転", &pack);
}

}  // namespace uking::ai
