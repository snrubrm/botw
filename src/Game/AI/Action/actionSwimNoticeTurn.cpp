#include "Game/AI/Action/actionSwimNoticeTurn.h"
#include "Game/AI/aiUnk_71005D6D10.h"
#include "Game/AI/aiUnk_71007377D4.h"
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

// NON_MATCHING: stack layout only (the original keeps the Unk4 query at sp+8 and the -ey temporary at sp+0x20)
void SwimNoticeTurn::calc_() {
    WaterFloatBase::calc_();
    auto* actor = mActor;
    auto* as_list = actor ? actor->getASList() : nullptr;
    if (as_list) {
        ksys::as::ASList::Unk4 query;
        if (sub_71005DD5B0(actor, 0x29, &query, 0, 0)) {
            sub_710028AFE0(actor, query._10);
        } else if (as_list->x(0x29, nullptr, 0, 0, &ksys::as::ASList::Unk2::sub_71011638DC,
                                          true)) {
            sub_7100738AA8(mActor, 0.99f);
        } else {
            sub_7100738AA8(actor, 0.4f);
        }
        sub_7100738488(mActor, 0.1f, -sead::Vector3f::ey);
    }
    if (isFinishedAS(0, 0))
        setFinished();
}

}  // namespace uking::action
