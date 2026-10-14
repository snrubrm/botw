#include "Game/AI/AI/aiGolemRoot.h"
#include <math/seadMathCalcCommon.h>
#include "Game/Actor/actUnk_7100d3cd74.h"
#include "KingSystem/Utils/Thread/Message.h"
#include "Game/Actor/actEnemy.h"
#include "Game/Actor/actGiantEnemy.h"
#include "Game/Damage/dmgDamageManagerBase.h"
#include "KingSystem/ActorSystem/actActor.h"
#include "KingSystem/ActorSystem/actModelBindInfo.h"
#include "KingSystem/ActorSystem/actActorLinkConstDataAccess.h"
#include "KingSystem/ActorSystem/actActorSensorUtil.h"
#include "Game/AI/aiUnk_71005D6D10.h"
#include "KingSystem/ActorSystem/actActorSystem.h"
#include "KingSystem/ActorSystem/actActorUtil.h"
#include "KingSystem/ActorSystem/actUnk_71024ef4e8.h"
#include "KingSystem/ActorSystem/Profiles/actPlayerLink.h"
#include "KingSystem/Physics/System/physInstanceSet.h"
#include "KingSystem/Physics/CharacterController/physCharacterController.h"
#include "KingSystem/Physics/RigidBody/physRigidBodySet.h"
#include "KingSystem/System/VFR.h"
#include "Game/AI/aiUnk_71007377D4.h"
#include "KingSystem/Terrain/teraSystem.h"
#include "KingSystem/World/worldManager.h"
#include "KingSystem/ActorSystem/actActorChemicals.h"
#include "KingSystem/ActorSystem/actActorCreator.h"
#include "KingSystem/ActorSystem/actActorHeapUtil.h"
#include "KingSystem/ActorSystem/actActorParam.h"
#include "KingSystem/Resource/Actor/resResourceGParamList.h"
#include "KingSystem/Resource/GeneralParamList/resGParamListObjectGolem.h"

// 5E0904 tests actor contact height against its float argument.
bool sub_71005E0904(ksys::act::Actor* actor, f32 height);

