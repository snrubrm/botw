#include "Game/Actor/Action/actionAirOctaFloat.h"
#include "Game/Actor/AI/aiAirOctaDataMgr.h"
#include "Game/Actor/aiUnk_71007377D4.h"
#include "KingSystem/ActorSystem/actActorLinkConstDataAccess.h"
#include "KingSystem/ActorSystem/actActor.h"
#include "KingSystem/Physics/RigidBody/physRigidBody.h"
#include "KingSystem/System/VFR.h"
#include "KingSystem/Utils/Thread/Message.h"

// Existing global helper; complete native body applies chemical-motion impulses.
void sub_71002FF594(ksys::act::Actor* actor);

namespace uking::action {

namespace {
// Placeholder name: the user data of message 0x80000c8 when `_0` is 0xc.
struct Unk_80000c8_Payload {
    u32 _0;
    u32 _4;
    u32 _8;
    u32 _c;
    u32 _10;
    f32 _14;
};
}  // namespace

AirOctaFloat::AirOctaFloat(const InitArg& arg) : AirOctaMoveBase(arg) {}

AirOctaFloat::~AirOctaFloat() = default;

bool AirOctaFloat::init_(sead::Heap* heap) {
    return AirOctaMoveBase::init_(heap);
}

void AirOctaFloat::enter_(ksys::act::ai::InlineParamPack* params) {
    AirOctaMoveBase::enter_(params);
    if (auto* manager = sub_7100088DA8()) {
        if (manager->mBaseProcLink2.hasProc())
            _1c4.set(0.005f, 1.7f, 0.005f);
        else
            _1c4.e = sead::Vector3f::zero.e;
    }
}

void AirOctaFloat::leave_() {
    AirOctaMoveBase::leave_();
}

void AirOctaFloat::loadParams_() {
    AirOctaMoveBase::loadParams_();
}

bool AirOctaFloat::handleMessage_(const ksys::Message* message) {
    if (message->getType() == 0x80000c8) {
        const auto* data = static_cast<const Unk_80000c8_Payload*>(message->getUserData());
        if (data && data->_0 == 0xc) {
            _1f8 = data->_14;
            return true;
        }
    }
    return false;
}

void AirOctaFloat::calc_() {
    if (_1f8 <= 0.0f) {
        if (auto* manager = sub_7100088DA8()) {
            const auto position = mActor->getMtx().getTranslation();
            const f32 x = position.x - manager->vec_F8.x;
            const f32 z = position.z - manager->vec_F8.z;
            if (x * x + z * z >= 0.1f * 0.1f)
                manager->sub_71002FB340(position.x, position.z);
        }
    } else {
        _1f8 -= ksys::VFR::instance()->getDeltaTime();
        auto* manager = sub_7100088DA8();
        auto* body = mActor->getMainBody();
        if (manager && body) {
            const auto position = mActor->getMtx().getTranslation();
            const auto velocity = body->getLinearVelocity();
            sead::Vector3f impulse = (manager->vec_F8 - (position + velocity)) * 30.0f;
            impulse *= ksys::VFR::instance()->getDeltaFrame();
            body->applyLinearImpulse(impulse);
        }
    }
    AirOctaMoveBase::calc_();
}

// NON_MATCHING: manager/data registers, reaction-vector temporaries and scalar multiplication stores differ.
void AirOctaFloat::m32() {
    auto* manager = sub_7100088DA8();
    if (!manager)
        return;
    auto* body = mActor->getMainBody();
    if (!body)
        return;
    auto* data = manager->sub_71002FB32C();
    const f32 delta = ksys::VFR::instance()->getDeltaFrame();
    const f32 time = ksys::VFR::instance()->getDeltaTime();
    sead::Vector3f gravity;
    sub_710072DC50(&gravity, mActor);
    gravity.y = -gravity.y;
    gravity *= time * body->getMass();
    body->applyLinearImpulse(gravity);
    if (!(manager->mFlags & 2)) {
        sub_71000845CC(manager, body);
        const sead::Vector3f position = mActor->getMtx().getTranslation();
        sead::Vector3f impulse;
        sub_7100088E38(1.7f, 0.08f, 0.5f, 0.5f, -1.0f, &impulse, &manager->vec_F8,
                        &position, &_1c4);
        impulse *= delta * body->getMass();
        body->applyLinearImpulse(impulse);
        sub_71002FF594(mActor);
        if (data && (data->_24.x != 0.0f || data->_24.y != 0.0f || data->_24.z != 0.0f)) {
            ksys::act::ActorLinkConstDataAccess linked;
            if (ksys::act::acquireActor(&manager->mBaseProcLink2, &linked)) {
                const f32 factor = delta * time * 1.02f;
                sead::Vector3f reaction(-data->_24.x, 0.0f, -data->_24.z);
                reaction *= factor;
                body->applyLinearImpulse(reaction);
            }
        }
    } else {
        const f32 factor = time * body->getMass();
        const sead::Vector3f impulse = factor * sead::Vector3f(0.0f, 20.0f, 0.0f);
        body->applyLinearImpulse(impulse);
    }
}

void AirOctaFloat::m33(sead::Vector3f* min, sead::Vector3f* max) {
    min->set(-3.0f, -3.0f, -3.0f);
    max->set(3.0f, 3.0f, 3.0f);
}

f32 AirOctaFloat::m34() {
    if (auto* manager = sub_7100089328()) {
        if (auto* data = manager->sub_71002FB32C()) {
            if (data->_b2)
                return *mAmplitude_s * 0.5f;
            if (data->_b1)
                return 0.0f;
        }
    }
    return *mAmplitude_s;
}

}  // namespace uking::action
