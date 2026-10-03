#include "Game/AI/Action/actionNPCEventWait.h"
#include "KingSystem/ActorSystem/AS/ASList.h"
#include "KingSystem/ActorSystem/actActor.h"
#include "KingSystem/ActorSystem/actAiRoot.h"

namespace uking::action {

NPCEventWait::NPCEventWait(const InitArg& arg) : ksys::act::ai::Action(arg) {}

NPCEventWait::~NPCEventWait() = default;

bool NPCEventWait::init_(sead::Heap* heap) {
    return ksys::act::ai::Action::init_(heap);
}

void NPCEventWait::enter_(ksys::act::ai::InlineParamPack* params) {
    ksys::act::ai::Action::enter_(params);
}

void NPCEventWait::leave_() {
    resetRootAiFlag(ksys::act::ai::RootAiFlag::_5);
    mActor->getASList()->goLimpFromHeadShotMaybe(0x37, _20, 1);
}

void NPCEventWait::loadParams_() {}

void NPCEventWait::calc_() {
    ksys::act::ai::Action::calc_();
}

}  // namespace uking::action
