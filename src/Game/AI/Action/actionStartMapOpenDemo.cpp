#include "Game/AI/Action/actionStartMapOpenDemo.h"
#include "KingSystem/ActorSystem/actActor.h"
#include "Game/UI/uiUtils.h"

namespace uking::action {

StartMapOpenDemo::StartMapOpenDemo(const InitArg& arg) : ksys::act::ai::Action(arg) {}

StartMapOpenDemo::~StartMapOpenDemo() = default;

bool StartMapOpenDemo::init_(sead::Heap* heap) {
    return ksys::act::ai::Action::init_(heap);
}

void StartMapOpenDemo::loadParams_() {
    getDynamicParam(&mIsPlayerClose_d, "IsPlayerClose");
}

bool StartMapOpenDemo::oneShot_() {
    if (!mActor)
        return false;
    sead::Vector3f pos;
    mActor->getMtx().getTranslation(pos);
    s32 index = 0;
    if (!ui::sub_7100A9F57C(&index, pos, 5.0f))
        return false;
    ui::sub_7100A9A308(index, *mIsPlayerClose_d);
    return true;
}

}  // namespace uking::action
