#include "Game/AI/Action/actionForkGanonAscendingCreateManage.h"
#include "KingSystem/Utils/Thread/Message.h"

namespace uking::action {

ForkGanonAscendingCreateManage::ForkGanonAscendingCreateManage(const InitArg& arg)
    : ksys::act::ai::Action(arg) {}

ForkGanonAscendingCreateManage::~ForkGanonAscendingCreateManage() = default;

bool ForkGanonAscendingCreateManage::init_(sead::Heap* heap) {
    _38.sub_710074431C(heap, mCreateGrudgeName_s.cstr(), *mMaxNum_s);
    return true;
}

void ForkGanonAscendingCreateManage::enter_(ksys::act::ai::InlineParamPack* params) {
    ksys::act::ai::Action::enter_(params);
}

void ForkGanonAscendingCreateManage::leave_() {
    auto* elem = _38._8;
    for (s32 i = 0; i != _38._0; ++i, ++elem)
        elem->sub_7100744310();
}

void ForkGanonAscendingCreateManage::loadParams_() {
    getStaticParam(&mMaxNum_s, "MaxNum");
    getStaticParam(&mCreateGrudgeName_s, "CreateGrudgeName");
}

bool ForkGanonAscendingCreateManage::handleMessage_(const ksys::Message* message) {
    if (_48.m2(*message)) {
        _38.sub_71007445BC(_48._34._0, _48._34._30);
        _48.x();
        return true;
    }
    return false;
}

bool ForkGanonAscendingCreateManage::updateForPreDelete() {
    _38.sub_71007444AC();
    return true;
}

void ForkGanonAscendingCreateManage::calc_() {
    _38.sub_710074456C();
}

bool ForkGanonAscendingCreateManage::hasUpdateForPreDeleteCb() {
    return true;
}

}  // namespace uking::action
