#include "Game/gameMotorcycleMgr.h"
#include <algorithm>
#include <math/seadMathCalcCommon.h>
#include <codec/seadHashCRC32.h>
#include "Game/Actor/actHorseRideInfo.h"
#include "Game/Actor/aiXlinkHandle.h"
#include "Game/UI/uiUtils.h"
#include "Game/gameSceneSubsys12.h"
#include <prim/seadSafeString.h>
#include "KingSystem/ActorSystem/actActor.h"
#include "KingSystem/ActorSystem/actActorSystem.h"
#include "KingSystem/ActorSystem/Profiles/actPlayerLink.h"
#include "KingSystem/World/worldManager.h"
#include "KingSystem/ActorSystem/actActorLinkConstDataAccess.h"
#include "KingSystem/Physics/RigidBody/Shape/physCapsuleShape.h"
#include "KingSystem/Physics/RigidBody/physRigidBodyCapsule.h"
#include "KingSystem/Physics/System/physHavokAI.h"
#include "KingSystem/Physics/System/physNavMeshCharacter.h"
#include "KingSystem/Physics/System/physRayCastBodyQuery.h"
#include "KingSystem/Physics/System/physShapeCastWithInfo.h"
#include "KingSystem/Physics/System/physQueryContactPointInfo.h"
#include "KingSystem/Physics/System/physInstanceSet.h"
#include "KingSystem/Physics/RigidBody/physRigidBody.h"
#include "KingSystem/ActorSystem/actInfoData.h"
#include "KingSystem/Utils/Byaml/Byaml.h"

