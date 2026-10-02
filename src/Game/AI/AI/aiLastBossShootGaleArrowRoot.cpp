#include "Game/AI/AI/aiLastBossShootGaleArrowRoot.h"
#include <gsys/gsysModel.h>
#include <gsys/gsysModelUnit.h>
#include <prim/seadSafeString.h>
#include "Game/Actor/actEnemy.h"
#include "KingSystem/ActorSystem/actActorConstDataAccess.h"

namespace uking::ai {

static sead::Vector3f sUnk_7102402898(0, sead::Mathf::pi(), 0);

LastBossShootGaleArrowRoot::LastBossShootGaleArrowRoot(const InitArg& arg)
    : LastBossShootNormalArrowRoot(arg) {}

LastBossShootGaleArrowRoot::~LastBossShootGaleArrowRoot() = default;

bool LastBossShootGaleArrowRoot::init_(sead::Heap* heap) {
    return LastBossShootNormalArrowRoot::init_(heap);
}

void LastBossShootGaleArrowRoot::enter_(ksys::act::ai::InlineParamPack* params) {
    LastBossShootNormalArrowRoot::enter_(params);

    auto* enemy = sead::DynamicCast<act::Enemy>(mActor);
    if (!enemy)
        return;

    sead::FormatFixedSafeString<32> name("%s%d", mPartsName_s.cstr(), _a0);
    ksys::act::ActorConstDataAccess accessor;
    ksys::act::acquireActor(&enemy->getActorPartsActor(name), &accessor);
    if (!accessor.hasProc())
        return;

    sead::Matrix34f mtx;
    const auto key = mActor->getModel()->searchBone("Wrist_ML");
    if (key.isValid()) {
        mActor->getModel()
            ->getUnits()
            .unsafeAt(key.model_unit_index)
            ->mModelUnit->getBoneWorldMatrix(&mtx, key.bone_index);
    } else {
        mtx = mActor->getMtx();
    }

    sead::Vector3f pos = mtx.getTranslation();
    const sead::Matrix33f rot_mtx(mtx);
    sead::Matrix34f rot;
    rot.makeR(sUnk_7102402898);
    sead::Vector3f offset = {0, 0, 4};
    offset.rotate(rot_mtx);
    offset.rotate(rot);
    pos += offset;

    accessor.setThisActorAsChild(mActor, false);
    accessor.setProperties(sead::Matrix34f(rot_mtx, pos), nullptr, nullptr, nullptr, false, 0, -1);
}

void LastBossShootGaleArrowRoot::calc_() {
    LastBossShootNormalArrowRoot::calc_();
}

void LastBossShootGaleArrowRoot::leave_() {
    LastBossShootNormalArrowRoot::leave_();
    if (_a0 != 0)
        return;

    if (auto* enemy = sead::DynamicCast<act::Enemy>(mActor)) {
        sead::FormatFixedSafeString<32> name("%s%d", mPartsName_s.cstr(), _a0);
        if (enemy->getActorPartsActor(name).hasProcInCalcState()) {
            ksys::act::ActorConstDataAccess accessor;
            ksys::act::acquireActor(&enemy->getActorPartsActor(name), &accessor);
            accessor.sleep(ksys::act::BaseProc::SleepWakeReason::_0);
        }
    }
    if (mActor->getConnectedCalcChild())
        mActor->resetConnectedCalcChild(false);
}

void LastBossShootGaleArrowRoot::loadParams_() {
    LastBossShootNormalArrowRoot::loadParams_();
}

}  // namespace uking::ai
