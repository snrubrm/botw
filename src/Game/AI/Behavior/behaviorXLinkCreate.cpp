#include "Game/AI/Behavior/behaviorXLinkCreate.h"

namespace uking::behavior {

XLinkCreate::XLinkCreate(const InitArg& arg) : OnStateXLinkCreate(arg) {}

XLinkCreate::~XLinkCreate() = default;

bool XLinkCreate::m6(sead::Heap* heap) {
    return OnStateXLinkCreate::m6(heap);
}

void XLinkCreate::m7() {
    OnStateXLinkCreate::m7();
    sub_7100647608();
}

void XLinkCreate::m8() {
    OnStateXLinkCreate::m8();
    sub_7100647608();
}

void XLinkCreate::m9() {
    OnStateXLinkCreate::m9();
}

void XLinkCreate::loadParams() {
    OnStateXLinkCreate::loadParams();
}

}  // namespace uking::behavior
