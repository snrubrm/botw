#include "Game/AI/Action/actionRotateTurnToTarget.h"
#include <limits>
#include "Game/AI/aiUnk_71005D6D10.h"
#include "Game/AI/aiUnk_71007377D4.h"
#include "KingSystem/ActorSystem/AS/ASList.h"
#include "KingSystem/ActorSystem/actActor.h"
#include "KingSystem/ActorSystem/actActorUtil.h"
#include "KingSystem/Physics/CharacterController/physCharacterController.h"
#include "KingSystem/System/Timer.h"
#include "KingSystem/System/VFR.h"
#include "KingSystem/Utils/MathUtil.h"

namespace uking::action {

RotateTurnToTarget::RotateTurnToTarget(const InitArg& arg) : ksys::act::ai::Action(arg) {}

RotateTurnToTarget::~RotateTurnToTarget() = default;

bool RotateTurnToTarget::init_(sead::Heap* heap) {
    return ksys::act::ai::Action::init_(heap);
}

void RotateTurnToTarget::leave_() {
    ksys::act::ai::Action::leave_();
}

void RotateTurnToTarget::loadParams_() {
    getStaticParam(&mAngSpd_s, "AngSpd");
    getStaticParam(&mIsJumpType_s, "IsJumpType");
    getStaticParam(&mASName_s, "ASName");
    getDynamicParam(&mTargetPos_d, "TargetPos");
    getStaticParam(&mIsChangeable_s, "IsChangeable");
}

void RotateTurnToTarget::m32() {
    sub_7100738488(mActor, 0.1f, -sead::Vector3f::ey);
}

void RotateTurnToTarget::enter_(ksys::act::ai::InlineParamPack* params) {
    sead::Vector3f up;
    if (auto* controller = mActor->getCharacterController()) {
        sead::Vector3f dir = controller->get70();
        dir.negate();
        if (dir.normalize() < sead::Mathf::epsilon())
            dir.set(sead::Vector3f::ey);
        up.set(dir);
    } else {
        up.set(sead::Vector3f::ey);
    }

    sead::Vector3f to_target = *mTargetPos_d;
    to_target -= mActor->getMtx().getTranslation();
    ksys::util::sub_71011EFA00(&to_target, to_target, up);
    to_target.normalize();

    sead::Vector3f front;
    mActor->getMtx().getBase(front, 2);
    ksys::util::sub_71011EFA00(&front, front, up);
    front.normalize();

    sead::Vector3f axis;
    f32 angle;
    ksys::util::sub_71011EEB08(&axis, &angle, front, to_target, sead::Vector3f::ey);
    mActor->getASList()->x_6(9, 0, sead::Mathf::rad2deg(angle) * axis.y);

    if (*mIsChangeable_s)
        mFlags.set(Flag::Changeable);
    else
        mFlags.reset(Flag::Changeable);
    _70 = false;
    _50.set(sead::Vector3f::ey);
    playAS(mASName_s.cstr(), false, 0, 0, -1.0f);
    auto* actor = mActor;
    _6c = 0.0f;
    if (actor->getASList()) {
        ksys::as::ASList::Unk4 query;
        if (sub_71005DD5B0(actor, 0x29, &query, 0, 0))
            m33(actor, query._10);
    }
}

void RotateTurnToTarget::calc_() {
    auto* actor = mActor;
    if (auto* as_list = actor->getASList()) {
        ksys::as::ASList::Unk4 query;
        if (sub_71005DD5B0(actor, 0x29, &query, 0, 0))
            m33(actor, query._10);
        else if (as_list->x(0x29, nullptr, 0, 0, &ksys::as::ASList::Unk2::sub_71011638DC, true))
            m34();
        else
            sub_7100738AA8(actor, 0.4f);
        m32();
    }

    if (isFinishedAS(0, 0))
        setFinished();
}

void RotateTurnToTarget::m33(ksys::act::Actor* actor, f32 time) {
    sead::Vector3f pos;
    actor->getMtx().getTranslation(pos);

    sead::Vector3f up = getUpDir(actor);

    sead::Vector3f to_target = *mTargetPos_d;
    to_target -= pos;
    ksys::util::sub_71011EFA00(&to_target, to_target, up);
    to_target.normalize();

    sead::Vector3f front;
    actor->getMtx().getBase(front, 2);
    ksys::util::sub_71011EFA00(&front, front, up);
    front.normalize();

    sead::Vector3f axis;
    f32 angle;
    ksys::util::sub_71011EEB08(&axis, &angle, front, to_target, sead::Vector3f::ey);

    if (*mIsJumpType_s) {
        angle = angle * 1.05f / time;
        ksys::act::sub_7100EE5A14(actor, angle * axis);
        return;
    }

    _70 = false;
    const f32 delta = ksys::VFR::instance()->getDeltaFrame();
    _6c = 0.9f / 0.75f / time;
    _50 = axis;
    sead::Matrix34f mtx;
    ksys::util::sub_71011F00EC(&mtx, to_target, up, pos, false);
    ksys::util::sub_71011F03C8(&mtx, actor->getMtx(), mtx, ksys::VFR::getLerpFactor(_6c),
                               delta * *mAngSpd_s, delta * (*mAngSpd_s * 0.1f),
                               std::numeric_limits<f32>::max(), 0.0f);
    ksys::act::sub_7100EE58C0(actor, mtx);
    _68 = time;
}

void RotateTurnToTarget::m34() {
    auto* actor = mActor;
    if (*mIsJumpType_s) {
        sub_7100738AA8(actor, 0.99f);
        return;
    }
    if (_70) {
        sub_7100738AA8(actor, 0.4f);
        return;
    }

    ksys::Timer::update(&_68, -1.0f);

    sead::Vector3f pos;
    actor->getMtx().getTranslation(pos);

    sead::Vector3f up = getUpDir(actor);

    sead::Vector3f to_target = *mTargetPos_d;
    to_target -= pos;
    ksys::util::sub_71011EFA00(&to_target, to_target, up);
    to_target.normalize();

    sead::Vector3f front;
    actor->getMtx().getBase(front, 2);
    ksys::util::sub_71011EFA00(&front, front, up);
    front.normalize();

    sead::Vector3f axis;
    f32 angle;
    ksys::util::sub_71011EEB08(&axis, &angle, front, to_target, sead::Vector3f::ey);

    if (axis.dot(_50) < 0.0f) {
        _70 = true;
        sub_7100738AA8(mActor, 0.4f);
        return;
    }

    const f32 delta = ksys::VFR::instance()->getDeltaFrame();
    sead::Matrix34f mtx;
    ksys::util::sub_71011F00EC(&mtx, to_target, up, pos, false);
    ksys::util::sub_71011F03C8(&mtx, actor->getMtx(), mtx, ksys::VFR::getLerpFactor(_6c),
                               delta * *mAngSpd_s, delta * (*mAngSpd_s * 0.1f),
                               std::numeric_limits<f32>::max(), 0.0f);
    ksys::act::sub_7100EE58C0(actor, mtx);
}

}  // namespace uking::action
