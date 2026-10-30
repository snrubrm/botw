#include "Game/Actor/aiUnk_7100724C64.h"
#include <gsys/gsysModel.h>
#include <gsys/gsysModelUnit.h>
#include "Game/Actor/AI/aiStalEnemyRoot.h"
#include "Game/Actor/aiUnk_71005D6D10.h"
#include "Game/Actor/actEnemy.h"
#include "Game/Actor/Damage/dmgDamageManager.h"
#include "Game/Actor/Damage/dmgInfoManager.h"
#include "Game/Actor/aiUnk_71007377D4.h"
#include "Game/Actor/aiUnk_710072BA90.h"
#include "KingSystem/ActorSystem/Awareness/actAwarenessInstance.h"
#include "KingSystem/ActorSystem/actActorUtil.h"
#include "KingSystem/ActorSystem/actActorSensorUtil.h"
#include "KingSystem/ActorSystem/actActorLinkConstDataAccess.h"
#include "KingSystem/ActorSystem/aiRootAi.h"
#include "KingSystem/ActorSystem/actTag.h"
#include "KingSystem/Physics/CharacterController/physCharacterController.h"
#include "KingSystem/Physics/Ragdoll/physRagdollInstance.h"
#include "KingSystem/Physics/Ragdoll/physRagdollRigidBody.h"
#include "KingSystem/Physics/System/physInstanceSet.h"
#include "KingSystem/XLink/xlinkXLink.h"

Unk_71024511a8::Unk_71024511a8() = default;

// The original retains the derived vtable store during member teardown, as in upstream's
// GameDataFlagSelector::~GameDataFlagSelector() (96101229).
// NON_MATCHING: the original inlines the base destructor's list removal.
Unk_71024511a8::~Unk_71024511a8() { ; }

bool Unk_71024511a8::sub_7100724938(ksys::act::Actor* actor, const sead::SafeString& target,
                                 const sead::SafeString& source) {
    if (mOwner)
        return false;
    _20 = target;
    _30.getKey().reset();
    _68 = source;
    _78.getKey().reset();
    auto* model = actor->getModel();
    _30.search(model, _20);
    if (!_30.isValid())
        return false;
    _78.search(model, _68);
    return _78.isValid();
}

// NON_MATCHING: one target-key field uses the object register instead of the key register.
void Unk_71024511a8::call(ksys::act::Actor* actor) {
    const auto& target = _30.getKey();
    const auto& source = _78.getKey();
    if (!target.isValid() || !source.isValid())
        return;
    auto* model = actor->getModel();
    if (!model)
        return;
    sead::Matrix34f matrix = sead::Matrix34f::ident;
    model->getUnits().unsafeAt(source.model_unit_index)->mModelUnit->getBoneWorldMatrix(
        &matrix, source.bone_index);
    model->setBoneWorldMatrix(target, matrix);
}

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

