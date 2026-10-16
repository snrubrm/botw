#include "Game/Actor/Action/actionRemainElectricCannonBeamFire.h"
#include "KingSystem/ActorSystem/actActorSensorUtil.h"
#include "KingSystem/Physics/RigidBody/physRigidBody.h"
#include <math/seadVector.h>
#include "KingSystem/ActorSystem/actActor.h"
#include "KingSystem/ActorSystem/actActorUtil.h"
#include "KingSystem/ActorSystem/actGlobalParameter.h"
#include "KingSystem/Physics/System/physRayCastBodyQuery.h"
#include "KingSystem/Resource/GeneralParamList/resGParamListObjectGlobal.h"
#include "KingSystem/System/Timer.h"
#include "KingSystem/Utils/MathUtil.h"

namespace uking::action {

RemainElectricCannonBeamFire::RemainElectricCannonBeamFire(const InitArg& arg)
    : ksys::act::ai::Action(arg) {}

RemainElectricCannonBeamFire::~RemainElectricCannonBeamFire() = default;

bool RemainElectricCannonBeamFire::init_(sead::Heap* heap) {
    return ksys::act::ai::Action::init_(heap);
}

void RemainElectricCannonBeamFire::enter_(ksys::act::ai::InlineParamPack* params) {
    _48 = 5.0f;
    const sead::Vector3f pos = *mTargetPos_d;
    sub_710022AF50(pos, false);
    _58 = 0;
    sub_71007A44E4(mActor, true);
}

void RemainElectricCannonBeamFire::leave_() {
    if (_50 && _50->isAddedToWorld())
        _50->removeFromWorld();
}

void RemainElectricCannonBeamFire::loadParams_() {
    getStaticParam(&mAtkDamage_s, "AtkDamage");
    getStaticParam(&mMinDamage_s, "MinDamage");
    getDynamicParam(&mIsProtected_d, "IsProtected");
    getDynamicParam(&mTargetPos_d, "TargetPos");
    getDynamicParam(&mSafePos_d, "SafePos");
}

// NON_MATCHING: register allocation of the push-out vector and the ray start / end copies.
void RemainElectricCannonBeamFire::calc_() {
    ksys::Timer::update(&_48, -1.0f);
    if (_48 <= 0.0f && _58 <= 3) {
        f32 radius = 0.0f;
        auto* global = ksys::act::GlobalParameter::instance();
        if (global && global->getGlobalParam())
            radius = global->getGlobalParam()->mGerudoQueenSafetyAreaRadius.ref();

        sead::Vector3f pos = sead::Vector3f::zero;
        ksys::util::sub_71011EEE98(&pos, static_cast<f32>(_58) * sead::Mathf::pi2() * 0.25f,
                                   radius * 2.5f);
        pos.x += mTargetPos_d->x;
        pos.z += mTargetPos_d->z;
        const sead::Vector3f safe_pos = *mSafePos_d;
        if (sead::Vector2f(pos.x - safe_pos.x, pos.z - safe_pos.z).length() <= radius) {
            sead::Vector3f dir(pos.x - safe_pos.x, sead::Vector3f::zero.y, pos.z - safe_pos.z);
            dir.normalize();
            pos.x = radius * dir.x + pos.x;
            pos.y = radius * dir.y + pos.y;
            pos.z = radius * dir.z + pos.z;
        }

        ksys::phys::RayCastBodyQuery query(nullptr, ksys::phys::GroundHit::HitAll);
        ksys::act::sub_7100EEACE8(&query);
        const sead::Vector3f start(pos.x, mActor->getMtx()(1, 3), pos.z);
        const sead::Vector3f end(pos.x, 0.0f, pos.z);
        query.setStartAndEnd(start, end);
        if (query.worldRayCast(ksys::phys::ContactLayerType::Entity)) {
            sead::Vector3f hit = sead::Vector3f::zero;
            query.getHitPosition(&hit);
            pos.y = hit.y;
        } else {
            pos.y = mTargetPos_d->y;
        }
        sub_710022AF50(pos, true);
        if (++_58 == 4)
            setFinished();
        else
            _48 = 5.0f;
    }
}

}  // namespace uking::action
