#include "Game/AI/Action/actionAnmArmorBindAction.h"
#include "KingSystem/ActorSystem/AS/ASList.h"
#include "KingSystem/ActorSystem/actActor.h"
#include "KingSystem/System/SystemTimers.h"
#include "KingSystem/Utils/Thread/Message.h"

namespace uking::action {

AnmArmorBindAction::AnmArmorBindAction(const InitArg& arg) : ArmorBindAction(arg) {}

AnmArmorBindAction::~AnmArmorBindAction() = default;

bool AnmArmorBindAction::init_(sead::Heap* heap) {
    return ArmorBindAction::init_(heap);
}

void AnmArmorBindAction::enter_(ksys::act::ai::InlineParamPack* params) {
    ArmorBindAction::enter_(params);
}

void AnmArmorBindAction::leave_() {
    ArmorBindAction::leave_();
}

void AnmArmorBindAction::loadParams_() {
    ArmorBindAction::loadParams_();
}

bool AnmArmorBindAction::handleMessage_(const ksys::Message* message) {
    if (message->getType() != 0x4000001)
        return false;

    auto* as_list = mActor->getASList();
    if (!as_list)
        return true;
    auto* timers = ksys::SystemTimers::instance();
    if (!timers)
        return true;

    const f32 frame = f32(u32(timers->mFrameCounterB) % 300) + timers->mVfrTimer;
    as_list->sub_710115F1D8(0, 1, frame / 300.0f);
    return true;
}

void AnmArmorBindAction::calc_() {
    ArmorBindAction::calc_();
}

}  // namespace uking::action
