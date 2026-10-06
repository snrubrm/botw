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

// NON_MATCHING: register numbering (the original keeps the x difference of the flattened direction in s8 and
// reads the actor's y without a copy of its translation) and the order of the early-out copy.
void GanonApproachOnWallRoot::sub_71003E1318(sead::Vector3f* out) {
    const sead::Vector3f target = *mTargetPos_d;
    sead::Vector3f home;
    mActor->getHomePos(&home);
    const sead::Vector3f position = mActor->getMtx().getTranslation();
    if (position.y - home.y < 10.0f) {
        *out = position;
        out->y += 20.0f;
        return;
    }
    const sead::Vector3f flat(target.x, home.y, target.z);
    sead::Vector3f dir = home - flat;
    if (dir.x == 0 && dir.y == 0 && dir.z == 0)
        dir = sead::Vector3f::ex;
    const f32 length = dir.normalize();
    f32 dist = length;
    if (!(*mMinDist_s < length))
        dist = *mMinDist_s <= *mMaxDist_s ? *mMinDist_s : *mMaxDist_s;
    *out = home + dir * dist;
    out->y += 16.0f;
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
