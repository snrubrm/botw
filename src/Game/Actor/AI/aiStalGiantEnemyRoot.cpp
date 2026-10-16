#include "Game/Actor/AI/aiStalGiantEnemyRoot.h"
#include <prim/seadFormatPrint.h>
#include <prim/seadFormatPrint.h>
#include "KingSystem/ActorSystem/actActorLinkConstDataAccess.h"
#include "Game/Actor/aiUnk_7100724C64.h"
#include "Game/Actor/aiUnk_71005D6D10.h"
#include "Game/Actor/aiUnk_7102451120.h"
#include "KingSystem/ActorSystem/actActorSensorUtil.h"
#include "KingSystem/ActorSystem/actAttackSensor.h"
#include "KingSystem/ActorSystem/actActorUtil.h"
#include "KingSystem/Physics/RigidBody/physRigidBody.h"
#include "KingSystem/Physics/RigidBody/physRigidBodySet.h"
#include "KingSystem/Terrain/teraSystem.h"
#include "KingSystem/Physics/CharacterController/physCharacterController.h"
#include "Game/Actor/actEnemy.h"
#include "Game/Actor/actGiantEnemy.h"
#include "Game/Actor/Damage/dmgDamageManagerBase.h"
#include "KingSystem/ActorSystem/actChemical.h"
#include "KingSystem/ActorSystem/actAiInlineParam.h"

