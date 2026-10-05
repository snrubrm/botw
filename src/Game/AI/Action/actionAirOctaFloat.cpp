#include "Game/AI/Action/actionAirOctaFloat.h"
#include "Game/AI/AI/AirOcta/AirOctaDataMgr.h"
#include "KingSystem/ActorSystem/actActor.h"
#include "KingSystem/Physics/RigidBody/physRigidBody.h"
#include "KingSystem/System/VFR.h"
#include "KingSystem/Utils/Thread/Message.h"

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

AirOctaFloat::AirOctaFloat(const InitArg& arg) : AirOctaFloatBase(arg) {}

AirOctaFloat::~AirOctaFloat() = default;

bool AirOctaFloat::init_(sead::Heap* heap) {
    return AirOctaFloatBase::init_(heap);
}

// NON_MATCHING: vector address scheduling and zero-vector copy stores differ.
void AirOctaFloat::enter_(ksys::act::ai::InlineParamPack* params) {
    AirOctaFloatBase::enter_(params);
    if (auto* manager = sub_7100088DA8()) {
        if (manager->mBaseProcLink2.hasProc())
            _1c4.set(0.005f, 1.7f, 0.005f);
        else
            _1c4 = sead::Vector3f::zero;
    }
}

void AirOctaFloat::leave_() {
    AirOctaFloatBase::leave_();
}

void AirOctaFloat::loadParams_() {
    AirOctaFloatBase::loadParams_();
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
    AirOctaFloatBase::calc_();
}

}  // namespace uking::action
