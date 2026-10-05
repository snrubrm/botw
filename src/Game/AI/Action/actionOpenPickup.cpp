#include "Game/AI/Action/actionOpenPickup.h"

// The original global helper name is retained; its source namespace is unknown.
void callGetDemoHandler(ksys::act::Actor* actor, const sead::SafeString& name);

namespace uking::ui {
// The second argument is passed as -1 but unused by the native callee; its type is inferred.
bool sub_7100A963C0(const sead::SafeString& name, s32 option);
}

namespace uking::action {

OpenPickup::OpenPickup(const InitArg& arg) : ksys::act::ai::Action(arg) {}

OpenPickup::~OpenPickup() = default;

bool OpenPickup::init_(sead::Heap* heap) {
    return ksys::act::ai::Action::init_(heap);
}

void OpenPickup::enter_(ksys::act::ai::InlineParamPack* params) {
    if (*mIsAddPorch_d)
        callGetDemoHandler(nullptr, mPorchItemName_d);
    ui::sub_7100A963C0(mPorchItemName_d, -1);
    setFinished();
    mFlags.set(Flag::Changeable);
}

void OpenPickup::leave_() {
    ksys::act::ai::Action::leave_();
}

void OpenPickup::loadParams_() {
    getDynamicParam(&mIsAddPorch_d, "IsAddPorch");
    getDynamicParam(&mPorchItemName_d, "PorchItemName");
}

void OpenPickup::calc_() {
    ksys::act::ai::Action::calc_();
}

}  // namespace uking::action
