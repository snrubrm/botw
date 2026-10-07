#include "Game/AI/Action/actionFireWood.h"
#include "Game/Damage/dmgDamageManagerBase.h"
#include "Game/Damage/dmgDamageManager.h"
#include "KingSystem/ActorSystem/actActorParam.h"
#include "KingSystem/Resource/Actor/resResourceDamageParam.h"
#include "Game/gameUnk_71008ba8d8.h"
#include "KingSystem/Utils/Thread/Message.h"
#include "KingSystem/ActorSystem/actActor.h"
#include "KingSystem/ActorSystem/actAiRoot.h"
#include "KingSystem/ActorSystem/actActorUtil.h"
#include "KingSystem/Physics/RigidBody/physRigidBody.h"
#include "KingSystem/Physics/System/physInstanceSet.h"
#include "KingSystem/Physics/System/physSystem.h"
#include "KingSystem/ActorSystem/actActorSensorUtil.h"
#include "KingSystem/Event/evtManager.h"

namespace uking::action {

FireWood::FireWood(const InitArg& arg) : FireWoodBase(arg) {}

FireWood::~FireWood() = default;

bool FireWood::init_(sead::Heap* heap) {
    return FireWoodBase::init_(heap);
}

void FireWood::enter_(ksys::act::ai::InlineParamPack* params) {
    FireWoodBase::enter_(params);
    _40 = false;
    if (auto* damage_mgr = mActor->getDamageMgr())
        damage_mgr->mField_34 = 0;
    auto* actor = mActor;
    auto* main_body = actor->getMainBody();
    auto* body = actor->findPhysicsBodyByName(ksys::act::getStr_Body().cstr(), "Barrier");
    auto* physics = mActor->getPhysics();
    auto* handler = ksys::phys::System::instance()->sub_7101216894(
        ksys::phys::ContactLayerType::Entity, 1);
    if (physics)
        physics->sub_7100FBDFA4(handler);
    if (main_body && actor->getMapObject())
        main_body->changeMotionType(ksys::phys::MotionType::Fixed);
    if (body) {
        body->setContactAll();
        body->disableContactLayer(ksys::phys::ContactLayer::EntitySmallObject);
    }
}

void FireWood::leave_() {
    FireWoodBase::leave_();
}

void FireWood::loadParams_() {
    FireWoodBase::loadParams_();
    mActor->getRootAi()->getAITreeVariable2(&mIsDrop_a, "IsDrop");
}

// NON_MATCHING: scheduling only (the original loads mActor and the SafeString vtable before the branch)
void FireWood::m32(bool burning) {
    FireWoodBase::m32(burning);
    if (!burning) {
        ksys::act::disableAttClient(mActor, "KillTime");
        mActor->emitBasicSigOff();
        if (*mIsDrop_a) {
            auto* body = mActor->findPhysicsBodyByName(ksys::act::getStr_Body().cstr(), "Cutting");
            if (body)
                body->removeFromWorld();
        }
    } else {
        ksys::act::enableAttClient(mActor, "KillTime");
        mActor->emitBasicSigOn();
        if (*mIsDrop_a) {
            auto* body = mActor->findPhysicsBodyByName(ksys::act::getStr_Body().cstr(), "Cutting");
            if (body)
                body->addToWorld();
        }
    }
}

// NON_MATCHING: clang merges the false-return branches and forms the final damage comparison as a boolean.
bool FireWood::m33() {
    if (mActor->isDelete())
        return false;
    if (mActor->isDeleteRequested())
        return false;
    const auto* param = mActor->getParam();
    if (!param || !param->getRes().mDamageParam || !param->getRes().mDamageParam->mBreakable.ref())
        return true;
    if (const auto* life = mActor->getLife(); life && *life < 1)
        return false;
    auto* damage = sead::DynamicCast<dmg::DamageManager>(mActor->getDamageMgr());
    if (!damage)
        return true;
    if (damage->_216.isOn(2))
        return false;
    if (s32(damage->getDamage()) > 0)
        return false;
    return true;
}

bool FireWood::handleMessage_(const ksys::Message* message) {
    if (message->getType() == 0x180001c && _30 && m33()) {
        if (!uking::callDemo007_1(mActor))
            return false;
        _40 = true;
        if (auto* damage_mgr = mActor->getDamageMgr())
            damage_mgr->mField_34 = 1;
        return true;
    }
    return FireWoodBase::handleMessage_(message);
}

void FireWood::calc_() {
    FireWoodBase::calc_();
    if (_40) {
        auto* manager = ksys::evt::Manager::instance();
        if (manager && !manager->_1d2b8 && !(manager->_1d2f4 & 0x100)) {
            _40 = false;
            if (auto* damage_mgr = mActor->getDamageMgr())
                damage_mgr->mField_34 = 0;
        }
    }
}

}  // namespace uking::action
