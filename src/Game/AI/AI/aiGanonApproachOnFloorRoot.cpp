#include "Game/AI/AI/aiGanonApproachOnFloorRoot.h"
#include "KingSystem/ActorSystem/actAiInlineParam.h"
#include "KingSystem/ActorSystem/actActor.h"
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
