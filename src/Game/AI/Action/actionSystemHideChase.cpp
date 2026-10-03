#include "Game/AI/Action/actionSystemHideChase.h"
#include "KingSystem/ActorSystem/actActorUtil.h"

namespace uking::action {

SystemHideChase::SystemHideChase(const InitArg& arg) : SystemHide(arg) {}

SystemHideChase::~SystemHideChase() = default;

bool SystemHideChase::init_(sead::Heap* heap) {
    return SystemHide::init_(heap);
}

void SystemHideChase::enter_(ksys::act::ai::InlineParamPack* params) {
    SystemHide::enter_(params);
    ksys::act::sub_7100EE57FC(mActor, *mTargetPos_d);
}

void SystemHideChase::leave_() {
    SystemHide::leave_();
}

void SystemHideChase::loadParams_() {
    SystemHide::loadParams_();
    getDynamicParam(&mTargetPos_d, "TargetPos");
}

void SystemHideChase::calc_() {
    SystemHide::calc_();
    ksys::act::sub_7100EE57FC(mActor, *mTargetPos_d);
}

}  // namespace uking::action
