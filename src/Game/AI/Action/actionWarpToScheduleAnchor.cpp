#include "Game/AI/Action/actionWarpToScheduleAnchor.h"
#include "Game/Actor/actNPC.h"
#include "KingSystem/ActorSystem/actActor.h"
#include "KingSystem/ActorSystem/actActorUtil.h"
#include "KingSystem/Map/mapObject.h"

namespace uking::action {

WarpToScheduleAnchor::WarpToScheduleAnchor(const InitArg& arg) : ksys::act::ai::Action(arg) {}

WarpToScheduleAnchor::~WarpToScheduleAnchor() = default;

bool WarpToScheduleAnchor::init_(sead::Heap* heap) {
    return ksys::act::ai::Action::init_(heap);
}

// NON_MATCHING: register allocation only (translation x / y callee-saved registers swapped)
bool WarpToScheduleAnchor::oneShot_() {
    if (auto* object = ksys::act::findLinkReferenceObj(mActor, mAnchorName_d, mUniqueName_d, nullptr)) {
        const sead::Vector3f scale = mActor->getScale();
        const sead::Vector3f translation = object->getTranslate();
        const sead::Vector3f rotation = object->getRotate();
        sead::Matrix34f mtx;
        mtx.makeSRT(scale, rotation, translation);
        mActor->setMtx(mtx, false, true);
        if (auto* npc = sead::DynamicCast<uking::act::NPC>(mActor)) {
            npc->_10a4 = mtx.m[1][3];
            npc->_fe8 |= 2;
        }
    }
    return true;
}

void WarpToScheduleAnchor::loadParams_() {
    getDynamicParam(&mAnchorName_d, "AnchorName");
    getDynamicParam(&mUniqueName_d, "UniqueName");
}

}  // namespace uking::action
