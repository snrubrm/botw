#include "Game/Actor/Action/actionDRCAppNoUseTag.h"
#include "KingSystem/ActorSystem/actActor.h"
#include "Game/UI/uiUtils.h"

namespace uking::action {

DRCAppNoUseTag::DRCAppNoUseTag(const InitArg& arg) : BasicSignalForbidTag(arg) {}

DRCAppNoUseTag::~DRCAppNoUseTag() = default;

bool DRCAppNoUseTag::init_(sead::Heap* heap) {
    return BasicSignalForbidTag::init_(heap);
}

void DRCAppNoUseTag::enter_(ksys::act::ai::InlineParamPack* params) {
    BasicSignalForbidTag::enter_(params);
}

void DRCAppNoUseTag::leave_() {
    BasicSignalForbidTag::leave_();
}

void DRCAppNoUseTag::loadParams_() {
    BasicSignalForbidTag::loadParams_();
    getMapUnitParam(&mDRCAppNoUseCause_m, "DRCAppNoUseCause");
}

void DRCAppNoUseTag::calc_() {
    BasicSignalForbidTag::calc_();
}

void DRCAppNoUseTag::m32() {
    ui::sub_7100A9C0FC(*mDRCAppNoUseCause_m);
    mActor->m107();
}

}  // namespace uking::action
