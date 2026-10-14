#include "Game/Actor/AI/aiGanonApproachOnFloorRoot.h"
#include "KingSystem/ActorSystem/actAiInlineParam.h"
#include "KingSystem/ActorSystem/actActor.h"
#include "Game/Actor/aiUnk_71007377D4.h"
#include <math/seadQuat.h>
#include <math/seadMatrix.h>
#include "KingSystem/Physics/System/physRayCastForRequest.h"

namespace uking::ai {

GanonApproachOnFloorRoot::GanonApproachOnFloorRoot(const InitArg& arg) : ksys::act::ai::Ai(arg) {
    for (auto*& request : _f8)
        request = nullptr;
}

GanonApproachOnFloorRoot::~GanonApproachOnFloorRoot() = default;

bool GanonApproachOnFloorRoot::init_(sead::Heap* heap) {
    if (mActor->getModel())
        _258.search(mActor->getModel(), "Head");
    else
        _258.getKey().reset();
    return true;
}

void GanonApproachOnFloorRoot::enter_(ksys::act::ai::InlineParamPack* params) {
    ksys::act::ai::Ai::enter_(params);
}

// NON_MATCHING: operand order of the rotation products (the original multiplies matrix element * component) and
// scheduling
void GanonApproachOnFloorRoot::sub_71003E056C(const sead::Vector3f& dir) {
    sead::Vector3f origin;
    mActor->getMtx().getTranslation(origin);
    origin.y += 1.2f;
    _120[_f0] = origin;
    const f32 angles[5] = {*mCheckPosAng0_s, *mCheckPosAng1_s, *mCheckPosAng2_s, *mCheckPosAng3_s,
                           *mCheckPosAng4_s};
    for (int i = 0; i < 5; ++i) {
        sead::Quatf q;
        q.setAxisRadian(sead::Vector3f::ey, angles[i]);
        sead::Matrix34f mtx;
        mtx.fromQuat(q);
        sead::Vector3f rotated;
        rotated.setRotated(mtx, dir);
        sead::Vector3f end = origin + rotated * 20.0f;
        sub_710072EC24(_f8[i], origin, end, ksys::phys::RayCast::NormalCheckingMode::_0, 0.5f);
        _15c[_f0 * 5 + i] = end;
    }
}

void GanonApproachOnFloorRoot::leave_() {
    for (auto*& request : _f8) {
        if (request && !request->isRequestFinished()) {
            request->release();
            request = nullptr;
        }
    }
}

void GanonApproachOnFloorRoot::loadParams_() {
    getStaticParam(&mFinDist_s, "FinDist");
    getStaticParam(&mApproachTime_s, "ApproachTime");
    getStaticParam(&mFinFarDist_s, "FinFarDist");
    getStaticParam(&mMoveFrontRate_s, "MoveFrontRate");
    getStaticParam(&mMoveFrontLRRate_s, "MoveFrontLRRate");
    getStaticParam(&mMoveBackLRRate_s, "MoveBackLRRate");
    getStaticParam(&mCloseDist_s, "CloseDist");
    getStaticParam(&mForbitAngMin_s, "ForbitAngMin");
    getStaticParam(&mForbitAngMax_s, "ForbitAngMax");
    getStaticParam(&mCheckPosAng0_s, "CheckPosAng0");
    getStaticParam(&mCheckPosAng1_s, "CheckPosAng1");
    getStaticParam(&mCheckPosAng2_s, "CheckPosAng2");
    getStaticParam(&mCheckPosAng3_s, "CheckPosAng3");
    getStaticParam(&mCheckPosAng4_s, "CheckPosAng4");
    getDynamicParam(&mIsMoveSide_d, "IsMoveSide");
    getDynamicParam(&mIsChangeable_d, "IsChangeable");
    getDynamicParam(&mTargetPos_d, "TargetPos");
    getDynamicParam(&mMoveDstPos_d, "MoveDstPos");
}

void GanonApproachOnFloorRoot::changeToMove(const sead::Vector3f& pos, const sead::Vector3f& dst_pos) {
    ksys::act::ai::InlineParamPack pack;
    pack.addVec3(pos, "TargetPos", -1);
    pack.addVec3(dst_pos, "DstPos", -1);
    pack.addBool(*mIsChangeable_d, "IsChangeable", -1);
    changeChild("移動", &pack);
}

}  // namespace uking::ai
