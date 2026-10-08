#include "KingSystem/ActorSystem/actUnk_71024ef4e8.h"
#include "KingSystem/ActorSystem/actUnk_71024ef620.h"
#include "KingSystem/ActorSystem/actCCAccessor.h"
#include "KingSystem/Physics/CharacterController/physCharacterController.h"
#include "KingSystem/Physics/Constraint/physConstraint.h"
#include "KingSystem/Physics/Ragdoll/physRagdollInstance.h"
#include "KingSystem/Physics/Ragdoll/physRagdollRigidBody.h"
#include "KingSystem/Physics/RigidBody/physRigidBody.h"

namespace ksys::act {

void Unk_71024ef4e8::sub_7100EB480C(sead::Vector3f* out) const {
    _20->getCenterOfMassInWorld(out);
}

void Unk_71024ef4e8::sub_7100EB2448() {
    if (mAttachInfo)
        mAttachInfo->sub_7100EB0D30();
}

// NON_MATCHING: the original tests _b8->_74 before the _110 mask (ours sinks it) and loads _c0->_60 with ldrh
bool Unk_71024ef4e8::sub_7100EB5784() const {
    if (_110.isOnBit(11))
        return false;
    if (mAttachInfo->_48 & 2)
        return !(mAttachInfo->_48 & 0x80);
    if (_b8->_74 & 1)
        return false;
    if ((_110.getDirect() & 0x2100) == 0x2000)
        return false;
    return !_c0->_60.isOnBit(0);
}

void Unk_71024ef4e8::sub_7100EB57F0(const sead::Matrix34f& mtx) {
    mMtx = mtx;
    _110.reset(0x880000);
    _110.set(0x80000);
    _188 = mtx;
    _1b8 = 1.0f;
    _1bc = 1.0f;
}

void Unk_71024ef4e8::sub_7100EB51B0(const sead::Vector3f& a, const sead::Vector3f& b, int c) {
    _110.set(0x40);
    sub_7100EB4928(0, c, a, b, false, 0.0f);
}

void Unk_71024ef4e8::sub_7100EB51E0() {
    _20->removeFromWorld();
    _38->sub_7100F6A074();
    _18->changeWorldState(phys::RagdollInstance::WorldState::NotAddedToWorld);
    _110.reset(0x4070c0);
    _10->sub_7100F5F458(MotionType::_1);
    _130 = 0;
}

void Unk_71024ef4e8::sub_7100EB523C(const sead::Vector3f& a, const sead::Vector3f& b) {
    _114 = a;
    _120 = b;
}

void Unk_71024ef4e8::sub_7100EB5270(int a) {
    sub_7100EB4928(1, a, sead::Vector3f::zero, sead::Vector3f::zero, true, 0.0f);
    _110.set(0x300);
}

void Unk_71024ef4e8::sub_7100EB52BC(int a) {
    sub_7100EB4928(5, a, sead::Vector3f::zero, sead::Vector3f::zero, true, 0.0f);
    _110.set(0x300);
}

void Unk_71024ef4e8::sub_7100EB5308(bool a, int b, f32 f) {
    const int type = a ? (_110.isOnBit(6) ? 1 : 2) : 1;
    if (_110.isOnBit(13))
        sub_7100EB4814(type, 0, f);
    else
        sub_7100EB4928(type, b, sead::Vector3f::zero, sead::Vector3f::zero, false, f);
    _110.reset(0x1300);
    _110.set(0x1200);
    _144 = _48;
}

void Unk_71024ef4e8::sub_7100EB2394() {
    _20->setWaterBuoyancyScale(_48);
    _20->setCenterOfMassInLocal(_4c);
    _20->setMass(_5c);
    for (int i = 0; i < _18->getRigidBodies_().size(); ++i)
        _18->getRigidBodies_()[i]->setMass(_60[i]);
}

void Unk_71024ef4e8::sub_7100EB5550() {
    _110.set(0x4);
}

void Unk_71024ef4e8::sub_7100EB5634() {
    _110.set(0x8);
}

void Unk_71024ef4e8::sub_7100EB5644() {
    _110.reset(0x8);
}

void Unk_71024ef4e8::sub_7100EB5654() {
    _110.set(0x20);
}

void Unk_71024ef4e8::sub_7100EB538C(int a, f32 f) {
    const bool b13 = _110.isOnBit(13);
    _110.set(0x1000000);
    if (b13)
        sub_7100EB4814(6, 0, f);
    else
        sub_7100EB4928(6, a, sead::Vector3f::zero, sead::Vector3f::zero, false, f);
    _110.reset(0x1300);
    _110.set(0x1200);
    _144 = _48;
}

void Unk_71024ef4e8::sub_7100EB5410() {
    if (_110.isOnBit(13)) {
        _20->removeFromWorld();
        _38->sub_7100F6A074();
        _18->changeWorldState(phys::RagdollInstance::WorldState::NotAddedToWorld);
        _110.reset(0x4070c0);
        _10->sub_7100F5F458(MotionType::_1);
        _130 = 0;
    }
    _110.reset(0x1001300);
    sub_7100EB2394();
}

void Unk_71024ef4e8::sub_7100EB548C() {
    _1b8 = 0;
    _1bc = 0;
    _1c0 = 0.2f;
    _10->physicsXXXGetMtx_1(&_188);
    _110.reset(0x8006);
    _110.set(0x2);
}

void Unk_71024ef4e8::sub_7100EB54D8() {
    for (int i = 0; i < _18->getRigidBodies_().size(); ++i)
        _18->getRigidBodies_()[i]->setContactLayer(phys::ContactLayer::EntityRagdoll);
}

void Unk_71024ef4e8::sub_7100EB5560() {
    _18->changeWorldState(phys::RagdollInstance::WorldState::NotAddedToWorld);
    for (int i = 0; i < _18->getRigidBodies_().size(); ++i)
        _18->getRigidBodies_()[i]->setContactLayer(phys::ContactLayer::EntityRagdoll);
    _110.reset(0x28006);
    sead::Matrix34f mtx;
    mAttachInfo->getBody()->getTransform(&mtx);
    _1ec.x = mtx.m[0][3];
    _1ec.y = mtx.m[1][3];
    _1ec.z = mtx.m[2][3];
    _110.set(0x200000);
}

void Unk_71024ef4e8::sub_7100EB5664(bool a, const sead::Vector3f* v) {
    _110.reset(0x20);
    if (a) {
        _110.set(0x800000);
        _200 = *v;
    } else {
        _110.reset(0x800000);
        _200.set(0, 0, 0);
    }
}

void Unk_71024ef4e8::sub_7100EB56B4(bool a) {
    if (!a) {
        _110.reset(0x150000);
        _110.set(0x50000);
    } else {
        _110.set(0x150000);
    }
    _1e8 = 0;
    _1f8 = 0;
}

void Unk_71024ef4e8::sub_7100EB56E8() {
    _18->changeWorldState(phys::RagdollInstance::WorldState::NotAddedToWorld);
    for (int i = 0; i < _18->getRigidBodies_().size(); ++i)
        _18->getRigidBodies_()[i]->setContactLayer(phys::ContactLayer::EntityRagdoll);
    _110.reset(0x150000);
    _148 = 0;
    _150 = 0;
}

}  // namespace ksys::act
