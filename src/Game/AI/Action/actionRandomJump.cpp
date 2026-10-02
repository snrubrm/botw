#include "Game/AI/Action/actionRandomJump.h"
#include "Game/AI/aiUnk_710073fa90.h"
#include "Game/AI/aiUnk_71007377D4.h"
#include "KingSystem/ActorSystem/actActor.h"
#include "KingSystem/Physics/CharacterController/physCharacterController.h"
#include "KingSystem/ActorSystem/actUnk_71007A24BC.h"

namespace uking::action {

RandomJump::RandomJump(const InitArg& arg) : ksys::act::ai::Action(arg) {}

RandomJump::~RandomJump() = default;

bool RandomJump::init_(sead::Heap* heap) {
    return ksys::act::ai::Action::init_(heap);
}

void RandomJump::enter_(ksys::act::ai::InlineParamPack* params) {
    ksys::act::ai::Action::enter_(params);
}

void RandomJump::leave_() {
    auto* actor = mActor;
    if (ksys::act::sub_71007A4864(actor, false)) {
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

// NON_MATCHING: the original keeps the normalized up vector in registers and stores it after the epsilon check
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
        on_ground = ksys::act::sub_71007A4864(mActor, false);

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
        const bool hit = ksys::act::sub_71007A4638(actor, false);
        if (hit && !_ac)
            sub_710072C1B4(cc, _a0);
        _ac = hit;
    }

    sub_710073FA94(&_7c, actor);
    sead::Vector3f up = -cc->get70();
    if (up.normalize() < sead::Mathf::epsilon())
        up.set(sead::Vector3f::ey);
    sub_710074006C(&_7c, _a0, up, true, 0.5f, 2 * sead::Mathf::pi(), 0.0f);
    sub_7100740E04(_7c, cc);
}

bool RandomJump::isFinished() const {
    if (_78 == 2 || ActionBase::isFinished())
        return true;
    return _78 == 1 && ksys::act::sub_71007A4864(mActor, false);
}

}  // namespace uking::action
