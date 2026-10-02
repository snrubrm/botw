#include "Game/AI/Behavior/behaviorXLinkCreateModelTracks.h"
#include <gsys/gsysModelAccessKey.h>
#include <gsys/gsysModel.h>
#include "KingSystem/ActorSystem/actActor.h"

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

// NON_MATCHING: the original keeps two branches (x / y copied in each) with a shared z read through a row
// pointer; ours selects the matrix first (early-return and element-wise forms tried)
void XLinkCreateModelTracks::m16(sead::Vector3f* out) {
    auto* actor = mActor;
    if (auto* model = actor->getModel())
        model->getMatrix().getTranslation(*out);
    else
        actor->getMtx().getTranslation(*out);
}

}  // namespace uking::behavior
