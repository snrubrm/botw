#include "Game/AI/AI/aiAirOctaBoardBurn.h"
#include "Game/AI/AI/AirOcta/AirOctaDataMgr.h"
#include "KingSystem/ActorSystem/actActor.h"
#include "KingSystem/ActorSystem/actActorConstDataAccess.h"
#include "KingSystem/ActorSystem/actActorUtil.h"
#include "KingSystem/ActorSystem/actAiInlineParam.h"

namespace uking::ai {

AirOctaBoardBurn::AirOctaBoardBurn(const InitArg& arg) : SeqTwoAction(arg) {}

AirOctaBoardBurn::~AirOctaBoardBurn() = default;

bool AirOctaBoardBurn::init_(sead::Heap* heap) {
    return SeqTwoAction::init_(heap);
}

void AirOctaBoardBurn::enter_(ksys::act::ai::InlineParamPack* params) {
    auto* mgr = sead::DynamicCast<AirOctaDataMgr>(*static_cast<Unk_71025afb58**>(mAirOctaDataMgr_a));
    sead::Vector3f pos = sead::Vector3f::zero;
    ksys::act::ActorConstDataAccess accessor;
    if (mgr && ksys::act::acquireActor(&mgr->mBaseProcLink2, &accessor) && accessor.hasProc())
        accessor.getActorMtx().getTranslation(pos);
    ksys::act::ai::InlineParamPack pack;
    pack.addVec3(pos, "TargetPos", -1);
    SeqTwoAction::enter_(&pack);
}

void AirOctaBoardBurn::leave_() {
    SeqTwoAction::leave_();
}

void AirOctaBoardBurn::loadParams_() {
    SeqTwoAction::loadParams_();
    getAITreeVariable(&mAirOctaDataMgr_a, "AirOctaDataMgr");
}

void AirOctaBoardBurn::calc_() {
    SeqTwoAction::calc_();
    if (isCurrentChild("先行動"))
        mActor->m93(4, 0.0f);
    else
        mActor->m93(0, 0.0f);
}

}  // namespace uking::ai
