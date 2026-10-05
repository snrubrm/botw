#include "Game/AI/AI/aiGanonApproachOnWallRoot.h"
#include "KingSystem/ActorSystem/actActor.h"
#include "KingSystem/Physics/CharacterController/physCharacterController.h"

namespace uking::ai {

GanonApproachOnWallRoot::GanonApproachOnWallRoot(const InitArg& arg) : ksys::act::ai::Ai(arg) {}

GanonApproachOnWallRoot::~GanonApproachOnWallRoot() = default;

bool GanonApproachOnWallRoot::init_(sead::Heap* heap) {
    return ksys::act::ai::Ai::init_(heap);
}

void GanonApproachOnWallRoot::enter_(ksys::act::ai::InlineParamPack* params) {
    _68 = 3;
    if (sub_71003E0DC4())
        setFinished();
    _78.reset(*mApproachTime_s);
    if (auto* controller = mActor->getCharacterController()) {
        _6c = controller->get70();
        const f32 length = _6c.length();
        if (length > 0.0f)
            _6c *= 1.0f / length;
    }
}

void GanonApproachOnWallRoot::leave_() {
    ksys::act::ai::Ai::leave_();
}

void GanonApproachOnWallRoot::loadParams_() {
    getStaticParam(&mApproachTime_s, "ApproachTime");
    getStaticParam(&mMinDist_s, "MinDist");
    getStaticParam(&mMaxDist_s, "MaxDist");
    getStaticParam(&mFinDist_s, "FinDist");
    getStaticParam(&mIsInterpolateYUp_s, "IsInterpolateYUp");
    getDynamicParam(&mTargetPos_d, "TargetPos");
}

}  // namespace uking::ai
