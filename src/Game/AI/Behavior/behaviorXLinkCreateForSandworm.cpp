#include "Game/AI/Behavior/behaviorXLinkCreateForSandworm.h"

namespace uking::behavior {

XLinkCreateForSandworm::XLinkCreateForSandworm(const InitArg& arg) : OnStateXLinkCreate(arg) {}

XLinkCreateForSandworm::~XLinkCreateForSandworm() = default;

bool XLinkCreateForSandworm::m6(sead::Heap* heap) {
    return OnStateXLinkCreate::m6(heap);
}

void XLinkCreateForSandworm::m7() {
    OnStateXLinkCreate::m7();
    sub_7100647278();
}

void XLinkCreateForSandworm::m9() {
    OnStateXLinkCreate::m9();
    _90.getKey().reset();
}

void XLinkCreateForSandworm::loadParams() {
    OnStateXLinkCreate::loadParams();
    getStaticParam(&mPosType_s, "PosType");
    getStaticParam(&mBoneKey_s, "BoneKey");
}

}  // namespace uking::behavior
