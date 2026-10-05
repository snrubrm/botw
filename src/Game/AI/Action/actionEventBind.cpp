#include "Game/AI/Action/actionEventBind.h"
#include "KingSystem/ActorSystem/actActor.h"
#include "KingSystem/Event/evtManager.h"

namespace uking::action {

EventBind::EventBind(const InitArg& arg) : ksys::act::ai::Action(arg) {}

EventBind::~EventBind() = default;

bool EventBind::init_(sead::Heap* heap) {
    *static_cast<Unk_71025afb58**>(mEventBindUnit_a) = &_130;
    return true;
}

void EventBind::enter_(ksys::act::ai::InlineParamPack* params) {
    ksys::act::ai::Action::enter_(params);
}

void EventBind::leave_() {
    if (!*mIsContinueBind_d) {
        if (auto* bind = _130._8) {
            mActor->sub_71011DA834(bind);
            _130._8 = nullptr;
        } else {
            mActor->sub_71011DA834(&_90);
        }
    }
}

void EventBind::loadParams_() {
    getDynamicParam(&mRotOffsetX_d, "RotOffsetX");
    getDynamicParam(&mRotOffsetY_d, "RotOffsetY");
    getDynamicParam(&mRotOffsetZ_d, "RotOffsetZ");
    getDynamicParam(&mTransOffsetX_d, "TransOffsetX");
    getDynamicParam(&mTransOffsetY_d, "TransOffsetY");
    getDynamicParam(&mTransOffsetZ_d, "TransOffsetZ");
    getDynamicParam(&mIsContinueBind_d, "IsContinueBind");
    getDynamicParam(&mActorName_d, "ActorName");
    getDynamicParam(&mUniqueName_d, "UniqueName");
    getDynamicParam(&mNodeName_d, "NodeName");
    getAITreeVariable(&mEventBindUnit_a, "EventBindUnit");
}

void EventBind::calc_() {
    ksys::act::ai::Action::calc_();
}

ksys::act::BaseProcLink* EventBind::m32() {
    if (auto* manager = ksys::evt::Manager::instance())
        return manager->getBaseProcLinkFromActiveEvent(mActorName_d, mUniqueName_d);
    return nullptr;
}

}  // namespace uking::action
