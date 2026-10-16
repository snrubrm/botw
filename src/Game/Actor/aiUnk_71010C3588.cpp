#include "Game/Actor/aiUnk_71010C3588.h"
#include <aal/aalShape.h>
#include <aal/aalHandle.h>
#include <aal/aalSoundSource.h>
#include <aal/aalSpeakerBalanceUnifier.h>
#include <xlink2/xlink2AssetExecutorSLink.h>
#include <xlink2/xlink2EventSLink.h>
#include "KingSystem/Physics/RigidBody/physRigidBody.h"
#include "Game/gameUnkRttiPlaceholders.h"
#include "KingSystem/ActorSystem/actReaction.h"
#include "KingSystem/XLink/xlinkActorUtil.h"
#include "KingSystem/ActorSystem/actActor.h"
#include "KingSystem/XLink/xlinkXLink.h"
#include "KingSystem/Physics/RigidBody/physRigidBodyCapsule.h"
#include "KingSystem/Physics/RigidBody/physRigidBodyCylinder.h"
#include "KingSystem/Physics/RigidBody/physRigidBodySphere.h"
#include "KingSystem/Physics/RigidBody/Shape/physCapsuleShape.h"
#include "KingSystem/ActorSystem/actActorChemicals.h"
#include "KingSystem/ActorSystem/actChemicalElementHolder.h"
#include "KingSystem/World/worldManager.h"
#include "KingSystem/World/worldChemicalMgr.h"

Unk_710250c260::Unk_710250c260() = default;

Unk_710250c260::~Unk_710250c260() {
    if (mBody) {
        if (mBody->isAddedToWorld())
            mBody->removeFromWorldImmediately(nullptr);
        delete mBody;
        mBody = nullptr;
    }
}

// NON_MATCHING: scheduling (the matrix pointer is moved to a callee-saved register earlier).
void Unk_710250c260::sub_71010C36A4(f32 length, f32 radius, const sead::Matrix34f* mtx, sead::Heap* heap,
                                    ksys::act::Actor* actor) {
    _20 = actor;
    ksys::phys::CapsuleParam param;
    param.vertex_a = sead::Vector3f::zero;
    param.vertex_b.setRotated(*mtx, sead::Vector3f::ey * length);
    param.radius = radius;
    param.contact_layer = ksys::phys::ContactLayer::SensorChemicalElement;
    param.name = "FireCapsule";
    param.motion_type = ksys::phys::MotionType::Keyframed;
    mBody = ksys::phys::CapsuleRigidBody::make(&param, heap);
    if (!mBody)
        return;
    _28 = *mtx;
    _58 = length;
    _5c = radius;
    mBody->setTransform(*mtx, ksys::phys::PropagateToLinkedMotions(true));
    if (actor && actor->getChemicalContainer())
        _18 = actor->getChemicalContainer()->_68;
}

void Unk_710250c260::sub_71010C38F4(const sead::Matrix34f* mtx) {
    _28 = *mtx;
    if (mBody) {
        if (auto* body = sead::DynamicCast<ksys::phys::CapsuleRigidBody>(mBody))
            body->changePositionAndRotation(_28, sead::Mathf::epsilon());
    }
    updateEffect();
}

void Unk_710250c260::sub_71010C3A1C(f32 radius) {
    _5c = radius;
    if (mBody) {
        if (auto* body = sead::DynamicCast<ksys::phys::CapsuleRigidBody>(mBody))
            body->setRadius(_5c);
    }
    updateEffect();
}

void Unk_710250c260::sub_71010C3B18(f32 length) {
    _58 = length;
    if (mBody) {
        if (auto* body = sead::DynamicCast<ksys::phys::CapsuleRigidBody>(mBody))
            body->setVertices(sead::Vector3f::zero, sead::Vector3f::ey * _58);
    }
    updateEffect();
}

