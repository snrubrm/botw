#include "Game/AI/Action/actionIgniteThreeActorAttack.h"
#include "KingSystem/ActorSystem/actActor.h"
#include "KingSystem/ActorSystem/AS/ASList.h"

namespace uking::action {

IgniteThreeActorAttack::IgniteThreeActorAttack(const InitArg& arg) : OnetimeStopASPlay(arg) {}

IgniteThreeActorAttack::~IgniteThreeActorAttack() = default;

void IgniteThreeActorAttack::enter_(ksys::act::ai::InlineParamPack* params) {
    OnetimeStopASPlay::enter_(params);
    _90 = 0;
}

void IgniteThreeActorAttack::leave_() {
    OnetimeStopASPlay::leave_();
}

void IgniteThreeActorAttack::loadParams_() {
    OnetimeStopASPlay::loadParams_();
    getDynamicParam(&mIgniteHandle_d, "IgniteHandle");
    getDynamicParam(&mIgniteHandle2_d, "IgniteHandle2");
    getDynamicParam(&mIgniteHandle3_d, "IgniteHandle3");
    getStaticParam(&mIgniteSpeed_s, "IgniteSpeed");
    getStaticParam(&mIgniteOffset_s, "IgniteOffset");
    getStaticParam(&mIgniteRotate_s, "IgniteRotate");
    getStaticParam(&mIgniteRotSpeed_s, "IgniteRotSpeed");
    getStaticParam(&mBaseNode_s, "BaseNode");
}

void IgniteThreeActorAttack::calc_() {
    OnetimeStopASPlay::calc_();
    if (auto* as_list = mActor->getASList()) {
        if (as_list->x(71, nullptr, 0, 0, &ksys::as::ASList::Unk2::sub_71011637EC, true)) {
            sub_71001B6AB8();
            _90 = _90 + 1;
        }
    }
}

}  // namespace uking::action
