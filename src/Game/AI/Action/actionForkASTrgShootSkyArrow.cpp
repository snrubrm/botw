#include "Game/AI/Action/actionForkASTrgShootSkyArrow.h"
#include <gsys/gsysModel.h>
#include <gsys/gsysModelUnit.h>
#include "KingSystem/ActorSystem/actActor.h"
#include "Game/Actor/actWeapon.h"
#include "Game/AI/aiUnk_71005D6D10.h"

namespace uking::action {

ForkASTrgShootSkyArrow::ForkASTrgShootSkyArrow(const InitArg& arg) : ksys::act::ai::Action(arg) {}

ForkASTrgShootSkyArrow::~ForkASTrgShootSkyArrow() = default;

bool ForkASTrgShootSkyArrow::init_(sead::Heap* heap) {
    return ksys::act::ai::Action::init_(heap);
}

void ForkASTrgShootSkyArrow::enter_(ksys::act::ai::InlineParamPack* params) {
    mFlags.set(Flag::Changeable);
    _58 = false;
}

void ForkASTrgShootSkyArrow::leave_() {
    sub_71005D787C(mActor, *mWeaponIdx_s, act::Unk_71002eda38(5));
}

void ForkASTrgShootSkyArrow::loadParams_() {
    getStaticParam(&mWeaponIdx_s, "WeaponIdx");
    getStaticParam(&mSeqBank_s, "SeqBank");
    getStaticParam(&mTargetBone_s, "TargetBone");
    getStaticParam(&mBaseBoneName_s, "BaseBoneName");
    getStaticParam(&mFrontDirOfBaseBone_s, "FrontDirOfBaseBone");
    getDynamicParam(&mTargetActor_d, "TargetActor");
}

// NON_MATCHING: same flow, but the original places the actor-matrix copy before the bone matrix call and keeps
// the normalised direction in different registers.
void ForkASTrgShootSkyArrow::sub_7100144CB4(sead::Vector3f* out) {
    auto* model = mActor->getModel();
    sead::Matrix34f mtx;
    bool found = false;
    if (model && !mBaseBoneName_s.isEmpty()) {
        const auto key = model->searchBone(mBaseBoneName_s);
        if (key.isValid()) {
            model->getUnits().unsafeAt(key.model_unit_index)->mModelUnit->getBoneWorldMatrix(&mtx, key.bone_index);
            found = true;
        }
    }
    if (!found)
        mtx = mActor->getMtx();
    sead::Vector3f dir = *mFrontDirOfBaseBone_s;
    dir.normalize();
    dir *= 100.0f;
    *out = sead::Vector3f(
        mtx.m[0][3] + dir.x * mtx.m[0][0] + dir.y * mtx.m[0][1] + dir.z * mtx.m[0][2],
        mtx.m[1][3] + dir.x * mtx.m[1][0] + dir.y * mtx.m[1][1] + dir.z * mtx.m[1][2],
        mtx.m[2][3] + dir.x * mtx.m[2][0] + dir.y * mtx.m[2][1] + dir.z * mtx.m[2][2]);
}

void ForkASTrgShootSkyArrow::calc_() {
    ksys::act::ai::Action::calc_();
}

}  // namespace uking::action
