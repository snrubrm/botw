#include "Game/AI/Action/actionRideHorseForEventAction.h"
#include "Game/Actor/actHorseRideInfo.h"
#include "Game/gameHorseMgr.h"
#include "KingSystem/ActorSystem/actActor.h"
#include "KingSystem/ActorSystem/actActorConstDataAccess.h"
#include "KingSystem/Utils/Thread/Message.h"
#include "KingSystem/ActorSystem/actCCAccessor.h"
#include "KingSystem/Physics/CharacterController/physCharacterController.h"

namespace uking::action {

RideHorseForEventAction::RideHorseForEventAction(const InitArg& arg) : ksys::act::ai::Action(arg) {}

RideHorseForEventAction::~RideHorseForEventAction() = default;

bool RideHorseForEventAction::init_(sead::Heap* heap) {
    return ksys::act::ai::Action::init_(heap);
}

void RideHorseForEventAction::enter_(ksys::act::ai::InlineParamPack* params) {
    if (auto* cc = mActor->getCharacterController())
        cc->sub_7100F5F458(ksys::act::MotionType::Hover);
}

void RideHorseForEventAction::leave_() {
    ksys::act::ai::Action::leave_();
}

void RideHorseForEventAction::loadParams_() {}

// NON_MATCHING: same calls; the original shares one accessor-destructor block with the failed-acquire path (falls through
// from sendMessage); ours keeps `&accessor` in x20 and jumps
void RideHorseForEventAction::calc_() {
    auto* manager = HorseMgr::instance();
    if (manager && manager->_60.hasProc()) {
        ksys::act::ActorConstDataAccess accessor;
        if (ksys::act::acquireActor(&manager->_60, &accessor)) {
            accessor.sub_7100D150E8(mActor);
            auto* ride_info = mActor->getPlayerRideInfo();
            if (ride_info && !(ride_info->_30 & 1))
                ride_info->sub_7100E7C054(&manager->_60);
            sendMessage(*accessor.getMessageTransceiverId(), ksys::MessageType(0x3800016), nullptr);
        }
    }
    setFinished();
}

}  // namespace uking::action
