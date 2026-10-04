#include "Game/AI/AI/aiLynelEscapeFromTarget.h"
#include <random/seadGlobalRandom.h>
#include "KingSystem/ActorSystem/actActor.h"
#include "KingSystem/ActorSystem/actAiInlineParam.h"
#include "KingSystem/System/Timer.h"

namespace uking::ai {

LynelEscapeFromTarget::LynelEscapeFromTarget(const InitArg& arg) : ksys::act::ai::Ai(arg) {}

LynelEscapeFromTarget::~LynelEscapeFromTarget() = default;

bool LynelEscapeFromTarget::init_(sead::Heap* heap) {
    return ksys::act::ai::Ai::init_(heap);
}

void LynelEscapeFromTarget::enter_(ksys::act::ai::InlineParamPack* params) {
    const s32 time = *mKeepTime_s;
    _60 = time;
    _64 = _68 = time;
    sead::Vector3f pos;
    if (sub_7100490F58(&pos))
        changeToEscapeMove(pos);
    else
        changeToCannotEscape();
}

// NON_MATCHING: the original materialises `this + 0x60` (the `_60` timer) once in a callee-saved register and uses
// it for the update / store / test; ours addresses `_60` through `this` each time (all other differences are the
// resulting register renaming)
void LynelEscapeFromTarget::calc_() {
    const f32 dist = (mActor->getMtx().getTranslation() - *mTargetPos_d).length();
    const f32 space_min = *mSpaceDistMin_s;
    if (dist > space_min) {
        ksys::Timer::update(&_60, -1.0f);
    } else {
        s32 value = _64;
        if (_64 != _68)
            value = sead::GlobalRandom::instance()->getS32Range(_64, _68);
        _60 = value;
    }

    auto* child = getCurrentChild();
    if (child->isFinished() || child->isFailed()) {
        if (isCurrentChild("逃走移動")) {
            if (dist > space_min || child->isFinished())
                setFinished();
            else
                setFailed();
        } else if (isCurrentChild("逃走不能")) {
            if (dist > space_min) {
                setFinished();
            } else {
                sead::Vector3f pos;
                if (sub_7100490F58(&pos))
                    changeToEscapeMove(pos);
                else
                    setFailed();
            }
        }
    } else if (child->isChangeable()) {
        if (_60 <= 0.0f) {
            setFinished();
            return;
        }
        if (isCurrentChild("逃走不能")) {
            sead::Vector3f pos;
            if (sub_7100490F58(&pos))
                changeToEscapeMove(pos);
        }
    }
}

void LynelEscapeFromTarget::leave_() {
    ksys::act::ai::Ai::leave_();
}

void LynelEscapeFromTarget::loadParams_() {
    getStaticParam(&mKeepTime_s, "KeepTime");
    getStaticParam(&mSpaceDistMin_s, "SpaceDistMin");
    getStaticParam(&mSpaceDist_s, "SpaceDist");
    getStaticParam(&mMoveDistMin_s, "MoveDistMin");
    getDynamicParam(&mTargetPos_d, "TargetPos");
}

}  // namespace uking::ai
