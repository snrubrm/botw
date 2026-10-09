#include "Game/AI/AI/aiForestGiantRoot.h"
#include <prim/seadFormatPrint.h>
#include <cmath>
#include "Game/AI/aiUnk_71005D6D10.h"
#include "KingSystem/ActorSystem/actPlayerInfo.h"
#include "Game/Actor/actEnemy.h"
#include "Game/Actor/actGiantEnemy.h"
#include "KingSystem/ActorSystem/actActorSensorUtil.h"
#include "KingSystem/ActorSystem/actAttackSensor.h"
#include "KingSystem/Physics/RigidBody/physRigidBody.h"
#include "KingSystem/Physics/RigidBody/physRigidBodySet.h"
#include "KingSystem/Physics/CharacterController/physCharacterController.h"
#include "Game/Damage/dmgInfoManager.h"
#include "KingSystem/Terrain/teraSystem.h"
#include "KingSystem/ActorSystem/actActor.h"
#include "KingSystem/ActorSystem/actActorUtil.h"
#include "KingSystem/ActorSystem/actActorConstDataAccess.h"
#include "KingSystem/ActorSystem/actAiInlineParam.h"

namespace uking::ai {

// 0x71023EFFE0
static const sead::SafeString sUnk_71023EFFE0[] = {"_Sleep", "_Far", "_Awake"};

// NON_MATCHING: register allocation only: the original keeps the two vtable addresses of _538 / _548 in x8 / x9
// and stores them after the second float; ours reuses x8.
ForestGiantRoot::ForestGiantRoot(const InitArg& arg) : EnemyRoot(arg) {}

ForestGiantRoot::~ForestGiantRoot() {
    deleteWeakPoints();
}

// NON_MATCHING: stack layout only: the original puts the name string at sp+8 and the formatter / accessor slot at
// sp+0x30; ours has them the other way round (same code otherwise).
void ForestGiantRoot::deleteWeakPoints() {
    if (auto* enemy = sead::DynamicCast<act::Enemy>(mActor)) {
        sead::FixedSafeString<16> name;
        for (u32 i = 0; i < 4; ++i) {
            (sead::StringCutOffPrintFormatter(&name) << "WeakPoint%d", i) << sead::flush;
            ksys::act::ActorConstDataAccess accessor;
            ksys::act::acquireActor(&enemy->getActorPartsActor(name), &accessor);
            accessor.deleteLater(ksys::act::BaseProc::DeleteReason::_0);
            enemy->sub_7100D3CFEC(name);
        }
    }
}

bool ForestGiantRoot::init_(sead::Heap* heap) {
    if (!EnemyRoot::init_(heap) || !sub_71003DA620(heap))
        return false;
    if (auto* controller = mActor->getCharacterController())
        controller->enableContactLayer(ksys::phys::ContactLayer::EntityGroundObject);
    _230.sub_7100705CD0(heap, mActor);
    *static_cast<Unk_7102450390**>(mGiantNecklaceUnit_a) = &_230;
    if (auto* giant = sead::DynamicCast<act::GiantEnemy>(mActor))
        giant->_1560 = mActor->findPhysicsBodyByName(sub_71007A24D0()->cstr(), "TgtBody");
    return true;
}

// NON_MATCHING: actor loads move across the necklace-count checks in the scan loop.
void ForestGiantRoot::enter_(ksys::act::ai::InlineParamPack* params) {
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
    _558.makeAllZero();
    for (s32 i = 0; i < sub_71005D7854(mActor); ++i) {
        if (sub_71005D83E8(mActor, i))
            _558.setBit(i);
    }
    if (auto* controller = mActor->getCharacterController())
        controller->enableContactLayer(ksys::phys::ContactLayer::EntityGroundObject);
    _230.sub_71007062D4();
    sub_71007214A0(&_538, mActor, "DynamicBody", "Body", sead::SafeString::cEmptyString,
                  sead::Mathf::infinity());
    sub_71005E1AE8(mActor);
    EnemyRoot::enter_(params);
}

void ForestGiantRoot::calc_() {
    _230.sub_71007063B8();
    sub_71003DAF1C();
    if (!sub_71005DD798(mActor, 19, nullptr, 0, 0)) {
        if (auto* terrain = ksys::tera::Terrain::instance()) {
            f32 radius = 1.0f;
            if (auto* controller = mActor->getCharacterController())
                controller->sub_7100F62E74(&radius, 0);
            auto* grass = terrain->sub_710114DE4C();
            const sead::Vector3f position = mActor->getMtx().getTranslation();
            grass->sub_710115101C(&position, radius);
        }
    }
    for (s32 i = 0; i < sub_71005D7854(mActor); ++i) {
        if (_558.isOnBit(i) && !sub_71005D83E8(mActor, i)) {
            _558.resetBit(i);
            if (auto* giant = sead::DynamicCast<act::GiantEnemy>(mActor))
                giant->setNecklaceFlag(i);
        }
    }
    EnemyRoot::calc_();
    sub_71005E1D00(mActor);
}

// NON_MATCHING: the two XZ distance calculations use different float loads and registers.
void ForestGiantRoot::sub_71003DAF1C() {
    if (sub_71005DD798(mActor, 19, nullptr, 0, 0)) {
        if (_559 & 4) {
            if (auto* controller = mActor->getCharacterController())
                sub_71005DC158(controller);
            const auto& player_pos = getPlayerPosition();
            const f32 dx = player_pos.x - mActor->getMtx().getTranslation().x;
            const f32 dz = player_pos.z - mActor->getMtx().getTranslation().z;
            if (std::sqrt(dx * dx + dz * dz) > 50.0f) {
                _559 = (_559 & ~7) | 2;
                sub_71003DB978(sUnk_71023EFFE0[2], sUnk_71023EFFE0[1],
                              sUnk_71023EFFE0[0], sead::SafeString::cEmptyString);
            } else {
                _559 = (_559 & ~7) | 1;
                sub_71003DB978(sUnk_71023EFFE0[2], sUnk_71023EFFE0[0],
                              sUnk_71023EFFE0[1], sead::SafeString::cEmptyString);
            }
        } else {
            const u8 flags = _559;
            const auto& player_pos = getPlayerPosition();
            const f32 dx = player_pos.x - mActor->getMtx().getTranslation().x;
            const f32 dz = player_pos.z - mActor->getMtx().getTranslation().z;
            if (std::sqrt(dx * dx + dz * dz) > 50.0f) {
                if (!(flags & 2)) {
                    _559 = (_559 & ~3) | 2;
                    sub_71003DB978(sUnk_71023EFFE0[0], sUnk_71023EFFE0[1],
                                  sead::SafeString::cEmptyString, sead::SafeString::cEmptyString);
                }
            } else if (!(flags & 1)) {
                _559 = (_559 & ~3) | 1;
                sub_71003DB978(sUnk_71023EFFE0[1], sUnk_71023EFFE0[0],
                              sead::SafeString::cEmptyString, sead::SafeString::cEmptyString);
            }
        }
    } else if (!(_559 & 4)) {
        _559 = (_559 & ~7) | 4;
        sub_71003DB978(sUnk_71023EFFE0[0], sUnk_71023EFFE0[2], sUnk_71023EFFE0[1],
                      sead::SafeString::cEmptyString);
        if (auto* controller = mActor->getCharacterController())
            sub_71005DBE1C(controller, 0, 0, true, false, false, true);
    } else if (_559 & 3) {
        _559 = (_559 & ~7) | 4;
        sub_71003DB978(sUnk_71023EFFE0[0], sUnk_71023EFFE0[2], sUnk_71023EFFE0[1],
                      sead::SafeString::cEmptyString);
    }
}

void ForestGiantRoot::m37() {
    bool is_sleep;
    auto* enemy = sead::DynamicCast<act::Enemy>(mActor);
    if (enemy && enemy->_e84.isOnBit(8))
        is_sleep = true;
    else
        is_sleep = sub_71005DD798(mActor, 19, nullptr, 0, 0);

    ksys::act::ai::InlineParamPack params;
    params.addBool(is_sleep, "IsSleep", -1);
    changeChild("リアクション", &params);
}

void ForestGiantRoot::leave_() {
    _230.sub_7100706C3C();
    EnemyRoot::leave_();
}

bool ForestGiantRoot::handleMessage_(const ksys::Message* message) {
    if (_230.sub_7100707224(message))
        return true;
    return EnemyRoot::handleMessage_(message);
}

bool ForestGiantRoot::handleAck_(const ksys::MessageAck* ack) {
    return _230.sub_71007073D0(ack);
}

// NON_MATCHING: the suffix tests occupy different basic-block positions.
void ForestGiantRoot::sub_71003DB978(const sead::SafeString& add_suffix1,
                                        const sead::SafeString& add_suffix2,
                                        const sead::SafeString& remove_suffix1,
                                        const sead::SafeString& remove_suffix2) {
    auto* set = mActor->getRigidBodyByName(ksys::act::getStr_Body().cstr());
    if (!set)
        return;
    for (s32 i = 0; i < set->getRigidBodies().size(); ++i) {
        auto* body = set->getRigidBodies().at(i);
        if (!body)
            continue;
        const auto name = body->getHkBodyName();
        if (name.endsWith(add_suffix2) || name.endsWith(add_suffix1))
            body->addToWorld();
        else if ((!remove_suffix1.isEmpty() && name.endsWith(remove_suffix1)) ||
                 (!remove_suffix2.isEmpty() && name.endsWith(remove_suffix2)))
            body->removeFromWorld();
    }
}

// NON_MATCHING: register allocation only: the original computes &mIsDamageToEnemy_s into x20 before the fourth
// WeakPointNode getStaticParam call (x20 holds the formatter output pointer until then).
void ForestGiantRoot::loadParams_() {
    EnemyRoot::loadParams_();
    sead::FixedSafeString<64> key;
    for (u32 i = 0; i < 4; ++i) {
        (sead::StringCutOffPrintFormatter(&key) << "WeakPointNode%d", i) << sead::flush;
        getStaticParam(&mWeakPointNode_s[i], key);
    }
    getStaticParam(&mIsDamageToEnemy_s, "IsDamageToEnemy");
    getAITreeVariable(&mIgnoreGiantArmorCondition_a, "IgnoreGiantArmorCondition");
    getAITreeVariable(&mGiantNecklaceUnit_a, "GiantNecklaceUnit");
    _230.sub_7100706E98(this);
}

}  // namespace uking::ai

