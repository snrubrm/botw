#include "Game/AI/AI/aiFlyingEnemyFindPlayer.h"
#include "Game/AI/aiUnk_71005D6D10.h"
#include "Game/AI/aiUnk_71007320F0.h"
#include "Game/AI/aiUnk_71007377D4.h"
#include "KingSystem/ActorSystem/actActor.h"
#include "KingSystem/ActorSystem/Profiles/actDynamicActor.h"
#include "KingSystem/ActorSystem/actActorConstDataAccess.h"
#include "KingSystem/Physics/System/physRayCastBodyQuery.h"

namespace uking::ai {

FlyingEnemyFindPlayer::FlyingEnemyFindPlayer(const InitArg& arg) : EnemyBaseFindPlayer(arg) {}

FlyingEnemyFindPlayer::~FlyingEnemyFindPlayer() = default;

bool FlyingEnemyFindPlayer::init_(sead::Heap* heap) {
    return EnemyBaseFindPlayer::init_(heap);
}

void FlyingEnemyFindPlayer::enter_(ksys::act::ai::InlineParamPack* params) {
    EnemyBaseFindPlayer::enter_(params);
}

void FlyingEnemyFindPlayer::calc_() {
    EnemyBaseFindPlayer::calc_();
}

void FlyingEnemyFindPlayer::leave_() {
    EnemyBaseFindPlayer::leave_();
}

void FlyingEnemyFindPlayer::loadParams_() {
    EnemyBaseFindPlayer::loadParams_();
}

bool FlyingEnemyFindPlayer::sub_71003D2E30(const sead::Vector3f& pos) {
    auto* actor = mActor;
    if (!sead::IsDerivedFrom<ksys::act::DynamicActor>(actor))
        return false;
    auto* target = sub_71005D9050(actor);
    if (!target)
        return false;

    sead::Vector3f start;
    actor->getMtx().getTranslation(start);
    start.y += 0.1f;
    const sead::Vector3f end = pos;

    ksys::phys::RayCastBodyQuery query(sub_710072E804(actor, 0), ksys::phys::GroundHit::HitAll);
    ksys::act::ActorConstDataAccess accessor;
    ksys::act::acquireActor(target, &accessor);
    if (auto* handler = sub_7100738C18(target, 0))
        query.addIgnoredGroup(handler);
    query.enableLayer(ksys::phys::ContactLayer::EntityGround);
    query.enableLayer(ksys::phys::ContactLayer::EntityGroundRough);
    query.enableLayer(ksys::phys::ContactLayer::EntityGroundObject);
    query.enableLayer(ksys::phys::ContactLayer::EntityGroundSmooth);
    query.enableLayer(ksys::phys::ContactLayer::EntityObject);
    query.enableLayer(ksys::phys::ContactLayer::EntityTree);
    query.setStartAndEnd(start, end);
    query.setNormalCheckingMode(ksys::phys::RayCast::NormalCheckingMode::_0);
    return !query.worldRayCast(ksys::phys::ContactLayerType::Entity);
}

bool FlyingEnemyFindPlayer::m35() {
    auto* actor = mActor;
    if (!actor)
        return false;
    const auto& target = sub_71005D9330(actor);
    const f32 max_dist = *mAttackRange_s + sub_71007320F0(actor, *mWeaponIdx_s);
    if (!inlineIsTargetInReach(target, max_dist, *mAttackVMin_s, *mAttackVMax_s, actor->getMtx(),
                               sead::Mathf::pi(), 0.8f, 1.2f)) {
        return false;
    }
    return sub_71003D2E30(sub_71005D960C(mActor));
}

bool FlyingEnemyFindPlayer::m36(bool b) {
    return sub_71003D2E30(sub_71005D960C(mActor));
}

bool FlyingEnemyFindPlayer::m37() {
    sead::Vector3f pos = sub_71005D98D8(mActor);
    pos.y += 0.8f;
    return sub_71003D2E30(pos);
}

}  // namespace uking::ai
