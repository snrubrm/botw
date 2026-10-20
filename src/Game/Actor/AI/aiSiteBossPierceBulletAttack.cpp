#include "Game/Actor/AI/aiSiteBossPierceBulletAttack.h"
#include "Game/Actor/aiUnk_71005D6D10.h"
#include "Game/Actor/actSiteBoss.h"
#include <gsys/gsysModel.h>
#include <gsys/gsysModelUnit.h>
#include "KingSystem/ActorSystem/actActorLinkConstDataAccess.h"
#include "KingSystem/ActorSystem/actActorUtil.h"
#include "KingSystem/ActorSystem/actAiInlineParam.h"

namespace uking::ai {

SiteBossPierceBulletAttack::SiteBossPierceBulletAttack(const InitArg& arg)
    : SiteBossShootNormalArrowRoot(arg) {}

SiteBossPierceBulletAttack::~SiteBossPierceBulletAttack() = default;

bool SiteBossPierceBulletAttack::init_(sead::Heap* heap) {
    return SiteBossShootNormalArrowRoot::init_(heap);
}

void SiteBossPierceBulletAttack::enter_(ksys::act::ai::InlineParamPack* params) {
    SiteBossShootNormalArrowRoot::enter_(params);
    _338 = false;
}

void SiteBossPierceBulletAttack::leave_() {
    SiteBossShootNormalArrowRoot::leave_();
    if (auto* child = mActor->getConnectedCalcChild()) {
        child->sleep(ksys::act::BaseProc::SleepWakeReason::_0);
        mActor->resetConnectedCalcChild(false);
    }
    if (!_338)
        m41();
}

void SiteBossPierceBulletAttack::calc_() {
    SiteBossShootNormalArrowRoot::calc_();
    if (isCurrentChild("弾発射"))
        sub_71005D74E8(mActor);
}

bool SiteBossPierceBulletAttack::m34() {
    return sub_7100588164(false);
}

void SiteBossPierceBulletAttack::m37() {
    m41();
    ksys::act::ai::InlineParamPack params;
    sead::Vector3f target;
    m45(&target);
    params.addVec3(target, "TargetPos", -1);
    params.addPointer(nullptr, "ArrowHandle", ksys::AIDefParamType::BaseProcHandle, -1);
    if (auto* boss = sead::DynamicCast<act::SiteBoss>(mActor)) {
        params.addActor(*boss->_1560.sub_710066DE04(0), "IgniteActor", -1);
        params.addInt(_144, "Index", -1);
        params.addInt(m44(), "AtAttr", -1);
        changeChild("弾発射", &params);
    }
}

// NON_MATCHING: the original computes the length of the actor matrix's z axis without using it (only the sqrtf
// call for a NaN remains), and regalloc differs
void SiteBossPierceBulletAttack::m39() {
    auto* boss = sead::DynamicCast<act::SiteBoss>(mActor);
    if (!boss)
        return;
    boss->_1560.sub_710066C568(nullptr, 20);
    auto* actor = mActor;
    auto* link = boss->_1560.sub_710066DE04(0);
    if (!link->hasProc())
        return;

    sead::Matrix34f mtx;
    const auto key = mActor->getModel()->searchBone("Muzzle_A");
    if (key.isValid()) {
        actor->getModel()
            ->getUnits()
            .unsafeAt(key.model_unit_index)
            ->mModelUnit->getBoneWorldMatrix(&mtx, key.bone_index);
    } else {
        mtx = actor->getMtx();
    }

    ksys::act::ActorLinkConstDataAccess accessor;
    ksys::act::acquireActor(link, &accessor);
    accessor.setThisActorAsChild(actor, false);
    accessor.setProperties(mtx, nullptr, nullptr, nullptr, false, 0, -1);
}

void SiteBossPierceBulletAttack::m40() {
    if (auto* boss = sead::DynamicCast<act::SiteBoss>(mActor))
        boss->_1560.sub_710066C590(nullptr, 20);
}

void SiteBossPierceBulletAttack::m41() {
    if (auto* boss = sead::DynamicCast<act::SiteBoss>(mActor)) {
        boss->_1560.sub_710066C5B8(nullptr, 20);
        _338 = true;
    }
}

s32 SiteBossPierceBulletAttack::m44() {
    return 12;
}

void SiteBossPierceBulletAttack::m50(ksys::act::BaseProc* proc, s32 idx) {
    if (auto* boss = sead::DynamicCast<act::SiteBoss>(mActor))
        boss->_1560.sub_710066DB98(proc, idx);
}

}  // namespace uking::ai
