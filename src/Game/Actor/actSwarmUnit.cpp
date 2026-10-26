#include "Game/Actor/actSwarm.h"
#include <gsys/gsysModel.h>
#include <math/seadMatrixCalcCommon.h>
#include "KingSystem/Graphics/gfxUnk_710260af28.h"
#include "KingSystem/Physics/RigidBody/physRigidBody.h"
#include "KingSystem/Physics/RigidBody/physRigidBodySphere.h"
#include "KingSystem/Resource/resResDerived.h"
#include "KingSystem/Resource/resUnk_71024F9938.h"

namespace uking::act {

void Swarm::UnitBody::BodyState::sub_71002D7870(bool paused) {
    if (paused) {
        if (_18) {
            _18->setLinearVelocity(sead::Vector3f::zero);
            _18->setAngularVelocity(sead::Vector3f::zero);
        }
    } else if (_18 && _10) {
        _18->changePositionAndRotation(_10->_8);
    }
}

void Swarm::BodyInfo::sub_71002D71C8(bool paused) {
    if (paused) {
        if (_18) {
            _18->setLinearVelocity(sead::Vector3f::zero);
            _18->setAngularVelocity(sead::Vector3f::zero);
        }
    } else if (_18) {
        sead::Vector3f world_position;
        world_position.setMul(_20->getMtx(), _c);
        _18->changePosition(world_position, ksys::phys::KeepAngularVelocity{false});
    }
}

Swarm::Unit::Unit()
    : _8(sead::Matrix34f::ident), _38(sead::Vector3f::zero), _5c(0.1f),
      _60(sead::Vector3f::zero), _78(nullptr), _80(0), _88(), _98(), _a8(nullptr), _b0(nullptr),
      _b8(0), _bc(1.0f), _c0(0), _c8(0), _d0(0) {}

void Swarm::Unit::sub_71002DAA98() {
    if (!(_b8 & 2))
        _b8 = (_b8 & ~0xc) | 8;
}

void Swarm::Unit::sub_71002DAA78() {
    if (_b8 & 2) {
        _b8 = (_b8 & ~0xe) | 4;
        _bc = 0;
    }
}

void Swarm::Unit::sub_71002D93E8(const sead::Matrix33f& rotation) {
    sead::Matrix34CalcCommon<f32>::copy(_8, rotation, _8.getTranslation());
}

void Swarm::Unit::sub_71002D9434(const sead::Vector3f& position) {
    sead::Vector3f world_position;
    world_position.setMul(_b0->getMtx(), position);
    _8.setTranslation(world_position);
}

void Swarm::Unit::sub_71002D94C8(sead::Vector3f* out) const {
    if (out) {
        _8.getTranslation(*out);
        out->setMul(_b0->_15b8, *out);
    }
}

void Swarm::Unit::sub_71002DAA58(f32 opacity) {
    if (_78)
        Unk_710260af28::instance()->sub_7100F1DCA8(_78, opacity, false);
}

}  // namespace uking::act

// Resets the unit: state flags, full opacity, identity pose, and re-registers its model with the owner.
void uking::act::Swarm::Unit::m6() {
    _b8 = 0;
    _bc = 1.0f;
    _8 = sead::Matrix34f::ident;
    _d0 = 0;
    _b0->sub_71011CED70(_78);
    _b0->sub_71011C5630(_78);
}

void uking::act::Swarm::Unit::m8() {
    _38.updateStats();
    _8.m[0][3] += _38.mean.x;
    _8.m[1][3] += _38.mean.y;
    _8.m[2][3] += _38.mean.z;
}

bool uking::act::Swarm::Unit::m9() {
    if (_78) {
        _78->clearModelAccesssHandle();
        _78->setFlagsA0(0x10);
        if (_78->testFlagsA1(2))
            return false;
    }
    return true;
}

void uking::act::Swarm::Unit::m10() {
    _b0->sub_71002D484C(this);
}

bool uking::act::Swarm::Unit::m4(Swarm* owner, sead::Heap* heap) {
    _b0 = owner;
    return sub_71002D9588(heap);
}

void uking::act::Swarm::Unit::m5() {
    for (s32 i = 0; i < _98.size(); ++i)
        _98[i].sub_7100FDD264();
    _98.freeBuffer();
    if (_78) {
        gsys::Model::sub_7100BF69F8(_78);
        _78 = nullptr;
    }
    for (s32 i = 0; i < _88.size(); ++i)
        _88[i].requestUnload2();
    _88.freeBuffer();
}
