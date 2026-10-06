#include "Game/AI/AI/aiWolfLinkRoot.h"
#include "Game/Actor/actWolfLink.h"
#include "Game/Damage/dmgDamageManager.h"
#include "KingSystem/ActorSystem/actActor.h"
#include "KingSystem/ActorSystem/actActorParam.h"
#include "KingSystem/ActorSystem/actActorSensorUtil.h"
#include "KingSystem/ActorSystem/actActorUtil.h"
#include "KingSystem/ActorSystem/AS/ASList.h"
#include "KingSystem/ActorSystem/Awareness/actAwarenessInstance.h"
#include "KingSystem/Physics/RigidBody/physRigidBody.h"
#include "KingSystem/Physics/RigidBody/physRigidBodySet.h"
#include "KingSystem/Physics/System/physInstanceSet.h"
#include "KingSystem/ActorSystem/actAiInlineParam.h"
#include "KingSystem/Physics/System/physNavMeshCharacter.h"
#include "KingSystem/Resource/Actor/resResourceGParamList.h"
#include "KingSystem/Resource/GeneralParamList/resGParamListObjectWolfLink.h"

namespace uking::ai {

WolfLinkRoot::WolfLinkRoot(const InitArg& arg) : ksys::act::ai::Ai(arg) {}

WolfLinkRoot::~WolfLinkRoot() = default;

bool WolfLinkRoot::init_(sead::Heap* heap) {
    _f8 = false;
    auto* wolf = sead::DynamicCast<act::WolfLink>(mActor);
    if (!wolf) {
        _e8 = nullptr;
        return false;
    }
    _e8 = wolf;
    _f0 = wolf->getParam()->getRes().mGParamList->getWolfLink();
    return _f0 != nullptr;
}

static const sead::SafeString sUnk_7102432be0 = "AtkBody";

// NON_MATCHING: the two zero stores to _44.value / _44.prev_value are merged into one 8-byte store (the original keeps
// `stp z, 0` + a separate `str wzr`)
void WolfLinkRoot::enter_(ksys::act::ai::InlineParamPack* params) {
    auto* actor = mActor;
    if (actor) {
        auto* mgr = sead::DynamicCast<dmg::DamageManager>(actor->getDamageMgr());
        if (mgr) {
            auto* awareness = actor->getAwareness();
            if (awareness) {
                auto* set = actor->getPhysics()->findBodyByName(*sub_71007A24BC());
                if (set) {
                    auto* body = set->findBodyByHavokName(sUnk_7102432be0);
                    if (body) {
                        auto* as_list = actor->getASList();
                        if (as_list) {
                            awareness->enable();
                            awareness->_328 = 0x2000b8;
                            body->setTransform(actor->getMtx());
                            sub_71007A3258(body, nullptr);
                            sub_71007A2B64(body, nullptr);
                            mgr->_68 = _e8->sub_71002F4428();
                            mgr->addDamageCallback(1, &_88);
                            mgr->addDamageCallback(4, &_60);
                            mgr->addDamageCallback(4, &_b0);
                            actor->getASList()->sub_710115BAF8("Root");
                            as_list->x_6(9, 0, 0.0f);
                            _38 = actor->getMtx().getBase(2);
                            _44.value = 0;
                            _44.prev_value = 0;
                            m39();
                            return;
                        }
                    }
                }
            }
        }
    }
    setFailed();
}

void WolfLinkRoot::leave_() {
    auto* mgr = mActor->getDamageMgr();
    if (!mgr) {
        setFailed();
        return;
    }
    mgr->removeDamageCallback(&_88);
    mgr->removeDamageCallback(&_b0);
    mgr->removeDamageCallback(&_60);
}

void WolfLinkRoot::loadParams_() {}

bool WolfLinkRoot::handleMessage_(const ksys::Message* message) {
    return false;
}

bool WolfLinkRoot::m34() {
    bool ret = false;
    if (mActor->get68f().load()) {
        const f32 y = mActor->getMtx().m[1][3];
        if (mActor->get6f0() - y > _f0->mSubmergedDepth.ref())
            ret = !isCurrentChild("水中行動");
    }
    return ret;
}

// NON_MATCHING: the original computes &_e8->_c48 after getAttacker()
bool WolfLinkRoot::m35() {
    if (auto* life = mActor->getLife();
        life && *life <= 0 &&
        !mActor->getActorFlags2().isOn(ksys::act::Actor::ActorFlag2::Alive)) {
        return true;
    }

    auto* mgr = sead::DynamicCast<dmg::DamageManager>(_e8->getDamageMgr());
    if (!mgr)
        return false;

    if (!_e8->_c48._8.hasProc())
        _e8->_c48.sub_71002DBC8C(*mgr->getAttacker(), nullptr, nullptr);

    const s32 type = mgr->getField54();
    if (type == 20)
        return true;

    const s32 damage = mgr->getDamage();
    if (damage < 1)
        return false;

    if (mgr->_216.isOn(2))
        return true;

    switch (type) {
    case 15:
    case 17:
    case 21:
    case 22:
    case 27:
        return true;
    default:
        return false;
    }
}

void WolfLinkRoot::m36() {
    if (isCurrentChild("リアクション"))
        return;

    if (m35()) {
        changeChild("リアクション");
        ksys::act::disableAllAttClients(mActor);
    } else if (m34()) {
        sub_710060B508();
    } else {
        isChangeable();
    }
}

void WolfLinkRoot::m37() {
    if (!isCurrentChild("水中行動"))
        return;

    if (mActor->get68f().load()) {
        const f32 y = mActor->getMtx().m[1][3];
        if (mActor->get6f0() - y > _f0->mSubmergedDepth.ref())
            return;
    }
    sub_710060B700();
}

void WolfLinkRoot::m38() {
    auto* child = getCurrentChild();
    if (child->isFinished() || child->isFailed())
        sub_710060B700();
}

// NON_MATCHING: the original shares one changeChild call between the two branches
void WolfLinkRoot::m39() {
    if (!_f8) {
        _f8 = true;
        changeChild("出現");
    } else {
        auto* life = mActor->getLife();
        if (!life || *life > 0) {
            sub_710060B700();
            return;
        }
        changeChild("リアクション");
    }
    ksys::act::disableAllAttClients(mActor);
}

void WolfLinkRoot::sub_710060B508() {
    _e8->sub_71002F2E78(act::WolfLink::Idx14f8::_14);
    _e8->_1698 |= 0x20;
    _e8->m45()->inlineReset();
    ksys::act::ai::InlineParamPack params;
    params.addInt(1, "WarpType", -1);
    ksys::act::disableAllAttClients(mActor);
    changeChild("水中行動", &params);
}

void WolfLinkRoot::sub_710060B700() {
    sead::Vector3f pos;
    mActor->getMtx().getTranslation(pos);
    ksys::act::ai::InlineParamPack params;
    params.addVec3(pos, "TargetPos", -1);
    ksys::act::enableAllAttClients(mActor);
    changeChild("通常行動", &params);
}

// 0x710060b8d8
void Unk_7102432d40::call(s32* a1, s32* a2, u32* a3, u32* a4, s32* a5,
                          dmg::DamageCallbackInfo* a6) {
    if (*a5 == -1)
        return;
    auto* manager = sead::DynamicCast<dmg::DamageManagerBase>(mDamageManager);
    if (!manager)
        return;
    if (!manager->getAttacker()->hasProc())
        return;
    if (*a5 != 6)
        return;
    *a1 = 0;
    *a5 = -1;
    auto* info = sead::DynamicCast<dmg::DamageCallbackInfo>(a6);
    if (info)
        info->mFlags = 0;
}

}  // namespace uking::ai
