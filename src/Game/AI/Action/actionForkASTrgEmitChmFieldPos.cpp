#include "Game/AI/Action/actionForkASTrgEmitChmFieldPos.h"
#include "Game/AI/aiUnk_71005D6D10.h"
#include "KingSystem/ActorSystem/actActor.h"

namespace uking::action {

ForkASTrgEmitChmFieldPos::ForkASTrgEmitChmFieldPos(const InitArg& arg) : ForkEmitChmField(arg) {}

ForkASTrgEmitChmFieldPos::~ForkASTrgEmitChmFieldPos() = default;

bool ForkASTrgEmitChmFieldPos::init_(sead::Heap* heap) {
    return ForkEmitChmField::init_(heap);
}

void ForkASTrgEmitChmFieldPos::enter_(ksys::act::ai::InlineParamPack* params) {
    ForkEmitChmField::enter_(params);
}

void ForkASTrgEmitChmFieldPos::leave_() {
    ForkEmitChmField::leave_();
}

void ForkASTrgEmitChmFieldPos::loadParams_() {
    ForkEmitChmField::loadParams_();
    getStaticParam(&mOffsetPos_s, "OffsetPos");
}

void ForkASTrgEmitChmFieldPos::calc_() {
    ForkEmitChmField::calc_();
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
