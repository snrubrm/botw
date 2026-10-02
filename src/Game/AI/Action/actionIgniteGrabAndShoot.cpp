#include "Game/AI/Action/actionIgniteGrabAndShoot.h"
#include "Game/AI/aiUnk_71005D6D10.h"
#include "Game/AI/aiUnk_71007377D4.h"
#include "Game/AI/aiUnk_710073fa90.h"
#include "KingSystem/ActorSystem/actActor.h"
#include "KingSystem/Physics/CharacterController/physCharacterController.h"
#include "KingSystem/Utils/MathUtil.h"

namespace uking::action {

IgniteGrabAndShoot::IgniteGrabAndShoot(const InitArg& arg) : ksys::act::ai::Action(arg) {}

IgniteGrabAndShoot::~IgniteGrabAndShoot() = default;

bool IgniteGrabAndShoot::init_(sead::Heap* heap) {
    if (!_28.init(heap))
        return false;
    return _60.init(heap);
}

void IgniteGrabAndShoot::enter_(ksys::act::ai::InlineParamPack* params) {
    mFlags.reset(Flag::Changeable);
    _a0 = 0;
    _60.enter(params);
    playAS("GrabAndShoot", false, 0, 0, -1.0f);
}

void IgniteGrabAndShoot::leave_() {
    if (_a0 == 1)
        _28.leave();
    else
        _60.leave();
}

void IgniteGrabAndShoot::loadParams_() {
    _28.loadParams();
    _60.loadParams();
    getStaticParam(&mRotSpd_s, "RotSpd");
}

void IgniteGrabAndShoot::calc_() {
    if (_a0 == 1) {
        _28.calc();
    } else {
        _60.calc();
        if (_60.isFinished()) {
            _60.leave();
            _28.enter(nullptr);
            _a0 = 1;
        }
    }

    if (isFinishedAS(0, 0))
        setFinished();

    auto* controller = mActor->getCharacterController();
    if (!controller)
        return;

    if (sub_71005DD798(mActor, 0x29, nullptr, 0, 0)) {
        sub_710073FA94(&_a4, mActor);

        sead::Vector3f up;
        sead::Vector3f dir = controller->get70();
        dir.negate();
        if (dir.normalize() < sead::Mathf::epsilon())
            dir.set(sead::Vector3f::ey);
        up.set(dir);

        sead::Vector3f to_target = *_28.mTargetPos_d;
        to_target -= mActor->getMtx().getTranslation();
        ksys::util::sub_71011EFA00(&to_target, to_target, up);
        to_target.normalize();
        sub_710074006C(&_a4, to_target, up, true, 0.08f, *mRotSpd_s, *mRotSpd_s * 0.1f);
        sub_7100740E04(_a4, controller);
    } else {
        sub_7100738660(controller, 0.75f);
    }
    sub_7100737C0C(controller, 0.75f, -sead::Vector3f::ey);
}

}  // namespace uking::action
