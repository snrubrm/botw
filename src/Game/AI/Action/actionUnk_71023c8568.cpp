#include "Game/AI/Action/actionUnk_71023c8568.h"
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

Unk_71023c8568::Unk_71023c8568(ksys::act::ai::ActionBase* owner) : Unk_71025afc58(owner) {}

void Unk_71023c8568::enter_(ksys::act::ai::InlineParamPack* params) {
    sead::Vector3f up;
    if (auto* controller = mOwner->getActor()->getCharacterController()) {
        sead::Vector3f dir = controller->get70();
        dir.negate();
        if (dir.normalize() < sead::Mathf::epsilon())
            dir.set(sead::Vector3f::ey);
        up.set(dir);
    } else {
        up.set(sead::Vector3f::ey);
    }

    sead::Vector3f to_target;
    m13(&to_target);
    to_target -= mOwner->getActor()->getMtx().getTranslation();
    ksys::util::sub_71011EFA00(&to_target, to_target, up);
    to_target.normalize();

    sead::Vector3f front;
    mOwner->getActor()->getMtx().getBase(front, 2);
    ksys::util::sub_71011EFA00(&front, front, up);
    front.normalize();

    sead::Vector3f axis;
    f32 angle;
    ksys::util::sub_71011EEB08(&axis, &angle, front, to_target, sead::Vector3f::ey);
    mOwner->getActor()->getASList()->x_6(9, 0, sead::Mathf::rad2deg(angle) * axis.y);

    mFlags.reset(Flag::Changeable);
    _58 = false;
    _38.set(sead::Vector3f::ey);
    auto* actor = mOwner->getActor();
    _54 = 0.0f;
    if (actor->getASList()) {
        ksys::as::ASList::Unk4 query;
        if (sub_71005DD5B0(actor, 0x29, &query, 0, 0))
            m15(actor, query._10);
    }
}

void Unk_71023c8568::calc_() {
    auto* actor = mOwner->getActor();
    auto* as_list = actor->getASList();
    if (!as_list)
        return;

    ksys::as::ASList::Unk4 query;
    if (sub_71005DD5B0(actor, 0x29, &query, 0, 0)) {
        m15(actor, query._10);
        if (*mIsJumpType_s)
            mFlags.reset(Flag::Changeable);
    } else if (as_list->x(0x29, nullptr, 0, 0, &ksys::as::ASList::Unk2::sub_71011638DC, true)) {
        m16();
    } else {
        mFlags.set(Flag::Changeable);
        sub_7100738AA8(actor, 0.4f);
    }
    m14();
}

void Unk_71023c8568::loadParams_() {
    getStaticParam(&mAngSpd_s, "AngSpd");
    getStaticParam(&mIsJumpType_s, "IsJumpType");
}

void Unk_71023c8568::m14() {
    sub_7100738488(mOwner->getActor(), 0.1f, -sead::Vector3f::ey);
}

void Unk_71023c8568::m15(ksys::act::Actor* actor, f32 time) {
    sead::Vector3f pos;
    actor->getMtx().getTranslation(pos);

    sead::Vector3f up = getUpDir(actor);

    sead::Vector3f to_target;
    m13(&to_target);
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

    const f32 delta = ksys::VFR::instance()->getDeltaFrame();
    _54 = 0.9f / 0.75f / time;
    _38 = axis;
    sead::Matrix34f mtx;
    ksys::util::sub_71011F00EC(&mtx, to_target, up, pos, false);
    ksys::util::sub_71011F03C8(&mtx, actor->getMtx(), mtx, ksys::VFR::getLerpFactor(_54),
                               delta * *mAngSpd_s, delta * (*mAngSpd_s * 0.1f),
                               std::numeric_limits<f32>::max(), 0.0f);
    ksys::act::sub_7100EE58C0(actor, mtx);
    _50 = time;
}

void Unk_71023c8568::m16() {
    auto* actor = mOwner->getActor();
    if (*mIsJumpType_s) {
        sub_7100738AA8(actor, 0.99f);
        return;
    }
    if (_58) {
        sub_7100738AA8(actor, 0.4f);
        return;
    }

    ksys::Timer::update(&_50, -1.0f);

    sead::Vector3f pos;
    actor->getMtx().getTranslation(pos);

    sead::Vector3f up = getUpDir(actor);

    sead::Vector3f to_target;
    m13(&to_target);
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

    if (axis.dot(_38) < 0.0f) {
        _58 = true;
        sub_7100738AA8(mOwner->getActor(), 0.4f);
        return;
    }

    const f32 delta = ksys::VFR::instance()->getDeltaFrame();
    sead::Matrix34f mtx;
    ksys::util::sub_71011F00EC(&mtx, to_target, up, pos, false);
    ksys::util::sub_71011F03C8(&mtx, actor->getMtx(), mtx, ksys::VFR::getLerpFactor(_54),
                               delta * *mAngSpd_s, delta * (*mAngSpd_s * 0.1f),
                               std::numeric_limits<f32>::max(), 0.0f);
    ksys::act::sub_7100EE58C0(actor, mtx);
}
