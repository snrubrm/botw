#include "Game/AI/AI/aiSimpleShootingEnemyFindPlayer.h"
#include "Game/AI/aiUnk_71007320F0.h"
#include "Game/AI/aiUnk_71005D6D10.h"
#include "Game/AI/aiUnk_71007377D4.h"
#include "Game/Actor/actEnemy.h"
#include "KingSystem/ActorSystem/Awareness/actAwarenessInstance.h"
#include "KingSystem/ActorSystem/Profiles/actDynamicActor.h"
#include "KingSystem/ActorSystem/actActor.h"
#include "KingSystem/Physics/System/physRayCastBodyQuery.h"

namespace uking::ai {

SimpleShootingEnemyFindPlayer::SimpleShootingEnemyFindPlayer(const InitArg& arg)
    : EnemyBaseFindPlayer(arg) {}

SimpleShootingEnemyFindPlayer::~SimpleShootingEnemyFindPlayer() = default;

bool SimpleShootingEnemyFindPlayer::init_(sead::Heap* heap) {
    return EnemyBaseFindPlayer::init_(heap);
}

void SimpleShootingEnemyFindPlayer::enter_(ksys::act::ai::InlineParamPack* params) {
    EnemyBaseFindPlayer::enter_(params);
}

void SimpleShootingEnemyFindPlayer::calc_() {
    EnemyBaseFindPlayer::calc_();
}

void SimpleShootingEnemyFindPlayer::leave_() {
    EnemyBaseFindPlayer::leave_();
}

void SimpleShootingEnemyFindPlayer::loadParams_() {
    EnemyBaseFindPlayer::loadParams_();
    getStaticParam(&mShootBaseDist_s, "ShootBaseDist");
    getStaticParam(&mShootDistRatio_s, "ShootDistRatio");
}

f32 SimpleShootingEnemyFindPlayer::m34() {
    return *mShootBaseDist_s + sub_71007320F0(mActor, *mWeaponIdx_s) * *mShootDistRatio_s;
}

bool SimpleShootingEnemyFindPlayer::m35() {
    auto* actor = mActor;
    if (!actor)
        return false;
    const auto& target = sub_71005D9330(actor);
    const f32 max_dist = m34();
    if (!inlineIsTargetInReach(target, max_dist, *mAttackVMin_s, *mAttackVMax_s, actor->getMtx(),
                               sead::Mathf::pi(), sead::Mathf::maxNumber(), 0.8f)) {
        return false;
    }
    auto* enemy = sead::DynamicCast<act::Enemy>(mActor);
    return enemy && (enemy->_c48._7c == 2 || enemy->_c48._7c == 5);
}

bool SimpleShootingEnemyFindPlayer::m36(bool b) {
    auto* actor = mActor;
    if (!actor)
        return false;
    sead::Vector3f pos;
    actor->getMtx().getTranslation(pos);
    if (sub_710072F788(actor, pos, sub_71005D9330(actor), nullptr))
        return true;
    return m35();
}

// NON_MATCHING: same instructions and registers (`(x | 1) != 3`, `x != 5`, and), but the original computes the `x != 5`
// flag first; ours schedules the `(x | 1)` compare first (the base class tests `(x & ~1) != 2`)
bool SimpleShootingEnemyFindPlayer::m42(s32 x) {
    return (x | 1) != 3 && x != 5;
}

bool SimpleShootingEnemyFindPlayer::m43() {
    const s32 state = sub_71005D9744(mActor);
    if (!EnemyBaseFindPlayer::m43())
        return false;
    return m42(state);
}

// 0x710056fb20
bool SimpleShootingEnemyFindPlayer::m37() {
    auto* actor = mActor;
    if (!actor)
        return false;
    sead::Vector3f pos;
    actor->getMtx().getTranslation(pos);
    const sead::Vector3f& target = sub_71005D98D8(actor);
    const f32 dx = target.x - pos.x;
    const f32 dz = target.z - pos.z;
    if (!(std::sqrt(dx * dx + dz * dz) >= m34())) {
        if (sub_710072F788(actor, pos, target, nullptr))
            return true;
        return sub_710056FC10(target);
    }
    return false;
}

// 0x710056fc10
bool SimpleShootingEnemyFindPlayer::sub_710056FC10(const sead::Vector3f& target) {
    auto* actor = sead::DynamicCast<ksys::act::DynamicActor>(mActor);
    if (!actor)
        return false;
    const auto& awareness_pos = actor->getAwareness()->_2c8;
    sead::Vector3f start;
    start.x = awareness_pos.x;
    start.y = awareness_pos.y;
    start.z = awareness_pos.z;
    const sead::Vector3f end = target;
    ksys::phys::RayCastBodyQuery query(sub_710072E804(mActor, 0), ksys::phys::GroundHit::HitAll);
    query.enableLayer(ksys::phys::ContactLayer::EntityGround);
    query.enableLayer(ksys::phys::ContactLayer::EntityGroundRough);
    query.enableLayer(ksys::phys::ContactLayer::EntityGroundObject);
    query.enableLayer(ksys::phys::ContactLayer::EntityGroundSmooth);
    query.enableLayer(ksys::phys::ContactLayer::EntityObject);
    query.enableLayer(ksys::phys::ContactLayer::EntityTree);
    query.setStartAndEnd(start, end);
    query.setNormalCheckingMode(ksys::phys::RayCast::NormalCheckingMode::_0);
    if (auto* link = sub_71005D9050(actor))
        query.addIgnoredGroup(sub_7100738C18(link, 0));
    return !query.worldRayCast(ksys::phys::ContactLayerType::Entity);
}

}  // namespace uking::ai
