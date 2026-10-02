#include "Game/AI/AI/aiTargetPartsPos.h"
#include "Game/Actor/actEnemy.h"
#include "KingSystem/ActorSystem/actActorConstDataAccess.h"

namespace uking::ai {

TargetPartsPos::TargetPartsPos(const InitArg& arg) : TargetPosAI(arg) {}

TargetPartsPos::~TargetPartsPos() = default;

bool TargetPartsPos::init_(sead::Heap* heap) {
    return TargetPosAI::init_(heap);
}

void TargetPartsPos::enter_(ksys::act::ai::InlineParamPack* params) {
    TargetPosAI::enter_(params);
}

void TargetPartsPos::calc_() {
    TargetPosAI::calc_();
}

void TargetPartsPos::leave_() {
    TargetPosAI::leave_();
}

void TargetPartsPos::loadParams_() {
    TargetPosAI::loadParams_();
    getStaticParam(&mPartsName_s, "PartsName");
}

void TargetPartsPos::m35(sead::Vector3f* pos) {
    if (auto* enemy = sead::DynamicCast<act::Enemy>(mActor)) {
        auto& link = enemy->getActorPartsActor(mPartsName_s);
        if (link.hasProcInCalcState()) {
            ksys::act::ActorConstDataAccess accessor;
            ksys::act::acquireActor(&link, &accessor);
            accessor.getActorMtx().getTranslation(*pos);
        }
    }
}

}  // namespace uking::ai
