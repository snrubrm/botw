#include "Game/AI/Behavior/behaviorXLinkCreateForSandworm.h"
#include "KingSystem/ActorSystem/actActor.h"

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

void XLinkCreateForSandworm::m8() {
    if (auto* model = mActor->getModel()) {
        if (!mBoneKey_s.isEmpty())
            _90.search(model, mBoneKey_s);
    }
    OnStateXLinkCreate::m8();
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
