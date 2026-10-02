#include "Game/AI/AI/aiWolfLinkRoot.h"
#include "Game/Actor/actWolfLink.h"
#include "Game/Damage/dmgDamageManager.h"
#include "KingSystem/ActorSystem/actActor.h"
#include "KingSystem/ActorSystem/actActorParam.h"
#include "KingSystem/ActorSystem/actActorUtil.h"
#include "KingSystem/ActorSystem/actAiInlineParam.h"
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

void WolfLinkRoot::enter_(ksys::act::ai::InlineParamPack* params) {
    ksys::act::ai::Ai::enter_(params);
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

bool WolfLinkRoot::handleMessage_(const ksys::Message& message) {
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

void WolfLinkRoot::sub_710060B700() {
    sead::Vector3f pos;
    mActor->getMtx().getTranslation(pos);
    ksys::act::ai::InlineParamPack params;
    params.addVec3(pos, "TargetPos", -1);
    ksys::act::enableAllAttClients(mActor);
    changeChild("通常行動", &params);
}

}  // namespace uking::ai
