#include "Game/AI/AI/aiOneMemoryMagicBattleBase.h"
#include <random/seadGlobalRandom.h>
#include "Game/AI/aiUnk_71005D6D10.h"
#include "Game/Actor/actEnemy.h"
#include "KingSystem/ActorSystem/actActor.h"
#include "KingSystem/ActorSystem/actAiInlineParam.h"
#include "KingSystem/ActorSystem/actActorCreator.h"
#include "KingSystem/ActorSystem/actActorHeapUtil.h"
#include "KingSystem/ActorSystem/actActorParam.h"
#include "KingSystem/Resource/Actor/resResourceGParamList.h"
#include "KingSystem/Resource/GeneralParamList/resGParamListObjectAttack.h"

namespace uking::ai {

OneMemoryMagicBattleBase::OneMemoryMagicBattleBase(const InitArg& arg) : EnemyBattle(arg) {}

OneMemoryMagicBattleBase::~OneMemoryMagicBattleBase() = default;

bool OneMemoryMagicBattleBase::init_(sead::Heap* heap) {
    return EnemyBattle::init_(heap);
}

void OneMemoryMagicBattleBase::enter_(ksys::act::ai::InlineParamPack* params) {
    auto* actor = mActor;
    ksys::act::InstParamPack pack;
    sead::FixedSafeString<32> name;
    pack->addPosition(actor->getMtx().getTranslation());
    m44(&name, &pack);
    ksys::act::ActorCreator::instance()->requestCreateActor(
        name.cstr(), ksys::act::ActorHeapUtil::instance()->getBaseProcHeap(), &_c8, &pack, nullptr,
        1);
    _d8 = false;
    EnemyBattle::enter_(params);
}

void OneMemoryMagicBattleBase::calc_() {
    _d8 = sead::GlobalRandom::instance()->getS32Range(0, 100) < *mMagicPer_s;
    if (_c8.hasProcCreationFailed())
        _c8.deleteProcIfFailed();
    if (!_c8.isAllocatedOrFailed()) {
        auto* actor = mActor;
        ksys::act::InstParamPack pack;
        sead::FixedSafeString<32> name;
        pack->addPosition(actor->getMtx().getTranslation());
        m44(&name, &pack);
        ksys::act::ActorCreator::instance()->requestCreateActor(
            name.cstr(), ksys::act::ActorHeapUtil::instance()->getBaseProcHeap(), &_c8, &pack,
            nullptr, 1);
    }

    auto* child = getCurrentChild();
    if (child->isFinished() || child->isFailed()) {
        if (isCurrentChild("魔法攻撃")) {
            sub_7100381ED4();
            m37();
            return;
        }
    } else if (child->isChangeable() && isCurrentChild("戦闘準備") && m45()) {
        sub_710049D600();
        return;
    }

    if (isCurrentChild("魔法攻撃"))
        child->setDynamicParam(sub_71005D9330(mActor), "TargetPos");
    else
        EnemyBattle::calc_();
}

void OneMemoryMagicBattleBase::leave_() {
    EnemyBattle::leave_();
    _c8.deleteProc();
}

void OneMemoryMagicBattleBase::loadParams_() {
    EnemyBattle::loadParams_();
    getStaticParam(&mEnlargeTime_s, "EnlargeTime");
    getStaticParam(&mAttackRatio_s, "AttackRatio");
    getStaticParam(&mBreathSize_s, "BreathSize");
    getStaticParam(&mMagicName_s, "MagicName");
    getStaticParam(&mMagicPer_s, "MagicPer");
    getStaticParam(&mAttackPowDirect_s, "AttackPowDirect");
}

void OneMemoryMagicBattleBase::m44(sead::BufferedSafeString* name, ksys::act::InstParamPack* pack) {
    auto* actor = mActor;
    name->copy(mMagicName_s);
    f32 power;
    if (*mAttackPowDirect_s >= 0)
        power = *mAttackPowDirect_s;
    else
        power = actor->getParam()->getRes().mGParamList->getAttack()->mPower.ref() *
                *mAttackRatio_s;
    (*pack)->add(s32(power), "AttackPower");
    (*pack)->add(f32(*mEnlargeTime_s), "ScaleTime");
    (*pack)->add(actor->getParam()->getRes().mGParamList->getAttack()->mRange.ref(), "Range");
    ksys::act::ActorCreator::addScale(*pack, *mBreathSize_s);
}

void OneMemoryMagicBattleBase::sub_710049D600() {
    ksys::act::ai::InlineParamPack params;
    params.addPointer(&_c8, "IgniteHandle", ksys::AIDefParamType::BaseProcHandle, -1);
    params.addVec3(sub_71005D9330(mActor), "TargetPos", -1);
    changeChild("魔法攻撃", &params);
}

bool OneMemoryMagicBattleBase::m45() {
    if (_d8) {
        auto* enemy = sead::DynamicCast<act::Enemy>(mActor);
        if (enemy && enemy->_e68.value <= sead::Mathf::epsilon())
            return sub_7100382558();
    }
    return false;
}

}  // namespace uking::ai
