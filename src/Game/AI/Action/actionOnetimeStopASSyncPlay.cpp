#include "Game/AI/Action/actionOnetimeStopASSyncPlay.h"
#include "KingSystem/ActorSystem/AS/ASList.h"

namespace uking::action {

OnetimeStopASSyncPlay::OnetimeStopASSyncPlay(const InitArg& arg) : OnetimeStopASPlay(arg) {}

OnetimeStopASSyncPlay::~OnetimeStopASSyncPlay() = default;

void OnetimeStopASSyncPlay::enter_(ksys::act::ai::InlineParamPack* params) {
    OnetimeStopASPlay::enter_(params);
    if (auto* as_list = mActor->getASList()) {
        as_list->startAnimationMaybe(-1.0f, -1.0f, mSyncASName_s.cstr(), *mSyncASSlot_s,
                                     *mSyncASSequenceBank_s, true);
    }
}

void OnetimeStopASSyncPlay::loadParams_() {
    OnetimeStopASPlay::loadParams_();
    getStaticParam(&mSyncASSlot_s, "SyncASSlot");
    getStaticParam(&mSyncASSequenceBank_s, "SyncASSequenceBank");
    getStaticParam(&mSyncASName_s, "SyncASName");
}

}  // namespace uking::action