void Unk_7102450390::sub_71007062D4() {
    _2c0 = uking::dmg::DamageInfoMgr::instance()->get11f0().sub_7100674A94(mActor);
    if (!_2c0)
        _2cc.reset(60.0f);
    if (_2d8.hasProc()) {
        ksys::act::ActorConstDataAccess accessor;
        ksys::act::acquireActor(&_2d8, &accessor);
        accessor.wakeUp(ksys::act::BaseProc::SleepWakeReason::_0);
        mActor->sendMessage(*accessor.getMessageTransceiverId(), ksys::MessageType(0x300000c),
                            nullptr, false);
    }
    _2f8.reset(30.0f);
}

// NON_MATCHING: the formatter and string occupy different stack slots.
ksys::act::Actor* Unk_7102450390::sub_7100706D0C(u32 slot) {
    auto* parts = mActor->m101();
    if (!parts)
        return nullptr;
    sead::FixedSafeString<64> name;
    (sead::StringCutOffPrintFormatter(&name) << "Necklace%d", slot) << sead::flush;
    return sead::DynamicCast<ksys::act::Actor>(
        parts->getActorPartsActor(name).getProc(nullptr, mActor));
}

void Unk_7102450390::sub_7100706C3C() {
    uking::dmg::DamageInfoMgr::instance()->get11f0().sub_7100674B30(mActor);
    if (_2d8.hasProc()) {
        ksys::act::ActorConstDataAccess accessor;
        ksys::act::acquireActor(&_2d8, &accessor);
        mActor->sendMessage(*accessor.getMessageTransceiverId(), ksys::MessageType(0x300000d),
                            nullptr, false);
    }
    if (_2e8.isAllocatedOrFailed())
        _2e8.deleteProc();
    if (auto* actor = sub_7100706D0C(0))
        actor->deleteLater(ksys::act::BaseProc::DeleteReason::_0);
}
