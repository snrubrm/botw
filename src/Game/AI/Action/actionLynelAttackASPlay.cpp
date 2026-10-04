#include "Game/AI/Action/actionLynelAttackASPlay.h"
#include <cmath>
#include "Game/Actor/actRideable.h"
#include "KingSystem/ActorSystem/AS/ASList.h"
#include "KingSystem/ActorSystem/actActor.h"
#include "Game/AI/aiUnk_71005D6D10.h"
#include "Game/AI/aiUnk_71007320F0.h"
#include "Game/AI/aiUnk_71007377D4.h"
#include "Game/AI/aiUnk_710073fa90.h"
#include "KingSystem/Physics/CharacterController/physCharacterController.h"
#include "KingSystem/System/VFR.h"
#include "KingSystem/Utils/MathUtil.h"

namespace uking::action {

LynelAttackASPlay::LynelAttackASPlay(const InitArg& arg) : ksys::act::ai::Action(arg) {}

LynelAttackASPlay::~LynelAttackASPlay() = default;

bool LynelAttackASPlay::init_(sead::Heap* heap) {
    return ksys::act::ai::Action::init_(heap);
}

// NON_MATCHING: the original loads mActor / the ASList after the float multiply (a once-used local for the
// turn value reproduces it; not applied)
void LynelAttackASPlay::sub_71001DEC28(const sead::Vector3f& pos) {
    sead::Vector3f to_target = *mTargetPos_d;
    to_target -= pos;
    to_target.normalize();

    sead::Vector3f front;
    mActor->getMtx().getBase(front, 2);
    ksys::util::sub_71011EFA00(&front, front, sead::Vector3f::ey);
    front.normalize();

    sead::Vector3f axis;
    f32 angle;
    ksys::util::sub_71011EEB08(&axis, &angle, front, to_target, sead::Vector3f::ey);
    mActor->getASList()->x_6(9, 0, sead::Mathf::rad2deg(angle) * axis.y);
}

void LynelAttackASPlay::enter_(ksys::act::ai::InlineParamPack* params) {
    _1c0 = 0;
    sead::Vector3f pos;
    mActor->getMtx().getTranslation(pos);
    sub_71001DEC28(pos);
    auto* as_list = mActor->getASList();
    auto* rideable = mActor->m132();
    if (!mASName_s.isEmpty()) {
        if (rideable) {
            if (!*mIsIgnoreSame_s || as_list->x_1(0, 0) != mASName_s)
                rideable->_18.sub_7100E786F0(mASName_s);
        } else {
            playAS(mASName_s.cstr(), *mIsIgnoreSame_s, 0, 0, -1.0f);
        }
    }
    if (*mChangeableTiming_s == 0)
        mFlags.set(Flag::Changeable);
    else
        mFlags.reset(Flag::Changeable);
}

void LynelAttackASPlay::leave_() {
    _a8.sub_710070E4C0();
}

void LynelAttackASPlay::loadParams_() {
    getStaticParam(&mWeaponIdx_s, "WeaponIdx");
    getStaticParam(&mEndState_s, "EndState");
    getStaticParam(&mChangeableTiming_s, "ChangeableTiming");
    getStaticParam(&mRotSpeed_s, "RotSpeed");
    getStaticParam(&mSpeed_s, "Speed");
    getStaticParam(&mTransAccRatio_s, "TransAccRatio");
    getStaticParam(&mRotAccRatio_s, "RotAccRatio");
    getStaticParam(&mRange_s, "Range");
    getStaticParam(&mPosReduceRatio_s, "PosReduceRatio");
    getStaticParam(&mRotReduceRatio_s, "RotReduceRatio");
    getStaticParam(&mJumpUpSpeedReduceRatio_s, "JumpUpSpeedReduceRatio");
    getStaticParam(&mIsIgnoreSame_s, "IsIgnoreSame");
    getStaticParam(&mUseAnimeDriven_s, "UseAnimeDriven");
    getStaticParam(&mIsCheckNavMesh_s, "IsCheckNavMesh");
    getStaticParam(&mASName_s, "ASName");
    getDynamicParam(&mTargetPos_d, "TargetPos");
}

// inline-only in the original; name is a guess (the same sequence is inlined at two places of calc_)
inline void LynelAttackASPlay::slowDown(ksys::phys::CharacterController* controller) {
    const f32 speed = controller->sub_7100F5EF00() / 30.0f;
    controller->sub_7100F5E7F0(
        sead::Mathf::clampMin(speed - _1cc * ksys::VFR::instance()->getDeltaFrame(), 0.0f) * 30.0f);
}

void LynelAttackASPlay::sub_71001DF2E0() {
    switch (*mChangeableTiming_s) {
    case 2:
        if (mActor->getASList()->x_7(0, 0, &ksys::as::ASList::Unk2::sub_7101162FE8))
            mFlags.set(Flag::Changeable);
        else
            mFlags.reset(Flag::Changeable);
        break;
    case 3:
        if (sub_71005DD798(mActor, 22, nullptr, 0, 0))
            mFlags.reset(Flag::Changeable);
        else
            mFlags.set(Flag::Changeable);
        break;
    }

    if (isFinishedAS(0, 0)) {
        switch (*mEndState_s) {
        case 2:
            mFlags.set(Flag::Changeable);
            break;
        case 1:
            setFinished();
            break;
        }
    }
}

void LynelAttackASPlay::sub_71001DF3BC(const sead::Vector3f& pos) {
    if (sub_71005DD734(mActor, 41, nullptr, 0, 0)) {
        _a8.sub_710070E4C0();
        _1c0 &= ~3;
    }
    if (sub_71005DD734(mActor, 47, nullptr, 0, 0))
        _1c0 &= ~4;
    if (sub_71005DD734(mActor, 43, nullptr, 0, 0))
        _1c0 &= ~8;

    ksys::as::ASList::Unk4 query41;
    if (sub_71005DD5B0(mActor, 41, &query41, 0, 0)) {
        _1c8 = mActor->getAngVelocity().y;
        if (query41.name.isEmpty()) {
            _1c0 |= 2;
        } else {
            _1c0 |= 1;
            _a8.sub_710070E4EC(query41.name);
        }
    }

    ksys::as::ASList::Unk4 query47;
    if (sub_71005DD5B0(mActor, 47, &query47, 0, 0)) {
        _1c0 |= 4;
        const f32 dx = mTargetPos_d->x - pos.x;
        const f32 dz = mTargetPos_d->z - pos.z;
        const f32 dist = std::sqrt(dx * dx + dz * dz);
        const f32 range = *mRange_s;
        const f32 left =
            sead::Mathf::clampMin(dist - (range + sub_71007320F0(mActor, *mWeaponIdx_s)), 0.0f);
        f32 speed = 0.0f;
        if (left != 0.0f)
            speed = sead::Mathf::clampMax(left / query47._10, *mSpeed_s);
        _1c4 = speed;
    }

    ksys::as::ASList::Unk4 query43;
    if (sub_71005DD5B0(mActor, 43, &query43, 0, 0)) {
        _1c0 |= 8;
        f32 speed;
        if (auto* controller = mActor->getCharacterController()) {
            speed = controller->sub_7100F5EF00() / 30.0f;
        } else {
            const auto& vel = mActor->getVelocity();
            speed = std::sqrt(vel.x * vel.x + vel.z * vel.z);
        }
        if (query43._10 > 0.0f)
            speed /= query43._10;
        _1cc = speed;
    }
}

void LynelAttackASPlay::sub_71001DF63C(f32* speed, const sead::Vector3f& pos) {
    if (*speed <= 0.0f || !*mIsCheckNavMesh_s)
        return;

    sead::Vector3f dir = *mTargetPos_d - pos;
    dir.y = 0.0f;
    const f32 length = dir.normalize();

    sead::Vector3f hit;
    if (sub_710072FD0C(mActor, pos, dir, &hit, -1, length, -1.0f, -1.0f, -1.0f))
        return;

    const f32 dist = sead::Mathf::clampMin((hit - pos).dot(dir), 0.0f);
    const f32 max_speed = dist / ksys::VFR::instance()->getDeltaFrame();
    *speed = sead::Mathf::clampMax(*speed, max_speed);
}

void LynelAttackASPlay::sub_71001DF7D4(f32* speed, const sead::Vector3f& pos) {
    if (*speed <= 0.0f)
        return;

    const f32 dist = (*mTargetPos_d - pos).length();
    const f32 range = *mRange_s;
    const f32 left = sead::Mathf::clampMin(dist - (range + sub_71007320F0(mActor, *mWeaponIdx_s)), 0.0f);
    const f32 max_speed = left / ksys::VFR::instance()->getDeltaFrame();
    *speed = sead::Mathf::clampMax(*speed, max_speed);
}

void LynelAttackASPlay::sub_71001DF8DC(ksys::phys::CharacterController* controller,
                                       const sead::Vector3f& pos) {
    sead::Vector3f dir;
    dir.set(*mTargetPos_d);
    dir -= pos;
    dir.y = 0.0f;
    dir.normalize();

    ksys::VFR::lerp(&_1c8, *mRotSpeed_s, *mRotAccRatio_s, 1.0f, 0.01f);
    sub_710073FA94(&_1d0, mActor);
    sub_710074006C(&_1d0, dir, sead::Vector3f::ey, true, 0.14f, _1c8, 0.0f);
    sub_7100740E04(_1d0, controller);
}

void LynelAttackASPlay::sub_71001DFA04(ksys::phys::CharacterController* controller,
                                       const sead::Vector3f& pos) {
    sead::Vector3f front;
    mActor->getMtx().getBase(front, 2);
    front.normalize();

    f32 speed = front.x * mActor->getVelocity().x + front.y * mActor->getVelocity().y +
                front.z * mActor->getVelocity().z;
    ksys::VFR::lerp(&speed, _1c4, *mTransAccRatio_s, 1.0f, 0.01f);
    sub_71001DF7D4(&speed, pos);
    sub_71001DF63C(&speed, pos);
    controller->sub_7100F5EDBC(front);
    controller->sub_7100F5E7F0(speed * 30.0f);
    controller->sub_7100F5EDD8(1.0f);
    controller->sub_7100F5EDE0(0.0f);
}

void LynelAttackASPlay::calc_() {
    sub_71001DF2E0();
    sead::Vector3f pos;
    mActor->getMtx().getTranslation(pos);
    sub_71001DEC28(pos);
    sub_71001DF3BC(pos);
    sub_710073852C(mActor->getCharacterController(), *mJumpUpSpeedReduceRatio_s);

    if (_1c0 & 1) {
        _a8.sub_710070E714();
        _a8.sub_710070E7A8(mTargetPos_d, 0.14f, *mRotSpeed_s, *mRotAccRatio_s);
        if (!(_1c0 & 4))
            return;

        sead::Vector3f front;
        mActor->getMtx().getBase(front, 2);
        front.normalize();
        f32 speed = _1c4 * 30.0f;
        auto* controller = mActor->getCharacterController();
        if (!controller)
            return;

        sead::Vector3f pos2;
        mActor->getMtx().getTranslation(pos2);
        sub_71001DF63C(&speed, pos2);
        sub_71001DF7D4(&speed, pos2);

        const sead::Vector3f vel = controller->_64;
        sead::Vector3f dir = vel * controller->sub_7100F5EF00() + front * speed;
        const f32 length = dir.normalize();
        controller->sub_7100F5EDBC(dir);
        controller->sub_7100F5E7F0(length);
    } else if (*mUseAnimeDriven_s) {
        auto* as_list = mActor->getASList();
        auto* controller = mActor->getCharacterController();
        if (!as_list || !controller) {
            setFailed();
            return;
        }
        if (_1c0 & 4) {
            if (_1c0 & 2) {
                sub_71001DF8DC(controller, pos);
            } else {
                controller->sub_7100F5FB24(as_list->sub_710115D3B8() * 30.0f);
            }
            sub_71001DFA04(controller, pos);
        } else if (_1c0 & 8) {
            if (_1c0 & 2) {
                sub_71001DF8DC(controller, pos);
            } else {
                controller->sub_7100F5FB24(as_list->sub_710115D3B8() * 30.0f);
            }
            slowDown(controller);
        } else if (_1c0 & 2) {
            uking::act::sub_7100E7F4FC(as_list, controller, 1.0f);
            sub_71001DF8DC(controller, pos);
        } else if (auto* rideable = mActor->m132()) {
            uking::act::sub_7100E7F698(rideable, as_list, controller);
        } else {
            uking::act::sub_7100E7F318(as_list, controller, 1.0f);
        }
    } else {
        auto* controller = mActor->getCharacterController();
        if (!controller) {
            setFailed();
            return;
        }
        if (_1c0 & 4) {
            if (_1c0 & 2) {
                sub_71001DF8DC(controller, pos);
            } else {
                sub_7100738660(controller, *mRotReduceRatio_s);
            }
            sub_71001DFA04(controller, pos);
        } else if (_1c0 & 8) {
            if (_1c0 & 2) {
                sub_71001DF8DC(controller, pos);
            } else {
                sub_7100738660(controller, *mRotReduceRatio_s);
            }
            slowDown(controller);
        } else if (_1c0 & 2) {
            sub_7100737C0C(controller, *mPosReduceRatio_s, -sead::Vector3f::ey);
            sub_71001DF8DC(controller, pos);
        } else {
            sub_7100737C0C(controller, *mPosReduceRatio_s, -sead::Vector3f::ey);
            sub_7100738660(controller, *mRotReduceRatio_s);
        }
    }
}

}  // namespace uking::action
