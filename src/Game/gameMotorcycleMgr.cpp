#include "Game/gameMotorcycleMgr.h"
#include <math/seadMathCalcCommon.h>
#include "Game/Actor/actHorseRideInfo.h"
#include "KingSystem/ActorSystem/actActor.h"
#include "KingSystem/ActorSystem/actActorSystem.h"
#include "KingSystem/ActorSystem/Profiles/actPlayerLink.h"
#include "KingSystem/World/worldManager.h"
#include "KingSystem/ActorSystem/actActorConstDataAccess.h"
#include "KingSystem/Physics/RigidBody/Shape/Capsule/physCapsuleShape.h"
#include "KingSystem/Physics/RigidBody/Shape/Capsule/physCapsuleRigidBody.h"
#include "KingSystem/Physics/System/physHavokAI.h"
#include "KingSystem/Physics/System/physRayCastBodyQuery.h"
#include "KingSystem/Physics/RigidBody/physRigidBody.h"

namespace uking {

SEAD_SINGLETON_DISPOSER_IMPL(MotorcycleMgr)

MotorcycleMgr::MotorcycleMgr() : _148() {}

// NON_MATCHING: register allocation / scheduling (the constant 1.0f and 1 swap registers; the
// capsule parameter stores are scheduled differently)
void MotorcycleMgr::init(sead::Heap* heap) {
    mEnergyHandle = ksys::gdt::Manager::instance()->getF32Handle("Motorcycle_Energy");
    ksys::gdt::Manager::instance()->addReinitCallback(mSlot);

    _c8 = 0;
    _17e = 0;
    _178 = 0;
    mEnergy = 1000.0f;

    ksys::phys::CapsuleParam param;
    param.contact_layer = ksys::phys::ContactLayer::EntityObject;
    param.motion_type = ksys::phys::MotionType::Fixed;
    param.vertex_a = {0.0f, 0.97f, -0.9f};
    param.vertex_b = {0.0f, 0.97f, 1.0f};
    param.radius = 0.97f;
    param.name = "MotorcycleShapeCast";
    _d0 = ksys::phys::CapsuleRigidBody::make(&param, heap);
}

bool MotorcycleMgr::isProhibited(const sead::Vector3f& pos, ksys::act::PlayerLink* player) {
    if (!player)
        player = ksys::act::ActorSystem::instance()->getPlayerLink();
    if (player && player->m211())
        return false;
    auto* mgr = ksys::world::Manager::instance();
    if (!mgr)
        return true;
    switch (mgr->getClimate(pos)) {
    case ksys::world::Climate::GerudoDesertClimate:
    case ksys::world::Climate::EldinClimateLv1:
    case ksys::world::Climate::EldinClimateLv2:
    case ksys::world::Climate::GerudoDesertClimateLv2:
        return false;
    default:
        return true;
    }
}

// NON_MATCHING: the original re-reads the query position relative to `_d8` after every call; we keep
// strength-reduced pointers into it in extra callee-saved registers (frame 0x50 instead of 0x40)
bool MotorcycleMgr::spawnMotorcycle_x(sead::Vector3f* out_pos, sead::Vector3f* out_normal,
                                      ksys::phys::RayCastBodyQuery* cast) {
    auto* query = _d8;
    const sead::Vector3f& pos = query->_c;
    f32 end_offset;
    if (query->_24 == 0x17 && _17d) {
        const sead::Vector3f start = pos;
        cast->setStart(start);
        end_offset = -1.0f;
    } else {
        const sead::Vector3f start(pos.x, pos.y + 2.0f + 1.0f, pos.z);
        cast->setStart(start);
        end_offset = -2.0f;
    }
    const sead::Vector3f end(pos.x, pos.y + end_offset, pos.z);
    cast->setEnd(end);

    if (!cast->worldRayCast(ksys::phys::ContactLayerType::Entity))
        return false;
    if (auto* body = cast->getHitRigidBody()) {
        if (body->getMotionType() == ksys::phys::MotionType::Dynamic)
            return false;
    }
    const auto material = cast->getMaterialMask().getMaterial();
    const sead::SafeString sub_material = cast->getMaterialMask().getSubMaterialName();
    if (material == ksys::phys::Material::Water)
        return false;
    if (material == ksys::phys::Material::Soil && sub_material == "Stone_DgnLight")
        return false;
    if (cast->getHitNormalInline().y < 0.64278764f)
        return false;
    cast->getHitPosition(out_pos);
    out_normal->set(cast->getHitNormalInline());
    return true;
}

// NON_MATCHING: scheduling / register allocation of the corner computations (the original keeps the first
// two corners' components in callee-saved registers and stores `end` with a pair store)
bool MotorcycleMgr::spawnMotorcycle_x_0(const sead::Vector3f& pos_, const sead::Vector3f& size,
                                        const sead::Vector3f& dir_,
                                        ksys::phys::RayCastBodyQuery* cast) {
    const sead::Vector3f pos = pos_;
    const sead::Vector3f dir = dir_;
    sead::Vector3f start, end;
    const f32 cx = dir.x * 1.3f + pos.x;
    const f32 cy = dir.y * 1.3f + pos.y;
    const f32 cz = dir.z * 1.3f + pos.z;
    start.x = cx + size.x * 0.5f;
    start.y = cy + size.y * 0.5f;
    start.z = cz + size.z * 0.5f;
    end.x = cx - size.x * 0.5f;
    end.y = cy - size.y * 0.5f;
    end.z = cz - size.z * 0.5f;
    cast->setStart(start);
    cast->setEnd(end);
    bool hit = cast->worldRayCast(ksys::phys::ContactLayerType::Entity);
    if (hit) {
        const f32 bx = pos.x - dir.x * 1.1f;
        const f32 by = pos.y - dir.y * 1.1f;
        const f32 bz = pos.z - dir.z * 1.1f;
        start.x = bx + size.x * 0.5f;
        end.x = bx - size.x * 0.5f;
        start.y = by + size.y * 0.5f;
        end.y = by - size.y * 0.5f;
        start.z = bz + size.z * 0.5f;
        end.z = bz - size.z * 0.5f;
        cast->setStart(start);
        cast->setEnd(end);
        hit = cast->worldRayCast(ksys::phys::ContactLayerType::Entity);
    }
    return hit;
}

void MotorcycleMgr::setMotorcycleEnergyIter(ksys::gdt::Manager::ReinitEvent*) {
    mEnergyHandle = ksys::gdt::Manager::instance()->getF32Handle("Motorcycle_Energy");
}

void MotorcycleMgr::clampMotorcycleEnergy() {
    if (!ksys::gdt::Manager::instance()->getF32(mEnergyHandle, &mEnergy)) {
        mEnergy = 1000.0f;
        return;
    }
    mEnergy = sead::Mathf::clamp(mEnergy, 0.0f, 1000.0f);
}

bool MotorcycleMgr::checkIsActorRidingMotorcycle(ksys::act::Actor* actor) {
    auto* ride_info = actor->getPlayerRideInfo();
    if (ride_info && mProcLink.hasProc() && ride_info->_18 == mProcLink)
        return true;
    return false;
}

bool MotorcycleMgr::x(ksys::act::BaseProc* actor) {
    return actor && mProcLink.hasProcById(actor);
}

bool MotorcycleMgr::x_0() {
    return mProcLink.hasProc();
}

bool MotorcycleMgr::hasHavokQueryStarted() const {
    return _17e == 1;
}

bool MotorcycleMgr::sub_710067B63C(sead::Vector3f* pos) {
    if (!mProcLink.hasProc())
        return false;
    ksys::act::ActorConstDataAccess accessor;
    ksys::act::acquireActor(&mProcLink, &accessor);
    const auto& mtx = accessor.getActorMtx();
    pos->x = mtx(0, 3);
    pos->y = mtx(1, 3);
    pos->z = mtx(2, 3);
    return true;
}

bool MotorcycleMgr::sub_710067B6BC(sead::Matrix34f* mtx) {
    if (!mProcLink.hasProc())
        return false;
    ksys::act::ActorConstDataAccess accessor;
    ksys::act::acquireActor(&mProcLink, &accessor);
    accessor.sub_7100D11860(mtx);
    return true;
}

void MotorcycleMgr::sub_710067AFB0() {
    if (auto* actor = sead::DynamicCast<ksys::act::Actor>(mProcLink.getProc(nullptr)))
        actor->setFlag(ksys::act::Actor::ActorFlag::_1c, true);
}

void MotorcycleMgr::effectFadeXLink() {
    if (_148.sub_7101241B6C())
        _148.fadeXLink();
}

MotorcycleMgr::~MotorcycleMgr() {
    delete _d0;
    if (mProcHandle.isAllocatedOrFailed())
        mProcHandle.deleteProc();
    if (_d8)
        ksys::phys::HavokAI::instance()->destroyQuery(_d8);
    if (auto* gdt_mgr = ksys::gdt::Manager::instance())
        gdt_mgr->removeReinitCallback(mSlot);

    if (_168.getEvent() && _168.getEvent()->getCreateId() == _168.getCreateId()) {
        _168.fade();
        _168.reset();
    }
    if (_148.sub_7101241B6C()) {
        if (_148.mELink.getEvent() &&
            _148.mELink.getEvent()->getCreateId() == _148.mELink.getCreateId()) {
            _148.mELink.fade();
            _148.mELink.reset();
        }
        if (_148.mSLink.getEvent() &&
            _148.mSLink.getEvent()->getCreateId() == _148.mSLink.getCreateId()) {
            _148.mSLink.fade();
            _148.mSLink.reset();
        }
        _148.fadeXLink();
    }
}

}  // namespace uking