namespace uking::ai {

// NON_MATCHING: short-circuit contact/timer test and timer reloads differ from the native schedule.
void Unk_71003ffbf0::sub_71003FFBF0() {
    if (!_0 || !_20 || !_10 || !_18)
        return;
    const bool contact = sub_71003FFD3C() || sub_71005E0904(_0, *_20);
    if (contact || (_10 ? *_10 > 0.0f : false)) {
        *_10 += ksys::VFR::instance()->getDeltaFrame();
        if (contact)
            _8 = _10 ? *_10 : 0.0f;
        if ((_10 ? *_10 : 0.0f) - _8 > (_18 ? f32(*_18) : 0.0f))
            *_10 = 0.0f;
    }
}

// NON_MATCHING: the original keeps the bounds check of the outer rigid body set lookup (and reloads the
// set table pointer in the loop); the compiler folds it away
// 0x71003ffd3c
bool Unk_71003ffbf0::sub_71003FFD3C() {
    auto* actor = _0;
    auto* link = sub_71005D9050(actor);
    if (link && ksys::act::isPlayerProfile(link)) {
        auto* info = ksys::act::ActorSystem::instance()->getPlayerLink()->getAttachedTargetActor2()
                         ->mAttachInfo;
        if (info->_48 & 2) {
            auto* body = info->_c0;
            if (body) {
                if (auto* physics = actor->getPhysics()) {
                    const s32 count = physics->getNumRigidBodySets();
                    for (s32 i = 0; i < count; ++i) {
                        auto* set = physics->getRigidBodySet(i);
                        const s32 body_count = set->getRigidBodies().size();
                        for (s32 j = 0; j < body_count; ++j) {
                            if (set->getRigidBody(j) == body)
                                return true;
                        }
                    }
                }
            }
        }
    }
    return false;
}

void Unk_71023f5460::call(s32* a1, s32* a2, u32* a3, u32* a4, s32* a5,
                          dmg::DamageCallbackInfo* a6) {
    if (*a4 != 4 || *a5 == -1)
        return;

    auto* actor = mDamageManager->mActor;
    const auto* body_set = actor->getRigidBodyByName(sub_71007A24D0()->cstr());
    if (!body_set)
        return;
    auto* body = body_set->getRigidBody(0);
    if (!body)
        return;

    const s32 num = sub_71007A26AC(actor);
    bool found = false;
    for (s32 i = 0; i < num; ++i) {
        const auto* info = sub_71007A255C(actor, i);
        if (info && info->_50 == 0x10) {
            if (info->_c0 != body)
                return;
            found = true;
        }
    }
    if (found) {
        *a5 = -1;
        *a4 = -1;
    }
}

// NON_MATCHING: life-stage branches and accessor stack/register allocation differ.
void GolemRoot::calc_() {
    GolemRootBase::calc_();
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
    _360.sub_71003FFBF0();
    if (ksys::world::Manager::instance()->isAocField())
        return;
    auto* damage_manager = mActor->getDamageMgr();
    if (!damage_manager)
        return;
    const s32 damage = s32(damage_manager->getDamage());
    if (damage < 1)
        return;
    const s32 quarter = mActor->getMaxLife() / 4;
    auto* life = mActor->getLife();
    const s32 stage = (life ? *life : 1) / quarter;
    life = mActor->getLife();
    if (u32(stage) > 2 || stage == ((life ? *life : 1) + damage) / quarter)
        return;
    if (sub_7100731B70(mActor, stage))
        return;
    sub_7100731A30(mActor, stage);
    if (auto* parts = mActor->m101()) {
        auto& link = parts->getActorPartsActor("WeakPoint");
        ksys::act::ActorLinkConstDataAccess accessor;
        ksys::act::acquireActor(&link, &accessor);
        if (accessor.hasProc())
            _388.sub_710070DBB0(*accessor.getMessageTransceiverId(), true);
    }
}

// NON_MATCHING: the binding helper inlines here; stack/register allocation and return branches differ.
bool GolemRoot::sub_71004003E4(sead::Heap* heap) {
    auto* enemy = sead::DynamicCast<act::Enemy>(mActor);
    if (!enemy)
        return true;

    sead::Vector3f position = enemy->getMtx().getTranslation();
    position.y += 1.0f;
    const sead::SafeString part_name = "WeakPoint";
    const sead::SafeString* actor_name = &mGolemWeakPointActor_m;
    if (mGolemWeakPointActor_m.isEmpty())
        actor_name = &mActor->getParam()->getRes().mGParamList->getGolem()->mDefaultWeakPointActor.ref();
    if (actor_name->isEmpty())
        return true;

    ksys::act::InstParamPack pack;
    pack->addPosition(position);
    ksys::act::ActorCreator::setCreatePriorityState1(pack, mActor);
    pack->addNoDisplay();
    auto* actor = ksys::act::ActorCreator::instance()->createActor(
        actor_name->cstr(), ksys::act::ActorHeapUtil::instance()->getBaseProcHeap(), &pack, false,
        false);
    if (!actor)
        return false;

    sub_7100400C40(actor, mGolemWeakPointLocation_m);
    actor->setDeleteDistance(sead::Mathf::infinity());
    sub_7100738C88(actor, mActor);
    if (auto* chemical = actor->getChemicalContainer()) {
        if (auto* parent_chemical = mActor->getChemicalContainer())
            chemical->sub_7100E38588(parent_chemical->_68);
    }
    enemy->sub_7100D3CED8(part_name, heap);
    enemy->sub_7100D3D108(part_name, actor);
    return true;
}

void GolemRoot::sub_7100400C40(ksys::act::Actor* actor, const sead::SafeString& bone) {
    if (bone.isEmpty())
        return;
    if (auto* enemy = sead::DynamicCast<act::Enemy>(actor)) {
        auto* binding = enemy->_f38;
        if (!binding)
            return;
        binding->x(mActor);
        binding->_28 = bone.cstr();
        binding->_30.getKey().reset();
    }
}

bool GolemRoot::handleMessage_(const ksys::Message* message) {
    if (message->getType() == 0x3000003 || message->getType() == 0x3000004) {
        if (auto* parts = mActor->m101()) {
            auto& link = parts->getActorPartsActor("WeakPoint");
            if (link.hasProc()) {
                ksys::act::ActorLinkConstDataAccess accessor;
                ksys::act::acquireActor(&link, &accessor);
                mActor->sendMessageOnProcessingThread(*accessor.getMessageTransceiverId(),
                                                      message->getType(), nullptr, true);
            }
        }
    }
    return GolemRootBase::handleMessage_(message);
}

GolemRoot::GolemRoot(const InitArg& arg) : GolemRootBase(arg) {}

void GolemRoot::sub_710040007C() {
    auto* enemy = sead::DynamicCast<act::Enemy>(mActor);
    if (!enemy)
        return;

    auto& link = enemy->getActorPartsActor("WeakPoint");
    ksys::act::ActorLinkConstDataAccess accessor;
    ksys::act::acquireActor(&link, &accessor);
    accessor.deleteLater(ksys::act::BaseProc::DeleteReason::_0);
    enemy->sub_7100D3CFEC("WeakPoint");
}

GolemRoot::~GolemRoot() {
    sub_710040007C();
}

// NON_MATCHING: the contact timer pointer initialization is scheduled differently.
bool GolemRoot::init_(sead::Heap* heap) {
    if (!GolemRootBase::init_(heap))
        return false;
    if (!sub_71004003E4(heap) && !sub_71005D6D10())
        return false;

    _360._0 = mActor;
    _360._10 = mGolemClimbedTime_a;
    _360._18 = mClimbFinishTime_s;
    _360._20 = mStandContactHeight_s;
    if (auto* physics = mActor->getPhysics()) {
        if (auto* set = physics->findBodyByName(ksys::act::getStr_Tgt())) {
            for (s32 i = 0; i < set->getRigidBodies().size(); ++i) {
                if (auto* body = set->getRigidBody(i))
                    body->setFlag200();
            }
        }
    }
    if (*mIsBreakContactTree_s) {
        if (auto* set = mActor->getRigidBodyByName(ksys::act::getStr_Body().cstr())) {
            for (s32 i = 0; i < set->getRigidBodies().size(); ++i) {
                if (auto* body = set->getRigidBody(i))
                    sub_71005DBF28(body, 0, 0, false, false, false, true);
            }
        }
    }
    if (auto* giant = sead::DynamicCast<act::GiantEnemy>(mActor))
        giant->_1560 = mActor->findPhysicsBodyByName(sub_71007A24D0()->cstr(), "TgtBody");
    return true;
}

void GolemRoot::enter_(ksys::act::ai::InlineParamPack* params) {
    if (auto* enemy = sead::DynamicCast<act::Enemy>(mActor))
        enemy->_e90 = 4;
    setDamageCallbackTiming(mActor, 0, &_3b0);
    GolemRootBase::enter_(params);
    if (auto* controller = mActor->getCharacterController())
        controller->enableContactLayer(ksys::phys::ContactLayer::EntityGroundObject);
    _3a0.sub_7100721380(sead::Mathf::infinity(), mActor);
    if (*mIsBreakContactTree_s) {
        if (auto* set = mActor->getRigidBodyByName(ksys::act::getStr_Body().cstr())) {
            for (s32 i = 0; i < set->getRigidBodies().size(); ++i) {
                if (auto* body = set->getRigidBodies()[i])
                    sub_71005DBF28(body, 0, 0, false, false, false, true);
            }
        }
    }
}

void GolemRoot::leave_() {
    GolemRootBase::leave_();
    sub_71005DA114(mActor, &_3b0);
}

void GolemRoot::loadParams_() {
    GolemRootBase::loadParams_();
    getStaticParam(&mClimbFinishTime_s, "ClimbFinishTime");
    getStaticParam(&mStandContactHeight_s, "StandContactHeight");
    getStaticParam(&mIsBreakContactTree_s, "IsBreakContactTree");
    getMapUnitParam(&mGolemWeakPointLocation_m, "GolemWeakPointLocation");
    getMapUnitParam(&mGolemSleepType_m, "GolemSleepType");
    getMapUnitParam(&mGolemWeakPointActor_m, "GolemWeakPointActor");
    getAITreeVariable(&mGolemClimbedTime_a, "GolemClimbedTime");
}

}  // namespace uking::ai
