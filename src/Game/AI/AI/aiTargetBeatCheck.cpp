#include "Game/AI/AI/aiTargetBeatCheck.h"
#include "Game/AI/aiUnk_71005D6D10.h"
#include "KingSystem/ActorSystem/actActor.h"
#include "KingSystem/ActorSystem/actActorConstDataAccess.h"
#include "KingSystem/ActorSystem/actActorUtil.h"
#include "KingSystem/ActorSystem/actAiInlineParam.h"
#include "KingSystem/ActorSystem/actPlayerInfo.h"

namespace uking::ai {

TargetBeatCheck::TargetBeatCheck(const InitArg& arg) : ksys::act::ai::Ai(arg) {}

TargetBeatCheck::~TargetBeatCheck() = default;

bool TargetBeatCheck::init_(sead::Heap* heap) {
    return ksys::act::ai::Ai::init_(heap);
}

void TargetBeatCheck::enter_(ksys::act::ai::InlineParamPack* params) {
    if (sub_71005BC648()) {
        ksys::act::ai::InlineParamPack child_params;
        child_params.addVec3(sub_71005D9330(mActor), "TargetPos", -1);
        changeChild("撃破", &child_params);
    } else {
        ksys::act::ai::InlineParamPack child_params;
        child_params.addVec3(sub_71005D9330(mActor), "TargetPos", -1);
        changeChild("未撃破", &child_params);
    }
}

void TargetBeatCheck::calc_() {
    auto* child = getCurrentChild();
    child->setDynamicParam(sub_71005D9330(mActor), "TargetPos");
    if (child->isFinished()) {
        if (child->isFinished())
            setFinished();
        else
            setFailed();
    } else if (child->isFailed()) {
        if (child->isFinished())
            setFinished();
        else
            setFailed();
    } else if (child->isChangeable()) {
        const bool is_not_beaten = isCurrentChild("未撃破");
        const bool beaten = sub_71005BC648();
        if (is_not_beaten) {
            if (beaten) {
                ksys::act::ai::InlineParamPack params;
                params.addVec3(sub_71005D9330(mActor), "TargetPos", -1);
                changeChild("撃破", &params);
            }
        } else if (!beaten) {
            ksys::act::ai::InlineParamPack params;
            params.addVec3(sub_71005D9330(mActor), "TargetPos", -1);
            changeChild("未撃破", &params);
        }
    }
}

bool TargetBeatCheck::sub_71005BC648() {
    auto* link = sub_71005D9050(mActor);
    if (!link || !link->hasProc() || sub_71005D777C(link))
        return true;

    ksys::act::ActorConstDataAccess accessor;
    ksys::act::acquireActor(link, &accessor);
    if (accessor.sub_7100D10E6C(26))
        return true;
    if (ksys::act::isPlayerProfile(link)) {
        if (sub_710072B660())
            return true;
    }
    return false;
}

void TargetBeatCheck::leave_() {
    ksys::act::ai::Ai::leave_();
}

void TargetBeatCheck::loadParams_() {}

}  // namespace uking::ai
