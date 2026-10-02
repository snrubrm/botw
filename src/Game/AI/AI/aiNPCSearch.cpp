#include "Game/AI/AI/aiNPCSearch.h"
#include "KingSystem/ActorSystem/Awareness/actAwarenessInstance.h"
#include "KingSystem/ActorSystem/actActor.h"
#include "KingSystem/ActorSystem/actAiInlineParam.h"
#include "KingSystem/ActorSystem/actPlayerInfo.h"

namespace uking::ai {

NPCSearch::NPCSearch(const InitArg& arg) : ksys::act::ai::Ai(arg) {}

NPCSearch::~NPCSearch() = default;

bool NPCSearch::init_(sead::Heap* heap) {
    return ksys::act::ai::Ai::init_(heap);
}

void NPCSearch::enter_(ksys::act::ai::InlineParamPack* params) {
    _50 = false;
    if (*mIsHearing_d) {
        ksys::act::ai::InlineParamPack child_params;
        child_params.addVec3(*mTargetPos_d, "TargetPos", -1);
        child_params.addActor(*mTarget_d, "TargetActor", -1);
        changeChild("音気づき", &child_params);
    } else {
        ksys::act::ai::InlineParamPack child_params;
        child_params.addBool(false, "ForceNotice", -1);
        child_params.addActor(*mTarget_d, "TargetActor", -1);
        changeChild("プレイヤー発見", &child_params);
    }
}

void NPCSearch::calc_() {
    if (isCurrentChild("音気づき")) {
        if (auto* awareness = mActor->getAwareness()) {
            if (auto* sensor = awareness->_260[0]) {
                const s32 num = sensor->_8.size();
                for (s32 i = 0; i < num; ++i) {
                    auto* current = awareness->_260[0];
                    auto* entry = current && current->_8.size() > i ?
                                      ksys::act::sub_7100D78E30(&current->_8, i) :
                                      nullptr;
                    auto& link = entry->_0.mLink;
                    if (link == ksys::act::PlayerInfo::getSomeProcLink()) {
                        ksys::act::ai::InlineParamPack params;
                        params.addBool(false, "ForceNotice", -1);
                        params.addActor(link, "TargetActor", -1);
                        changeChild("プレイヤー発見", &params);
                    }
                }
            }
        }
    }

    auto* child = getCurrentChild();
    if (child->isFinished() || child->isFailed())
        setFinished();
}

void NPCSearch::leave_() {
    ksys::act::ai::Ai::leave_();
}

void NPCSearch::loadParams_() {
    getDynamicParam(&mIsHearing_d, "IsHearing");
    getDynamicParam(&mTargetPos_d, "TargetPos");
    getDynamicParam(&mTarget_d, "Target");
}

}  // namespace uking::ai
