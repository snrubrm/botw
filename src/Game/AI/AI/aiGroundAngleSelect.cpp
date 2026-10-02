#include "Game/AI/AI/aiGroundAngleSelect.h"
#include <math/seadMathCalcCommon.h>
#include "KingSystem/ActorSystem/actActor.h"
#include "KingSystem/Physics/CharacterController/physCharacterController.h"

namespace uking::ai {

GroundAngleSelect::GroundAngleSelect(const InitArg& arg) : ksys::act::ai::Ai(arg) {}

GroundAngleSelect::~GroundAngleSelect() = default;

bool GroundAngleSelect::init_(sead::Heap* heap) {
    return ksys::act::ai::Ai::init_(heap);
}

// NON_MATCHING: block order of the two changeChild calls ("平地" first in the original)
void GroundAngleSelect::enter_(ksys::act::ai::InlineParamPack* params) {
    const f32 cos = sead::Mathf::cos(*mSlopeAngle_s);
    sead::Vector3f normal;
    auto* cc = mActor->getCharacterController();
    if ((cc && cc->sub_7100F5F234(&normal) && normal.y < cos) ||
        (*mIsCheckActorMtx_s && mActor->getMtx().m[1][1] < cos)) {
        changeChild("斜面", params);
    } else {
        changeChild("平地", params);
    }
}

// NON_MATCHING: block order of the slope test (the original's normal shares its stack slot with the
// SafeString temporaries, as if the test were an inline helper)
void GroundAngleSelect::calc_() {
    auto* child = getCurrentChild();
    if (child->isFinished() || child->isFailed() || !child->isChangeable() ||
        !*mIsCheckEveryFrame_s) {
        return;
    }

    bool on_slope;
    {
        const f32 cos = sead::Mathf::cos(*mSlopeAngle_s);
        sead::Vector3f normal;
        auto* cc = mActor->getCharacterController();
        on_slope = (cc && cc->sub_7100F5F234(&normal) && normal.y < cos) ||
                   (*mIsCheckActorMtx_s && mActor->getMtx().m[1][1] < cos);
    }
    if (on_slope) {
        if (!isCurrentChild("斜面"))
            changeChild("斜面");
    } else {
        if (!isCurrentChild("平地"))
            changeChild("平地");
    }
}

bool GroundAngleSelect::isFailed() const {
    return ksys::act::ai::Ai::isFailed() || getCurrentChild()->isFailed();
}

bool GroundAngleSelect::isFinished() const {
    return ksys::act::ai::Ai::isFinished() || getCurrentChild()->isFinished();
}

void GroundAngleSelect::leave_() {
    ksys::act::ai::Ai::leave_();
}

void GroundAngleSelect::loadParams_() {
    getStaticParam(&mSlopeAngle_s, "SlopeAngle");
    getStaticParam(&mIsCheckEveryFrame_s, "IsCheckEveryFrame");
    getStaticParam(&mIsCheckActorMtx_s, "IsCheckActorMtx");
}

}  // namespace uking::ai
