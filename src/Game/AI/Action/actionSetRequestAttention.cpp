#include "Game/AI/Action/actionSetRequestAttention.h"
#include "KingSystem/ActorSystem/actActorUtil.h"

namespace uking::action {

SetRequestAttention::SetRequestAttention(const InitArg& arg) : ksys::act::ai::Action(arg) {}

SetRequestAttention::~SetRequestAttention() = default;

bool SetRequestAttention::init_(sead::Heap* heap) {
    return ksys::act::ai::Action::init_(heap);
}

void SetRequestAttention::enter_(ksys::act::ai::InlineParamPack* params) {
    auto* actor = mActor;
    if (*mIsOn_s) {
        if (*mIsAll_s)
            ksys::act::enableAllAttClients(actor);
        else
            ksys::act::enableAttClient(actor, mAttName_s);
    } else {
        if (*mIsAll_s)
            ksys::act::disableAllAttClients(actor);
        else
            ksys::act::disableAttClient(actor, mAttName_s);
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
