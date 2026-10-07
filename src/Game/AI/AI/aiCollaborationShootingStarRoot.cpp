#include "Game/AI/AI/aiCollaborationShootingStarRoot.h"
#include <codec/seadHashCRC32.h>
#include "KingSystem/ActorSystem/Profiles/actPlayerBase.h"

namespace uking::ai {

CollaborationShootingStarRoot::CollaborationShootingStarRoot(const InitArg& arg)
    : ksys::act::ai::Ai(arg) {}

// The original keeps this class's vtable store, which a defaulted destructor drops. Written like
// upstream's GameDataFlagSelector::~GameDataFlagSelector() { ; } (commit 96101229).
CollaborationShootingStarRoot::~CollaborationShootingStarRoot() {
    ;
}

bool CollaborationShootingStarRoot::init_(sead::Heap* heap) {
    return ksys::act::ai::Ai::init_(heap);
}

void CollaborationShootingStarRoot::enter_(ksys::act::ai::InlineParamPack* params) {
    auto* anchor = ksys::world::ShootingStarMgrEx::sub_71010D0464(mIdentifier);
    const bool started = anchor && anchor->sub_71010D0734();
    changeChild(started ? "光の柱を出す" : "飛んでいく");
    ksys::act::acc::PlayerBase player;
    if (!started && player.getPlayerFromPlayerInfo()) {
        const bool state = player.sub_7100D0FF48() && player.m188();
        const bool other_state = player.m186();
        if (state || other_state) {
            if (anchor)
                anchor->sub_71010D1394();
            mActor->deleteLater(ksys::act::BaseProc::DeleteReason::_0);
            setFinished();
        }
    }
}

void CollaborationShootingStarRoot::leave_() {
    _58.fadeXLink();
}

void CollaborationShootingStarRoot::loadParams_() {
    getAITreeVariable(&mCollaboShootingStarId_a, "CollaboShootingStarId");
    const sead::SafeString id = mCollaboShootingStarId_a->cstr();
    mIdentifier.name = id;
    mIdentifier.hash = sead::HashCRC32::calcStringHash(id.cstr());
}

}  // namespace uking::ai
