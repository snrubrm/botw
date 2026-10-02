#include "Game/AI/AI/aiSwimEnemyNormal.h"
#include "Game/AI/aiUnk_71005D6D10.h"
#include "KingSystem/ActorSystem/actActor.h"
#include "KingSystem/ActorSystem/actActorUtil.h"
#include "KingSystem/Physics/CharacterController/physCharacterController.h"
#include "KingSystem/Physics/System/physInstanceSet.h"
#include "KingSystem/Physics/System/physRayCastBodyQuery.h"

namespace uking::ai {

SwimEnemyNormal::SwimEnemyNormal(const InitArg& arg) : EnemyNormal(arg) {}

SwimEnemyNormal::~SwimEnemyNormal() = default;

void SwimEnemyNormal::enter_(ksys::act::ai::InlineParamPack* params) {
    EnemyNormal::enter_(params);
    if (!sub_71005B4E0C())
        return;
    auto* controller = mActor->getCharacterController();
    if (!controller)
        return;
    auto* physics = mActor->getPhysics();
    if (!physics)
        return;
    const s32 idx = physics->sub_7100FBE7F0("Swimming");
    if (idx < 0)
        return;
    controller->sub_7100F5F270(idx);
    _3d0 = 1;
}

void SwimEnemyNormal::leave_() {
    EnemyNormal::leave_();
    auto* controller = mActor->getCharacterController();
    if (!controller)
        return;
    auto* physics = mActor->getPhysics();
    if (!physics)
        return;
    const s32 idx = physics->sub_7100FBE7F0("Standing");
    if (idx < 0)
        return;
    controller->sub_7100F5F270(idx);
    _3d0 = 0;
}

void SwimEnemyNormal::loadParams_() {
    EnemyNormal::loadParams_();
}

void SwimEnemyNormal::calc_() {
    EnemyNormal::calc_();
    sub_71005B488C();
}

void SwimEnemyNormal::sub_71005B488C() {
    switch (_3d0) {
    case 0: {
        if (!mActor->get68f())
            return;
        if (!sub_71005B4E0C())
            return;
        auto* controller = mActor->getCharacterController();
        if (!controller)
            return;
        auto* physics = mActor->getPhysics();
        if (!physics)
            return;
        const s32 idx = physics->sub_7100FBE7F0("Swimming");
        if (idx < 0)
            return;
        controller->sub_7100F5F270(idx);
        _3d0 = 1;
        break;
    }
    case 1: {
        if (mActor->get68f())
            return;
        auto* controller = mActor->getCharacterController();
        if (!controller)
            return;
        auto* physics = mActor->getPhysics();
        if (!physics)
            return;
        const s32 idx = physics->sub_7100FBE7F0("Standing");
        if (idx < 0)
            return;
        controller->sub_7100F5F270(idx);
        _3d0 = 0;
        break;
    }
    }
}

// NON_MATCHING: scheduling of the start/end computation (the original stores all six components after
// computing them, in pairs)
bool SwimEnemyNormal::sub_71005B4E0C() {
    if (!mActor)
        return false;

    const auto& mtx = mActor->getMtx();
    const sead::Vector3f pos = mtx.getTranslation();
    const sead::Vector3f front = mtx.getBase(2);
    sead::Vector3f start = pos - front * 1.5f;
    start.y += 2.0f;
    sead::Vector3f end = front * 3.5f + pos;
    end.y += 2.0f;

    ksys::phys::RayCastBodyQuery query(nullptr, ksys::phys::GroundHit::HitAll);
    query.setStartAndEnd(start, end);
    query.enableLayer(ksys::phys::ContactLayer::EntityGround);
    query.enableLayer(ksys::phys::ContactLayer::EntityGroundRough);
    query.enableLayer(ksys::phys::ContactLayer::EntityGroundObject);
    query.enableLayer(ksys::phys::ContactLayer::EntityTree);
    return !query.worldRayCast(ksys::phys::ContactLayerType::Entity);
}

s32 SwimEnemyNormal::m52(s32 idx) {
    static const s32 sTable[] = {0, 2, 4, 8};
    return sTable[idx];
}

bool SwimEnemyNormal::m70() {
    sead::Vector3f pos;
    m48(&pos);
    if ((pos - mActor->getMtx().getTranslation()).length() > 5.0f)
        return true;
    return EnemyNormal::m70();
}

void SwimEnemyNormal::m49(Unk1* out, s32 idx) {
    const s32 value = m52(idx);
    if (isCurrentChild("待機") || isCurrentChild("諦め"))
        out->_0 = value;
    else if (isCurrentChild("音気づき"))
        out->_0 = value == 2 ? -1 : value;
    else if (isCurrentChild("攻撃反応"))
        out->_0 = value != 0 ? -1 : 0;
    else
        EnemyNormal::m49(out, idx);
}

void SwimEnemyNormal::m50(Unk1* out, s32 idx) {
    if (isCurrentChild("攻撃反応") || isCurrentChild("見失い") || isCurrentChild("諦め"))
        out->_0 = -1;
    else
        EnemyNormal::m49(out, idx);
}

void SwimEnemyNormal::m60(Unk3* out) {
    if (isCurrentChild("攻撃反応") || isCurrentChild("見失い"))
        out->_0 = 1;
    else if (isCurrentChild("プレイヤー発見") || isCurrentChild("音気づき"))
        EnemyNormal::m60(out);
    else
        out->_0 = -1;
}

void SwimEnemyNormal::m61(Unk3* out) {
    if ((isCurrentChild("プレイヤー発見") || isCurrentChild("不審者発見")) &&
        sub_710039DB34(true)) {
        if (auto* link = sub_71005D9050(mActor)) {
            if (ksys::act::isPlayerProfile(link))
                out->_4 |= 2;
        }
        out->_0 = 1;
    } else {
        EnemyNormal::m61(out);
    }
}

s32 SwimEnemyNormal::m53() {
    return 4;
}

}  // namespace uking::ai
