#include "Game/Actor/AI/aiGanonThrowActorRoot.h"
#include "Game/Actor/aiUnk_71005D6D10.h"
#include "Game/Actor/actEnemy.h"
#include "Game/Actor/actLastBoss.h"
#include "KingSystem/ActorSystem/aiRootAi.h"
#include "KingSystem/ActorSystem/actAiInlineParam.h"
#include "KingSystem/ActorSystem/actActorLinkConstDataAccess.h"
#include "Game/Actor/actSiteBoss.h"
#include "KingSystem/ActorSystem/actActorCreator.h"
#include "KingSystem/ActorSystem/actActorHeapUtil.h"
#include "KingSystem/ActorSystem/actInstParamPack.h"
#include "KingSystem/Physics/System/physInstanceSet.h"

namespace uking::ai {

GanonThrowActorRoot::GanonThrowActorRoot(const InitArg& arg) : ksys::act::ai::Ai(arg) {}

GanonThrowActorRoot::~GanonThrowActorRoot() {
    auto* enemy = sead::DynamicCast<act::Enemy>(mActor);
    if (!enemy)
        return;

    ksys::act::ActorLinkConstDataAccess accessor;
    ksys::act::acquireActor(&enemy->getActorPartsActor(mRegisterPartsName_s), &accessor);
    if (accessor.hasProc())
        accessor.deleteLater(ksys::act::BaseProc::DeleteReason::_0);
    enemy->sub_7100D3CFEC(mRegisterPartsName_s);
}

bool GanonThrowActorRoot::init_(sead::Heap* heap) {
    auto* enemy = sead::DynamicCast<act::Enemy>(mActor);
    if (!enemy)
        return false;

    if (sub_71005D6D10())
        return true;

    enemy->sub_7100D3CED8(mRegisterPartsName_s, heap);
    auto* actor = sub_71003EF66C(0);
    if (!actor)
        return false;
    enemy->sub_7100D3D108(mRegisterPartsName_s, actor);
    return true;
}

void GanonThrowActorRoot::enter_(ksys::act::ai::InlineParamPack* params) {
    _a0 = false;
    auto* enemy = sead::DynamicCast<act::Enemy>(mActor);
    if (!enemy) {
        changeChild("生成待ち");
        setFailed();
        return;
    }

    ksys::act::ActorLinkConstDataAccess accessor;
    ksys::act::acquireActor(&enemy->getActorPartsActor(mRegisterPartsName_s), &accessor);
    if (!accessor.hasProc() || accessor.isStateCalc())
        changeChild("生成待ち");
    else if (*mIsThrowQuick_s)
        m36();
    else
        changeChild("所持");
}

void GanonThrowActorRoot::calc_() {
    getCurrentChild()->setDynamicParam(*mTargetPos_d, "TargetPos");
    sub_71005D7444(mActor, *mTargetPos_d, true, true);

    if (isCurrentChild("生成待ち")) {
        auto* enemy = sead::DynamicCast<act::Enemy>(mActor);
        if (!enemy)
            return;

        ksys::act::ActorLinkConstDataAccess accessor;
        ksys::act::acquireActor(&enemy->getActorPartsActor(mRegisterPartsName_s),
                                &accessor);
        if (!accessor.hasProc() || !accessor.isStateSleep())
            setFailed();
        else if (*mIsThrowQuick_s)
            m36();
        else
            changeChild("所持");
        return;
    }

    if (isCurrentChild("所持")) {
        auto* child = getCurrentChild();
        if (child->isFinished() || child->isFailed())
            m36();
        return;
    }

    if (isCurrentChild("投げる")) {
        auto* child = getCurrentChild();
        if (child->isFinished() || child->isFailed()) {
            _a0 = true;
            if (*mIsWaitBulletDelete_s) {
                changeChild("弾消え待ち");
                return;
            }
            setFinished();
        }
        return;
    }

    if (isCurrentChild("弾消え待ち") && m35())
        setFinished();
}

void GanonThrowActorRoot::leave_() {
    if (*mIsWaitBulletDelete_s || mActor->getRootAi()->getNewChildIdx() == 0) {
        if (auto* boss = sead::DynamicCast<act::LastBoss>(mActor)) {
            if (!boss->_14f8._30.isOnBit(9))
                m38();
        }
        if (*mIsSendDeleteMessageAtLeave_s)
            m38();
    }
    sub_71005D74E8(mActor);
}

void GanonThrowActorRoot::loadParams_() {
    getStaticParam(&mAttackDamage_s, "AttackDamage");
    getStaticParam(&mAtMinDamage_s, "AtMinDamage");
    getStaticParam(&mAddAtackPower_s, "AddAtackPower");
    getStaticParam(&mIsThrowQuick_s, "IsThrowQuick");
    getStaticParam(&mIsWaitBulletDelete_s, "IsWaitBulletDelete");
    getStaticParam(&mIsSetSystemGroupHandler_s, "IsSetSystemGroupHandler");
    getStaticParam(&mIsSendDeleteMessageAtLeave_s, "IsSendDeleteMessageAtLeave");
    getStaticParam(&mThrowActorName_s, "ThrowActorName");
    getStaticParam(&mRegisterPartsName_s, "RegisterPartsName");
    getDynamicParam(&mTargetPos_d, "TargetPos");
    getDynamicParam(&mViewPos_d, "ViewPos");
}

bool GanonThrowActorRoot::isFinished() const {
    if (isCurrentChild("投げる")) {
        auto* child = getCurrentChild();
        if ((child->isFinished() || child->isFailed()) && !*mIsWaitBulletDelete_s)
            return true;
        return false;
    }
    if (isCurrentChild("弾消え待ち") && m34())
        return true;
    return false;
}

bool GanonThrowActorRoot::m34() const {
    if (auto* enemy = sead::DynamicCast<act::Enemy>(mActor)) {
        ksys::act::ActorLinkConstDataAccess accessor;
        ksys::act::acquireActor(&enemy->getActorPartsActor(mRegisterPartsName_s),
                                &accessor);
        if (accessor.hasProc() && accessor.isStateSleep())
            return true;
    }
    return false;
}

bool GanonThrowActorRoot::m35() {
    if (auto* enemy = sead::DynamicCast<act::Enemy>(mActor)) {
        ksys::act::ActorLinkConstDataAccess accessor;
        ksys::act::acquireActor(&enemy->getActorPartsActor(mRegisterPartsName_s),
                                &accessor);
        if (accessor.hasProc() && accessor.isStateSleep())
            return true;
    }
    return false;
}

void GanonThrowActorRoot::m36() {
    ksys::act::ai::InlineParamPack params;
    params.addVec3(*mTargetPos_d, "TargetPos", -1);
    auto* target = sub_71005D9050(mActor);
    if (!target) {
        setFailed();
        return;
    }
    params.addActor(*target, "TargetActor", -1);
    params.addString(mRegisterPartsName_s.cstr(), "ThrowPartsName", -1);
    changeChild("投げる", &params);
}

// Creates the thrown actor (ThrowActorName) 1 above the actor with the attack params; its attack power grows with
// the number of defeated Blights (counted 3 / 4 for the SiteBoss kinds 4 / 8).
ksys::act::Actor* GanonThrowActorRoot::sub_71003EF66C(s32 count) {
    ksys::act::InstParamPack pack;
    ksys::act::ActorCreator::setCreatePriorityState1(pack, mActor);
    pack->addPosition(mActor->getMtx().getTranslation() + sead::Vector3f(0.0f, 1.0f, 0.0f));

    s32 num_dead = getNumberOfDeadBlights();
    if (mActor->getProfile() == "SiteBoss") {
        if (auto* boss = sead::DynamicCast<act::SiteBoss>(mActor)) {
            const u32 kind = boss->_1534 & ~3u;
            if (kind == 4)
                num_dead = 3;
            else if (kind == 8)
                num_dead = 4;
        }
    }
    pack->add(*mAttackDamage_s + *mAddAtackPower_s * num_dead, "AttackPower");
    pack->add(120.0f, "ScaleTime");
    pack->add(200.0f, "Range");
    ksys::act::ActorCreator::addScale(pack, 1.0f);
    pack->add(0.4f, "AtkRadiusMax");
    pack->add(*mAtMinDamage_s, "AtMinDamage");
    pack->add(m37(count), "Count");
    pack->add(sead::Vector3f(0.0f, 2.0f, 0.0f), "PosOffset");

    auto* proc = ksys::act::ActorCreator::instance()->createActor(
        mThrowActorName_s.cstr(), ksys::act::ActorHeapUtil::instance()->getBaseProcHeap(), &pack,
        true, false);
    auto* actor = sead::DynamicCast<ksys::act::Actor>(proc);
    if (actor && *mIsSetSystemGroupHandler_s && actor->getPhysics() && mActor->getPhysics())
        actor->getPhysics()->sub_7100FBDFA4(mActor->getPhysics()->get188(0));
    return actor;
}

void GanonThrowActorRoot::m38() {
    auto* enemy = sead::DynamicCast<act::Enemy>(mActor);
    if (!enemy)
        return;

    ksys::act::ActorLinkConstDataAccess accessor;
    ksys::act::acquireActor(&enemy->getActorPartsActor(mRegisterPartsName_s), &accessor);
    if (accessor.hasProc() && accessor.isStateCalc()) {
        if (*mIsSendDeleteMessageAtLeave_s)
            sendMessage(*accessor.getMessageTransceiverId(), ksys::MessageType(0x800005c), nullptr);
        else
            accessor.sleep(ksys::act::BaseProc::SleepWakeReason::_0);
    }
}

}  // namespace uking::ai
