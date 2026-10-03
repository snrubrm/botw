#include "Game/AI/Action/actionSystemHide.h"
#include "KingSystem/ActorSystem/actActor.h"

namespace uking::action {

SystemHide::SystemHide(const InitArg& arg) : ksys::act::ai::Action(arg) {}

SystemHide::~SystemHide() = default;

bool SystemHide::init_(sead::Heap* heap) {
    return ksys::act::ai::Action::init_(heap);
}

void SystemHide::enter_(ksys::act::ai::InlineParamPack* params) {
    ksys::act::ai::Action::enter_(params);
}

void SystemHide::leave_() {
    ksys::act::ai::Action::leave_();
}

void SystemHide::loadParams_() {
    getStaticParam(&mIsOnAttention_s, "IsOnAttention");
    getStaticParam(&mASName_s, "ASName");
}

void SystemHide::calc_() {
    if (isFinished() || isFailed())
        return;
    if (m32()) {
        mActor->deleteLater(ksys::act::BaseProc::DeleteReason::_0);
        setFailed();
    }
}

bool SystemHide::m32() {
    return mActor->sub_7100EE1E94();
}

}  // namespace uking::action
