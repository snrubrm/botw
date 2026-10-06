#include "Game/AI/Action/actionWaitOnObjBase.h"
#include "KingSystem/Physics/CharacterController/physCharacterController.h"
#include "Game/AI/aiUnk_71007377D4.h"
#include "Game/AI/aiUnk_710073fa90.h"
#include "KingSystem/ActorSystem/actActor.h"
#include "KingSystem/Utils/MathUtil.h"

namespace uking::action {

WaitOnObjBase::WaitOnObjBase(const InitArg& arg) : ksys::act::ai::Action(arg) {}

WaitOnObjBase::~WaitOnObjBase() = default;

bool WaitOnObjBase::init_(sead::Heap* heap) {
    return ksys::act::ai::Action::init_(heap);
}

// NON_MATCHING: same instructions; the original schedules the loads of the two normalisations of
// `velocity` / the `velocity -= up * 0.1f` step element by element (x, then the y/z pair) while ours
// loads x/y first
void WaitOnObjBase::enter_(ksys::act::ai::InlineParamPack* params) {
    auto* actor = mActor;
    auto* controller = actor->getCharacterController();
    if (!controller) {
        setFailed();
        return;
    }
    _ac.changeMotionType(controller, ksys::act::MotionType::_0);
    _a0 = controller->get70();
    controller->sub_7100F5E754(false);
    _9c = controller->sub_7100F5F100();
    _6c = actor->getMtx().getTranslation();

    sead::Vector3f up;
    actor->getMtx().getBase(up, 1);
    up.normalize();
    _78 = up;

    sead::Vector3f velocity = actor->getVelocity();
    ksys::util::sub_71011EFA00(&velocity, velocity, up);
    const f32 speed = velocity.normalize();
    _60.value = speed;
    _60.prev_value = speed;

    velocity -= up * 0.1f;
    velocity.normalize();
    sub_710072C1B4(controller, velocity);

    sead::Vector3f ang_velocity;
    ksys::util::sub_71011EFA54(&ang_velocity, actor->getAngVelocity(), up);
    const f32 ang_speed = ang_velocity.length() / 30.0f;
    _30.value = ang_speed;
    _30.prev_value = ang_speed;
    sub_710073FA90(&_3c, actor);
    mFlags.set(Flag::Changeable);
    _84 = 0;
    _88 = 0;
    _8c = 1.0f;
    _90 = 40.0f;
    _94 = 40.0f;
    _98 = 1.0f;
}

void WaitOnObjBase::leave_() {
    if (auto* controller = mActor->getCharacterController()) {
        _ac.resetMotionType(controller);
        controller->sub_7100F5EE1C(_a0);
        controller->sub_7100F5E754(true);
        controller->sub_7100F5EDE8(sead::Vector3f::ey);
    }
}

void WaitOnObjBase::loadParams_() {
    getStaticParam(&mPosReduceRatio_s, "PosReduceRatio");
    getStaticParam(&mRotReduceRatio_s, "RotReduceRatio");
}

void WaitOnObjBase::calc_() {
    ksys::act::ai::Action::calc_();
}

}  // namespace uking::action
