#include "Game/Actor/AI/aiShutterFence.h"
#include "KingSystem/ActorSystem/actActor.h"

namespace uking::ai {

ShutterFence::ShutterFence(const InitArg& arg) : ksys::act::ai::Ai(arg) {}

// The original keeps the vtable store that a defaulted destructor drops (same form as upstream's
// GameDataFlagSelector::~GameDataFlagSelector() { ; }, commit 96101229).
ShutterFence::~ShutterFence() {
    ;
}

bool ShutterFence::init_(sead::Heap* heap) {
    return ksys::act::ai::Ai::init_(heap);
}

void ShutterFence::enter_(ksys::act::ai::InlineParamPack* params) {
    auto* actor = mActor;
    if (!mASKeyName_Off_s.isEmpty())
        changeAS(mASKeyName_Off_s.cstr(), false, 0, 0);
    if (actor->checkBasicSig())
        changeChild("プリオープン");
    else
        changeChild("クローズ待機");
}

// 0x710056b7e0
void ShutterFence::calc_() {
    auto* actor = mActor;
    auto* child = getCurrentChild();
    if (isCurrentChild("クローズ待機") && (child->isChangeable() || child->isFinished()) &&
        actor->checkBasicSig()) {
        if (!mASKeyName_On_s.isEmpty())
            changeAS(mASKeyName_On_s.cstr(), true, 0, 0);
        changeChild("オープン");
    } else if (isCurrentChild("オープン待機") && (child->isChangeable() || child->isFinished()) &&
               !actor->checkBasicSig()) {
        if (!mASKeyName_On_s.isEmpty())
            changeAS(mASKeyName_On_s.cstr(), true, 0, 0);
        changeChild("クローズ");
    } else if (isCurrentChild("クローズ") && child->isFinished()) {
        actor->sub_7100EE20A4();
        changeChild("クローズ待機");
    } else if ((isCurrentChild("プリオープン") || isCurrentChild("オープン")) && child->isFinished()) {
        actor->sub_7100EE2050();
        changeChild("オープン待機");
    }
}

void ShutterFence::leave_() {
    ksys::act::ai::Ai::leave_();
}

void ShutterFence::loadParams_() {
    getStaticParam(&mASKeyName_On_s, "ASKeyName_On");
    getStaticParam(&mASKeyName_Off_s, "ASKeyName_Off");
}

}  // namespace uking::ai
