#include "Game/AI/Action/actionForkASTrgEmitShockWavePos.h"
#include "Game/AI/aiUnk_71005D6D10.h"
#include "KingSystem/ActorSystem/actActor.h"

namespace uking::action {

ForkASTrgEmitShockWavePos::ForkASTrgEmitShockWavePos(const InitArg& arg)
    : ForkASTrgEmitShockWave(arg) {}

ForkASTrgEmitShockWavePos::~ForkASTrgEmitShockWavePos() = default;

bool ForkASTrgEmitShockWavePos::init_(sead::Heap* heap) {
    return ForkASTrgEmitShockWave::init_(heap);
}

void ForkASTrgEmitShockWavePos::enter_(ksys::act::ai::InlineParamPack* params) {
    ForkASTrgEmitShockWave::enter_(params);
}

void ForkASTrgEmitShockWavePos::leave_() {
    ForkASTrgEmitShockWave::leave_();
}

void ForkASTrgEmitShockWavePos::loadParams_() {
    ForkASTrgEmitShockWave::loadParams_();
    getStaticParam(&mOffsetPos_s, "OffsetPos");
}

void ForkASTrgEmitShockWavePos::calc_() {
    ForkASTrgEmitShockWave::calc_();
}

bool ForkASTrgEmitShockWavePos::m33(sead::Matrix34f* mtx) {
    if (!sub_71005DD780(mActor, 0x3b, nullptr, 0, 0))
        return false;

    const sead::Matrix34f& actor_mtx = mActor->getMtx();
    const sead::Vector3f pos = actor_mtx * *mOffsetPos_s;
    *mtx = actor_mtx;
    mtx->setTranslation(pos);
    return true;
}

}  // namespace uking::action
