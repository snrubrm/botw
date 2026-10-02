#include "Game/AI/Action/actionChanegToLog.h"
#include "KingSystem/ActorSystem/actActor.h"
#include "Game/AI/aiUnk_71005D6D10.h"
#include "KingSystem/XLink/xlinkActorUtil.h"
#include "KingSystem/ActorSystem/actTag.h"
#include "KingSystem/ActorSystem/actActorUtil.h"

namespace uking::action {

ChanegToLog::ChanegToLog(const InitArg& arg) : ksys::act::ai::Action(arg) {}

ChanegToLog::~ChanegToLog() = default;

bool ChanegToLog::init_(sead::Heap* heap) {
    return ksys::act::ai::Action::init_(heap);
}

void ChanegToLog::enter_(ksys::act::ai::InlineParamPack* params) {
    auto* actor = mActor;
    if (!ksys::act::hasTag(actor, ksys::act::tags::ExistOnlyTrunk) &&
        ksys::act::hasTag(actor, ksys::act::tags::Tree)) {
        sub_71005E01CC(actor, 1, 0);
    }
    mFlags.set(Flag::Changeable);
    setFinished();
    if (!actor->getMapObject())
        ksys::eft::searchAndEmitELink(actor, "Leaf");
}

void ChanegToLog::leave_() {
    ksys::act::ai::Action::leave_();
}

void ChanegToLog::loadParams_() {}

void ChanegToLog::calc_() {
    ksys::act::ai::Action::calc_();
}

}  // namespace uking::action
