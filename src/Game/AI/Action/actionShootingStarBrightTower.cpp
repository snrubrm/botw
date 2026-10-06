#include "Game/AI/Action/actionShootingStarBrightTower.h"
#include <algorithm>
#include "KingSystem/ActorSystem/actActor.h"
#include "KingSystem/ActorSystem/actActorCreator.h"
#include "KingSystem/ActorSystem/actActorHeapUtil.h"
#include "KingSystem/ActorSystem/actActorParam.h"
#include "KingSystem/ActorSystem/actInstParamPack.h"
#include "KingSystem/Resource/Actor/resResourceDrop.h"
#include "KingSystem/ActorSystem/actPlayerInfo.h"
#include "KingSystem/Physics/RigidBody/physRigidBody.h"
#include "KingSystem/Physics/System/physRayCastBodyQuery.h"
#include "KingSystem/System/Timer.h"
#include "KingSystem/World/worldManager.h"
#include "KingSystem/World/worldShootingStarMgr.h"
#include "KingSystem/XLink/xlinkXLink.h"

namespace uking::action {

ShootingStarBrightTower::ShootingStarBrightTower(const InitArg& arg) : ksys::act::ai::Action(arg) {}

ShootingStarBrightTower::~ShootingStarBrightTower() = default;

bool ShootingStarBrightTower::init_(sead::Heap* heap) {
    return ksys::act::ai::Action::init_(heap);
}

void ShootingStarBrightTower::enter_(ksys::act::ai::InlineParamPack* params) {
    mActor->getActorFlags2().set(ksys::act::Actor::ActorFlag2::_20);
    mActor->getXLink()->_cc.reset(0x80000);
    _6c = sead::Matrix34f::ident;
    sead::Vector3f pos = mActor->getMtx().getTranslation();
    if (auto* world = ksys::world::Manager::instance()) {
        if (auto* star = world->getShootingStarMgr())
            star->tryGetStarPosition(&pos);
    }
    const sead::Vector3f& dir = *mHitGroundAngle_d;
    _6c.setTranslation(pos);
    const f32 length = dir.length();
    if (length > 0)
        _9c.setScale(dir, 1.0f / length);
    xlinkSearchAndEmit(mActor, "BrightTower", 2, &_30);
    _30.sub_7101241A44(_6c);
    _60 = pos;
    _a8 = 50.0f;
}

void ShootingStarBrightTower::leave_() {
    _30.fadeXLink();
}

void ShootingStarBrightTower::loadParams_() {
    getStaticParam(&mDisappearDistance_s, "DisappearDistance");
    getDynamicParam(&mHitGroundAngle_d, "HitGroundAngle");
}

void ShootingStarBrightTower::shootingStarDropStuff(const sead::Vector3f& pos) {
    ksys::act::InstParamPack pack;
    pack->addPosition(pos - _9c * 0.05f);
    auto* drop = mActor->getParam()->getRes().mDropTable;
    if (drop && drop->getNumTables() >= 1) {
        const s32 repeat_num = std::max(drop->getRepeatNum("Normal"), 1);
        for (s32 i = 0; i < repeat_num; ++i) {
            const sead::SafeString& name = drop->getRandomDropFromTable("Normal");
            if (!name.isEmpty()) {
                ksys::act::ActorCreator::instance()->requestCreateActor(
                    name.getStringTop(), ksys::act::ActorHeapUtil::instance()->getBaseProcHeap(), &_50,
                    &pack, nullptr, 2);
            }
        }
    }
}

// NON_MATCHING: register allocation of the landing position math, the branch layout of the "moved" test, and the
// load order of the player / actor positions in the distance check.
void ShootingStarBrightTower::calc_() {
    if (isFinished() || isFailed())
        return;
    mActor->getMainBody()->setGravityFactor(0.0f);
    mActor->getMainBody()->setPosition(_60, ksys::phys::PropagateToLinkedMotions{true});
    ksys::phys::RayCastBodyQuery query(nullptr, ksys::phys::GroundHit::HitAll);
    query.enableLayer(ksys::phys::ContactLayer::EntityGround);
    query.enableLayer(ksys::phys::ContactLayer::EntityGroundObject);
    query.enableLayer(ksys::phys::ContactLayer::EntityGroundRough);
    query.enableLayer(ksys::phys::ContactLayer::EntityGroundSmooth);
    query.enableLayer(ksys::phys::ContactLayer::EntityHitOnlyGround);
    const sead::Vector3f start = _60 - _9c * (_a8 * 0.5f);
    query.setStartAndDisplacementScaled(start, _9c, _a8);
    query.setNormalCheckingMode(ksys::phys::RayCast::NormalCheckingMode::_0);
    if (query.worldRayCast(ksys::phys::ContactLayerType::Entity)) {
        sead::Vector3f hit_pos;
        sead::Vector3f hit_normal;
        query.getHitPosition(&hit_pos);
        query.getHitNormal(&hit_normal);
        hit_pos = hit_pos - _9c * 0.25f + hit_normal * 0.25f;
        const bool moved = _6c.m[0][3] != hit_pos.x || _6c.m[1][3] != hit_pos.y ||
                           _6c.m[2][3] != hit_pos.z;
        _6c.setTranslation(hit_pos);
        if (moved)
            _30.sub_7101241A44(_6c);
        _ac = 0;
    } else {
        _a8 += 0.5f;
        ksys::Timer::update(&_ac, 1.0f);
    }
    if (_50.isAllocatedOrFailed()) {
        if (_50.isProcReady()) {
            _50.releaseAndWakeProc();
            setFinished();
        }
    } else {
        const sead::Vector3f& player_pos = getPlayerPosition();
        const f32 dx = player_pos.x - mActor->getMtx().m[0][3];
        const f32 dz = player_pos.z - mActor->getMtx().m[2][3];
        if (dx * dx + dz * dz < *mDisappearDistance_s * *mDisappearDistance_s) {
            const sead::Vector3f pos{_6c.m[0][3], _6c.m[1][3], _6c.m[2][3]};
            shootingStarDropStuff(pos);
            if (auto* world = ksys::world::Manager::instance()) {
                if (auto* star = world->getShootingStarMgr())
                    star->resetStarPosition();
            }
        } else if (auto* world = ksys::world::Manager::instance()) {
            auto* star = world->getShootingStarMgr();
            if ((star && star->isScheduledTime()) || _ac > 90.0f) {
                if (auto* world2 = ksys::world::Manager::instance()) {
                    if (auto* star2 = world2->getShootingStarMgr())
                        star2->resetStarPosition();
                }
                setFailed();
            }
        }
    }
}

}  // namespace uking::action