namespace uking::ai {

// NON_MATCHING: the second contact callback stores its vtable before the infinity value;
// the original initializes that value before storing the callback vtable.
StalGiantEnemyRoot::StalGiantEnemyRoot(const InitArg& arg) : StalEnemyRoot(arg) {}

StalGiantEnemyRoot::~StalGiantEnemyRoot() {
    auto* actor = mActor;
    sub_7100724E1C(actor, 2);
    sub_7100724E1C(actor, 3);
    sub_7100724E1C(actor, 4);
    sub_7100724E1C(actor, 5);
    sub_7100724E1C(actor, 6);
    sub_71005A3530();
}

bool StalGiantEnemyRoot::init_(sead::Heap* heap) {
    return StalEnemyRoot::init_(heap);
}

void StalGiantEnemyRoot::enter_(ksys::act::ai::InlineParamPack* params) {
    if (auto* set = mActor->getRigidBodyByName(ksys::act::getStr_EntitySensor().cstr())) {
        for (s32 i = 0; i < set->getRigidBodies().size(); ++i) {
            auto* body = set->getRigidBodies().at(i);
            if (body && !body->isAddedToWorld() && !body->isAddingBodyToWorld())
                body->addToWorld();
        }
    }
    if (auto* set = mActor->getRigidBodyByName(ksys::act::getStr_Body().cstr())) {
        for (s32 i = 0; i < set->getRigidBodies().size(); ++i) {
            if (auto* body = set->getRigidBodies().at(i))
                body->clearEntityMotionFlag10(false);
        }
    }
    if (*mIsDamageToEnemy_s)
        getActorAttackSensor(mActor)->_20 |= 0x18;
    if (auto* sensor = sub_71007A2844(mActor))
        sensor->_18 |= 0x800;

    StalEnemyRoot::enter_(params);

    if (auto* giant = sead::DynamicCast<act::GiantEnemy>(mActor)) {
        for (auto& entry : _340.mEntries) {
            if (entry.mAttachment._30.isValid() && entry.mAttachment._78.isValid())
                giant->_1570.append(&entry.mAttachment);
            else
                entry._18 = -1;
        }
        sub_7100727AA0(giant, 1);
        sub_7100727AA0(giant, 3);
        sub_7100727AA0(giant, 4);
        sub_7100727AA0(giant, 5);
    }
    if (auto* controller = mActor->getCharacterController())
        controller->enableContactLayer(ksys::phys::ContactLayer::EntityGroundObject);
    sub_71007214A0(&_818, mActor, "BodyDynamic", "Body", "BgSensor", sead::Mathf::infinity());
    sub_71005E1AE8(mActor);
}

void StalGiantEnemyRoot::leave_() {
    StalEnemyRoot::leave_();
    if (auto* giant = sead::DynamicCast<act::GiantEnemy>(mActor)) {
        for (auto& entry : _340.mEntries)
            giant->_1570.erase(&entry.mAttachment);
    }
}

void StalGiantEnemyRoot::calc_() {
    StalEnemyRoot::calc_();
    sub_71005E1D00(mActor);
    if (sub_71005DD798(mActor, 19, nullptr, 0, 0))
        return;
    auto* terrain = ksys::tera::Terrain::instance();
    if (!terrain)
        return;
    f32 radius = 1.0f;
    if (auto* controller = mActor->getCharacterController())
        controller->sub_7100F62E74(&radius, 0);
    auto* grass = terrain->sub_710114DE4C();
    const sead::Vector3f pos = mActor->getMtx().getTranslation();
    grass->sub_710115101C(&pos, radius);
}

void StalGiantEnemyRoot::loadParams_() {
    StalEnemyRoot::loadParams_();
    getStaticParam(&mActorNameChin_s, "ActorNameChin");
    getStaticParam(&mActorNameRib1_s, "ActorNameRib1");
    getStaticParam(&mActorNameRib2_s, "ActorNameRib2");
    getStaticParam(&mActorNameRib3_s, "ActorNameRib3");
    getStaticParam(&mActorNameRib4_s, "ActorNameRib4");
    getStaticParam(&mIsDamageToEnemy_s, "IsDamageToEnemy");
    sead::FixedSafeString<64> key;
    for (u32 i = 0; i < 4; i++) {
        (sead::StringCutOffPrintFormatter(&key) << "WeakPointNode%d", i) << sead::flush;
        getStaticParam(&mWeakPointNode_s[i], key);
    }
    sead::FixedSafeString<64> entry_key;
    for (u32 i = 0; i < 3; i++) {
        auto& entry = _340.mEntries[i];
        (sead::StringCutOffPrintFormatter(&entry_key) << "NecklaceTgtName%d", i) << sead::flush;
        getStaticParam(&entry.mNecklaceTgtName_s, entry_key);
        (sead::StringCutOffPrintFormatter(&entry_key) << "NecklaceWeaponIdx%d", i) << sead::flush;
        getStaticParam(&entry.mNecklaceWeaponIdx_s, entry_key);
    }
}

void StalGiantEnemyRoot::m35(ksys::act::ai::InlineParamPack* params) {
    bool is_sleep = false;
    if (auto* enemy = sead::DynamicCast<act::Enemy>(mActor))
        is_sleep = enemy->_e84.isOnBit(8);
    params->addBool(is_sleep, "IsSleep", -1);
}

bool StalGiantEnemyRoot::m34() {
    if (StalEnemyRoot::m34())
        return true;

    if (_2e8._8.isOnBit(0))
        return false;

    auto* giant = sead::DynamicCast<act::GiantEnemy>(mActor);
    if (!giant)
        return false;

    if (giant->_e84.isOnBit(8)) {
        if (auto* damage_mgr = mActor->getDamageMgr()) {
            const s32 damage = damage_mgr->getDamage();
            if (damage > 0)
                return true;
        }
    }

    for (int i = 0; i < 4; ++i) {
        auto* part = sead::DynamicCast<ksys::act::Actor>(giant->_14c8._8[i].getProc(nullptr, nullptr));
        if (!part)
            continue;
        auto* chemical = part->getChemicalStuff();
        if (!chemical)
            continue;
        if (chemical->_c0 == 2 || chemical->_1b8 > 0)
            return true;
    }
    return false;
}

// NON_MATCHING: the accessor does not reuse the formatter temporary's stack slot in our build
// Deletes the four "WeakPoint%d" part actors and releases their slots.
void StalGiantEnemyRoot::sub_71005A3530() {
    auto* enemy = sead::DynamicCast<act::Enemy>(mActor);
    if (!enemy)
        return;
    sead::FixedSafeString<16> name;
    for (u32 i = 0; i < 4; i++) {
        (sead::StringCutOffPrintFormatter(&name) << "WeakPoint%d", i) << sead::flush;
        ksys::act::ActorLinkConstDataAccess accessor;
        ksys::act::acquireActor(&enemy->getActorPartsActor(name), &accessor);
        accessor.deleteLater(ksys::act::BaseProc::DeleteReason::_0);
        enemy->sub_7100D3CFEC(name);
    }
}

}  // namespace uking::ai
