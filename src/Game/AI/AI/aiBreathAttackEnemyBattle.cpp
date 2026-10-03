#include "Game/AI/AI/aiBreathAttackEnemyBattle.h"
#include "Game/Damage/dmgInfoManager.h"
#include "KingSystem/ActorSystem/actActorUtil.h"
#include "Game/AI/aiUnk_71005D6D10.h"
#include "Game/AI/aiUnk_71007377D4.h"
#include "Game/Actor/actEnemy.h"
#include "KingSystem/ActorSystem/actActor.h"
#include "KingSystem/ActorSystem/actActorConstDataAccess.h"
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
    sub_710033E970();
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

void BreathAttackEnemyBattle::leave_() {
    ksys::act::ai::Ai::leave_();
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
void BreathAttackEnemyBattle::sub_710033E970() {
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

bool BreathAttackEnemyBattle::m38() {
    if (auto* enemy = sead::DynamicCast<act::Enemy>(mActor))
        return enemy->_e68.value <= sead::Mathf::epsilon();
    return false;
}

}  // namespace uking::ai