// NON_MATCHING: the handle copy stores the id before the event pointer in the original.
void Unk_710250c260::sub_71010C3C44(int mode) {
    if (!mBody)
        return;
    if (!mBody->isAddedToWorld() || mBody->isRemovingBodyFromWorld())
        mBody->addToWorld();
    if (!_8) {
        Unk_710250c118Arg arg;
        arg.body = mBody;
        arg._4 = mode;
        arg._0 = _18;
        auto* holder = ksys::world::Manager::instance()->getChemicalMgrUnchecked()->_ae8;
        _8 = holder ? holder->sub_71010C760C(&arg) : nullptr;
    }
    auto* actor = _20;
    if (actor || (actor = ksys::act::Reaction::instance()->_38))
        _60 = ksys::eft::searchAndEmitELink(actor, "FirePillar");
    updateEffect();
}

void Unk_710250c260::sub_71010C3D70(bool reset_links) {
    if (_8) {
        delete _8;
        _8 = nullptr;
    }
    if (mBody && (mBody->isAddedToWorld() || mBody->isAddingBodyToWorld())) {
        if (reset_links)
            mBody->removeFromWorldAndResetLinks();
        else
            mBody->removeFromWorld();
    }
    _60.fade();
}

Unk_710250c3c8::Unk_710250c3c8() = default;

Unk_710250c3c8::~Unk_710250c3c8() {
    destroy(true);
    if (mBody) {
        if (mBody->isAddedToWorld())
            mBody->removeFromWorldImmediately(nullptr);
        delete mBody;
        mBody = nullptr;
    }
    if (mShape) {
        mShape->destroy();
        mShape = nullptr;
    }
}

void Unk_710250c3c8::destroy(bool remove_links) {
    if (_8) {
        delete _8;
        _8 = nullptr;
    }
    if (mBody && (mBody->isAddedToWorld() || mBody->isAddingBodyToWorld())) {
        if (remove_links)
            mBody->removeFromWorldAndResetLinks();
        else
            mBody->removeFromWorld();
    }
    _58.fade();
    if (_68.isActive()) {
        if (auto* executor = static_cast<xlink2::EventSLink*>(_68.getEvent())->getAliveAssetExecutor())
            if (auto* source = executor->getHandle()->getSoundSource())
                if (auto* calculator = source->mSpatialCalculator)
                    calculator->detachShape(true);
    }
    _68.fade();
    _18 &= ~2;
}

// NON_MATCHING: the default "no name" store is kept in the original and vertex_b is stored as 4 + 8 bytes.
void Unk_710250c3c8::sub_71010C42B4(sead::Heap* heap) {
    ksys::phys::CapsuleParam param;
    param.name = "WindCapsule";
    param.vertex_a = sead::Vector3f::zero;
    param.vertex_b = sead::Vector3f::ey;
    param.radius = 4.0f;
    param.contact_layer = ksys::phys::ContactLayer::SensorChemicalElement;
    param.motion_type = ksys::phys::MotionType::Keyframed;
    param.enable_deactivation = false;
    param.toi = true;
    mBody = ksys::phys::CapsuleRigidBody::make(&param, heap);
    if (!mBody)
        return;
    mShape = aal::ShapeCapsule::create("WindCapsule", heap);
    if (mShape) {
        mShape->mFlags.resetBit(aal::Shape::KeepPosition);
        mShape->mFlags.resetBit(aal::Shape::KeepRotation);
    }
    _18 |= 1;
}

bool Unk_710250c3c8::sub_71010C4284() const {
    return !mBody || !mBody->isAddedToWorld();
}


Unk_710250c118::~Unk_710250c118() = default;

Unk_710250c280::~Unk_710250c280() = default;

Unk_710250c3e8::~Unk_710250c3e8() {
    _68 = false;
    _69 = false;
    if (_70.isActive()) {
        _70.fade();
        _70.reset();
    }
    if (_80.isActive()) {
        if (auto* executor = static_cast<xlink2::EventSLink*>(_80.getEvent())->getAliveAssetExecutor())
            if (auto* source = executor->getHandle()->getSoundSource())
                if (auto* calculator = source->mSpatialCalculator)
                    calculator->detachShape(true);
    }
    _80.fade();
    if (_90) {
        _90->destroy();
        _90 = nullptr;
    }
}

