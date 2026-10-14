#include "Game/Actor/AI/aiGanonApproachOnWallRoot.h"
#include "Game/Actor/actLastBoss.h"
#include "KingSystem/ActorSystem/actActor.h"
#include "KingSystem/ActorSystem/actAiInlineParam.h"
#include "KingSystem/ActorSystem/aiRootAi.h"
#include "KingSystem/System/VFR.h"
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

// NON_MATCHING: the original's home position shares its stack slot with the param pack (it goes out of scope
// earlier) and the two vector copies share the z store.
// Starts the move child (移動) towards the approach position; returns true when the actor is already high enough on the
// wall and near the target (then the destination is the current position).
bool GanonApproachOnWallRoot::sub_71003E0DC4() {
    sead::Vector3f dst;
    sead::Vector3f target;
    sub_71003E1318(&target);
    sead::Vector3f pos;
    sub_71002C64A0(&pos, mActor);
    sub_71003E14B8(&dst, target);

    bool arrived;
    const sead::Vector3f current = mActor->getMtx().getTranslation();
    sead::Vector3f home;
    mActor->getHomePos(&home);
    if (home.y + 14.0f > current.y ||
        !((current - target).squaredLength() <= *mFinDist_s * *mFinDist_s)) {
        pos = dst;
        arrived = false;
    } else {
        dst = mActor->getMtx().getTranslation();
        arrived = true;
    }

    ksys::act::ai::InlineParamPack pack;
    pack.addVec3(pos, "TargetPos", -1);
    pack.addVec3(dst, "DstPos", -1);
    pack.addBool(!testRootAiFlag2(ksys::act::ai::RootAiFlag2::_0), "IsChangeable", -1);
    changeChild("移動", &pack);
    return arrived;
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

// NON_MATCHING: the up-vector interpolation into _6c (stores and the copy are scheduled differently); the unused home
// position (first getHomePos) is in the original.
void GanonApproachOnWallRoot::calc_() {
    sead::Vector3f dst;
    sead::Vector3f target;
    sub_71003E1318(&target);
    _78.update();
    sub_71003E14B8(&dst, target);
    sead::Vector3f pos;
    sub_71002C64A0(&pos, mActor);
    sead::Vector3f home;
    mActor->getHomePos(&home);

    const sead::Vector3f current = mActor->getMtx().getTranslation();
    sead::Vector3f current_home;
    mActor->getHomePos(&current_home);
    if ((!(current_home.y + 14.0f > current.y) &&
         (current - target).squaredLength() <= *mFinDist_s * *mFinDist_s) ||
        _78.value <= sead::Mathf::epsilon()) {
        setFinished();
    }
    getCurrentChild()->setDynamicParam(pos, "TargetPos");
    getCurrentChild()->setDynamicParam(dst, "DstPos");

    if (!*mIsInterpolateYUp_s)
        return;

    auto* controller = mActor->getCharacterController();
    if (!controller) {
        setFailed();
        return;
    }

    sead::Vector3f up = mActor->getMtx().getTranslation();
    sub_71002C62EC(&up, mActor, 10.0f);
    const f32 max_step = ksys::VFR::instance()->getDeltaFrame() * 0.1f;
    const sead::Vector3f diff = up - _6c;
    const f32 length = diff.length();
    if (length > max_step)
        _6c += diff * (1.0f / length) * max_step;
    else
        _6c = up;
    _6c.normalize();
    controller->sub_7100F5EDE8(_6c);
    controller->sub_7100F5EE1C(_6c * 29.0f);
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
