#include "Game/AI/Behavior/behaviorSetXLinkProperty.h"

namespace uking::behavior {

SetXLinkProperty::SetXLinkProperty(const InitArg& arg) : ksys::act::ai::Behavior(arg) {}

SetXLinkProperty::~SetXLinkProperty() = default;

bool SetXLinkProperty::m6(sead::Heap* heap) {
    return true;
}

void SetXLinkProperty::m7() {}

void SetXLinkProperty::loadParams() {
    getStaticParam(&mPropertyIndex_s, "PropertyIndex");
    getStaticParam(&mValue_s, "Value");
    getStaticParam(&mResetValue_s, "ResetValue");
}

}  // namespace uking::behavior
