#include "Game/gameSceneSubsysMisc.h"
#include <geom/seadGeometry.h>
#include <geom/seadSegment.h>
#include <prim/seadScopedLock.h>
#include "KingSystem/ActorSystem/actActor.h"
#include "KingSystem/ActorSystem/actActorConstDataAccess.h"
#include "KingSystem/ActorSystem/Profiles/actPlayerBase.h"
#include "Game/AI/aiXlinkHandle.h"
#include "KingSystem/ActorSystem/actActorSensorUtil.h"
#include "KingSystem/Physics/System/physRayCastBodyQuery.h"
#include "KingSystem/Physics/RigidBody/physRigidBodyFromShape.h"
#include "KingSystem/Physics/RigidBody/physRigidBodyFromResource.h"
#include "KingSystem/Physics/physMaterialMask.h"
#include "KingSystem/ActorSystem/actReaction.h"
#include "KingSystem/XLink/xlinkActorUtil.h"

SEAD_SINGLETON_DISPOSER_IMPL(GameSceneSubsys4)

// NON_MATCHING: the five lists are laid out and initialised as in the original; only the scheduling of the
// address computations for the second list differs.
GameSceneSubsys4::GameSceneSubsys4() = default;

GameSceneSubsys4::~GameSceneSubsys4() = default;

bool Unk_710243c208::m2(const Unk_PathNode* node) {
    const sead::Segment3f segment(node->_48, node->_54);
    f32 t = 0;
    const f32 distance = sead::Mathf::sqrt(sead::Geometry::calcSquaredDistancePointToSegment(mPos, segment, &t));
    return !(t > 0) || !(distance <= 3.0f);
}

void GameSceneSubsys4::m4() {
    mRequests.clear();
    mPoints.clear();
    mList1008.clear();
    mList1218.clear();
    mList14a0.clear();
}

void GameSceneSubsys4::m5() {
    mRequests.clear();
    mPoints.clear();
    mList1008.clear();
    mList1218.clear();
    mList14a0.clear();
}

void GameSceneSubsys4::sub_710066B8C0(ksys::act::BaseProc* actor) {
    sead::ScopedLock<sead::JobQueueLock> lock(&mLock);
    for (auto it = mRequests.begin(); it != mRequests.end(); ++it) {
        if (it->mLink.hasProcById(actor) || !it->mLink.hasProc()) {
            mRequests.erase(&*it);
            break;
        }
    }
}

// NON_MATCHING: member store scheduling differs.
Unk_7100905034::Unk_7100905034() {
    _100._34 = 1;
    for (s32 i = 0; i < mBodyStates.size(); ++i) {
        mBodyStates[i].gravity = 0;
        mBodyStates[i].friction = 1;
        mBodyStates[i].restitution = 1;
    }
}

// NON_MATCHING: the disposer keeps the existing out-of-line message callback destructor; the original
// inlines that cleanup. createInstance differs only in final member store scheduling.
SEAD_SINGLETON_DISPOSER_IMPL(GameSceneSubsys5)

// NON_MATCHING: final pointer and flag initialization stores are scheduled differently.
GameSceneSubsys5::GameSceneSubsys5() {
    _d8.fill(false);
    _fc.fill(false);
    _fe.fill(false);
    _dc.fill(sead::Vector3f::zero);
    _f4.fill(0);
    _124 = 0.1f;
    _128 = 0.7f;
}

// NON_MATCHING: the original inlines the message callback cleanup.
GameSceneSubsys5::~GameSceneSubsys5() = default;

void GameSceneSubsys5::init() {
    _58._44 = 1;
    _58._34 = 0.5f;
    _58._38 = 0.5f;
}

bool sub_71009059FC(const ksys::phys::RigidBody* body) {
    if (const auto* shape = sead::DynamicCast<const ksys::phys::RigidBodyFromShape>(body)) {
        if (shape->tryGetMaterialMask()->getMaterial() == ksys::phys::Material::Metal)
            return true;
    } else if (const auto* resource = sead::DynamicCast<const ksys::phys::RigidBodyFromResource>(body)) {
        if (resource->isMaterial(ksys::phys::Material::Metal))
            return true;
    }
    return false;
}

bool GameSceneSubsys5::sub_71009059D4() const {
    return _d8[_148];
}

void GameSceneSubsys5::sub_71009059EC(ksys::act::ActorConstDataAccess* accessor) {
    if (accessor)
        ksys::act::acquireActor(&_a8, accessor);
}

void GameSceneSubsys5::sub_7100905F30() {
    if (_48.isActive())
        return;
    _48 = ksys::eft::searchAndEmitELink(ksys::act::Reaction::sInstance->_30, "MagneConnect");
}

bool GameSceneSubsys5::sub_7100905B34() const {
    return _fc[_148];
}

bool GameSceneSubsys5::sub_7100905BEC() const {
    if (!_d8[_148])
        return true;
    if (!_32f)
        return true;
    return _138 > 3.5f;
}

bool GameSceneSubsys5::sub_7100905B4C(const sead::Vector3f& pos) const {
    if (!_331)
        return false;
    return (_dc[_148] - pos).length() <= _f4[_148];
}

bool GameSceneSubsys5::sub_7100905D44(ksys::act::Actor* actor) const {
    return actor->getId() == _140;
}

void GameSceneSubsys5::sub_7100905CA8(const sead::Vector3f& pos, f32 radius) {
    _dc[_144] = pos;
    _f4[_144] = radius;
}

