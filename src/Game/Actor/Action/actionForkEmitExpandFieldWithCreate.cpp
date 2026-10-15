#include "Game/Actor/Action/actionForkEmitExpandFieldWithCreate.h"
#include "KingSystem/ActorSystem/actActorLinkConstDataAccess.h"
#include "Game/Actor/actUnk_7100d3cd74.h"
#include "KingSystem/ActorSystem/actActor.h"
#include "Game/Actor/aiUnk_71005D6D10.h"
#include "KingSystem/ActorSystem/Profiles/actBullet.h"
#include "KingSystem/ActorSystem/actActorCreator.h"
#include "KingSystem/ActorSystem/actActorHeapUtil.h"
#include "KingSystem/ActorSystem/actActorParam.h"
#include "KingSystem/ActorSystem/actInstParamPack.h"
#include "KingSystem/Resource/Actor/resResourceGParamList.h"
#include "KingSystem/Resource/GeneralParamList/resGParamListObjectChemicalType.h"

namespace uking::action {

ForkEmitExpandFieldWithCreate::ForkEmitExpandFieldWithCreate(const InitArg& arg)
    : ForkEmitExpandField(arg) {}

ForkEmitExpandFieldWithCreate::~ForkEmitExpandFieldWithCreate() {
    auto* parts = mActor->m101();
    if (*mIsSetPartsLink_s && parts) {
        parts->sub_7100D3CFEC(mPartsKey_s);
    } else if (_a8.hasProc()) {
        ksys::act::ActorLinkConstDataAccess accessor;
        ksys::act::acquireActor(&_a8, &accessor);
        if (accessor.isStateSleep())
            accessor.deleteLater(ksys::act::BaseProc::DeleteReason::_0);
    }
}

// NON_MATCHING: parts checks, live registers and the debug-failure return use different scheduling.
bool ForkEmitExpandFieldWithCreate::init_(sead::Heap* heap) {
    if (!ForkEmitExpandField::init_(heap))
        return false;
    auto* actor = mActor;
    auto* parts = actor->m101();
    const auto* chemical = mActor->getParam()->getRes().mGParamList->getChemicalType();
    const sead::SafeString& name =
        chemical ? chemical->mEmitChemicalActor.ref() : sead::SafeString::cEmptyString;
    if (parts && *mIsSetPartsLink_s) {
        if (!parts->sub_7100D3CED8(mPartsKey_s, heap))
            return false;
        if (parts->getActorPartsActor(mPartsKey_s).hasProc())
            return true;
    }
    if (name.isEmpty())
        return true;
    ksys::act::InstParamPack params;
    params->addMatrix(actor->getMtx());
    ksys::act::ActorCreator::addScale(params, *mScale_s);
    params->add(*mScaleTime_s, "ScaleTime");
    params->add(*mIsReuseActor_s, "IsReuseActor");
    auto* creator = ksys::act::ActorCreator::instance();
    name.cstr();
    auto* created = creator->createActor(
        name.getStringTop(), ksys::act::ActorHeapUtil::instance()->getBaseProcHeap(),
        &params, true, false);
    if (!created)
        return sub_71005D6D10();
    if (auto* bullet = sead::DynamicCast<ksys::act::Bullet>(created)) {
        bullet->sub_710000497C(mActor);
        bullet->sub_71000048BC(mActor);
        bullet->_bd0._0.acquire(mActor, false);
    }
    if (parts && *mIsSetPartsLink_s)
        parts->sub_7100D3D108(mPartsKey_s, created);
    else
        _a8.acquire(created, false);
    return true;
}

void ForkEmitExpandFieldWithCreate::enter_(ksys::act::ai::InlineParamPack* params) {
    ForkEmitExpandField::enter_(params);
    sub_710014E780(&mActor->getMtx());
}

void ForkEmitExpandFieldWithCreate::leave_() {
    ForkEmitExpandField::leave_();
}

void ForkEmitExpandFieldWithCreate::loadParams_() {
    ForkEmitExpandField::loadParams_();
    getStaticParam(&mScaleTime_s, "ScaleTime");
    getStaticParam(&mIsReuseActor_s, "IsReuseActor");
    getStaticParam(&mIsSetPartsLink_s, "IsSetPartsLink");
}

void ForkEmitExpandFieldWithCreate::calc_() {
    ForkEmitExpandField::calc_();
}

ksys::act::BaseProcLink& ForkEmitExpandFieldWithCreate::m32() {
    auto* parts = mActor->m101();
    if (*mIsSetPartsLink_s && parts)
        return parts->getActorPartsActor(mPartsKey_s);
    return _a8;
}

}  // namespace uking::action
