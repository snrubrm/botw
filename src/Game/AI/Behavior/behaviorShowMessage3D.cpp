#include "Game/AI/Behavior/behaviorShowMessage3D.h"

namespace uking::behavior {

ShowMessage3D::ShowMessage3D(const InitArg& arg) : ksys::act::ai::Behavior(arg) {}

// Empty-statement body as in upstream's GameDataFlagSelector::~GameDataFlagSelector() (96101229):
// the original keeps the vtable store that a defaulted destructor drops (SafeString member).
ShowMessage3D::~ShowMessage3D() {
    ;
}

void ShowMessage3D::m7() {
    _50.sub_7100721C48();
}

void ShowMessage3D::loadParams() {
    getStaticParam(&mDelayFrame_s, "DelayFrame");
    getStaticParam(&mIsCloseOtherMessage_s, "IsCloseOtherMessage");
    getStaticParam(&mUseVoiceFolder_s, "UseVoiceFolder");
    getStaticParam(&mLabelName_s, "LabelName");
}

}  // namespace uking::behavior
