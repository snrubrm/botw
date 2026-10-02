#include "Game/AI/Behavior/behaviorXLinkCreateModelTracks.h"

namespace uking::behavior {

XLinkCreateModelTracks::XLinkCreateModelTracks(const InitArg& arg) : XLinkCreate(arg) {}

XLinkCreateModelTracks::~XLinkCreateModelTracks() = default;

bool XLinkCreateModelTracks::m6(sead::Heap* heap) {
    return XLinkCreate::m6(heap);
}

void XLinkCreateModelTracks::m7() {
    XLinkCreate::m7();
}

void XLinkCreateModelTracks::m8() {
    m16(&_78);
    XLinkCreate::m8();
}

void XLinkCreateModelTracks::m9() {
    XLinkCreate::m9();
}

void XLinkCreateModelTracks::loadParams() {
    XLinkCreate::loadParams();
}

void XLinkCreateModelTracks::m15(sead::Vector3f* out) {
    *out = _78;
}

}  // namespace uking::behavior
