#include "Game/Actor/actExtendedEntity.h"
#include "KingSystem/Physics/CharacterController/physCharacterController.h"
#include "KingSystem/Physics/Constraint/physLimitHingeCs.h"
#include "KingSystem/Physics/RigidBody/physRigidBody.h"
#include "KingSystem/Physics/System/physUtil.h"
#include "KingSystem/System/VFR.h"
#include <math/seadMathCalcCommon.h>
#include <math/seadQuat.h>

namespace uking::act {

ExtendedEntity::ExtendedEntity() = default;

ExtendedEntity::~ExtendedEntity() = default;

// NON_MATCHING: the compiler combines the two repeated copies of each hinge frame axis.
bool ExtendedEntity::init(const InitArg& arg) {
    if (!arg.controller || !arg.body)
        return true;
    _20 = arg._18;
    _2c = arg._24;
    _30 = arg._28;
    _34 = arg._2c;
    _38 = arg._30;
    _3c = arg._34;
    _40 = arg._38;
    _44 = arg._3c;
    _48 = arg._40;
    _4c = arg._44;
    _50 = arg._48;
    _54 = arg._4c;
    ksys::phys::LimitHingeCs::Param param;
    param.body_a = arg.controller->sub_7100F61A34();
    param.body_b = arg.body;
    param._18 = false;
    param._24 = _20;
    arg.body->getCenterOfMassInLocal(&param._30);
    param._3c = sead::Vector3f::ex;
    param._48 = sead::Vector3f::ex;
    param._54 = sead::Vector3f::ez;
    param._60 = sead::Vector3f::ez;
    param._6c = -sead::Mathf::pi() / 6;
    param._70 = sead::Mathf::pi() / 6;
    _10 = ksys::phys::LimitHingeCs::make(param, arg.heap);
    if (arg.radius > sead::Mathf::epsilon()) {
        _60 = new (arg.heap) FrameSet;
        if (!_60)
            return false;
        _60->_0 = param._24;
        _60->_c = param._30;
        _60->_18 = param._3c;
        _60->_24 = param._48;
        _60->_30 = param._54;
        _60->_3c = param._60;
        _60->_48 = arg.radius;
    }
    _68 = 0;
    _18 = ksys::phys::Unk_71024f9510::make(arg.heap, arg.body, arg.controller, false);
    if (!_10)
        return false;
    _0 = arg.controller;
    _8 = arg.body;
    return true;
}

// NON_MATCHING: the final translation additions and stores are scheduled differently.
void ExtendedEntity::sub_7100E63F70(const sead::Matrix34f& transform, bool attach) {
    _58 = 0;
    if (!_10)
        return;
    _0->sub_7100F5E864(true);
    _8->setFlag100000();
    if (attach && (_0->sub_7100F5E954() || _0->sub_7100F635B4())) {
        sead::Vector3f pivot;
        pivot.setRotated(transform, _20);
        sead::Vector3f center;
        _8->getCenterOfMassInLocal(&center);
        center.setRotated(transform, -center);
        sead::Matrix34f body_transform = transform;
        body_transform.m[0][3] = center.x + (pivot.x + body_transform.m[0][3]);
        body_transform.m[1][3] = center.y + (pivot.y + body_transform.m[1][3]);
        body_transform.m[2][3] = center.z + (pivot.z + body_transform.m[2][3]);
        _8->setTransform(body_transform);
        _8->addToWorld();
        _10->sub_7100F6A0FC(1.0f, _2c);
        // The original discards the constraint operation's bool result.
        _10->sub_7100F6A92C(_8);
        _10->sub_7100F69FF0();
    }
}

// NON_MATCHING: enum temporaries use separate stack slots and the branch layout differs.
void ExtendedEntity::sub_7100E64154(bool disable) {
    if (!_10)
        return;
    if (disable || (_58 & (1 << int(Flag(Flag::_0)))) || !_0->sub_7100F5E954()) {
        if (_10->_50 & 1)
            _10->sub_7100F6A074();
        if (_8->isAddedToWorld())
            _8->removeFromWorld();
    } else {
        if (!(_10->_50 & 1)) {
            if (_60) {
                _10->sub_7100F6E584(_60->_0, _60->_c, _60->_18, _60->_24, _60->_30, _60->_3c);
                _8->setCenterOfMassInLocal(_60->_c);
                _68 = 0;
            }
            _10->sub_7100F6A0FC(1.0f, _2c);
            // The original discards the constraint operation's bool result.
            _10->sub_7100F6A92C(_8);
            _10->sub_7100F69FF0();
        } else if (_58 & (1 << int(Flag(Flag::_4)))) {
            _10->sub_7100F6A0FC(1.0f, _2c);
        }
        const bool force = _58 & (1 << int(Flag(Flag::_1)));
        bool added = false;
        if (!_8->isAddedToWorld()) {
            _8->addToWorld();
            added = true;
        }
        sead::Matrix34f transform;
        _0->physicsXXXGetMtx_1(&transform);
        sub_7100E64318(transform, force || added, added);
        _58 &= ~(1 << int(Flag(Flag::_1)));
    }
    _58 &= ~(1 << int(Flag(Flag::_4)));
}

// NON_MATCHING: matrix and vector arithmetic scheduling differs in the rotation reset path.
bool ExtendedEntity::sub_7100E64318(const sead::Matrix34f& transform, bool force,
                                    bool reset_rotation) {
    sead::Vector3f pivot;
    pivot.setMul(transform, _20);
    sead::Vector3f position;
    _8->getPosition(&position);
    sead::Vector3f center;
    _8->getCenterOfMassInLocal(&center);
    position -= pivot;
    const f32 ratio = position.squaredLength() / center.squaredLength();
    if (!(ratio > 5.76f || ratio < 0.1736111f || force))
        return false;

    center.setRotated(transform, -center);
    sead::Matrix34f body_transform;
    if (reset_rotation) {
        const f32 upper = _10->sub_7100F6E34C();
        const f32 lower = _10->sub_7100F6E340();
        sead::Quatf rotation;
        rotation.setAxisRadian(transform.getBase(0), -((upper + lower) * 0.5f));
        sead::Matrix33f rotation_mtx;
        rotation_mtx.fromQuat(rotation);
        body_transform.setMul(rotation_mtx, transform);
        center.setRotated(rotation_mtx, center);
    } else {
        body_transform = transform;
    }
    body_transform.setTranslation(center + pivot);
    _8->setTransform(body_transform);
    _8->setLinearVelocity(sead::Vector3f::zero, sead::Mathf::epsilon());
    _8->setAngularVelocity(sead::Vector3f::zero, sead::Mathf::epsilon());
    return true;
}

void ExtendedEntity::sub_7100E64E60() {
    if (_10) {
        if (_10->_50 & 1)
            _10->sub_7100F6A074();
        if (_8->isAddedToWorld())
            _8->removeFromWorld();
    }
}

void ExtendedEntity::sub_7100E64EAC(f32 scale) {
    if (_0)
        _0->sub_7100F62DD0(scale);
    if (_8)
        _8->setColImpulseScale(scale);
}

void ExtendedEntity::sub_7100E63F20() {
    if (_18) {
        ksys::phys::sub_7100FCFEB8(_18);
        _18 = nullptr;
    }
    if (_10) {
        ksys::phys::Constraint::destroy(_10);
        _10 = nullptr;
    }
    _0 = nullptr;
    _8 = nullptr;
    if (_60) {
        operator delete(_60);
        _60 = nullptr;
    }
}

// NON_MATCHING: every instruction corresponds, but our frame is 0x10 bytes larger (the two Flag
// temporaries get separate slots instead of sharing one) and the frame data copies sit 0x10 higher.
void ExtendedEntity::sub_7100E64CDC(f32 delta) {
    if (!_10)
        return;

    if (!(_58 & (1 << int(Flag(Flag::_3))))) {
        if (!(_58 & (1 << int(Flag(Flag::_2)))))
            _10->sub_7100F6E314(-delta - _44, _48 - delta);
    }

    if (!_60)
        return;

    const sead::Vector3f frame = _60->_0;
    sead::Vector3f center = _60->_c;

    ksys::VFR::lerp(&_68, 0.0f, 0.35f, 0.15f, 0.005f);
    center.z += _68;

    _10->sub_7100F6E584(frame, center, _60->_18, _60->_24, _60->_30, _60->_3c);
    _8->setCenterOfMassInLocal(center);
}

void ExtendedEntity::sub_7100E64DE8(bool on) {
    const u8 mask = 1 << int(Flag(Flag::_0));
    if (on) {
        _58 |= mask;
        sub_7100E64E60();
    } else {
        _58 &= ~mask;
    }
}

// 0x7100e64b60: the signed angle of `a` around the Y axis relative to `b` (placeholder name).
// NON_MATCHING: identical instructions; our scheduler swaps s9 and s10 for the cross product's y and z.
f32 sub_7100E64B60(const sead::Vector3f& a, const sead::Vector3f& b) {
    sead::Vector3f axis;
    axis.setCross(sead::Vector3f::ey, b);
    axis.normalize();

    sead::Vector3f proj = a - axis * a.dot(axis);
    proj.normalize();

    const f32 angle = sead::Mathf::acos(sead::Mathf::clamp(proj.y, -1.0f, 1.0f));
    return angle * sead::Mathf::sign(proj.dot(b));
}

}  // namespace uking::act
