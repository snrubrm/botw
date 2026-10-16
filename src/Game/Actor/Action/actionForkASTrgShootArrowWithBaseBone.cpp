#include "Game/Actor/Action/actionForkASTrgShootArrowWithBaseBone.h"
#include <gsys/gsysModel.h>
#include <math/seadQuat.h>
#include "Game/Actor/aiUnk_71005D6D10.h"
#include "KingSystem/ActorSystem/actActor.h"
#include "KingSystem/Utils/MathUtil.h"

namespace uking::action {

ForkASTrgShootArrowWithBaseBone::ForkASTrgShootArrowWithBaseBone(const InitArg& arg)
    : ForkASTrgShootArrow(arg) {}

// Empty-statement body as in upstream's GameDataFlagSelector::~GameDataFlagSelector() (96101229):
// the original keeps the vtable store that a defaulted destructor drops.
ForkASTrgShootArrowWithBaseBone::~ForkASTrgShootArrowWithBaseBone() {
    ;
}

bool ForkASTrgShootArrowWithBaseBone::init_(sead::Heap* heap) {
    return ForkASTrgShootArrow::init_(heap);
}

void ForkASTrgShootArrowWithBaseBone::enter_(ksys::act::ai::InlineParamPack* params) {
    ForkASTrgShootArrow::enter_(params);
}

void ForkASTrgShootArrowWithBaseBone::leave_() {
    ForkASTrgShootArrow::leave_();
}

void ForkASTrgShootArrowWithBaseBone::loadParams_() {
    ForkASTrgShootArrow::loadParams_();
    getStaticParam(&mFrontDirAngle_s, "FrontDirAngle");
    getStaticParam(&mIsAddTargetActorAimPosHeight_s, "IsAddTargetActorAimPosHeight");
    getStaticParam(&mBaseBoneName_s, "BaseBoneName");
    getStaticParam(&mFrontDirOfBaseBone_s, "FrontDirOfBaseBone");
}

void ForkASTrgShootArrowWithBaseBone::calc_() {
    ForkASTrgShootArrow::calc_();
}

// Aims along the front direction of the base bone, turned towards the target by at most FrontDirAngle.
void ForkASTrgShootArrowWithBaseBone::m32(sead::Vector3f* dir) {
    auto* model = mActor->getModel();
    if (!model)
        return ForkASTrgShootArrow::m32(dir);
    const gsys::BoneAccessKey key = model->searchBone(mBaseBoneName_s);
    if (!key.isValid())
        return ForkASTrgShootArrow::m32(dir);

    sead::Vector3f front = *mFrontDirOfBaseBone_s;
    front.normalize();
    sead::Matrix34f mtx;
    model->getBoneWorldMatrix(key, &mtx);
    front.rotate(mtx);

    const sead::Vector3f pos = mActor->getMtx().getTranslation();
    sead::Vector3f target = *mTargetPos_d;
    if (*mIsAddTargetActorAimPosHeight_s)
        target.y += sub_71005D93CC(mActor).y - sub_71005D9330(mActor).y;
    target -= pos;
    target.normalize();

    sead::Vector3f axis;
    f32 angle;
    ksys::util::sub_71011EEB08(&axis, &angle, front, target, sead::Vector3f::ey);
    if (angle <= *mFrontDirAngle_s) {
        front = target;
    } else {
        sead::Quatf q;
        q.setAxisRadian(axis, *mFrontDirAngle_s);
        sead::Matrix34f rot;
        rot.fromQuat(q);
        front.rotate(rot);
    }
    *dir = front;
}

}  // namespace uking::action