f32 Unk_710250c3e8::m14(sead::Vector3f* out, const sead::Vector3f& pos, ksys::act::Chemical* chemical) {
    *out = sead::Vector3f::ey * mArg._8;
    if (chemical && !(chemical->_c & 0x8000)) {
        const sead::Vector3f body_pos = mArg.body->getPosition();
        sead::Vector3f dir(pos.x - body_pos.x, 0.0f, pos.z - body_pos.z);
        dir.normalize();
        *out += dir * 0.75f;
    }
    f32 length = out->normalize();
    auto* mgr = ksys::world::Manager::instance();
    if (mgr->getChemicalMgr())
        mgr->getChemicalMgr()->x_2(out, &length, mHolder, chemical);
    if (!_68)
        length = 0.0f;
    return length;
}

bool Unk_710250c3e8::m29(const ElementName& name, sead::Heap* heap) {
    _68 = true;
    if (mHolder) {
        mHolder->_3c = mArg._8;
        mHolder->_1c = sead::Vector3f::ey;
    }
    setRigidBody(mArg.body, true);
    _69 = true;
    _90 = aal::ShapeCapsule::create("Updraft", heap);
    if (_90) {
        _90->mFlags.resetBit(aal::Shape::KeepPosition);
        _90->mFlags.resetBit(aal::Shape::KeepRotation);
    }
    return true;
}

void Unk_710250c3e8::m35(f32 delta_frame) {
    if (mHolder)
        mHolder->_3c = mArg._8;
    sub_71010C5154();
    if (_90) {
        _90->setPosition(m6());
        _90->setRadius(mArg._10);
        const sead::Vector3f vector = sead::Vector3f::ey * mArg._c;
        _90->setVector(vector);
    }
    sub_71010C53D8();
    f32 t = delta_frame / 1000.0f + _98;
    _98 = t > 1.0f ? t - 1.0f : t;
}

// NON_MATCHING: the _69 load is scheduled later and the scale / matrix floats are computed in another order.
void Unk_710250c3e8::sub_71010C5154() {
    const bool active = _70.isActive();
    if (!_69) {
        if (active) {
            _70.fade();
            _70.reset();
            return;
        }
    } else if (!active) {
        auto* actor = ksys::act::Reaction::instance()->_38;
        if (actor) {
            if (actor->getXLink()) {
                const f32 half_height = mArg._c * 0.5f;
                actor->getXLink()->sub_7101231468(0x19, mArg._10, false);
                actor->getXLink()->sub_7101231468(0x1a, half_height, false);
                actor->getXLink()->sub_7101231468(0x1b, 20.0f, false);
            }
            _70 = ksys::eft::searchAndEmitELink(actor, "Chemical_Updraft");
        }
    }
    if (_70.isActive()) {
        const sead::Vector3f& pos = m6();
        const f32 height = mArg._c;
        const f32 diameter = mArg._10 + mArg._10;
        const sead::Vector3f center = pos + sead::Vector3f::ey * height * 0.5f;
        const sead::Matrix34f mtx(1, 0, 0, center.x,  //
                                  0, 1, 0, center.y,  //
                                  0, 0, 1, center.z);
        _70.setMatrix(mtx, {diameter, height, diameter});
    }
}

// NON_MATCHING: register allocation (one more callee-saved register keeps &_80), as in
// ElementDirectionalWindOrGust::doEmitSLink.
void Unk_710250c3e8::sub_71010C53D8() {
    if (_80.isActive())
        return;
    auto* reaction = ksys::act::Reaction::instance();
    if (!reaction->_38)
        return;
    _80 = ksys::eft::searchAndEmitSLink(reaction->_38, "windBurn", false);
    if (!_80.isActive())
        return;
    _80.getEvent()->resetFlagBit(1);
    auto* shape = _90;
    if (shape && _80.isActive()) {
        if (auto* executor = static_cast<xlink2::EventSLink*>(_80.getEvent())->getAliveAssetExecutor())
            if (auto* source = executor->getHandle()->getSoundSource())
                source->mSpatialSetting.setShape(shape);
    }
}

