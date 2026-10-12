#include "Game/AI/Action/actionForkASTrgEmitChmFieldPos.h"
#include "Game/AI/aiUnk_71005D6D10.h"
#include "KingSystem/ActorSystem/actActor.h"

namespace uking::action {

ForkASTrgEmitChmFieldPos::ForkASTrgEmitChmFieldPos(const InitArg& arg) : ForkTrgEmitChmFieldBase(arg) {}

ForkASTrgEmitChmFieldPos::~ForkASTrgEmitChmFieldPos() = default;

bool ForkASTrgEmitChmFieldPos::init_(sead::Heap* heap) {
    return ForkTrgEmitChmFieldBase::init_(heap);
}

void ForkASTrgEmitChmFieldPos::enter_(ksys::act::ai::InlineParamPack* params) {
    ForkTrgEmitChmFieldBase::enter_(params);
}

void ForkASTrgEmitChmFieldPos::leave_() {
    ForkTrgEmitChmFieldBase::leave_();
}

void ForkASTrgEmitChmFieldPos::loadParams_() {
    ForkTrgEmitChmFieldBase::loadParams_();
    getStaticParam(&mOffsetPos_s, "OffsetPos");
}

void ForkASTrgEmitChmFieldPos::calc_() {
    ForkTrgEmitChmFieldBase::calc_();
}

bool ForkASTrgEmitChmFieldPos::m34(sead::Matrix34f* mtx) {
    if (!sub_71005DD780(mActor, 71, nullptr, 0, 0))
        return false;

    const auto& actor_mtx = mActor->getMtx();
    const sead::Vector3f pos = actor_mtx * *mOffsetPos_s;
    *mtx = actor_mtx;
    mtx->setTranslation(pos);
    return true;
}

}  // namespace uking::action
