#include "Game/Actor/Behavior/behaviorOnChangeXLinkCreateForLocator.h"

namespace uking::behavior {

OnChangeXLinkCreateForLocator::OnChangeXLinkCreateForLocator(const InitArg& arg)
    : OnChangeXLinkCreate(arg) {}

void OnChangeXLinkCreateForLocator::calc() {
    OnChangeXLinkCreate::calc();
}

void OnChangeXLinkCreateForLocator::enter() {
    OnChangeXLinkCreate::enter();
}

void OnChangeXLinkCreateForLocator::leave() {
    OnChangeXLinkCreate::leave();
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
