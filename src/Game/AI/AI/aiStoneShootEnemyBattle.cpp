#include "Game/AI/AI/aiStoneShootEnemyBattle.h"
#include <random/seadGlobalRandom.h>
#include "KingSystem/ActorSystem/actActor.h"
#include "KingSystem/ActorSystem/actActorCreator.h"
#include "KingSystem/ActorSystem/actActorHeapUtil.h"
#include "KingSystem/ActorSystem/actAiInlineParam.h"
#include "KingSystem/ActorSystem/actInstParamPack.h"

namespace uking::ai {

StoneShootEnemyBattle::StoneShootEnemyBattle(const InitArg& arg) : EnemyBattle(arg) {}

StoneShootEnemyBattle::~StoneShootEnemyBattle() = default;

bool StoneShootEnemyBattle::init_(sead::Heap* heap) {
    return EnemyBattle::init_(heap);
}

void StoneShootEnemyBattle::enter_(ksys::act::ai::InlineParamPack* params) {
    EnemyBattle::enter_(params);
    mActor->resetConnectedCalcChild(false);

    ksys::act::InstParamPack pack;
    pack->addPosition(mActor->getMtx().getTranslation());
    // 0.8 + 0.4 * [0, 1): the constant pool holds 0.4f exactly, not 1.2f - 0.8f
    ksys::act::ActorCreator::addScale(pack, 0.8f + 0.4f * sead::GlobalRandom::instance()->getF32());
    m44(&_a0, &pack);
}

void StoneShootEnemyBattle::calc_() {
    EnemyBattle::calc_();
    if (isCurrentChild("戦闘攻撃"))
        return;

    if (_a0.hasProcCreationFailed())
        _a0.deleteProcIfFailed();
    else if (_a0.isAllocatedOrFailed())
        return;

    ksys::act::InstParamPack pack;
    pack->addPosition(mActor->getMtx().getTranslation());
    // 0.8 + 0.4 * [0, 1): the constant pool holds 0.4f exactly, not 1.2f - 0.8f
    ksys::act::ActorCreator::addScale(pack, 0.8f + 0.4f * sead::GlobalRandom::instance()->getF32());
    m44(&_a0, &pack);
}

void StoneShootEnemyBattle::leave_() {
    EnemyBattle::leave_();
    _a0.deleteProc();
    mActor->resetConnectedCalcChild(false);
}

void StoneShootEnemyBattle::loadParams_() {
    EnemyBattle::loadParams_();
    getStaticParam(&mShootItemName_s, "ShootItemName");
}

bool StoneShootEnemyBattle::m41() {
    return _a0.isProcReady();
}

void StoneShootEnemyBattle::m43(ksys::act::ai::InlineParamPack* params) {
    params->addPointer(&_a0, "IgniteHandle", ksys::AIDefParamType::BaseProcHandle, -1);
}

void StoneShootEnemyBattle::m44(ksys::act::BaseProcHandle* handle,
                                ksys::act::InstParamPack* params) {
    ksys::act::ActorCreator::instance()->requestCreateActor(
        mShootItemName_s.cstr(), ksys::act::ActorHeapUtil::instance()->getBaseProcHeap(), handle,
        params, nullptr, 1);
}

}  // namespace uking::ai
