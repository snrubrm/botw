#include "Game/Actor/Behavior/behaviorXLinkCreateModelTracks.h"
#include <gsys/gsysModelAccessKey.h>
#include <gsys/gsysModel.h>
#include "KingSystem/ActorSystem/actActor.h"

namespace uking::behavior {

XLinkCreateModelTracks::XLinkCreateModelTracks(const InitArg& arg) : XLinkCreate(arg) {}

XLinkCreateModelTracks::~XLinkCreateModelTracks() = default;

bool XLinkCreateModelTracks::init_(sead::Heap* heap) {
    return XLinkCreate::init_(heap);
}

void XLinkCreateModelTracks::calc() {
    XLinkCreate::calc();
}

void XLinkCreateModelTracks::enter() {
    m16(&_78);
    XLinkCreate::enter();
}

void XLinkCreateModelTracks::leave() {
    XLinkCreate::leave();
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
