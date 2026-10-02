#include "Game/AI/Action/actionRequestEventFromMapUnit.h"
#include "Game/gameUnk_71008ba8d8.h"
#include "KingSystem/ActorSystem/actActor.h"
#include "KingSystem/Event/evtManager.h"
#include "KingSystem/Map/mapObject.h"

namespace uking::action {

RequestEventFromMapUnit::RequestEventFromMapUnit(const InitArg& arg) : ksys::act::ai::Action(arg) {}

RequestEventFromMapUnit::~RequestEventFromMapUnit() = default;

bool RequestEventFromMapUnit::init_(sead::Heap* heap) {
    return ksys::act::ai::Action::init_(heap);
}

void RequestEventFromMapUnit::enter_(ksys::act::ai::InlineParamPack* params) {
    ksys::act::ai::Action::enter_(params);
    if (!mASKey_s.isEmpty())
        playAS(mASKey_s.cstr(), false, 0, 0, -1.0f);
}

void RequestEventFromMapUnit::leave_() {
    ksys::act::ai::Action::leave_();
}

void RequestEventFromMapUnit::loadParams_() {
    getStaticParam(&mIsWaitStartEvent_s, "IsWaitStartEvent");
    getStaticParam(&mASKey_s, "ASKey");
    getMapUnitParam(&mEventFlowName_m, "EventFlowName");
    getMapUnitParam(&mEventFlowEntryName_m, "EventFlowEntryName");
}

void RequestEventFromMapUnit::calc_() {
    ksys::evt::callEvent(mActor, mEventFlowName_m, mEventFlowEntryName_m, true, false);
    if (*mIsWaitStartEvent_s) {
        auto* actor = mActor;
        bool in_event = actor->get1a0() != nullptr;
        if (!in_event) {
            auto* obj = actor->getMapObject();
            in_event = obj && obj->getFlags0().isOn(ksys::map::Object::Flag0::_20000);
        }
        if (!in_event)
            return;
        auto* manager = ksys::evt::Manager::instance();
        if (manager && manager->isActiveEventNameEqualTo(mEventFlowName_m, mEventFlowEntryName_m))
            setFinished();
    } else if (isFinishedAS(0, 0)) {
        setFinished();
    }
}

}  // namespace uking::action
