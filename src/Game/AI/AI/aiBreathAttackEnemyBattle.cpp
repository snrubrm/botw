#include "Game/AI/AI/aiBreathAttackEnemyBattle.h"
#include "Game/Damage/dmgInfoManager.h"
#include "KingSystem/ActorSystem/actActorUtil.h"
#include "Game/AI/aiUnk_71005D6D10.h"
#include "Game/AI/aiUnk_71007377D4.h"
#include "Game/Actor/actEnemy.h"
#include "KingSystem/ActorSystem/actActor.h"
#include "KingSystem/ActorSystem/actActorConstDataAccess.h"
#include "KingSystem/ActorSystem/actActorCreator.h"
#include "KingSystem/ActorSystem/actActorHeapUtil.h"
#include "KingSystem/ActorSystem/actActorParam.h"
#include "KingSystem/ActorSystem/actInstParamPack.h"
#include "KingSystem/Resource/Actor/resResourceGParamList.h"
#include "KingSystem/Resource/GeneralParamList/resGParamListObjectAttack.h"
#include "KingSystem/ActorSystem/actAiInlineParam.h"
#include "KingSystem/ActorSystem/actAiRoot.h"

namespace uking::ai {

BreathAttackEnemyBattle::BreathAttackEnemyBattle(const InitArg& arg) : ksys::act::ai::Ai(arg) {}

BreathAttackEnemyBattle::~BreathAttackEnemyBattle() = default;

bool BreathAttackEnemyBattle::init_(sead::Heap* heap) {
    return ksys::act::ai::Ai::init_(heap);
}

void BreathAttackEnemyBattle::enter_(ksys::act::ai::InlineParamPack* params) {
    if (*mIsUpdateNoticeState_s) {
        auto* actor = mActor;
        actor->getActorFlags2().reset(ksys::act::Actor::ActorFlag2::_1000000);
        actor->getActorFlags2().set(ksys::act::Actor::ActorFlag2::_2000000);
    }
    m42();
    _a0.reset();
    if (!testRootAiFlag2(ksys::act::ai::RootAiFlag2::_1) &&
        !testRootAiFlag2(ksys::act::ai::RootAiFlag2::_0)) {
        if (auto* enemy = static_cast<act::Enemy*>(mActor)) {
            const s32 time = enemy->_f28.sub_7100001AA4(*mAttackIntervalIntensity_s);
            enemy->_e68 = ksys::Timer(time, time);
        }
    }
    changeToPrepareBattle();
}

void BreathAttackEnemyBattle::sub_710033EA88() {
    if (auto* enemy = static_cast<act::Enemy*>(mActor))
        enemy->startAttackInterval(*mAttackIntervalIntensity_s);
}

void BreathAttackEnemyBattle::sub_710033F27C(s32 time) {
    if (time < 0)
        return;
    if (auto* enemy = static_cast<act::Enemy*>(mActor))
        enemy->_e68 = ksys::Timer(time, time);
}

void BreathAttackEnemyBattle::sub_710033EDD0(sead::Vector3f* out) {
    ksys::act::ActorConstDataAccess accessor;
    ksys::act::acquireActor(&m34(), &accessor);
    accessor.getActorMtx().getTranslation(*out);
}

void BreathAttackEnemyBattle::calc_() {
    m43();
    auto* child = getCurrentChild();
    if (child->isFinished() || child->isFailed()) {
        if (isCurrentChild("戦闘準備")) {
            if (getCurrentChild()->isFailed())
                setFailed();
            else if (m39())
                m37();
        } else if (isCurrentChild("戦闘攻撃")) {
            if (getCurrentChild()->isFailed()) {
                setFailed();
            } else if (*mIsEndAfterAttack_s) {
                setFinished();
            } else {
                if (auto* enemy = static_cast<act::Enemy*>(mActor)) {
                    const s32 time = enemy->_f28.sub_7100001AA4(*mAttackIntervalIntensity_s);
                    enemy->_e68 = ksys::Timer(time, time);
                }
                changeToPrepareBattle();
            }
            if (*mIsDeleteBreath_s) {
                if (auto* actor = sead::DynamicCast<ksys::act::Actor>(_a0.getProc(nullptr, nullptr)))
                    actor->deleteLater(ksys::act::BaseProc::DeleteReason::_0);
            }
        }
        return;
    }

    if (getCurrentChild()->isChangeable() && isCurrentChild("戦闘準備")) {
        if (!mActor) {
            setFailed();
            return;
        }
        if (m39()) {
            m37();
            return;
        }
    }

    sead::Vector3f pos;
    sub_710033EDD0(&pos);
    getCurrentChild()->setDynamicParam(pos, "TargetPos");
}

void BreathAttackEnemyBattle::leave_() {
    _90.deleteProc();
    if (*mIsDeleteBreath_s) {
        if (auto* actor = sead::DynamicCast<ksys::act::Actor>(_a0.getProc(nullptr, nullptr)))
            actor->deleteLater(ksys::act::BaseProc::DeleteReason::_0);
    }
}

void BreathAttackEnemyBattle::loadParams_() {
    getStaticParam(&mEnlargeTime_s, "EnlargeTime");
    getStaticParam(&mAttackAngle_s, "AttackAngle");
    getStaticParam(&mAttackRatio_s, "AttackRatio");
    getStaticParam(&mBreathSize_s, "BreathSize");
    getStaticParam(&mAttackIntervalIntensity_s, "AttackIntervalIntensity");
    getStaticParam(&mGlobalNoAtkTime_s, "GlobalNoAtkTime");
    getStaticParam(&mIsEndAfterAttack_s, "IsEndAfterAttack");
    getStaticParam(&mIsDeleteBreath_s, "IsDeleteBreath");
    getStaticParam(&mBreathName_s, "BreathName");
    getStaticParam(&mIsUpdateNoticeState_s, "IsUpdateNoticeState");
}

ksys::act::BaseProcLink& BreathAttackEnemyBattle::m34() {
    auto* link = sub_71005D9050(mActor);
    if (link != nullptr)
        return *link;
    return ksys::act::getDummyBaseProcLink();
}

const sead::Vector3f* BreathAttackEnemyBattle::m35() {
    return &sub_71005D9330(mActor);
}

const sead::SafeString& BreathAttackEnemyBattle::m36() {
    return mBreathName_s;
}

// NON_MATCHING: stack slots of target_pos / accessor swapped (the original's accessor sits above
// target_pos, as if from an inline helper)
bool BreathAttackEnemyBattle::m40() {
    sead::Vector3f target_pos;
    {
        ksys::act::ActorConstDataAccess accessor;
        ksys::act::acquireActor(&m34(), &accessor);
        accessor.getActorMtx().getTranslation(target_pos);
    }
    if (!m38())
        return false;
    return sub_710072DDB8(target_pos, mActor->getMtx(), *mAttackAngle_s);
}

bool BreathAttackEnemyBattle::m39() {
    if (!m40() || !_90.isProcReady())
        return false;
    if (*mGlobalNoAtkTime_s < 0)
        return true;
    if (!ksys::act::isPlayerProfile(&m34()))
        return true;
    return dmg::DamageInfoMgr::instance()->get4f8().sub_7100671A40(mActor, *mGlobalNoAtkTime_s);
}

void BreathAttackEnemyBattle::m41() {}

void BreathAttackEnemyBattle::m43() {
    if (_90.hasProcCreationFailed())
        _90.deleteProcIfFailed();
    if (!_90.isAllocatedOrFailed())
        m42();
}

bool BreathAttackEnemyBattle::m44() {
    return _90.isProcReady();
}

// NON_MATCHING: stack layout (the original's accessor slot comes first, as if it came from an
// inlined helper)
void BreathAttackEnemyBattle::changeToPrepareBattle() {
    ksys::act::ai::InlineParamPack params;
    sead::Vector3f pos;
    {
        ksys::act::ActorConstDataAccess accessor;
        ksys::act::acquireActor(&m34(), &accessor);
        accessor.getActorMtx().getTranslation(pos);
    }
    params.addVec3(pos, "TargetPos", -1);
    changeChild("戦闘準備", &params);
}

void BreathAttackEnemyBattle::m37() {
    m41();
    ksys::act::ai::InlineParamPack pack;
    pack.addPointer(&_90, "IgniteHandle", ksys::AIDefParamType::BaseProcHandle, -1);
    const sead::Vector3f target_pos = *m35();
    pack.addVec3(target_pos, "TargetPos", -1);
    _a0.acquire(sead::DynamicCast<ksys::act::Actor>(_90.getProc()), false);
    changeChild("戦闘攻撃", &pack);
}

bool BreathAttackEnemyBattle::m38() {
    if (auto* enemy = sead::DynamicCast<act::Enemy>(mActor))
        return enemy->_e68.value <= sead::Mathf::epsilon();
    return false;
}

void BreathAttackEnemyBattle::m42() {
    auto* actor = mActor;
    ksys::act::InstParamPack pack;
    pack->addPosition(actor->getMtx().getTranslation());
    pack->add(s32(actor->getParam()->getRes().mGParamList->getAttack()->mPower.ref() *
                  *mAttackRatio_s),
              "AttackPower");
    pack->add(f32(*mEnlargeTime_s), "ScaleTime");
    pack->add(actor->getParam()->getRes().mGParamList->getAttack()->mRange.ref(), "Range");
    ksys::act::ActorCreator::addScale(pack, *mBreathSize_s);
    ksys::act::ActorCreator::setCreatePriorityState1(pack, mActor);
    ksys::act::ActorCreator::instance()->requestCreateActor(
        m36().cstr(), ksys::act::ActorHeapUtil::instance()->getBaseProcHeap(), &_90, &pack, nullptr,
        1);
}

}  // namespace uking::ai
