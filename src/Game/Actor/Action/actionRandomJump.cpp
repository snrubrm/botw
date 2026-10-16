#include "Game/Actor/Action/actionRandomJump.h"
#include "Game/Actor/aiUnk_710073fa90.h"
#include <random/seadGlobalRandom.h>
#include "KingSystem/Utils/MathUtil.h"
#include "Game/Actor/aiUnk_71007377D4.h"
#include "KingSystem/ActorSystem/actActor.h"
#include "KingSystem/Physics/CharacterController/physCharacterController.h"
#include "KingSystem/ActorSystem/actActorSensorUtil.h"

namespace uking::action {

RandomJump::RandomJump(const InitArg& arg) : ksys::act::ai::Action(arg) {}

RandomJump::~RandomJump() = default;

bool RandomJump::init_(sead::Heap* heap) {
    return ksys::act::ai::Action::init_(heap);
}

// NON_MATCHING: stack layout and register allocation (one more callee-saved register in ours).
void RandomJump::enter_(ksys::act::ai::InlineParamPack* params) {
    _78 = 0;
    auto* cc = mActor->getCharacterController();
    if (!cc) {
        setFailed();
        return;
    }

    sead::Vector3f pos;
    mActor->getMtx().getTranslation(pos);
    const f32 angle_limit = *mAngleLimit_s;
    const f32 angle = angle_limit * 2 * sead::GlobalRandom::instance()->getF32() - angle_limit;
    const f32 distance =
        *mDistanceMaxOffset_s * sead::GlobalRandom::instance()->getF32() + *mDistanceMin_s;
    const f32 height =
        *mHeightMin_s + *mHeightMaxOffset_s * sead::GlobalRandom::instance()->getF32();

    sead::Vector3f dir = mActor->getMtx().getBase(2);
    ksys::util::sub_71011EFA00(&dir, dir, getUpDir(cc->get70()));
    ksys::util::sub_71011EF010(&dir, angle);
    dir.normalize();
    _a0 = dir;

    const sead::Vector3f target = pos + dir * distance;
    f32 speed;
    f32 time = 0.0f;
    const sead::Vector3f gravity = getGravity(mActor) * (1.0f / 900.0f);
    const f32 value =
        sub_710072CD88(height, &speed, &time, &pos, &target, &gravity) ? speed : 0.0f;
    _60.value = _60.prev_value = value;
    _60.updateStats();
    cc->sub_7100F5EDD8(1.0f);
    cc->sub_7100F5E7F0(_60.value * 30.0f);
    sub_710072C1B4(cc, dir);
    cc->sub_7100F62B70(height);
    cc->sub_7100F5EF08(true);
    sub_710073FA90(&_7c, mActor);
    _ac = false;
    playAS(mASName_s.cstr(), false, 0, 0, -1.0f);
}

void RandomJump::leave_() {
    auto* actor = mActor;
    if (isBgGroundHit(actor, false)) {
        if (auto* cc = actor->getCharacterController())
            cc->sub_7100F5F6FC(sead::Vector3f::zero);
    }
}

void RandomJump::loadParams_() {
    getStaticParam(&mAngleLimit_s, "AngleLimit");
    getStaticParam(&mHeightMin_s, "HeightMin");
    getStaticParam(&mHeightMaxOffset_s, "HeightMaxOffset");
    getStaticParam(&mDistanceMin_s, "DistanceMin");
    getStaticParam(&mDistanceMaxOffset_s, "DistanceMaxOffset");
    getStaticParam(&mIsReturnByHitWall_s, "IsReturnByHitWall");
    getStaticParam(&mASName_s, "ASName");
}

// NON_MATCHING: regalloc (this / controller registers swapped: x19 / x20)
void RandomJump::calc_() {
    if (isFinished() || isFailed())
        return;

    auto* actor = mActor;
    auto* cc = actor->getCharacterController();
    if (!cc) {
        setFailed();
        return;
    }

    const u8 state = _78;
    bool on_ground = false;
    auto* controller = mActor->getCharacterController();
    if (!controller || !controller->mFlags.isOn(1))
        on_ground = isBgGroundHit(mActor, false);

    if (state != 0) {
        if (on_ground) {
            cc->sub_7100F5F6FC(sead::Vector3f::zero);
            setFinished();
            _78 = 2;
            return;
        }
    } else if (!on_ground) {
        _78 = 1;
    }

    _60 *= 0.978;
    _60.updateStats();
    cc->sub_7100F5E7F0(_60.value * 30.0f);

    if (*mIsReturnByHitWall_s) {
        const bool hit = isLandedMaybe(actor, false);
        if (hit && !_ac)
            sub_710072C1B4(cc, _a0);
        _ac = hit;
    }

    sub_710073FA94(&_7c, actor);
    sub_710074006C(&_7c, _a0, getUpDir(cc->get70()), true, 0.5f, 2 * sead::Mathf::pi(), 0.0f);
    sub_7100740E04(_7c, cc);
}

bool RandomJump::isFinished() const {
    if (_78 == 2 || ActionBase::isFinished())
        return true;
    return _78 == 1 && isBgGroundHit(mActor, false);
}

}  // namespace uking::action
