#include "Game/AI/aiUnk_7102450058.h"
#include <cmath>
#include "KingSystem/ActorSystem/actChemical.h"
#include "KingSystem/Chemical/chmSystemConfig.h"
#include "Game/AI/aiUnk_71007368A4.h"
#include "Game/AI/aiUnk_71007377D4.h"
#include "KingSystem/Physics/CharacterController/physCharacterController.h"
#include "KingSystem/ActorSystem/actActor.h"
#include "KingSystem/Physics/Constraint/physConstraint.h"
#include "KingSystem/Physics/RigidBody/physRigidBody.h"
#include "KingSystem/ActorSystem/actActorParam.h"
#include "KingSystem/ActorSystem/actActorUtil.h"
#include "KingSystem/ActorSystem/actCCAccessor.h"
#include "KingSystem/ActorSystem/actUnk_7100e4e084.h"
#include "KingSystem/Resource/Actor/resResourceGParamList.h"
#include "KingSystem/Resource/GeneralParamList/resGParamListObjectLiftable.h"

Unk_7102450298::Unk_7102450298(ksys::act::Actor* actor) : CarriedData(actor) {}

Unk_7102450298::~Unk_7102450298() = default;

bool Unk_7102450298::sub_71006F8AB4() const {
    if (!_30)
        return true;
    return !(_30->_50 & 1);
}

// NON_MATCHING: the inertia-vector address is formed after setMass rather than retained across the call; _38 is
// loaded after the first multiply instead of before it.
void Unk_7102450298::x_11() {
    f32 mass;
    if (mActor && mActor->getScale().x != 1.0f) {
        // Cubed in double precision like in x_0.
        const f64 s = mActor->getScale().x;
        mass = s * s * s * _38;
    } else {
        mass = _38;
    }
    _3c = mass;
    auto* body = mActor->getMainBody();
    auto* controller = mActor->getCharacterController();
    const f32 clamped_mass = sead::Mathf::max(mass, 0.01f);
    if (controller) {
        controller->sub_7100F60368(clamped_mass);
    } else if (body) {
        body->setMass(clamped_mass);
        body->setInertiaLocal(_48);
    }
    if (auto* chemical = mActor->getChemicalStuff()) {
        if (chemical->mMaterial->attribute.ref() & 0x80040) {
            body = mActor->getMainBody();
            auto* controller = mActor->getCharacterController();
            if (body && !controller)
                body->resetInertiaAndCenterOfMass();
        }
    }
}

void Unk_7102450298::x_10() {
    if (_30)
        _30->sub_7100F6A074();
}

bool Unk_7102450298::x_15() {
    return _30 && (_30->_50 & 1);
}

void Unk_7102450298::x_18(ksys::act::Actor* actor) {
    if (!actor || !mActor || !_30)
        return;
    auto* body = sub_71007394DC(mActor);
    auto* other_body = sub_71007394DC(actor);
    if (!body || !other_body)
        return;
    _30->sub_7100F6AAA4(body, other_body);
    auto* constraint = _30;
    constraint->sub_7100F6D420(body->getTransform(), other_body->getTransform(), body->getTransform());
    _30->sub_7100F69FF0();
}

void Unk_7102450298::x_22(ksys::phys::RigidBody* body) {
    if (!body)
        return;
    const sead::Matrix34f& mtx = mActor->getMtx();
    _30->sub_7100F6D420(mtx, body->getTransform(), mtx);
}

// NON_MATCHING: the original loads all three components into registers and copies the vector onto itself before
// normalising (the vector is a copy of the out parameter); ours normalises in place from memory
void Unk_7102450298::x_20() {
    auto* controller = mActor->getCharacterController();
    if (!controller)
        return;
    sead::Vector3f velocity;
    controller->sub_7100F5F598(&velocity);
    const sead::Vector2f horizontal(velocity.x, velocity.z);
    velocity.normalize();
    sub_710072C1B4(controller, velocity);
    controller->sub_7100F5E7F0(horizontal.length());
    controller->sub_7100F5FC8C(mActor->getMtx());
}

void Unk_7102450298::x_14() {
    CarriedData::x_14();
    _54 = true;
    _44 = 0.0f;
    if (const auto* param = mActor->getParam()) {
        if (const auto* gparams = param->getRes().mGParamList) {
            if (const auto* liftable = gparams->getLiftable())
                _54 = liftable->mIsUse2MassConstraintMode.ref();
        }
    }
}

void Unk_7102450298::x_0() {
    auto* actor = mActor;
    if (!actor)
        return;
    _38 = actor->m38();
    const f32 scale = actor->getScale().x;
    auto* data = actor->m100();
    // The original cubes the scale in double precision (std::pow(f32, 3) is a libm call in our build).
    const f64 s = scale;
    if (scale != 1.0f) {
        if (data) {
            if (data->_1c0 > 0.0f) {
                _38 = data->_1c0;
            } else {
                _38 = _38 / (s * s * s);
                data->_1c0 = _38;
            }
        } else {
            _38 = _38 / (s * s * s);
        }
    } else if (data && data->_1c0 <= 0.0f) {
        data->_1c0 = _38;
    }
    if (!actor->getCharacterController()) {
        if (auto* body = actor->getMainBody())
            body->getInertiaLocal(&_48);
    }
}

void Unk_7102450298::x_21() {
    _3c = (_54 && _10 > 3 ? 0.03f : 0.25f) * _40;
    if (sead::Mathf::abs(_3c - mActor->m38()) > 1.0f) {
        const f32 mass = _3c;
        auto* body = mActor->getMainBody();
        auto* controller = mActor->getCharacterController();
        const f32 body_mass = sead::Mathf::max(mass, 0.01f);
        if (controller) {
            controller->sub_7100F60368(body_mass);
        } else if (body) {
            body->setMass(body_mass);
            body->setInertiaLocal(sUnk_7101e7b5c8);
        }
    }
}

void Unk_7102450298::x_23(ksys::act::Actor* actor) {
    if (!actor)
        return;
    auto* carried_actor = mActor;
    auto* controller = actor->getCharacterController();
    if (!controller) {
        sub_710072DC9C(carried_actor, 1.0f);
        return;
    }
    const sead::Vector3f velocity = controller->sub_7100F62B80();
    f32 factor = controller->sub_7100F5F0E4() == ksys::act::MotionType::_1 ? 1.0f : 0.0f;
    if ((_2c & 2) && (velocity.x != 0.0f || velocity.y != 0.0f || velocity.z != 0.0f)) {
        _2c &= ~2;
        const f32 scale = carried_actor->m38();
        ksys::act::sub_7100EE5AA8(carried_actor,
                                  {velocity.x * scale, velocity.y * scale, velocity.z * scale});
        factor = 1.0f;
    }
    sub_710072DC9C(carried_actor, factor);
}
