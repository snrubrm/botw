#include "Game/AI/Action/actionSiteBossCreateChildDevice.h"
#include "Game/AI/aiUnk_71005D6D10.h"
#include "Game/Actor/actSiteBoss.h"
#include "KingSystem/ActorSystem/AS/ASList.h"
#include "KingSystem/ActorSystem/actActor.h"

namespace uking::action {

SiteBossCreateChildDevice::SiteBossCreateChildDevice(const InitArg& arg)
    : ksys::act::ai::Action(arg) {}

SiteBossCreateChildDevice::~SiteBossCreateChildDevice() = default;

bool SiteBossCreateChildDevice::init_(sead::Heap* heap) {
    return ksys::act::ai::Action::init_(heap);
}

void SiteBossCreateChildDevice::enter_(ksys::act::ai::InlineParamPack* params) {
    ksys::act::ai::Action::enter_(params);
}

void SiteBossCreateChildDevice::leave_() {
    mActor->getASList()->sub_710115B01C(3, 0, true);
    mActor->getASList()->sub_710115B01C(4, 0, true);
    mActor->getASList()->sub_710115B01C(5, 0, true);
    mActor->getASList()->sub_710115B01C(6, 0, true);
    mActor->getASList()->sub_710115C11C();
    if (_41)
        return;

    auto* target = sub_71005D9050(mActor);
    if (!target || !target->hasProcInCalcState())
        return;
    if (auto* boss = sead::DynamicCast<act::SiteBoss>(mActor))
        boss->_1560.sub_710066C518(target, 20);
}

void SiteBossCreateChildDevice::loadParams_() {
    getDynamicParam(&mIsCreateA_d, "IsCreateA");
    getDynamicParam(&mIsCreateB_d, "IsCreateB");
    getDynamicParam(&mIsCreateC_d, "IsCreateC");
    getDynamicParam(&mIsCreateD_d, "IsCreateD");
}

void SiteBossCreateChildDevice::calc_() {
    ksys::act::ai::Action::calc_();
}

int SiteBossCreateChildDevice::m32() {
    return (*mIsCreateA_d ? 1 : 0) | (*mIsCreateB_d ? 2 : 0) | (*mIsCreateC_d ? 4 : 0) | (*mIsCreateD_d ? 8 : 0);
}

}  // namespace uking::action
