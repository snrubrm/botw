#include "KingSystem/ActorSystem/actUnk_71024ef4e8.h"
#include "KingSystem/ActorSystem/actUnk_71024ef620.h"
#include "KingSystem/ActorSystem/actCCAccessor.h"
#include "KingSystem/Physics/CharacterController/physCharacterController.h"
#include "KingSystem/Physics/Constraint/physConstraint.h"
#include "KingSystem/Physics/Ragdoll/physRagdollInstance.h"
#include "KingSystem/Physics/Ragdoll/physRagdollRigidBody.h"
#include "KingSystem/Physics/RigidBody/physRigidBody.h"
#include "KingSystem/Physics/RigidBody/physRigidBodyFromResource.h"
#include "KingSystem/Physics/System/physRayCastBodyQuery.h"
#include "KingSystem/Physics/System/physInstanceSet.h"
#include "KingSystem/Utils/InitTimeInfo.h"

namespace ksys::act {

namespace {
// NON_MATCHING: the static initializer schedules the timestamp and record stores differently.
util::InitTimeInfoEx sInitTimeInfo;
Unk_71024ef4e8::AttachConfig sAttachConfigs[] = {
    {"FallDown", {4.0f, 0.5f, 4.0f}, 20.0f, 0.2f, 0.8f, -0.7f, -0.7f},
    {"Dead", {4.0f, 0.5f, 4.0f}, 20.0f, 1.0f, 1.0f, 1.0f, -0.85f},
    {"DeadDirect", {4.0f, 0.5f, 4.0f}, 1.0f, 1.0f, 1.0f, -0.5f, -0.85f},
    {"Climb", {4.0f, 0.5f, 4.0f}, 1.0f, 1.0f, 1.0f, 1.0f, 0.0f},
    {"Glide", {4.0f, 0.5f, 4.0f}, 1.0f, 1.0f, 1.0f, 1.0f, 0.0f},
    {"DeadMotorcycleSync", {4.0f, 0.5f, 4.0f}, 0.2f, 1.0f, 1.0f, 1.0f, 1.0f},
    {"DeadMotorcycle", {4.0f, 0.5f, 4.0f}, 0.2f, 1.0f, 1.0f, -0.85f, -0.85f},
};
static_assert(sizeof(Unk_71024ef4e8::AttachConfig) == 0x28);
}  // namespace

// NON_MATCHING: scalar scheduling and flag-test register allocation differ.
void Unk_71024ef4e8::sub_7100EB4814(int type, int a2, f32 f) {
    auto& config = sAttachConfigs[type];
    _1c8 = &config;
    _20->setInertiaLocal(config.inertia);
    _20->setLinearDamping(config.linear_damping);
    _20->setAngularDamping(config.angular_damping);
    f32 value;
    f32 change = 0.0f;
    if (a2 & 1) {
        value = 1.0f;
    } else {
        value = _1c8->_24;
        if (f > 0.0f) {
            change = -((_1c8->_20 - value) / f);
            value = _1c8->_20;
        }
    }
    _154 = _158 = value;
    _15c = change;
    _8->sub_7100FBDB90(_8->get112(), value);
    const f32 scale = _1c8->_14;
    const f32 inverse_scale = 1.0f / scale;
    _12c = scale;
    f32 factor = 1.0f;
    if (a2 & 1) {
        _20->setGravityFactor(0.0f);
        if (type != 5)
            factor = 0.001f;
    } else {
        _20->setGravityFactor(1.0f);
    }
    _38->sub_7100F6A0FC(factor, inverse_scale);
}

void Unk_71024ef4e8::sub_7100EB480C(sead::Vector3f* out) const {
    _20->getCenterOfMassInWorld(out);
}

void Unk_71024ef4e8::sub_7100EB4680() {
    if (!_110.isOnBit(23))
        return;
    _110.resetBit(23);
    sead::Vector3f position;
    _10->sub_7100F5F6E0(&position);
    if ((position - _200).length() > 20.0f)
        return;
    phys::RayCastBodyQuery query(nullptr, phys::GroundHit::Player);
    query.setNormalCheckingMode(phys::RayCast::NormalCheckingMode::_1);
    query.enableLayer(phys::ContactLayer::EntityGroundObject);
    query.enableLayer(phys::ContactLayer::EntityGround);
    query.enableLayer(phys::ContactLayer::EntityGroundSmooth);
    query.enableLayer(phys::ContactLayer::EntityTree);
    query.enableLayer(phys::ContactLayer::EntityAirWall);
    sead::Vector3f start = position;
    sead::Vector3f end = _200;
    start.y += 0.15f;
    end.y += 0.15f;
    query.setStartAndEnd(start, end);
    if (query.worldRayCast(phys::ContactLayerType::Entity)) {
        _10->warpActorToPosition(_200);
        _10->sub_7100F5F6FC(sead::Vector3f::zero);
        _10->sub_7100F5FB24(sead::Vector3f::zero);
    }
}

void Unk_71024ef4e8::sub_7100EB5950(sead::Vector3f* out, phys::RigidBody* body, f32 height) {
    sead::Matrix34f transform;
    body->getTransform(&transform);
    transform.getTranslation(*out);
    if (height != 0.0f)
        *out += transform.getBase(1) * height;
}

u32 Unk_71024ef4e8::sub_7100EB59E8(const sead::Vector3f& target,
                                 phys::CharacterController* controller,
                                 phys::RigidBody* body, f32 height) {
    phys::RayCastBodyQuery query(nullptr, phys::GroundHit::Player);
    query.setNormalCheckingMode(phys::RayCast::NormalCheckingMode::DoNotCheck);
    query.enableLayer(phys::ContactLayer::EntityGround);
    query.enableLayer(phys::ContactLayer::EntityGroundSmooth);
    sead::Vector3f start;
    if (controller) {
        controller->sub_7100F5F6E0(&start);
        if (!controller->sub_7100F5E954())
            return 0;
    } else {
        if (!body)
            return 0;
        body->getPosition(&start);
        if (!body->isAddedToWorld())
            return 0;
    }
    start += sead::Vector3f::ey * height;
    if ((start - target).length() > 3.0f)
        return 2;
    query.setNormalCheckingMode(phys::RayCast::NormalCheckingMode::_1);
    query.setStartAndEnd(start, target);
    query.setNormalCheckingMode(phys::RayCast::NormalCheckingMode::_1);
    if (!query.worldRayCast(phys::ContactLayerType::Entity))
        return 0;
    auto* hit_body = query.getHitRigidBody();
    if (!hit_body)
        return 0;
    auto* hit = sead::DynamicCast<phys::RigidBodyFromResource>(hit_body);
    if (!hit || !hit->isBvTreeOrStaticCompound())
        return 0;
    sead::Vector3f position;
    query.getHitPosition(&position);
    query.setEnd(position);
    query.setNormalCheckingMode(phys::RayCast::NormalCheckingMode::_0);
    return !query.worldRayCast(phys::ContactLayerType::Entity);
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