void sub_7100725AC4(ksys::act::Actor* actor, u32 part, const sead::SafeString& names) {
    if (names.isEmpty())
        return;
    sub_7100725B20(actor, names, sub_7100726004(actor, part));
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

// NON_MATCHING: the compiler shares the part-link lookup among the switch cases.
void sub_7100727AA0(ksys::act::Actor* actor, u32 part) {
    auto* enemy = sub_7100724D7C(actor);
    if (!enemy)
        return;
    auto* unit = sub_7100726FF4(enemy);
    if (!unit || !unit->_8.isOnBit(1))
        return;
    const char* part_name;
    const char* body_name;
    switch (part) {
    case 1:
        part_name = "StalLeftArm";
        body_name = "ArmL";
        break;
    case 3:
        part_name = "StalRib1";
        body_name = "Rib1";
        break;
    case 4:
        part_name = "StalRib2";
        body_name = "Rib2";
        break;
    case 5:
        part_name = "StalRib3";
        body_name = "Rib3";
        break;
    default:
        return;
    }
    sub_7100727CFC(enemy, body_name, enemy->getActorPartsActor(part_name).hasProc());
}

uking::ai::Unk_71024241a8* sub_7100726628(ksys::act::Actor* actor) {
    void* unit = nullptr;
    actor->getRootAi()->getAITreeVariable(&unit, "StalEnemyUnit");
    return sead::DynamicCast<uking::ai::Unk_71024241a8>(
        static_cast<Unk_71025afb58*>(*static_cast<void**>(unit)));
}

uking::ai::Unk_71024241a8* sub_7100726FF4(ksys::act::Actor* actor) {
    void* unit = nullptr;
    actor->getRootAi()->getAITreeVariable(&unit, "StalEnemyUnit");
    return sead::DynamicCast<uking::ai::Unk_71024241a8>(
        static_cast<Unk_71025afb58*>(*static_cast<void**>(unit)));
}

// NON_MATCHING: floating-point register allocation and operation scheduling differ.
bool sub_7100726C64(ksys::act::Actor* actor, const ksys::act::BaseProcLink* link) {
    ksys::act::ActorLinkConstDataAccess accessor;
    ksys::act::acquireActor(link, &accessor);
    if (!accessor.isStateCalc() || accessor.getLife() == 0)
        return false;

    auto* unit = sub_7100726FF4(actor);
    const f32 range = unit ? unit->_c : 80.0f;
    const f32 home_range = unit ? unit->_10 : 160.0f;
    const f32 height = unit ? unit->_14 : 60.0f;
    const auto pos = actor->getMtx().getTranslation();
    const auto target = accessor.getActorMtx().getTranslation();
    sead::Vector3f home;
    actor->getHomePos(&home);
    if (!(sead::Mathf::abs(target.y - pos.y) <= height))
        return false;
    const f32 dx = target.x - pos.x;
    const f32 dz = target.z - pos.z;
    if (!(dx * dx + dz * dz <= range * range))
        return false;
    const f32 home_dx = target.x - home.x;
    const f32 home_dz = target.z - home.z;
    return home_dx * home_dx + home_dz * home_dz <= home_range * home_range;
}

// NON_MATCHING: stack slots for the part name and AI tree variable are swapped.
void sub_71007270BC(uking::act::Enemy* enemy) {
    if (!enemy)
        return;
    if (enemy->getActorPartsActor("StalLeftArm").hasProc()) {
        enemy->sub_710001692C();
        return;
    }
    enemy->_f54.reset(0x18);
    void* unit = nullptr;
    enemy->getRootAi()->getAITreeVariable(&unit, "StalEnemyUnit");
    auto* stal_unit =
        sead::DynamicCast<uking::ai::Unk_71024241a8>(static_cast<Unk_71025afb58*>(*static_cast<void**>(unit)));
    if (stal_unit && stal_unit->_8.isOnBit(1))
        enemy->_f54.resetBit(2);
}

void sub_71007272A0(ksys::act::Actor* actor) {
    const bool has_head = sub_7100726004(actor, 0);
    auto* manager = actor->getDamageMgr();
    if (sead::IsDerivedFrom<uking::act::DamageManager>(manager))
        static_cast<uking::act::DamageManager*>(manager)->_216.change(8, has_head);
}

void sub_710072735C(ksys::act::Actor* actor, bool update, bool update_damage) {
    auto* enemy = sub_7100724D7C(actor);
    if (!enemy)
        return;
    if (update)
        sub_71007275C8(enemy);
    sub_71007270BC(enemy);
    const bool has_head = enemy->getActorPartsActor("StalHead").hasProc();
    if (update_damage) {
        auto* manager = sead::DynamicCast<uking::act::DamageManager>(actor->getDamageMgr());
        if (manager)
            manager->_216.change(8, has_head);
    }
    auto* unit = sub_7100726FF4(enemy);
    if (!unit || !unit->_8.isOnBit(1)) {
        if (auto* body = actor->findPhysicsBodyByName(sub_71007A24D0()->cstr(), "TgtHead")) {
            if (has_head)
                body->addToWorld();
            else
                body->removeFromWorld();
        }
    }
}

// NON_MATCHING: the compiler schedules material and slot temporaries differently.
void sub_71007275C8(uking::act::Enemy* enemy) {
    if (!enemy)
        return;
    auto* unit = sub_7100726FF4(enemy);
    const bool extended_parts = unit && unit->_8.isOnBit(1);
    auto& head = enemy->getActorPartsActor("StalHead");
    if (!extended_parts) {
        sub_7100725960(enemy, "Mt_Head", head.hasProc());
        if (auto* xlink = enemy->getXLink())
            xlink->_cc.changeBit(25, !head.hasProc());
    }
    sub_7100725960(enemy, "Mt_Eye", head.hasProc());
    sub_7100725960(enemy, "Mt_Arm_L", enemy->getActorPartsActor("StalLeftArm").hasProc());
    if (extended_parts) {
        sub_7100725960(enemy, "Mt_Chin", enemy->getActorPartsActor("StalChin").hasProc());
        sub_7100725960(enemy, "Mt_Rib_1", enemy->getActorPartsActor("StalRib1").hasProc());
        sub_7100725960(enemy, "Mt_Rib_2", enemy->getActorPartsActor("StalRib2").hasProc());
        sub_7100725960(enemy, "Mt_Rib_3", enemy->getActorPartsActor("StalRib3").hasProc());
        sub_7100725960(enemy, "Mt_Rib_4", enemy->getActorPartsActor("StalRib4").hasProc());
    }
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
        sead::DynamicCast<uking::ai::Unk_71024241a8>(static_cast<Unk_71025afb58*>(*static_cast<void**>(unit)));
    if (!stal_unit)
        return false;
    return stal_unit->_8.isOnBit(1);
}

// NON_MATCHING: the zero integer argument is materialized with a 32-bit register.
void sub_7100728B38(ksys::act::Actor* actor) {
    if (sub_71007271D4(actor))
        uking::act::DamageInfoMgr::instance()->get450().sub_710065D674(actor, 1, true, true, 0);
    sub_710073DE08(actor);
    if (auto* awareness = actor->get548())
        awareness->_18._50 = true;
}

bool sub_7100728C40(ksys::act::Actor* actor, const sead::Vector3f& velocity) {
    if (!sub_71007271D4(actor))
        return sub_71005D8748(actor, velocity, false, false, nullptr, false);

    sead::Matrix34f matrix = actor->getMtx();
    if (auto* controller = actor->getCharacterController())
        controller->physicsXXXGetMtx_1(&matrix);
    sead::Vector3f target;
    target.setMul(matrix, sead::Vector3f::ey);
    return sub_71005D88AC(actor, target, velocity, false, false, nullptr, false);
}

bool sub_7100728E00(ksys::act::Actor* actor, const sead::Vector3f& velocity) {
    if (sub_71007271D4(actor))
        return playerOrEnemyDropWeapon(actor, &velocity, 0, false, false, nullptr, false);
    return sub_71005D8748(actor, velocity, false, false, nullptr, false);
}

void sub_71007282F8(ksys::act::Actor* actor,
                    const uking::action::GolemDieFromRagdoll::RagdollBody& body) {
    auto* ragdoll = actor->getRagdollInstance();
    if (!ragdoll)
        return;
    const int bone = ragdoll->getBoneIndexByName(body.mRagdollBodyName_s);
    if (bone < 0)
        return;
    auto* unit = actor->getModel()->getUnits().unsafeAt(0)->mModelUnit;
    if (unit) {
        const int material = unit->searchMaterialIndex(body.mMaterialName_s);
        if (material >= 0 && unit->isMaterialVisible(material)) {
            ragdoll->setContactNone(bone);
            return;
        }
    }
    ragdoll->setContactAll(bone);
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
