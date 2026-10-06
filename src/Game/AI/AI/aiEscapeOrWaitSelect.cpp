#include "Game/AI/AI/aiEscapeOrWaitSelect.h"
#include <math/seadMathCalcCommon.h>
#include "Game/AI/aiUnk_71007377D4.h"
#include "KingSystem/ActorSystem/actActor.h"
#include "KingSystem/Utils/MathUtil.h"
#include "KingSystem/ActorSystem/actAiInlineParam.h"

namespace uking::ai {

EscapeOrWaitSelect::EscapeOrWaitSelect(const InitArg& arg) : ksys::act::ai::Ai(arg) {}

EscapeOrWaitSelect::~EscapeOrWaitSelect() = default;

bool EscapeOrWaitSelect::init_(sead::Heap* heap) {
    return ksys::act::ai::Ai::init_(heap);
}

bool EscapeOrWaitSelect::sub_71003C9440(sead::Vector3f* out) {
    const sead::Vector3f pos = mActor->getMtx().getTranslation();
    sead::Vector3f direction(mTargetPos_d->x - pos.x, 0.0f, mTargetPos_d->z - pos.z);
    const f32 length = direction.normalize();
    if (length > *mEscapeRange_s)
        return false;
    direction.x = -direction.x;
    direction.y = -direction.y;
    direction.z = -direction.z;
    const f32 angle = *mCheckBackAngle_s;
    sead::Vector3f ray;
    sead::Vector3f hit;
    for (const f32 a : {0.0f, angle, -angle}) {
        ray = direction;
        ksys::util::sub_71011EF010(&ray, a);
        if (sub_710072FD28(mActor, ray, &hit, -1, *mEscapeMoveDistMax_s, -1.0f, -1.0f, -1.0f)) {
            *out = hit;
            return true;
        }
        const f32 to_hit = sead::Mathf::sqrt((hit.x - pos.x) * (hit.x - pos.x) +
                                             (hit.z - pos.z) * (hit.z - pos.z));
        if (to_hit > *mEscapeMoveDistMin_s) {
            const f32 from_target = sead::Mathf::sqrt(
                (hit.x - mTargetPos_d->x) * (hit.x - mTargetPos_d->x) +
                (hit.z - mTargetPos_d->z) * (hit.z - mTargetPos_d->z));
            if (from_target > *mEscapeRange_s) {
                *out = hit;
                return true;
            }
        }
    }
    return false;
}

void EscapeOrWaitSelect::enter_(ksys::act::ai::InlineParamPack* params) {
    sead::Vector3f pos;
    if (sub_71003C9440(&pos))
        changeToEscapeMove(pos);
    else
        changeToCannotEscape();
}

void EscapeOrWaitSelect::calc_() {}

bool EscapeOrWaitSelect::isFailed() const {
    return getCurrentChild()->isFailed();
}

bool EscapeOrWaitSelect::isFinished() const {
    return getCurrentChild()->isFinished();
}

void EscapeOrWaitSelect::leave_() {
    ksys::act::ai::Ai::leave_();
}

void EscapeOrWaitSelect::loadParams_() {
    getStaticParam(&mEscapeRange_s, "EscapeRange");
    getStaticParam(&mEscapeMoveDistMin_s, "EscapeMoveDistMin");
    getStaticParam(&mEscapeMoveDistMax_s, "EscapeMoveDistMax");
    getStaticParam(&mCheckBackAngle_s, "CheckBackAngle");
    getDynamicParam(&mTargetPos_d, "TargetPos");
}

}  // namespace uking::ai