void Unk_710250c3e8::m33(bool a, bool fixed) {
    _68 = !a;
    if (mArg.body)
        mArg.body->setFixed(ksys::phys::Fixed(fixed), ksys::phys::PreserveVelocities(true));
    _69 = !a;
    sub_71010C5154();
    if (_80.isActive()) {
        if (auto* executor = static_cast<xlink2::EventSLink*>(_80.getEvent())->getAliveAssetExecutor())
            if (auto* source = executor->getHandle()->getSoundSource())
                if (auto* calculator = source->mSpatialCalculator)
                    calculator->detachShape(true);
    }
    _80.fade();
}

Unk_710250c550::~Unk_710250c550() = default;

Unk_710250c6d8::~Unk_710250c6d8() = default;

bool Unk_710250c118::m29(const ElementName& name, sead::Heap* heap) {
    if (mHolder)
        mHolder->_1a = u8(mArg._4);
    setRigidBody(mArg.body, true);
    return true;
}

void Unk_710250c118::m33(bool a, bool fixed) {
    if (mArg.body)
        mArg.body->setFixed(ksys::phys::Fixed(fixed), ksys::phys::PreserveVelocities(true));
}

bool Unk_710250c280::m29(const ElementName& name, sead::Heap* heap) {
    if (mHolder) {
        mHolder->_3c = mArg._0;
        mHolder->_1c = mArg._4;
    }
    setRigidBody(mArg.body, true);
    return true;
}

void Unk_710250c280::m35(f32 delta_frame) {
    if (mHolder) {
        mHolder->_3c = mArg._0;
        mHolder->_1c = mArg._4;
    }
}

void Unk_710250c280::m33(bool a, bool fixed) {
    if (mArg.body)
        mArg.body->setFixed(ksys::phys::Fixed(fixed), ksys::phys::PreserveVelocities(true));
}

f32 Unk_710250c280::m14(sead::Vector3f* out, const sead::Vector3f& pos, ksys::act::Chemical* chemical) {
    *out = mArg._4;
    return mArg._0;
}

// NON_MATCHING: the _64 load is scheduled one instruction earlier.
f32 Unk_710250c550::m14(sead::Vector3f* out, const sead::Vector3f& pos, ksys::act::Chemical* chemical) {
    *out = pos - _58;
    f32 distance = out->length();
    if (distance > 0.0f)
        *out *= 1.0f / distance;
    f32 t = sead::Mathf::clamp(distance / _68, 0.0f, 1.0f);
    t *= t;
    const f32 falloff = 1.0f - t * t;
    const f32 falloff2 = falloff * falloff;
    return _64 * falloff2;
}

bool Unk_710250c550::m29(const ElementName& name, sead::Heap* heap) {
    if (mHolder)
        mHolder->_18 |= 0x100;
    setRigidBody(_50, true);
    return true;
}

void Unk_710250c550::m33(bool a, bool fixed) {
    if (_50)
        _50->setFixed(ksys::phys::Fixed(fixed), ksys::phys::PreserveVelocities(true));
}

bool Unk_710250c6d8::m29(const ElementName& name, sead::Heap* heap) {
    if (mHolder)
        mHolder->_1a = 2;
    setRigidBody(_50, true);
    return true;
}

void Unk_710250c6d8::m33(bool a, bool fixed) {
    if (_50)
        _50->setFixed(ksys::phys::Fixed(fixed), ksys::phys::PreserveVelocities(true));
}

// NON_MATCHING: prologue argument moves are ordered differently.
bool Unk_710250c530::sub_71010C5A10(f32 max_height, f32 radius, const sead::Vector3f& pos) {
    if (_10->isAddedToWorld())
        return false;
    f32 height = ksys::act::sub_7100E41584(pos, max_height);
    if (height < max_height) {
        height -= radius;
        if (height < 0.0f)
            height = 0.0f;
    }
    if (!_10)
        return false;
    _10->setVertices(sead::Vector3f::ey * -radius, sead::Vector3f::ey * (height + radius));
    _10->setRadius(radius);
    _10->setPosition(pos, ksys::phys::PropagateToLinkedMotions(true));
    _10->addToWorld();
    _18 = pos;
    _24 = height;
    _28 = radius;
    if (!_8) {
        Unk_710250c3e8Arg arg;
        arg.body = _10;
        arg._8 = 20.0f;
        arg._c = height;
        arg._10 = radius;
        auto* holder = ksys::world::Manager::instance()->getChemicalMgrUnchecked()->_ae8;
        _8 = holder ? holder->sub_71010C79DC(&arg) : nullptr;
    }
    return true;
}

