#include "Game/AI/Action/actionOffMiss.h"
#include "KingSystem/ActorSystem/actActorUtil.h"

namespace uking::action {

OffMiss::OffMiss(const InitArg& arg) : Off(arg) {}

OffMiss::~OffMiss() = default;

bool OffMiss::init_(sead::Heap* heap) {
    return Off::init_(heap);
}

void OffMiss::enter_(ksys::act::ai::InlineParamPack* params) {
    Off::enter_(params);
    ksys::act::sub_7100EE3CAC(mActor, 0x08000080, nullptr);
}

void OffMiss::leave_() {
    Off::leave_();
}

void OffMiss::loadParams_() {
    Off::loadParams_();
}

void OffMiss::calc_() {
    Off::calc_();
}

}  // namespace uking::action
