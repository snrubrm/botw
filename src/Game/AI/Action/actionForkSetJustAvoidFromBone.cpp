#include "Game/AI/Action/actionForkSetJustAvoidFromBone.h"
#include <gsys/gsysModel.h>
#include <gsys/gsysModelAccessKey.h>
#include <gsys/gsysModelUnit.h>
#include "KingSystem/ActorSystem/actActor.h"
#include "KingSystem/Utils/MathUtil.h"

namespace uking::action {

ForkSetJustAvoidFromBone::ForkSetJustAvoidFromBone(const InitArg& arg) : ForkSetJustAvoid(arg) {}

// Empty-statement body as in upstream's GameDataFlagSelector::~GameDataFlagSelector() (96101229):
// the original keeps the vtable store that a defaulted destructor drops.
ForkSetJustAvoidFromBone::~ForkSetJustAvoidFromBone() {
    ;
}

bool ForkSetJustAvoidFromBone::init_(sead::Heap* heap) {
    return ForkSetJustAvoid::init_(heap);
}

void ForkSetJustAvoidFromBone::enter_(ksys::act::ai::InlineParamPack* params) {
    ForkSetJustAvoid::enter_(params);
}

void ForkSetJustAvoidFromBone::leave_() {
    ForkSetJustAvoid::leave_();
}

void ForkSetJustAvoidFromBone::loadParams_() {
    ForkSetJustAvoid::loadParams_();
    getStaticParam(&mTransBaseBoneName_s, "TransBaseBoneName");
    getStaticParam(&mRotBaseBoneName_s, "RotBaseBoneName");
    getStaticParam(&mBaseDir_s, "BaseDir");
}

void ForkSetJustAvoidFromBone::calc_() {
    ForkSetJustAvoid::calc_();
}

// NON_MATCHING: block layout only (the original places the matrix-front fallback of the direction / the actor
// translation before the bone-matrix paths, ours puts the bone paths first; the arithmetic is the same).
void ForkSetJustAvoidFromBone::m32(sead::Matrix34f* mtx) {
    auto* model = mActor->getModel();
    if (!model) {
        *mtx = mActor->getMtx();
        return;
    }

    sead::Matrix34f bone_mtx;
    sead::Vector3f dir;
    gsys::BoneAccessKey rot_key;
    if (!mRotBaseBoneName_s.isEmpty())
        rot_key = model->searchBone(mRotBaseBoneName_s);
    if (!rot_key.isValid()) {
        mActor->getMtx().getBase(dir, 2);
        dir.normalize();
    } else {
        model->getUnits().unsafeAt(rot_key.model_unit_index)->mModelUnit->getBoneWorldMatrix(&bone_mtx, rot_key.bone_index);
        dir.setMul(bone_mtx, *mBaseDir_s);
        dir.normalize();
    }

    sead::Vector3f pos;
    gsys::BoneAccessKey trans_key;
    if (!mTransBaseBoneName_s.isEmpty())
        trans_key = model->searchBone(mTransBaseBoneName_s);
    if (!trans_key.isValid()) {
        mActor->getMtx().getTranslation(pos);
    } else {
        model->getUnits().unsafeAt(trans_key.model_unit_index)->mModelUnit->getBoneWorldMatrix(&bone_mtx, trans_key.bone_index);
        bone_mtx.getTranslation(pos);
    }

    ksys::util::sub_71011F00EC(mtx, dir, sead::Vector3f::ey, pos, false);
}

}  // namespace uking::action
