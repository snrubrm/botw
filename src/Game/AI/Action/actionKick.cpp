#include "Game/AI/Action/actionKick.h"
#include "Game/AI/aiUnk_710073fa90.h"
#include "Game/AI/aiUnk_71005D6D10.h"
#include "Game/AI/aiUnk_71007368A4.h"
#include "Game/AI/aiUnk_71007377D4.h"
#include "KingSystem/ActorSystem/AS/ASList.h"
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
    if (auto* actor = mActor) {
        const sead::Vector3f gravity = getGravity(actor) * (1.0f / 900.0f);
        if (auto* controller = actor->getCharacterController())
            sub_7100737C0C(controller, 0.1f, gravity);
    }
    switch (_54) {
    case 0:
        sub_71001C8818();
        if (mActor->getASList()->x(0x47, nullptr, 0, 0, &ksys::as::ASList::Unk2::sub_71011637EC,
                                   true)) {
            if (!sub_71005DEC08(mTargetActor_d, mActor, *mCanKickArea_s, 999.0f,
                                sead::Mathf::pi()) ||
                sub_7100739030(mActor, *mTargetActor_d)) {
                sub_71001C8A10();
                _50 = true;
            } else {
                _50 = false;
            }
            _54 = 1;
        }
        break;
    case 1:
        if (auto* actor = mActor) {
            // discarded: the call is in the original
            getGravity(actor);
            if (auto* controller = actor->getCharacterController())
                sub_7100738660(controller, 0.1f);
        }
        break;
    }
    if (isFinishedAS(0, 0)) {
        if (_50)
            setFinished();
        else
            setFailed();
    }
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

// NON_MATCHING: a single fadd: the original adds the z terms as (up.z + impulse.z), ours as (impulse.z + up.z); everything
// else matches (rotation through `Matrix34f::makeR` + `rotate`, with the global axis copied first)
void Kick::sub_71001C8A10() {
    if (!mTargetActor_d)
        return;
    sead::Vector3f impulse;
    mActor->getMtx().getBase(impulse, 2);
    const sead::Vector3f axis = sead::Vector3f::ey;
    sead::Matrix34f rotation;
    rotation.makeR(axis * *mDirAngle_s);
    impulse.rotate(rotation);
    impulse *= *mPower_s;
    const sead::Vector3f up = sead::Vector3f::ey * *mUpRate_s;
    impulse = up + impulse;
    ksys::act::ActorConstDataAccess accessor;
    ksys::act::acquireActor(mTargetActor_d, &accessor);
    _88.sub_7100D3D3C4(0, &impulse, nullptr, true);
    _88.sub_7100D3D49C(mActor, &accessor, 0);
}

}  // namespace uking::action
