#include "Game/AI/AI/aiLynelEscapeFromTarget.h"
#include <random/seadGlobalRandom.h>
#include "KingSystem/ActorSystem/actActor.h"
#include "KingSystem/ActorSystem/actAiInlineParam.h"
#include "KingSystem/System/Timer.h"
#include "KingSystem/Utils/MathUtil.h"

bool sub_710072F99C(ksys::act::Actor* actor, const sead::Vector3f& from, const sead::Vector3f& to,
                    sead::Vector3f* out_pos, s32 kind, f32 tolerance, f32 unused);

namespace uking::ai {

LynelEscapeFromTarget::LynelEscapeFromTarget(const InitArg& arg) : ksys::act::ai::Ai(arg) {}

LynelEscapeFromTarget::~LynelEscapeFromTarget() = default;

bool LynelEscapeFromTarget::init_(sead::Heap* heap) {
    return ksys::act::ai::Ai::init_(heap);
}

void LynelEscapeFromTarget::enter_(ksys::act::ai::InlineParamPack* params) {
    const s32 time = *mKeepTime_s;
    _60.value = time;
    _60.min = _60.max = time;
    sead::Vector3f pos;
    if (sub_7100490F58(&pos))
        changeToEscapeMove(pos);
    else
        changeToCannotEscape();
}

void LynelEscapeFromTarget::calc_() {
    const f32 dist = (mActor->getMtx().getTranslation() - *mTargetPos_d).length();
    const f32 space_min = *mSpaceDistMin_s;
    if (dist > space_min)
        _60.update();
    else
        _60.reset();

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
        if (_60.value <= 0.0f) {
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

// NON_MATCHING: the original reloads the position copy from memory for `direction` (no store forwarding of z) and
// stores direction.y after direction.x; ours keeps z in a register (`mov w8, w8`) and stores y first.
bool LynelEscapeFromTarget::sub_7100490F58(sead::Vector3f* out) {
    sead::Vector3f position;
    mActor->getMtx().getTranslation(position);
    sead::Vector3f direction = position;
    direction.x = direction.x - mTargetPos_d->x;
    direction.y = 0;
    direction.z = direction.z - mTargetPos_d->z;
    direction.normalize();
    if (sub_71004914E0(out, position, direction))
        return true;
    ksys::util::sub_71011EF010(&direction, sead::Mathf::pi() / 4);
    if (sub_71004914E0(out, position, direction))
        return true;
    ksys::util::sub_71011EF010(&direction, -sead::Mathf::pi() / 2);
    return sub_71004914E0(out, position, direction);
}

bool LynelEscapeFromTarget::sub_71004914E0(sead::Vector3f* out, const sead::Vector3f& pos,
                                           const sead::Vector3f& direction) {
    sead::Vector3f target = direction;
    target *= *mSpaceDist_s;
    target += pos;
    sead::Vector3f hit;
    if (sub_710072F99C(mActor, pos, target, &hit, -1, -1.0f, -1.0f)) {
        *out = target;
        return true;
    }
    if ((hit - pos).length() > *mMoveDistMin_s) {
        *out = hit;
        return true;
    }
    return false;
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
