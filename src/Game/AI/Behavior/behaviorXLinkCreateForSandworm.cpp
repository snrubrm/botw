#include "Game/AI/Behavior/behaviorXLinkCreateForSandworm.h"
#include <gsys/gsysModel.h>
#include <gsys/gsysModelUnit.h>
#include "Game/AI/aiUnk_71007377D4.h"
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

// NON_MATCHING: stack layout (the original keeps `pos` at the bottom and shares the bone matrix slot with `height`)
void XLinkCreateForSandworm::sub_7100647278() {
    sead::Vector3f pos = mActor->getMtx().getTranslation();
    if (_90.isValid()) {
        sead::Matrix34f bone_mtx;
        mActor->getModel()
            ->getUnits()
            .unsafeAt(_90.getKey().model_unit_index)
            ->mModelUnit->getBoneWorldMatrix(&bone_mtx, _90.getKey().bone_index);
        pos = bone_mtx.getTranslation();
    }
    if (*mPosType_s == 1) {
        f32 height = 0;
        if (!sub_710072C21C(&height, &pos))
            height = mActor->getMtx()(1, 3);
        pos.y = height;
    }
    _58.sub_71012419B4(pos);
}

void XLinkCreateForSandworm::loadParams() {
    OnStateXLinkCreate::loadParams();
    getStaticParam(&mPosType_s, "PosType");
    getStaticParam(&mBoneKey_s, "BoneKey");
}

}  // namespace uking::behavior
