#include "Game/AI/Behavior/behaviorOnChangeXLinkCreateForLocator.h"

namespace uking::behavior {

OnChangeXLinkCreateForLocator::OnChangeXLinkCreateForLocator(const InitArg& arg)
    : OnChangeXLinkCreate(arg) {}

void OnChangeXLinkCreateForLocator::m7() {
    OnChangeXLinkCreate::m7();
}

void OnChangeXLinkCreateForLocator::m8() {
    OnChangeXLinkCreate::m8();
}

void OnChangeXLinkCreateForLocator::m9() {
    OnChangeXLinkCreate::m9();
}

void OnChangeXLinkCreateForLocator::loadParams() {
    OnChangeXLinkCreate::loadParams();
    getStaticParam(&mEmitSourceType_s, "EmitSourceType");
    getStaticParam(&mTargetLocaterName_s, "TargetLocaterName");
}

OnChangeXLinkCreateForLocator::~OnChangeXLinkCreateForLocator() {
    _58.freeBuffer();
}

}  // namespace uking::behavior
