#include "Game/AI/Action/actionSwimNoticeTurn.h"
#include "Game/AI/aiUnk_71005D6D10.h"
#include "KingSystem/ActorSystem/AS/ASList.h"
#include "KingSystem/ActorSystem/actActor.h"

namespace uking::action {

SwimNoticeTurn::SwimNoticeTurn(const InitArg& arg) : WaterFloatBase(arg) {}

SwimNoticeTurn::~SwimNoticeTurn() = default;

void SwimNoticeTurn::enter_(ksys::act::ai::InlineParamPack* params) {
    WaterFloatBase::enter_(params);
    playAS(mASName_s.cstr(), false, 0, 0, -1.0f);
    auto* actor = mActor;
    if (actor && actor->getASList()) {
        ksys::as::ASList::Unk4 query;
        if (sub_71005DD5B0(actor, 0x29, &query, 0, 0))
            sub_710028AFE0(actor, query._10);
    }
    mFlags.reset(Flag::Changeable);
}

void SwimNoticeTurn::leave_() {
    WaterFloatBase::leave_();
}

void SwimNoticeTurn::loadParams_() {
    WaterFloatBase::loadParams_();
    getStaticParam(&mAngSpd_s, "AngSpd");
    getStaticParam(&mASName_s, "ASName");
    getDynamicParam(&mTargetPos_d, "TargetPos");
}

void SwimNoticeTurn::calc_() {
    WaterFloatBase::calc_();
}

}  // namespace uking::action
