#include "Game/AI/AI/aiChildDeviceReflectArrow.h"
#include "KingSystem/ActorSystem/actActor.h"
#include "KingSystem/Physics/System/physInstanceSet.h"
#include <math/seadMathCalcCommon.h>
#include "KingSystem/ActorSystem/actActor.h"
#include "KingSystem/ActorSystem/actActorConstDataAccess.h"
#include "KingSystem/ActorSystem/actActorSensorUtil.h"
#include "KingSystem/Physics/RigidBody/physRigidBody.h"
#include "KingSystem/Utils/MathUtil.h"
#include "KingSystem/Utils/Thread/Message.h"

namespace uking::ai {

ChildDeviceReflectArrow::ChildDeviceReflectArrow(const InitArg& arg) : WithoutWeaponArrow(arg) {}

ChildDeviceReflectArrow::~ChildDeviceReflectArrow() {
    if (auto* physics = mActor->getPhysics())
        physics->sub_7100FB835C();
}

void ChildDeviceReflectArrow::enter_(ksys::act::ai::InlineParamPack* params) {
    WithoutWeaponArrow::enter_(params);
    _180 = ksys::Timer(0, 0);
    _158 = false;
    _159 = false;
    _15a = false;
    _160 = 0;
    _164 = 0;
    _15c = 0;
}

void ChildDeviceReflectArrow::loadParams_() {
    WithoutWeaponArrow::loadParams_();
    getStaticParam(&mReflectCountMax_s, "ReflectCountMax");
    getStaticParam(&mReflectAimSpeed_s, "ReflectAimSpeed");
    getStaticParam(&mReflectAccel_s, "ReflectAccel");
}

void ChildDeviceReflectArrow::m35() {
    WithoutWeaponArrow::m35();
}

bool ChildDeviceReflectArrow::m37(bool* broke_ice_block, bool* hit_player) {
    if (!hasAttackInfo(mActor))
        return false;

    bool result = true;
    const s32 num = getNumAttackInfoMaybe(mActor);
    for (s32 i = 0; i < num; ++i) {
        auto* info = getAttackInfo(mActor, i);
        if (!info)
            continue;

        auto* link = &info->_50;
        if (!link->hasProc())
            continue;

        ksys::act::ActorConstDataAccess accessor;
        ksys::act::acquireActor(link, &accessor);
        if (accessor.getName() == "Enemy_SiteBoss_Bow_ChildDevice") {
            result = false;
            *broke_ice_block = true;
        }
    }
    return result;
}

f32 ChildDeviceReflectArrow::m42() {
    return _15a ? WithoutWeaponArrow::m42() : *mReflectAccel_s;
}

f32 ChildDeviceReflectArrow::m43() {
    return _15a ? WithoutWeaponArrow::m43() : *mReflectAimSpeed_s;
}

s32 ChildDeviceReflectArrow::m47() {
    if (!_15a)
        return 0;
    return WithoutWeaponArrow::m47();
}

bool ChildDeviceReflectArrow::m48() {
    if (WithoutWeaponArrow::m48())
        return true;
    return isCurrentChild("反射");
}

bool ChildDeviceReflectArrow::m49() {
    return _158;
}

void ChildDeviceReflectArrow::m50(bool a1) {
    _158 = a1;
}

s32 ChildDeviceReflectArrow::m51() {
    return _15c;
}

sead::Vector3f* ChildDeviceReflectArrow::m52() {
    return &_174;
}

void ChildDeviceReflectArrow::m53(const sead::Vector3f& a1) {
    _174 = a1;
}

bool ChildDeviceReflectArrow::handleMessage_(const ksys::Message* message) {
    // Payloads of messages 0x8000056 / 0x8000054 (no sender found; layouts read from this function)
    struct ReflectPayload {
        bool _0;
        sead::Vector3f _4;
        sead::Vector3f _10;
        sead::Vector3f _1c;
    };
    struct CountPayload {
        u8 _0[0x1c];
        u32 _1c;
    };

    if (message && message->getBrokerId() == 0xffffffff) {
        if (message->getType() == 0x8000056) {
            if (message->getUserData()) {
                if (!m46() && !_159) {
                    auto* payload = static_cast<ReflectPayload*>(message->getUserData());
                    m50(true);
                    _168 = payload->_4;
                    f32 value;
                    bool reflected;
                    if (payload->_0 && *mReflectCountMax_s > m51()) {
                        m53(payload->_10);
                        ++_15c;
                        value = 0.3f;
                        reflected = false;
                    } else {
                        m53(payload->_1c);
                        value = 1.2f;
                        reflected = true;
                    }
                    _164 = value;
                    _15a = reflected;
                }
                return true;
            }
        }
        if (message->getType() == 0x8000054) {
            if (message->getUserData()) {
                auto* payload = static_cast<CountPayload*>(message->getUserData());
                _15c = ~(payload->_1c & 3) + *mReflectCountMax_s;
                return true;
            }
        }
    }
    return false;
}

void ChildDeviceReflectArrow::calc_() {
    WithoutWeaponArrow::calc_();
    _180.update();

    if (!m49()) {
        getCurrentChild()->setDynamicParam(false, "IsReInitShoot");
        return;
    }

    _160 = mActor->getVelocity().length();
    sead::Vector3f dir = _174;
    dir -= _168;
    const f32 distance = dir.normalize();

    sead::Matrix34f mtx;
    ksys::util::sub_71011F00EC(&mtx, dir, sead::Vector3f::ey, _168, false);
    if (auto* body = mActor->getMainBody())
        body->setTransform(mtx, ksys::phys::PropagateToLinkedMotions{true});
    m50(false);

    f32 speed = 0.2f;
    if (distance > 0.2f)
        speed = sead::Mathf::max(_160 * _164, 0.8f);
    dir *= speed;

    if ((m51() & 3) == 0) {
        m34(dir, false, "発射");
    } else {
        getCurrentChild()->setDynamicParam(dir, "FirstSpeed");
        getCurrentChild()->setDynamicParam(_174, "TargetPos");
        getCurrentChild()->setDynamicParam(true, "IsReInitShoot");
    }
    _159 = false;
}

}  // namespace uking::ai
