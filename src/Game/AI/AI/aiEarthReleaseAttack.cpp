#include "Game/AI/AI/aiEarthReleaseAttack.h"
#include "Game/AI/aiUnk_71005D6D10.h"
#include "Game/Actor/actEnemy.h"
#include "KingSystem/ActorSystem/actActor.h"
#include "KingSystem/ActorSystem/actAiInlineParam.h"
#include "KingSystem/ActorSystem/actActorCreator.h"
#include "KingSystem/ActorSystem/actActorHeapUtil.h"
#include "KingSystem/ActorSystem/actAiParam.h"

namespace uking::ai {

EarthReleaseAttack::EarthReleaseAttack(const InitArg& arg) : ksys::act::ai::Ai(arg) {}

EarthReleaseAttack::~EarthReleaseAttack() {
    if (_80.isAllocatedOrFailed())
        _80.deleteProc();
    if (auto* enemy = sead::DynamicCast<act::Enemy>(mActor))
        enemy->sub_7100D3CFEC(mEarthReleasePartsName_s);
}

bool EarthReleaseAttack::init_(sead::Heap* heap) {
    if (auto* enemy = sead::DynamicCast<act::Enemy>(mActor))
        enemy->sub_7100D3CED8(mEarthReleasePartsName_s, heap);
    return true;
}

void EarthReleaseAttack::enter_(ksys::act::ai::InlineParamPack* params) {
    sub_710037BC08();
    sub_710037BDF0();
}

void EarthReleaseAttack::sub_710037BC08() {
    if (_80.isAllocatedOrFailed())
        return;

    if (_80.hasProcCreationFailed())
        _80.deleteProcIfFailed();

    ksys::act::InstParamPack pack;
    m34(pack);
    ksys::act::ActorCreator::instance()->requestCreateActor(
        mEarthReleaseActorName_s.cstr(), ksys::act::ActorHeapUtil::instance()->getBaseProcHeap(),
        &_80, &pack, nullptr, 2);
}

// NON_MATCHING: scheduling of the "@P" key setup
void EarthReleaseAttack::m34(ksys::act::InstParamPack& pack) {
    pack->addPosition(mActor->getMtx().getTranslation());
    pack->add(*mAttackPower_s, "AttackPower");
    pack->add(*mEnlargeTime_s, "ScaleTime");
    pack->add(*mRange_s, "Range");
    ksys::act::ActorCreator::addScale(pack, *mScale_s);
}

void EarthReleaseAttack::calc_() {
    if (_80.hasProcCreationFailed())
        _80.deleteProcIfFailed();
    if (!_80.isAllocatedOrFailed())
        sub_710037BC08();

    if (isFinished() || isFailed())
        return;

    auto* child = getCurrentChild();
    if (!child || (!child->isFinished() && !child->isFailed()))
        return;

    child->isFailed();
    if (*mUseAfterAction_s && isCurrentChild("先行動")) {
        ksys::act::ai::InlineParamPack pack;
        changeChild("後行動", &pack);
    } else {
        setFinished();
    }
}

void EarthReleaseAttack::leave_() {
    _80.deleteProc();
}

void EarthReleaseAttack::loadParams_() {
    getStaticParam(&mAttackPower_s, "AttackPower");
    getStaticParam(&mEnlargeTime_s, "EnlargeTime");
    getStaticParam(&mRange_s, "Range");
    getStaticParam(&mScale_s, "Scale");
    getStaticParam(&mUseAfterAction_s, "UseAfterAction");
    getStaticParam(&mEarthReleaseActorName_s, "EarthReleaseActorName");
    getStaticParam(&mEarthReleasePartsName_s, "EarthReleasePartsName");
}

void EarthReleaseAttack::sub_710037BDF0() {
    ksys::act::ai::InlineParamPack pack;
    pack.addPointer(&_80, "IgniteHandle", ksys::AIDefParamType::BaseProcHandle, -1);
    pack.addVec3(sub_71005D9330(mActor), "TargetPos", -1);
    changeChild("先行動", &pack);
}

}  // namespace uking::ai
