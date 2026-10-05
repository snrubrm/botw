#include "Game/AI/AI/aiMoveLOSFeedback.h"
#include "KingSystem/ActorSystem/actAiInlineParam.h"
#include "KingSystem/ActorSystem/actActor.h"
#include "KingSystem/Physics/System/physNavMeshCharacter.h"

// Source namespace and input constness are inferred from the named caller; declaration only.
bool sub_7100742664(sead::Vector3f* hit, ksys::phys::NavMeshCharacter* nav,
                    const sead::Vector3f* position, f32 length, f32 tolerance);

namespace uking::ai {

MoveLOSFeedback::MoveLOSFeedback(const InitArg& arg) : ksys::act::ai::Ai(arg) {}

MoveLOSFeedback::~MoveLOSFeedback() = default;

bool MoveLOSFeedback::init_(sead::Heap* heap) {
    _50 = ksys::Timer(0, 0);
    return true;
}

void MoveLOSFeedback::enter_(ksys::act::ai::InlineParamPack* params) {
    _50.value = _50.previous_value = 0.0f;
    ksys::act::ai::InlineParamPack pack;
    pack.addVec3(*mTargetPos_d, "TargetPos", -1);
    changeChild("移動", &pack);
}

void MoveLOSFeedback::calc_() {
    if (isFinished() || isFailed())
        return;
    auto* child = getCurrentChild();
    if (!child) {
        setFailed();
        return;
    }
    if (child->isFinished() || child->isFailed()) {
        if (isCurrentChild("移動")) {
            if (child->isFinished())
                setFinished();
            else
                setFailed();
        } else {
            _50.value = _50.previous_value = *mFramesCooldownFeedback_s;
            ksys::act::ai::InlineParamPack pack;
            pack.addVec3(*mTargetPos_d, "TargetPos", -1);
            changeChild("移動", &pack);
        }
        return;
    }
    if (isCurrentChild("移動")) {
        auto* nav = mActor->m45();
        if (!nav) {
            setFailed();
            return;
        }
        if (!(_50.value <= sead::Mathf::epsilon())) {
            _50.update();
        } else {
            sead::Vector3f hit;
            if (!sub_7100742664(&hit, nav, &nav->_248, *mLOSCheckLength_s, 10.0f))
                changeToCollide(hit);
        }
    }
}

void MoveLOSFeedback::leave_() {
    ksys::act::ai::Ai::leave_();
}

void MoveLOSFeedback::loadParams_() {
    getStaticParam(&mFramesCooldownFeedback_s, "FramesCooldownFeedback");
    getStaticParam(&mLOSCheckLength_s, "LOSCheckLength");
    getDynamicParam(&mTargetPos_d, "TargetPos");
}

void MoveLOSFeedback::changeToCollide(const sead::Vector3f& hit_pos) {
    if (!isCurrentChild("衝突")) {
        ksys::act::ai::InlineParamPack pack;
        pack.addVec3(*mTargetPos_d, "TargetPos", -1);
        pack.addVec3(hit_pos, "HitPos", -1);
        changeChild("衝突", &pack);
    }
}

}  // namespace uking::ai
