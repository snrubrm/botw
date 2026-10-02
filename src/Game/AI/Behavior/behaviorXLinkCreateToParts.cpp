#include "Game/AI/Behavior/behaviorXLinkCreateToParts.h"

namespace uking::behavior {

XLinkCreateToParts::XLinkCreateToParts(const InitArg& arg) : XLinkCreate(arg) {}

// Empty-statement body as in upstream's GameDataFlagSelector::~GameDataFlagSelector() (96101229):
// the original keeps the vtable store that a defaulted destructor drops (SafeString member).
XLinkCreateToParts::~XLinkCreateToParts() {
    ;
}

bool XLinkCreateToParts::m6(sead::Heap* heap) {
    return XLinkCreate::m6(heap);
}

void XLinkCreateToParts::m7() {
    XLinkCreate::m7();
}

void XLinkCreateToParts::m8() {
    XLinkCreate::m8();
}

void XLinkCreateToParts::m9() {
    XLinkCreate::m9();
}

void XLinkCreateToParts::loadParams() {
    XLinkCreate::loadParams();
    getStaticParam(&mPartsName_s, "PartsName");
    getStaticParam(&mOffset_s, "Offset");
}

}  // namespace uking::behavior
