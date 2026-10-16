#include "Game/Actor/Behavior/behaviorSetXLinkProperty.h"

#include "KingSystem/ActorSystem/actActor.h"
#include "KingSystem/XLink/xlinkXLink.h"

namespace uking::behavior {

SetXLinkProperty::SetXLinkProperty(const InitArg& arg) : ksys::act::ai::Behavior(arg) {}

SetXLinkProperty::~SetXLinkProperty() = default;

bool SetXLinkProperty::init_(sead::Heap* heap) {
    return true;
}

void SetXLinkProperty::calc() {}

void SetXLinkProperty::loadParams() {
    getStaticParam(&mPropertyIndex_s, "PropertyIndex");
    getStaticParam(&mValue_s, "Value");
    getStaticParam(&mResetValue_s, "ResetValue");
}

void SetXLinkProperty::enter() {
    if (auto* link = mActor->getXLink()) {
        if (*mPropertyIndex_s == 0)
            link->sub_7101231468(27, *mValue_s, false);
    }
}

void SetXLinkProperty::leave() {
    if (auto* link = mActor->getXLink()) {
        if (*mPropertyIndex_s == 0)
            link->sub_7101231468(27, *mResetValue_s, false);
    }
}

}  // namespace uking::behavior
