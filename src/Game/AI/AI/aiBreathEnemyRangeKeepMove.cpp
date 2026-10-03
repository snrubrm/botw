#include "Game/AI/AI/aiBreathEnemyRangeKeepMove.h"
#include "Game/Actor/actEnemy.h"
#include "KingSystem/ActorSystem/actActorConstDataAccess.h"
#include "KingSystem/ActorSystem/actActorCreator.h"
#include "KingSystem/ActorSystem/actActorHeapUtil.h"
#include "KingSystem/ActorSystem/actActorParam.h"
#include "KingSystem/ActorSystem/actInstParamPack.h"
#include "KingSystem/Resource/Actor/resResourceGParamList.h"
#include "KingSystem/Resource/GeneralParamList/resGParamListObjectAttack.h"

namespace uking::ai {

BreathEnemyRangeKeepMove::BreathEnemyRangeKeepMove(const InitArg& arg) : EnemyRangeKeepMove(arg) {}

BreathEnemyRangeKeepMove::~BreathEnemyRangeKeepMove() {
    if (auto* enemy = sead::DynamicCast<act::Enemy>(mActor))
        enemy->sub_7100D3CFEC(mBreathName_s.cstr());
}

bool BreathEnemyRangeKeepMove::init_(sead::Heap* heap) {
    if (!EnemyRangeKeepMove::init_(heap))
        return false;
    return sub_710033FB98(heap);
}

void BreathEnemyRangeKeepMove::enter_(ksys::act::ai::InlineParamPack* params) {
    EnemyRangeKeepMove::enter_(params);
    _16c = false;
    _160 = ksys::Timer(0, 0);
    changeChild("ブレス開始");
}

void BreathEnemyRangeKeepMove::leave_() {
    EnemyRangeKeepMove::leave_();
    sub_7100340570();
}

void BreathEnemyRangeKeepMove::loadParams_() {
    EnemyRangeKeepMove::loadParams_();
    getStaticParam(&mEnlargeTime_s, "EnlargeTime");
    getStaticParam(&mAttackRatio_s, "AttackRatio");
    getStaticParam(&mBreathSize_s, "BreathSize");
    getStaticParam(&mBreathName_s, "BreathName");
    getStaticParam(&mBaseNode_s, "BaseNode");
    getStaticParam(&mLoopTime_s, "LoopTime");
    getStaticParam(&mBreathEndDist_s, "BreathEndDist");
    getStaticParam(&mBreathMinTime_s, "BreathMinTime");
}

bool BreathEnemyRangeKeepMove::handleMessage_(const ksys::Message& message) {
    if (message.getType() == 0x3000003 && sub_710034076C()) {
        sub_7100340570();
        _16c = true;
    }
    return false;
}

bool BreathEnemyRangeKeepMove::sub_710034076C() {
    bool is_state_calc = false;
    if (auto* enemy = sead::DynamicCast<act::Enemy>(mActor)) {
        auto& link = enemy->getActorPartsActor(mBreathName_s.cstr());
        ksys::act::ActorConstDataAccess acc;
        ksys::act::acquireActor(&link, &acc);
        is_state_calc = acc.isStateCalc();
    }
    return is_state_calc;
}

void BreathEnemyRangeKeepMove::sub_7100340570() {
    if (auto* enemy = sead::DynamicCast<act::Enemy>(mActor)) {
        auto& link = enemy->getActorPartsActor(mBreathName_s.cstr());
        ksys::act::ActorConstDataAccess acc;
        ksys::act::acquireActor(&link, &acc);
        acc.sleep(ksys::act::BaseProc::SleepWakeReason::_0);
    }
}

// NON_MATCHING: the original branches on the Enemy cast result (keeping `enemy != nullptr` as a
// separate bool for the final check) where ours selects the pointer; regalloc follows
bool BreathEnemyRangeKeepMove::sub_710033FB98(sead::Heap* heap) {
    auto* actor = mActor;
    if (!actor)
        return false;

    auto* creator = ksys::act::ActorCreator::instance();
    if (creator && creator->isBlockSpawns())
        return true;

    auto* enemy = sead::DynamicCast<act::Enemy>(actor);
    if (enemy && enemy->getActorPartsActor(mBreathName_s.cstr()).hasProc())
        return true;

    ksys::act::InstParamPack pack;
    pack->addPosition(actor->getMtx().getTranslation());
    pack->add(s32(actor->getParam()->getRes().mGParamList->getAttack()->mPower.ref() *
                  *mAttackRatio_s),
              "AttackPower");
    pack->add(f32(*mEnlargeTime_s), "ScaleTime");
    pack->add(actor->getParam()->getRes().mGParamList->getAttack()->mRange.ref(), "Range");
    ksys::act::ActorCreator::addScale(pack, *mBreathSize_s);
    ksys::act::ActorCreator::setCreatePriorityState1(pack, actor);
    auto* breath = sead::DynamicCast<ksys::act::Actor>(ksys::act::ActorCreator::instance()->createActor(
        mBreathName_s.cstr(), ksys::act::ActorHeapUtil::instance()->getBaseProcHeap(), &pack, true,
        false));
    if (enemy && breath && enemy->sub_7100D3CED8(mBreathName_s.cstr(), heap)) {
        enemy->sub_7100D3D108(mBreathName_s.cstr(), breath);
        return true;
    }
    return false;
}

}  // namespace uking::ai
