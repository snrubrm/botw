#include "Game/Actor/Behavior/behaviorXLinkCreate.h"

namespace uking::behavior {

XLinkCreate::XLinkCreate(const InitArg& arg) : OnStateXLinkCreate(arg) {}

XLinkCreate::~XLinkCreate() = default;

bool XLinkCreate::init_(sead::Heap* heap) {
    return OnStateXLinkCreate::init_(heap);
}

void XLinkCreate::calc() {
    OnStateXLinkCreate::calc();
    sub_7100647608();
}

void XLinkCreate::enter() {
    OnStateXLinkCreate::enter();
    sub_7100647608();
}

void XLinkCreate::leave() {
    OnStateXLinkCreate::leave();
}

void XLinkCreate::loadParams() {
    OnStateXLinkCreate::loadParams();
}

}  // namespace uking::behavior
