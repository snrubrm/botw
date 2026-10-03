#include "Game/AI/AI/aiTargetPosAnchorOffsetSelf.h"
#include "KingSystem/ActorSystem/actActor.h"
#include "KingSystem/Map/mapObject.h"
#include "KingSystem/Map/mapObjectLink.h"

namespace uking::ai {

TargetPosAnchorOffsetSelf::TargetPosAnchorOffsetSelf(const InitArg& arg) : TargetPosAI(arg) {}

// The original keeps the vtable store that a defaulted destructor drops (same form as upstream's
// GameDataFlagSelector::~GameDataFlagSelector() { ; }, commit 96101229).
TargetPosAnchorOffsetSelf::~TargetPosAnchorOffsetSelf() {
    ;
}

bool TargetPosAnchorOffsetSelf::init_(sead::Heap* heap) {
    return TargetPosAI::init_(heap);
}

void TargetPosAnchorOffsetSelf::enter_(ksys::act::ai::InlineParamPack* params) {
    TargetPosAI::enter_(params);
}

void TargetPosAnchorOffsetSelf::calc_() {
    TargetPosAI::calc_();
}

void TargetPosAnchorOffsetSelf::leave_() {
    TargetPosAI::leave_();
}

void TargetPosAnchorOffsetSelf::loadParams_() {
    TargetPosAI::loadParams_();
    getStaticParam(&mDist_s, "Dist");
    getStaticParam(&mAnchorName_s, "AnchorName");
}

// NON_MATCHING: the original never reads the anchor's y (it stores y = 0 before the x / z differences,
// loading both anchor coordinates from one object load); ours subtracts all three components
void TargetPosAnchorOffsetSelf::m35(sead::Vector3f* pos) {
    if (auto* obj = mActor->getMapObject()) {
        if (auto* links = obj->getLinkData()) {
            auto objects = links->mObjects;
            for (s32 i = 0; i < objects.size(); ++i) {
                if (sead::SafeString(objects(i)->getUnitConfigName()) == mAnchorName_s) {
                    mActor->getMtx().getTranslation(*pos);
                    *pos -= objects(i)->getTranslate();
                    pos->y = 0;
                    pos->normalize();
                    *pos *= *mDist_s;
                    *pos += objects(i)->getTranslate();
                    return;
                }
            }
        }
    }
}

}  // namespace uking::ai