void GameSceneSubsys5::sub_7100905C8C() {
    _fe[_144] = true;
}

void GameSceneSubsys5::sub_7100905C70() {
    _fc[_144] = true;
}

void GameSceneSubsys5::sub_7100905B1C() {
    _331 = true;
}

void GameSceneSubsys5::sub_710090547C() {
    _331 = false;
    _d8[0] = false;
    _d8[1] = false;
    _dc[0].set(0, 0, 0);
    _dc[1].set(0, 0, 0);
    _f4[0] = 0;
    _f4[1] = 0;
    _fc[0] = false;
    _fc[1] = false;
    _fe[0] = false;
    _fe[1] = false;
}

void GameSceneSubsys5::sub_710090549C() {
    _331 = false;
    _d8[0] = false;
    _d8[1] = false;
    _dc[0].set(0, 0, 0);
    _dc[1].set(0, 0, 0);
    _f4[0] = 0;
    _f4[1] = 0;
    _fc[0] = false;
    _fc[1] = false;
    _fe[0] = false;
    _fe[1] = false;
}

void GameSceneSubsys5::sub_7100905DEC(ksys::act::BaseProc* proc) {
    _b8.acquire(proc, false);
}

void GameSceneSubsys5::sub_7100905DF8() {
    _b8.reset();
}

void GameSceneSubsys5::sub_7100905E00(ksys::act::ActorConstDataAccess* accessor) {
    if (accessor)
        ksys::act::acquireActor(&_b8, accessor);
}

void GameSceneSubsys5::sub_7100905E10(f32 value) {
    _138 = value;
}

void GameSceneSubsys5::sub_7100905F08(f32 value) {
    _13c = value;
}

bool GameSceneSubsys5::sub_7100905F10() const {
    return _c8.hasProc();
}

sead::Vector3f GameSceneSubsys5::sub_7100905F18() const {
    return _10c;
}

bool GameSceneSubsys5::sub_7100905F28() const {
    return _329;
}

sead::Vector3f GameSceneSubsys5::sub_7100905E18() const {
    ksys::act::acc::PlayerBase player;
    player.getPlayerFromPlayerInfo();
    sead::Vector3f direction(0, 0, 1);
    if (player.hasProc()) {
        direction = _dc[_148] - player.getPosCopyMagnesis();
        direction.normalize();
    }
    return direction;
}

void GameSceneSubsys5::sub_7100905B28() {
    _331 = false;
    _58._0 = false;
}

bool GameSceneSubsys5::sub_7100905C30() const {
    return _32f;
}

const sead::Vector3f& GameSceneSubsys5::sub_7100905C38() const {
    return _dc[_148];
}

void GameSceneSubsys5::sub_7100905C54() {
    _d8[_144] = true;
}

void GameSceneSubsys5::sub_7100905CEC(f32* out) const {
    if (out) {
        out[0] = _124;
        out[1] = _128;
    }
}

void GameSceneSubsys5::sub_7100905D04(const f32* value) {
    _124 = value[0];
    _128 = value[1];
}

f32 GameSceneSubsys5::sub_7100905D18() const {
    return _130;
}

void GameSceneSubsys5::sub_7100905D20(f32 value) {
    _130 = value;
}

f32 GameSceneSubsys5::sub_7100905D34() const {
    return _134;
}

void GameSceneSubsys5::sub_7100905D3C(f32 value) {
    _134 = value;
}

sead::Vector3f GameSceneSubsys5::sub_7100905D58() const {
    return _100;
}

void GameSceneSubsys5::sub_7100905D68(const sead::Vector3f& value) {
    _100 = value;
}

GameSceneSubsys5::Box* GameSceneSubsys5::sub_7100905D84() {
    return &_20;
}

void GameSceneSubsys5::sub_7100905D8C(const Box& box) {
    _20 = box;
}

void GameSceneSubsys5::sub_7100905D28(bool value) {
    _328 = value;
}

void GameSceneSubsys5::sub_7100905DE0(bool value) {
    _32f = value;
}


bool GameSceneSubsys5::sub_710090611C(f32 length, ksys::act::BaseProcLink*, const sead::Vector3f& start,
                                      const sead::Vector3f& dir, sead::Vector3f* out) {
    ksys::phys::RayCastBodyQuery query(nullptr, ksys::phys::GroundHit::HitAll);
    query.enableLayer(ksys::phys::ContactLayer::EntityObject);
    query.enableLayer(ksys::phys::ContactLayer::EntityGroundObject);
    query.enableLayer(ksys::phys::ContactLayer::EntitySmallObject);
    query.setStartAndEnd(start, start + dir * length);
    if (_320 && query.shapeRayCast(_320)) {
        if (out)
            query.getHitPosition(out);
        return true;
    }
    return false;
}

bool GameSceneSubsys5::sub_7100906218(ksys::act::BaseProcLink* link, const sead::Vector3f& start,
                                      const sead::Vector3f& dir, f32 length, sead::Vector3f* out) {
    bool hit = false;
    if (!link->hasProc()) {
        ksys::phys::RayCastBodyQuery query(nullptr, ksys::phys::GroundHit::HitAll);
        sub_71007A5230(&query);
        query.setStartAndDisplacement(start, dir * length);
        if (query.worldRayCast(ksys::phys::ContactLayerType::Entity)) {
            query.getHitPosition(out);
            hit = true;
        }
    }
    return hit;
}

void GameSceneSubsys5::sub_7100906044() {
    uking::xlink::fade(_48, -1);
}