void Unk_710250c530::sub_71010C5B78() {
    if (_8) {
        delete _8;
        _8 = nullptr;
    }
    if (_10 && (_10->isAddedToWorld() || _10->isAddingBodyToWorld()))
        _10->removeFromWorld();
}

// NON_MATCHING: the handle copy stores the id before the event pointer in the original.
bool Unk_710250c820::sub_71010C683C(f32 radius, const sead::Vector3f& pos) {
    if (!_10)
        return false;
    if (_10->isAddedToWorld() || _10->isAddingBodyToWorld())
        return false;
    _10->setRadius(radius);
    _10->setPosition(pos, ksys::phys::PropagateToLinkedMotions(true));
    _10->addToWorld();
    _18 = pos;
    _24 = radius;
    if (!_8) {
        ksys::phys::RigidBody* body = _10;
        auto* holder = ksys::world::Manager::instance()->getChemicalMgrUnchecked()->_ae8;
        _8 = holder ? holder->sub_71010C7DB8(&body) : nullptr;
    }
    if (auto* actor = ksys::act::Reaction::instance()->_38)
        _28 = ksys::eft::searchAndEmitELink(actor, "Chemical_Fire_Plant");
    const sead::Matrix34f mtx(1, 0, 0, _18.x,  //
                              0, 1, 0, _18.y,  //
                              0, 0, 1, _18.z);
    _28.setMatrix(mtx, {_24, _24, _24});
    return true;
}

void Unk_710250c820::sub_71010C69C4() {
    if (_8) {
        delete _8;
        _8 = nullptr;
    }
    if (_10 && (_10->isAddedToWorld() || _10->isAddingBodyToWorld()))
        _10->removeFromWorld();
    _28.fade();
}

// NON_MATCHING: the original computes the flag and NaN test as values and combines them, and reloads
// _10 before each final store.
void Unk_710250c698::sub_71010C5F2C() {
    if (!_18)
        return;
    const bool valid = !_20.isNan();
    if (!((_8 & 1) && valid && _2c > 0.0f && _30 > 0.0f)) {
        if (_10) {
            delete _10;
            _10 = nullptr;
        }
        if (_18->isAddedToWorld() || _18->isAddingBodyToWorld())
            _18->removeFromWorld();
        return;
    }
    if (!_18->isAddedToWorld() && !_18->isAddingBodyToWorld()) {
        if (auto* sphere = sead::DynamicCast<ksys::phys::SphereRigidBody>(_18)) {
            sphere->setPosition(_20, ksys::phys::PropagateToLinkedMotions(true));
            sphere->setRadius(_30);
        }
        _18->addToWorld();
    } else if (auto* sphere = sead::DynamicCast<ksys::phys::SphereRigidBody>(_18)) {
        sphere->changePosition(_20, ksys::phys::KeepAngularVelocity(false), sead::Mathf::epsilon());
        sphere->setRadius(_30);
    }
    if (!_10) {
        ksys::phys::RigidBody* body = _18;
        auto* holder = ksys::world::Manager::instance()->getChemicalMgrUnchecked()->_ae8;
        if (!holder) {
            _10 = nullptr;
            return;
        }
        _10 = holder->sub_71010C7BE0(&body);
        if (!_10)
            return;
    }
    _10->_58 = _20;
    _10->_68 = _30;
    _10->_64 = _2c;
}

void Unk_710250c698::sub_71010C61CC(const sead::Vector3f& pos, f32 radius, f32 strength) {
    _20 = pos;
    _30 = radius;
    _2c = strength;
}
