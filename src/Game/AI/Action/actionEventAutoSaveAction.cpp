#include "Game/AI/Action/actionEventAutoSaveAction.h"
#include "KingSystem/GameData/gdtSaveMgr.h"

namespace uking::action {

EventAutoSaveAction::EventAutoSaveAction(const InitArg& arg) : ksys::act::ai::Action(arg) {}

EventAutoSaveAction::~EventAutoSaveAction() = default;

bool EventAutoSaveAction::oneShot_() {
    auto* mgr = ksys::SaveMgr::instance();
    if (!mgr)
        return false;
    auto* object = mgr->get1020();
    if (!object)
        return false;
    return object->m0(true, false);
}

}  // namespace uking::action
