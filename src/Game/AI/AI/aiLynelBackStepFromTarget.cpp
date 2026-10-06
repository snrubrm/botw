#include "Game/AI/AI/aiLynelBackStepFromTarget.h"
#include "Game/AI/aiUnk_71007377D4.h"
#include "KingSystem/ActorSystem/actActor.h"
#include "KingSystem/ActorSystem/actAiInlineParam.h"
#include "KingSystem/Utils/MathUtil.h"

namespace uking::ai {

// NON_MATCHING: stack slots of the hit / ray vectors and the rotated-ray copies differ; the logic (cast three
// directions, accept a hit or a far-enough miss) is the same.
bool LynelBackStepFromTarget::sub_710048CEBC(sead::Vector3f* out) {
    const sead::Vector3f position = mActor->getMtx().getTranslation();
    sead::Vector3f direction = position;
    direction -= *mTargetPos_d;
    direction.y = 0.0f;
    direction.normalize();
    sead::Vector3f hit;
    if (sub_710072FD0C(mActor, position, direction, &hit, -1, *mMoveDist_s, -1.0f, -1.0f, -1.0f)) {
        *out = hit;
        return true;
    }
    if ((hit - position).length() <= *mMoveDistMin_s) {
        sead::Vector3f ray = direction;
        ksys::util::sub_71011EF010(&ray, *mAddCheckAngle_s);
        if (sub_710072FD0C(mActor, position, ray, &hit, -1, *mMoveDist_s, -1.0f, -1.0f, -1.0f)) {
            *out = hit;
            return true;
        }
        if ((hit - position).length() <= *mMoveDistMin_s) {
            ray = direction;
            ksys::util::sub_71011EF010(&ray, -*mAddCheckAngle_s);
            if (sub_710072FD0C(mActor, position, ray, &hit, -1, *mMoveDist_s, -1.0f, -1.0f,
                               -1.0f)) {
                *out = hit;
                return true;
            }
            if ((hit - position).length() <= *mMoveDistMin_s)
                return false;
        }
    }
    *out = hit;
    return true;
}

LynelBackStepFromTarget::LynelBackStepFromTarget(const InitArg& arg) : ksys::act::ai::Ai(arg) {}

LynelBackStepFromTarget::~LynelBackStepFromTarget() = default;

bool LynelBackStepFromTarget::init_(sead::Heap* heap) {
    return ksys::act::ai::Ai::init_(heap);
}

void LynelBackStepFromTarget::enter_(ksys::act::ai::InlineParamPack* params) {
    sead::Vector3f pos;
    if (sub_710048CEBC(&pos))
        changeToEscapeMove(pos);
    else
        changeToCannotEscape();
}

void LynelBackStepFromTarget::calc_() {}

bool LynelBackStepFromTarget::isFailed() const {
    return ksys::act::ai::Ai::isFailed() || getCurrentChild()->isFailed();
}

bool LynelBackStepFromTarget::isFinished() const {
    return ksys::act::ai::Ai::isFinished() || getCurrentChild()->isFinished();
}

void LynelBackStepFromTarget::leave_() {
    ksys::act::ai::Ai::leave_();
}

void LynelBackStepFromTarget::loadParams_() {
    getStaticParam(&mMoveDistMin_s, "MoveDistMin");
    getStaticParam(&mMoveDist_s, "MoveDist");
    getStaticParam(&mAddCheckAngle_s, "AddCheckAngle");
    getDynamicParam(&mTargetPos_d, "TargetPos");
}

}  // namespace uking::ai
