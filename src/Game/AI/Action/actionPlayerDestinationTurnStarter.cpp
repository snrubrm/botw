#include "Game/AI/Action/actionPlayerDestinationTurnStarter.h"
#include "KingSystem/ActorSystem/Profiles/actPlayer.h"
#include "KingSystem/ActorSystem/AS/ASList.h"
#include "KingSystem/ActorSystem/actActor.h"
#include "KingSystem/ActorSystem/actActorConstDataAccess.h"
#include "KingSystem/ActorSystem/actActorUtil.h"
#include "KingSystem/ActorSystem/actActorLinkConstDataAccess.h"
#include "KingSystem/Event/evtUnk_7100dc816c.h"

namespace uking::action {

PlayerDestinationTurnStarter::PlayerDestinationTurnStarter(const InitArg& arg)
    : PlayerAction(arg) {
    _28.reset();
}

PlayerDestinationTurnStarter::~PlayerDestinationTurnStarter() = default;

bool PlayerDestinationTurnStarter::init_(sead::Heap* heap) {
    return PlayerAction::init_(heap);
}

void PlayerDestinationTurnStarter::enter_(ksys::act::ai::InlineParamPack* params) {
    PlayerAction::enter_(params);
    m33();
    auto* player = static_cast<ksys::act::Player*>(mActor);
    player->_20bc.value = 0;
    player->_20bc.prev_value = 0;
    _28.reset();
    _28 = ksys::evt::sub_7100DC85D4(mActor);
    if (_28.hasProc()) {
        f32 x, z;
        {
            ksys::act::ActorConstDataAccess accessor;
            ksys::act::acquireActor(&_28, &accessor);
            const auto& mtx = accessor.getActorMtx();
            x = mtx(0, 3);
            z = mtx(2, 3);
        }
        _20 = ksys::util::Unk_7101EC6BAC(
            sead::Mathf::atan2Idx(x - static_cast<ksys::act::Player*>(mActor)->_1770.x,
                                  z - static_cast<ksys::act::Player*>(mActor)->_1770.z));
        if (static_cast<ksys::act::Player*>(mActor)->isRidingHorse())
            setFinished();
    }
}

void PlayerDestinationTurnStarter::leave_() {}

void PlayerDestinationTurnStarter::loadParams_() {}

void PlayerDestinationTurnStarter::calc_() {
    if (static_cast<ksys::act::Player*>(mActor)->sub_7100857014(-1.0f, &_20, -1, -1) && m34())
        setFinished();
    auto* player = static_cast<ksys::act::Player*>(mActor);
    player->_20bc.value = 0;
    player->_20bc.prev_value = 0;
    static_cast<ksys::act::Player*>(mActor)->actionCommon();
}

void PlayerDestinationTurnStarter::m33() {
    if (mActor->getASList()->x_1(0, 0) != "DemoWait")
        static_cast<ksys::act::Player*>(mActor)->switchToAnimSequenceMaybe("DemoWait", true, -1.0f);
}

bool PlayerDestinationTurnStarter::m34() {
    return true;
}

bool PlayerDestinationTurnStarter::m35() {
    return true;
}

}  // namespace uking::action
