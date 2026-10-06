#include <basis/seadNew.h>
#include "KingSystem/ActorSystem/Profiles/actAreaActor.h"
#include "KingSystem/Physics/RigidBody/physRigidBody.h"
#include "KingSystem/Physics/physMaterialMask.h"
#include "KingSystem/Physics/System/physCollisionInfo.h"
#include "KingSystem/Physics/System/physContactPointInfo.h"
#include "KingSystem/ActorSystem/actActorParam.h"
#include "KingSystem/Physics/System/physEntityGroupFilter.h"
#include "KingSystem/Resource/Actor/resResourceGParamList.h"
#include "KingSystem/Resource/GeneralParamList/resGParamListObjectAirWall.h"

namespace ksys::act {

AirWall::AirWall(const CreateArg& arg) : AreaActor(arg) {}

BaseProc* AirWall::construct(const CreateArg& arg, sead::Heap* heap) {
    return new (heap, std::nothrow) AirWall(arg);
}

void AirWall::preDelete2_(const PreDeleteArg& arg) {
    AreaActor::preDelete2_(arg);
    _890 = nullptr;
}

void AirWall::sub_7100E245B8(RigidBodyCallback* callback) {
    _890 = callback;
    sub_7100E2677C();
}

void AirWall::sub_7100E245C0(sead::IDelegate* callback) {
    _898 = callback;
    sub_7100E2677C();
}

void AirWall::m150() {
    if (_898) {
        _898->invoke();
        return;
    }
    phys::MaterialMask mask(0x21u);
    sub_7100E26784(&mask);
}

void AirWall::m149(phys::RigidBody* body) {
    AreaActor::m149(body);
    body->setContactNone();
    if (_890) {
        _890->invoke(body);
        return;
    }
    u32 mask = 0;
    mask = phys::orEntityGroundHitMask(mask, phys::GroundHit::Camera);
    mask = phys::orEntityGroundHitMask(mask, phys::GroundHit::AttackHitPlayer);
    mask = phys::orEntityGroundHitMask(mask, phys::GroundHit::AttackHitEnemy);
    mask = phys::orEntityGroundHitMask(mask, phys::GroundHit::CameraBody);
    mask = phys::orEntityGroundHitMask(mask, phys::GroundHit::IK);
    mask = phys::orEntityGroundHitMask(mask, phys::GroundHit::Grudge);
    mask = phys::orEntityGroundHitMask(mask, phys::GroundHit::LineOfSight);
    body->setGroundHitMask(body->getContactLayer(), mask);
}

void AirWall::m151() {
    if (auto* info = _848) {
        info->enableLayer(phys::ContactLayer::EntityPlayer);
        info->enableLayer(phys::ContactLayer::EntityNPC);
    }
    if (auto* point_info = _850) {
        point_info->subscribeLayer(phys::ContactLayer::EntityPlayer);
        point_info->subscribeLayer(phys::ContactLayer::EntityNPC);
    }
}

phys::ContactLayer AirWall::m152() {
    if (auto* param = getParam()) {
        if (auto* list = param->getRes().mGParamList) {
            if (auto* air_wall = list->getAirWall()) {
                if (air_wall->mLayer.ref() == "Ground")
                    return phys::ContactLayer::EntityGround;
            }
        }
    }
    return phys::ContactLayer::EntityAirWall;
}

}  // namespace ksys::act
