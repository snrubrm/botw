#include "Game/AI/Action/actionCreateGanonChemicalPillar.h"
#include "Game/AI/aiUnk_71005D6D10.h"
#include "KingSystem/ActorSystem/actActorConstDataAccess.h"
#include "KingSystem/ActorSystem/actActorCreator.h"
#include "KingSystem/ActorSystem/actActorHeapUtil.h"
#include "KingSystem/ActorSystem/actActor.h"
#include "KingSystem/ActorSystem/actInstParamPack.h"

namespace uking::action {

CreateGanonChemicalPillar::CreateGanonChemicalPillar(const InitArg& arg)
    : ksys::act::ai::Action(arg) {}

CreateGanonChemicalPillar::~CreateGanonChemicalPillar() {
    ksys::act::ActorConstDataAccess accessor;
    ksys::act::acquireActor(&_58, &accessor);
    accessor.deleteLater(ksys::act::BaseProc::DeleteReason::_0);
}

// NON_MATCHING: one scheduling difference — the original saves the created proc to x20 after
// loading the DynamicCast guard byte where ours saves it immediately before (independent
// operations in different order). Calls, branch structure, constants identical.
bool CreateGanonChemicalPillar::init_(sead::Heap* heap) {
    if (!sub_71005D6D10()) {
        ksys::act::InstParamPack params;
        params->add(*mAttackPower_s + *mAddAtkPower_m, "AttackPower");
        params->add(*mScaleTime_s, "ScaleTime");
        ksys::act::ActorCreator::addScale(params, 1.0f);
        params->add(*mAtMinDamage_s, "AtMinDamage");
        auto* creator = ksys::act::ActorCreator::instance();
        mCreateActorName_s.cstr();
        auto* proc = creator->createActor(mCreateActorName_s.getStringTop(),
                                          ksys::act::ActorHeapUtil::instance()->getBaseProcHeap(),
                                          &params, true, false);
        if (!proc)
            return false;

        auto* actor = sead::DynamicCast<ksys::act::Actor>(proc);
        if (!actor)
            return false;

        actor->getActorFlags2().set(ksys::act::Actor::ActorFlag2::_2000);
        _58.acquire(actor, false);
        return true;
    }
    return true;
}

void CreateGanonChemicalPillar::enter_(ksys::act::ai::InlineParamPack* params) {
    ksys::act::ai::Action::enter_(params);
}

void CreateGanonChemicalPillar::leave_() {
    ksys::act::ai::Action::leave_();
}

void CreateGanonChemicalPillar::loadParams_() {
    getStaticParam(&mAttackPower_s, "AttackPower");
    getStaticParam(&mAtMinDamage_s, "AtMinDamage");
    getStaticParam(&mScaleTime_s, "ScaleTime");
    getStaticParam(&mMaxScale_s, "MaxScale");
    getStaticParam(&mCreateActorName_s, "CreateActorName");
    getMapUnitParam(&mAddAtkPower_m, "AddAtkPower");
}

void CreateGanonChemicalPillar::calc_() {
    // NON_MATCHING: the original copies sead::Matrix34f::ident with scalar ldp/stp pairs and the locals are
    // laid out differently; (ours uses 16-byte vector copies)
    if (!_58.hasProc())
        return;
    ksys::act::ActorConstDataAccess accessor;
    ksys::act::acquireActor(&_58, &accessor);
    sead::Matrix34f mtx = sead::Matrix34f::ident;
    const sead::Vector3f pos = mActor->getMtx().getTranslation();
    mtx.setTranslation(pos.x, pos.y + 1.0f, pos.z);
    const sead::Vector3f scale{*mMaxScale_s, *mMaxScale_s, *mMaxScale_s};
    accessor.setProperties(mtx, nullptr, nullptr, &scale, false, 0, -1);
    mActor->sleep(ksys::act::BaseProc::SleepWakeReason(0));
}

}  // namespace uking::action
