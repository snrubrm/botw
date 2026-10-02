#include "Game/AI/AI/aiGanonThrowActorRoot.h"
#include "Game/AI/aiUnk_71005D6D10.h"
#include "Game/Actor/actEnemy.h"
#include "KingSystem/ActorSystem/actAiInlineParam.h"
#include "KingSystem/ActorSystem/actActorConstDataAccess.h"

namespace uking::ai {

GanonThrowActorRoot::GanonThrowActorRoot(const InitArg& arg) : ksys::act::ai::Ai(arg) {}

// NON_MATCHING: the original computes &mRegisterPartsName_s before &enemy->_1128
GanonThrowActorRoot::~GanonThrowActorRoot() {
    auto* enemy = sead::DynamicCast<act::Enemy>(mActor);
    if (!enemy)
        return;

    ksys::act::ActorConstDataAccess accessor;
    ksys::act::acquireActor(&enemy->_1128.getActorPartsActor(mRegisterPartsName_s), &accessor);
    if (accessor.hasProc())
        accessor.deleteLater(ksys::act::BaseProc::DeleteReason::_0);
    enemy->_1128.sub_7100D3CFEC(mRegisterPartsName_s);
}

// NON_MATCHING: the original computes &mRegisterPartsName_s before &enemy->_1128
bool GanonThrowActorRoot::init_(sead::Heap* heap) {
    auto* enemy = sead::DynamicCast<act::Enemy>(mActor);
    if (!enemy)
        return false;

    if (sub_71005D6D10())
        return true;

    enemy->_1128.sub_7100D3CED8(mRegisterPartsName_s, heap);
    auto* actor = sub_71003EF66C(0);
    if (!actor)
        return false;
    enemy->_1128.sub_7100D3D108(mRegisterPartsName_s, actor);
    return true;
}

// NON_MATCHING: the original computes &mRegisterPartsName_s before &enemy->_1128
void GanonThrowActorRoot::enter_(ksys::act::ai::InlineParamPack* params) {
    _a0 = false;
    auto* enemy = sead::DynamicCast<act::Enemy>(mActor);
    if (!enemy) {
        changeChild("生成待ち");
        setFailed();
        return;
    }

    ksys::act::ActorConstDataAccess accessor;
    ksys::act::acquireActor(&enemy->_1128.getActorPartsActor(mRegisterPartsName_s), &accessor);
    if (!accessor.hasProc() || accessor.isStateCalc())
        changeChild("生成待ち");
    else if (*mIsThrowQuick_s)
        m36();
    else
        changeChild("所持");
}

// NON_MATCHING: the original computes &mRegisterPartsName_s before &enemy->_1128
void GanonThrowActorRoot::calc_() {
    getCurrentChild()->setDynamicParam(*mTargetPos_d, "TargetPos");
    sub_71005D7444(mActor, *mTargetPos_d, true, true);

    if (isCurrentChild("生成待ち")) {
        auto* enemy = sead::DynamicCast<act::Enemy>(mActor);
        if (!enemy)
            return;

        ksys::act::ActorConstDataAccess accessor;
        ksys::act::acquireActor(&enemy->_1128.getActorPartsActor(mRegisterPartsName_s),
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
    ksys::act::ai::Ai::leave_();
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

// NON_MATCHING: the original computes &mRegisterPartsName_s before &enemy->_1128
bool GanonThrowActorRoot::m34() const {
    if (auto* enemy = sead::DynamicCast<act::Enemy>(mActor)) {
        ksys::act::ActorConstDataAccess accessor;
        ksys::act::acquireActor(&enemy->_1128.getActorPartsActor(mRegisterPartsName_s),
                                &accessor);
        if (accessor.hasProc() && accessor.isStateSleep())
            return true;
    }
    return false;
}

// NON_MATCHING: the original computes &mRegisterPartsName_s before &enemy->_1128
bool GanonThrowActorRoot::m35() {
    if (auto* enemy = sead::DynamicCast<act::Enemy>(mActor)) {
        ksys::act::ActorConstDataAccess accessor;
        ksys::act::acquireActor(&enemy->_1128.getActorPartsActor(mRegisterPartsName_s),
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

// NON_MATCHING: the original computes &mRegisterPartsName_s before &enemy->_1128; MessageType
// temporary at sp+0 instead of sp+4
void GanonThrowActorRoot::m38() {
    auto* enemy = sead::DynamicCast<act::Enemy>(mActor);
    if (!enemy)
        return;

    ksys::act::ActorConstDataAccess accessor;
    ksys::act::acquireActor(&enemy->_1128.getActorPartsActor(mRegisterPartsName_s), &accessor);
    if (accessor.hasProc() && accessor.isStateCalc()) {
        if (*mIsSendDeleteMessageAtLeave_s)
            sendMessage(*accessor.getMessageTransceiverId(), 0x800005c, nullptr);
        else
            accessor.sleep(ksys::act::BaseProc::SleepWakeReason::_0);
    }
}

}  // namespace uking::ai
