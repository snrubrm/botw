#include "Game/AI/Action/actionSetRequestAttention.h"
#include "KingSystem/ActorSystem/actActorUtil.h"

namespace uking::action {

SetRequestAttention::SetRequestAttention(const InitArg& arg) : ksys::act::ai::Action(arg) {}

SetRequestAttention::~SetRequestAttention() = default;

bool SetRequestAttention::init_(sead::Heap* heap) {
    return ksys::act::ai::Action::init_(heap);
}

// NON_MATCHING: the original loads mActor before the two bool params (scheduling)
void SetRequestAttention::enter_(ksys::act::ai::InlineParamPack* params) {
    if (*mIsOn_s) {
        if (*mIsAll_s)
            ksys::act::enableAllAttClients(mActor);
        else
            ksys::act::enableAttClient(mActor, mAttName_s);
    } else {
        if (*mIsAll_s)
            ksys::act::disableAllAttClients(mActor);
        else
            ksys::act::disableAttClient(mActor, mAttName_s);
    }
    setFinished();
}

void SetRequestAttention::leave_() {
    ksys::act::ai::Action::leave_();
}

void SetRequestAttention::loadParams_() {
    getStaticParam(&mIsOn_s, "IsOn");
    getStaticParam(&mIsAll_s, "IsAll");
    getStaticParam(&mAttName_s, "AttName");
}

void SetRequestAttention::calc_() {
    ksys::act::ai::Action::calc_();
}

}  // namespace uking::action
