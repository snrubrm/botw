#include "Game/AI/aiUnk_7100724C64.h"
#include <gsys/gsysModel.h>
#include <gsys/gsysModelUnit.h>
#include "Game/AI/AI/aiStalEnemyRoot.h"
#include "Game/Actor/actEnemy.h"
#include "KingSystem/ActorSystem/actActorUtil.h"
#include "KingSystem/ActorSystem/actAiRoot.h"
#include "KingSystem/ActorSystem/actTag.h"
#include "KingSystem/Physics/Ragdoll/physRagdollInstance.h"
#include "KingSystem/Physics/Ragdoll/physRagdollRigidBody.h"
#include "KingSystem/Physics/System/physInstanceSet.h"

// 0x71024511f8
static const char* const sUnk_71024511f8[] = {
    "StalHead", "StalLeftArm", "StalChin", "StalRib1", "StalRib2", "StalRib3", "StalRib4",
};

bool sub_7100724C80(ksys::act::Actor* actor, sead::Heap* heap, u32 part) {
    auto* enemy = sub_7100724D7C(actor);
    if (!enemy)
        return false;
    enemy->sub_7100D3CED8(sUnk_71024511f8[part], heap);
    return true;
}

uking::act::Enemy* sub_7100724D7C(ksys::act::Actor* actor) {
    if (actor) {
        auto* enemy = sead::DynamicCast<uking::act::Enemy>(actor);
        if (ksys::act::hasTag(enemy, ksys::act::tags::StalfosParts))
            return enemy;
    }
    return nullptr;
}

bool sub_7100724E1C(ksys::act::Actor* actor, u32 part) {
    auto* enemy = sub_7100724D7C(actor);
    if (!enemy)
        return false;
    enemy->sub_7100D3CFEC(sUnk_71024511f8[part]);
    return true;
}

ksys::act::BaseProcLink& sub_7100724F08(ksys::act::Actor* actor, u32 part) {
    auto* enemy = sub_7100724D7C(actor);
    if (!enemy)
        return ksys::act::getDummyBaseProcLink();
    return enemy->getActorPartsActor(sUnk_71024511f8[part]);
}

bool sub_7100724FE8(ksys::act::Actor* actor, ksys::act::BaseProc* proc, u32 part) {
    auto* enemy = sub_7100724D7C(actor);
    if (!enemy)
        return false;
    return enemy->sub_7100D3D108(sUnk_71024511f8[part], proc);
}

bool sub_71007250E4(ksys::act::Actor* actor, u32 part) {
    auto* enemy = sub_7100724D7C(actor);
    if (!enemy)
        return false;
    return enemy->sub_7100D3D2B4(sUnk_71024511f8[part]);
}

const char* sub_71007251D0() {
    return sUnk_71024511f8[0];
}

const char* sub_71007251DC() {
    return sUnk_71024511f8[1];
}

bool sub_71007251E8(ksys::act::Actor* actor, sead::Heap* heap) {
    return sub_7100724C80(actor, heap, 0);
}

bool sub_71007252D4(ksys::act::Actor* actor, sead::Heap* heap) {
    return sub_7100724C80(actor, heap, 1);
}

bool sub_71007253C0(ksys::act::Actor* actor) {
    return sub_7100724E1C(actor, 0);
}

bool sub_71007254A4(ksys::act::Actor* actor) {
    return sub_7100724E1C(actor, 1);
}

ksys::act::BaseProcLink& sub_7100725588(ksys::act::Actor* actor) {
    return sub_7100724F08(actor, 0);
}

ksys::act::BaseProcLink& sub_71007255A0(ksys::act::Actor* actor) {
    return sub_7100724F08(actor, 1);
}

bool sub_71007255B8(ksys::act::Actor* actor, ksys::act::BaseProc* proc) {
    return sub_7100724FE8(actor, proc, 0);
}

bool sub_71007256A4(ksys::act::Actor* actor, ksys::act::BaseProc* proc) {
    return sub_7100724FE8(actor, proc, 1);
}

bool sub_7100725790(ksys::act::Actor* actor, const ksys::act::BaseProcLink& link) {
    auto* enemy = sub_7100724D7C(actor);
    if (!enemy)
        return false;
    return enemy->sub_7100D3D1E0(sUnk_71024511f8[0], link);
}

bool sub_710072587C(ksys::act::Actor* actor) {
    return sub_71007250E4(actor, 0);
}