namespace uking {

// 0x71025c5fb8: set to 6.0f by the TU's global initialiser (0x710067b7c8, still undecompiled): the
// radius of the spawn nav mesh query and the squared-distance threshold.
KSYS_VISIBILITY_HIDDEN f32 sHavokQueryRadius;
// 0x71025c5fbc: set to 66.666664f by the same initialiser: the energy an actor without a
// "motorcycleEnergy" add value contributes.
KSYS_VISIBILITY_HIDDEN f32 sEnergyDefaultAdd;


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

bool MotorcycleMgr::checkAndStartQueryNavMesh(ksys::act::PlayerLink* player) {
    if (_17f)
        return false;
    return sub_7100679B30(_12c, player);
}

// 0x7100679dbc: whether the spawn query has a usable result. A pending query compares its position
// with the last accepted one (within the radius); a finished query checks the nav mesh material.
// NON_MATCHING: the bool result's false block stays at the fallthrough in our build (`b.le` instead
// of the original's `b.gt`), and the position components load in a different order.
bool MotorcycleMgr::spawnMotorcycle_checkHavokQueryStuff() {
    auto* query = _d8;
    if (query->_24 == 0x13)
        return false;
    if (query->_24 != 0x17) {
        const f32 dx = query->_c.x - _f0.m[0][3];
        const f32 dy = query->_c.y - _f0.m[1][3];
        const f32 dz = query->_c.z - _f0.m[2][3];
        return !(dx * dx + dy * dy + dz * dz > sHavokQueryRadius * sHavokQueryRadius);
    }

    sead::Vector3f pos;
    const auto result = ksys::phys::HavokAI::instance()->sub_7100F87ED0(
        &pos, query->_c, sHavokQueryRadius);
    if (!result.sub_7100F7EB40())
        return true;
    const f32 cost = ksys::phys::NavMeshCharacter::sub_7100F74FD8(
        ksys::phys::NavMeshCharacterType::Horse, result.sub_7100F7EEE4());
    bool usable = false;
    if (!(sead::Mathf::abs(cost) > std::numeric_limits<f32>::max())) {
        if (result.sub_7100F7EEE4() != 0x13)
            usable = true;
    }
    return usable;
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
// 0x710067a40c: a zero-length shape cast with the player's system group handler at the spawn
// position; the cast's rotation uses the box size and the query direction as two axes.
// NON_MATCHING: our subscribeAllLayers helper stores both masked words with one 64-bit store (the
// original stores each word), and the rotation matrix stores are scheduled differently.
bool MotorcycleMgr::spawnMotorcycleShapeCastStuff(sead::Vector3f* pos, sead::Vector3f* size,
                                                  sead::Vector3f* dir,
                                                  ksys::phys::InstanceSet* instance) {
    ksys::phys::ShapeCastWithInfo cast(_d0, 4, ksys::phys::ShapeCast::Mode::_0,
                                       sead::SafeString::cEmptyString,
                                       ksys::phys::LowPriority::No);
    if (instance)
        _d0->setSystemGroupHandler(instance->get188(0));
    auto* info = cast.getContactPointInfo();
    info->subscribeAllLayers();
    info->unsubscribeLayer(ksys::phys::ContactLayer::EntityWater);

    sead::Vector3f start = *pos;
    start.x = size->x * 0.5f + start.x;
    start.y = size->y * 0.5f + start.y;
    start.z = size->z * 0.5f + start.z;
    cast.setStartAndEnd(start, start);

    const sead::Vector3f cross = size->cross(*dir);
    cast.setRotation(sead::Matrix33f(cross.x, size->x, dir->x, cross.y, size->y, dir->y,
                                     cross.z, size->z, dir->z));

    _d0->setGroundHitType(ksys::phys::GroundHit::Animal);
    // called through a pointer in the original (not devirtualised)
    if ((&cast)->executeQuery(ksys::phys::ShapeCast::WeldClosestPoints::Yes))
        return false;
    _d0->setGroundHitType(ksys::phys::GroundHit::Player);
    return !(&cast)->executeQuery(ksys::phys::ShapeCast::WeldClosestPoints::Yes);
}

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

// NON_MATCHING: std::min uses stack temporaries and pointer selection instead of FMIN.
// 0x710067a7e4: asks the carried-actor subsystem for the names around the player, hashes them and
// turns the result into fuel (0 clears the spawn flag on the subsystem).
bool MotorcycleMgr::sub_710067A7E4(s32* out_a, s32* out_b) {
    auto* scene = GameSceneSubsys12::instance();
    if (!scene)
        return false;

    sead::FixedSafeString<64> names[5];
    sead::Buffer<sead::FixedSafeString<64>> buffer(5, names);

    if (out_a && out_b) {
        *out_b = scene->sub_7100664D64();
        *out_a = scene->sub_710066358C() - *out_b;
    }

    scene->sub_7100664E0C(nullptr, &buffer);

    EnergyCalculationArg arg;
    const s32 num_names = buffer.size();
    const auto* name = buffer.getBufferPtr();
    for (s32 i = 0; i != num_names; ++i)
        arg.hashes[i] = sead::HashCRC32::calcStringHash(name[i].cstr());

    const f32 energy = sub_710067A9DC(&arg);
    _c8 = energy;
    if (energy <= 0.0f) {
        scene->_a78.fetchAnd(0xfffffffeu);
        return false;
    }
    return true;
}

// 0x710067a9dc: computes the fuel from up to five actor names (their "motorcycleEnergy" BYML
// values) and caches the result with the hashes.
// NON_MATCHING: our loop strength-reduces the array index to a byte cursor (the original keeps the
// s32 index with its SafeArray bound check), which also moves the ByamlIter stack slots.
f32 MotorcycleMgr::sub_710067A9DC(EnergyCalculationArg* arg) {
    if (arg->hashes[0] == mLastEnergyHashes[0] && arg->hashes[1] == mLastEnergyHashes[1] &&
        arg->hashes[2] == mLastEnergyHashes[2] && arg->hashes[3] == mLastEnergyHashes[3] &&
        arg->hashes[4] == mLastEnergyHashes[4]) {
        arg->value = mLastEnergy;
        return arg->value;
    }

    f32 multiply = 1.0f;
    f32 add = 0.0f;
    for (s32 i = 0; i != 5; ++i) {
        if (arg->hashes(i) != 0) {
            al::ByamlIter actor_iter;
            al::ByamlIter energy_iter;
            if (ksys::act::InfoData::instance()->getActorIter(&actor_iter, arg->hashes(i), true)) {
                if (actor_iter.tryGetIterByKey(&energy_iter, "motorcycleEnergy")) {
                    f32 value;
                    if (energy_iter.tryGetFloatByKey(&value, "add"))
                        add += value;
                    if (energy_iter.tryGetFloatByKey(&value, "multiply"))
                        multiply *= value;
                } else {
                    add += sEnergyDefaultAdd;
                }
            }
        }
        mLastEnergyHashes[i] = arg->hashes(i);
    }
    arg->value = multiply * add;
    mLastEnergy = arg->value;
    return arg->value;
}

void MotorcycleMgr::sub_710067AB8C() {
    if (_c8 > 0.0f) {
        if (auto* scene = GameSceneSubsys12::instance()) {
            mEnergy = std::min(mEnergy + _c8, 1000.0f);
            _c8 = 0.0f;
            scene->sub_7100665360();
        }
    }
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
    ksys::act::ActorLinkConstDataAccess accessor;
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
    ksys::act::ActorLinkConstDataAccess accessor;
    ksys::act::acquireActor(&mProcLink, &accessor);
    accessor.sub_7100D11860(mtx);
    return true;
}

void MotorcycleMgr::sub_710067AF08(ksys::act::Unk117* arg) {
    if (auto* actor = sead::DynamicCast<ksys::act::Actor>(mProcLink.getProc(nullptr, nullptr)))
        actor->x_17(arg);
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

// NON_MATCHING: the final climate bit test is folded to `and w0, w8, #1`; the original
// branches to the shared `return true` block.
bool MotorcycleMgr::prepareNewSpawn(ksys::act::PlayerLink* player) {
    if (_17e == 1)
        return false;

    calculateSomePositionStuff(_12c, _138);

    if (!player)
        player = ksys::act::ActorSystem::instance()->getPlayerLink();
    if (player && player->m211())
        return false;

    auto* mgr = ksys::world::Manager::instance();
    if (!mgr)
        return true;

    switch (mgr->getClimate(_12c)) {
    case ksys::world::Climate::GerudoDesertClimate:
    case ksys::world::Climate::EldinClimateLv1:
    case ksys::world::Climate::EldinClimateLv2:
    case ksys::world::Climate::GerudoDesertClimateLv2:
        return false;
    }
    return true;
}

// NON_MATCHING: the climate test is lowered with a 1 << climate mask and the m211 branch is
// laid out the other way round; the operations and the marker effect calls match.
void MotorcycleMgr::checkUsableForSoundEffectAndMarker() {
    s32 state = calculateSomePositionStuff(_12c, _138);
    if (state == 0) {
        auto* player = ksys::act::ActorSystem::instance()->getPlayerLink();
        if (player && player->m211()) {
            state = 1;
        } else {
            state = 0;
            if (auto* mgr = ksys::world::Manager::instance()) {
                const auto climate = mgr->getClimate(_12c);
                if (climate == ksys::world::Climate::GerudoDesertClimate ||
                    climate == ksys::world::Climate::EldinClimateLv1 ||
                    climate == ksys::world::Climate::EldinClimateLv2 ||
                    climate == ksys::world::Climate::GerudoDesertClimateLv2)
                    state = 1;
            }
        }
    }

    if (s8(_17f) != state) {
        _148.fadeXLink();
        switch (state) {
        case -1:
        case 1:
            playEffectMaybe("BikeMarker_NG", &_148);
            break;
        case 0:
            playEffectMaybe("DLC2_Bike_Marker", &_148);
            break;
        default:
            break;
        }
        _17f = state;
    }

    if (_148.sub_7101241B6C()) {
        sead::Matrix34f mtx = sead::Matrix34f::ident;
        x_1(&mtx);
        _148.sub_7101241A44(mtx);
    }
}

// NON_MATCHING: the state test is lowered as ldrb + range compares (target ldrsb + cmn/ccmp)
// and the fade/reset block is laid out after the state-0 arm; the calls and strings match.
void MotorcycleMgr::playAppearPointSounds() {
    const s32 state = _17f;
    if (state == -1 || state == 1) {
        uking::xlink::fade(_168, -1);
        _168.reset();
    } else if (state == 0) {
        if (!_168.getEvent() || _168.getEvent()->getCreateId() != _168.getCreateId())
            uking::ui::playSound("BikeAppearPointPreview", &_168);
    }

    if (_179) {
        if (_17a)
            uking::ui::playSound("BikeAppearPointDecide", nullptr);
        _179 = false;
    }
}

}  // namespace uking

namespace uking {

// NON_MATCHING: request initialization, accessor cleanup and loop scheduling differ.
f32 MotorcycleMgr::sub_710067ADCC(const sead::SafeString& actor_name) {
    EnergyCalculationArg arg;
    s32 free_index = -1;
    if (auto* scene = GameSceneSubsys12::instance()) {
        for (s32 i = 0; i < 5; ++i) {
            if (auto* link = scene->sub_7100664DBC(i)) {
                ksys::act::ActorLinkConstDataAccess accessor;
                if (ksys::act::acquireActor(link, &accessor)) {
                    arg.hashes[i] = sead::HashCRC32::calcStringHash(accessor.getName().cstr());
                    continue;
                }
            }
            if (free_index == -1)
                free_index = i;
        }
    } else {
        free_index = 0;
    }
    if (free_index != -1 && !actor_name.isEmpty())
        arg.hashes[free_index] = sead::HashCRC32::calcStringHash(actor_name.cstr());
    return sub_710067A9DC(&arg);
}

}  // namespace uking
