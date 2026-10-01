#include "Game/AI/AI/aiEarthReleaseAttack.h"
#include "KingSystem/ActorSystem/actActor.h"
#include "KingSystem/ActorSystem/actAiInlineParam.h"
#include "KingSystem/ActorSystem/actActorCreator.h"
#include "KingSystem/ActorSystem/actActorHeapUtil.h"

namespace uking::ai {

EarthReleaseAttack::EarthReleaseAttack(const InitArg& arg) : ksys::act::ai::Ai(arg) {}

EarthReleaseAttack::~EarthReleaseAttack() = default;

bool EarthReleaseAttack::init_(sead::Heap* heap) {
    return ksys::act::ai::Ai::init_(heap);
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

}  // namespace uking::ai
