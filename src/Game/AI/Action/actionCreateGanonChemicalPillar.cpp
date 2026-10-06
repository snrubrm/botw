#include "Game/AI/Action/actionCreateGanonChemicalPillar.h"
#include "KingSystem/ActorSystem/actActorConstDataAccess.h"
#include "KingSystem/ActorSystem/actActor.h"

namespace uking::action {

CreateGanonChemicalPillar::CreateGanonChemicalPillar(const InitArg& arg)
    : ksys::act::ai::Action(arg) {}

CreateGanonChemicalPillar::~CreateGanonChemicalPillar() {
    ksys::act::ActorConstDataAccess accessor;
    ksys::act::acquireActor(&_58, &accessor);
    accessor.deleteLater(ksys::act::BaseProc::DeleteReason::_0);
}

bool CreateGanonChemicalPillar::init_(sead::Heap* heap) {
    return ksys::act::ai::Action::init_(heap);
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
