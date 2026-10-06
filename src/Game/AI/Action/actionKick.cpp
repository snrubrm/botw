#include "Game/AI/Action/actionKick.h"
#include "Game/AI/aiUnk_710073fa90.h"
#include "Game/AI/aiUnk_71007377D4.h"
#include "KingSystem/ActorSystem/actActor.h"
#include "KingSystem/ActorSystem/actActorConstDataAccess.h"
#include "KingSystem/ActorSystem/actActorLinkConstDataAccess.h"
#include "KingSystem/Physics/CharacterController/physCharacterController.h"
#include "KingSystem/Utils/MathUtil.h"

namespace uking::action {

Kick::Kick(const InitArg& arg) : ActionEx(arg) {}

Kick::~Kick() = default;

bool Kick::init_(sead::Heap* heap) {
    return ActionEx::init_(heap);
}

void Kick::enter_(ksys::act::ai::InlineParamPack* params) {
    playAS("Kick", false, 0, 0, -1.0f);
    _50 = false;
    _54 = 0;
    const f32 speed = mActor->getAngVelocity().length();
    _7c.value = speed;
    _7c.prev_value = speed;
    sub_710073FA90(&_58, mActor);
}

void Kick::loadParams_() {
    getStaticParam(&mPower_s, "Power");
    getStaticParam(&mUpRate_s, "UpRate");
    getStaticParam(&mDirAngle_s, "DirAngle");
    getStaticParam(&mCanKickArea_s, "CanKickArea");
    getStaticParam(&mRotSpeed_s, "RotSpeed");
    getDynamicParam(&mTargetActor_d, "TargetActor");
}

void Kick::calc_() {
    ActionEx::calc_();
}

void Kick::sub_71001C8818() {
    auto* controller = mActor->getCharacterController();
    if (!controller)
        return;
    sub_710073FA94(&_58, mActor);
    const sead::Vector3f up = getUpDir(controller->get70());
    ksys::act::ActorConstDataAccess accessor;
    ksys::act::acquireActor(mTargetActor_d, &accessor);
    sead::Vector3f dir =
        accessor.getActorMtx().getTranslation() - mActor->getMtx().getTranslation();
    ksys::util::sub_71011EFA00(&dir, dir, up);
    dir.normalize();
    _7c.lerp(*mRotSpeed_s, 0.1f);
    _7c.updateStats();
    sub_710074006C(&_58, dir, up, true, 0.12f, _7c.value, _7c.value * 0.1f);
    sub_7100740E04(_58, controller);
}

// NON_MATCHING: the original composes the rotation (0, DirAngle, 0) -> Matrix33 and applies it with a different
// association / operand order than sead's makeR + Vector3::mul; calls, constants and the stores match.
void Kick::sub_71001C8A10() {
    if (!mTargetActor_d)
        return;
    sead::Vector3f impulse;
    mActor->getMtx().getBase(impulse, 2);
    sead::Matrix33f rotation;
    rotation.makeR(sead::Vector3f::ey * *mDirAngle_s);
    impulse.mul(rotation);
    impulse = sead::Vector3f::ey * *mUpRate_s + impulse * *mPower_s;
    ksys::act::ActorConstDataAccess accessor;
    ksys::act::acquireActor(mTargetActor_d, &accessor);
    _88.sub_7100D3D3C4(0, &impulse, 0, true);
    _88.sub_7100D3D49C(mActor, &accessor, 0);
}

}  // namespace uking::action