bool sub_7100725960(ksys::act::Actor* actor, const sead::SafeString& material, bool visible) {
    auto* unit = actor->getModel()->getUnits().unsafeAt(0)->mModelUnit;
    if (!unit)
        return false;
    const int index = unit->searchMaterialIndex(material);
    if (index < 0)
        return false;
    unit->setMaterialVisible(index, visible);
    return true;
}

bool sub_71007259CC(ksys::act::Actor* actor, const sead::SafeString& material, bool visible) {
    auto* unit = actor->getModel()->getUnits().unsafeAt(0)->mModelUnit;
    if (!unit)
        return false;
    sead::FixedSafeString<64> name;
    name.format("%s_Seal", material.cstr());
    const int index = unit->searchMaterialIndex(name);
    if (index < 0)
        return false;
    unit->setMaterialVisible(index, visible);
    return true;
}

bool sub_7100726004(ksys::act::Actor* actor, u32 part) {
    auto* enemy = sub_7100724D7C(actor);
    if (!enemy)
        return true;
    return enemy->getActorPartsActor(sUnk_71024511f8[part]).hasProc();
}

// 0x71007260f4
void sub_71007260F4(ksys::act::Actor* actor, bool clear) {
    auto* physics = actor->getPhysics();
    if (!physics)
        return;
    auto* ragdoll = physics->getRagdollInstance();
    if (!ragdoll)
        return;
    auto& bodies = ragdoll->getRigidBodies_();
    const s32 count = bodies.size();
    for (s32 i = 0; i < count; ++i) {
        if (auto* body = bodies[i]) {
            if (clear)
                body->resetFlag1000000();
            else
                body->setFlag1000000();
        }
    }
}

bool sub_7100726620(ksys::act::Actor* actor) {
    return sub_7100726004(actor, 0);
}

uking::ai::Unk_71024241a8* sub_7100726628(ksys::act::Actor* actor) {
    void* unit = nullptr;
    actor->getRootAi()->getAITreeVariable(&unit, "StalEnemyUnit");
    return sead::DynamicCast<uking::ai::Unk_71024241a8>(
        *static_cast<Unk_71025afb58**>(unit));
}

uking::ai::Unk_71024241a8* sub_7100726FF4(ksys::act::Actor* actor) {
    void* unit = nullptr;
    actor->getRootAi()->getAITreeVariable(&unit, "StalEnemyUnit");
    return sead::DynamicCast<uking::ai::Unk_71024241a8>(
        *static_cast<Unk_71025afb58**>(unit));
}

bool sub_7100726E54(ksys::act::Actor* actor) {
    auto* enemy = sub_7100724D7C(actor);
    if (!enemy || ksys::act::hasTag(enemy, ksys::act::tags::TeamMoriblin))
        return true;
    return sub_7100726004(enemy, 1);
}

bool sub_7100726F20(ksys::act::Actor* actor) {
    return sub_7100726004(actor, 1);
}

bool sub_7100726F28(ksys::act::Actor* actor) {
    auto* enemy = sub_7100724D7C(actor);
    if (!enemy || !ksys::act::hasTag(enemy, ksys::act::tags::TeamBokoblin))
        return true;
    return sub_7100726004(enemy, 1);
}

bool sub_71007271D4(ksys::act::Actor* actor) {
    void* unit = nullptr;
    actor->getRootAi()->getAITreeVariable(&unit, "StalEnemyUnit");
    auto* stal_unit =
        sead::DynamicCast<uking::ai::Unk_71024241a8>(*static_cast<Unk_71025afb58**>(unit));
    if (!stal_unit)
        return false;
    return stal_unit->_8.isOnBit(1);
}

bool sub_7100728640(ksys::act::Actor* actor) {
    auto* unit = sub_7100726628(actor);
    if (unit && unit->_8.isOnBit(1)) {
        if (auto* enemy = sub_7100724D7C(actor)) {
            if (enemy->getActorPartsActor(sUnk_71024511f8[1]).hasProc() ||
                enemy->getActorPartsActor(sUnk_71024511f8[2]).hasProc() ||
                enemy->getActorPartsActor(sUnk_71024511f8[3]).hasProc() ||
                enemy->getActorPartsActor(sUnk_71024511f8[4]).hasProc() ||
                enemy->getActorPartsActor(sUnk_71024511f8[5]).hasProc() ||
                enemy->getActorPartsActor(sUnk_71024511f8[6]).hasProc()) {
                return true;
            }
        }
    }
    return false;
}
