#include "Game/AI/AI/aiGolemNoticeWorry.h"
#include "KingSystem/ActorSystem/Awareness/actAwarenessInstance.h"
#include "KingSystem/ActorSystem/actActor.h"
#include "KingSystem/ActorSystem/actAiInlineParam.h"

namespace uking::ai {

GolemNoticeWorry::GolemNoticeWorry(const InitArg& arg) : ksys::act::ai::Ai(arg) {}

GolemNoticeWorry::~GolemNoticeWorry() = default;

bool GolemNoticeWorry::init_(sead::Heap* heap) {
    return ksys::act::ai::Ai::init_(heap);
}

void GolemNoticeWorry::enter_(ksys::act::ai::InlineParamPack* params) {
    ksys::act::ai::Ai::enter_(params);
}

// NON_MATCHING: stack slot sharing (the original puts the first two isCurrentChild temporaries in
// the InlineParamPack's slot, ours in the TargetPos string's)
void GolemNoticeWorry::calc_() {
    auto* child = getCurrentChild();
    if (child->isFinished() || child->isFailed()) {
        if (isCurrentChild("回転") || !isCurrentChild("待機")) {
            changeChild("待機");
            return;
        }
        bool found = false;
        if (mTargetActor_d->hasProc()) {
            if (auto* awareness = mActor->getAwareness()) {
                if (auto* sensor = awareness->_260[3]) {
                    const s32 num = sensor->_8.size();
                    for (s32 i = 0; i < num; ++i) {
                        auto* current = awareness->_260[3];
                        if (!current || current->_8.size() <= i)
                            continue;
                        auto* entry = ksys::act::sub_7100D78E30(&current->_8, i);
                        if (entry && entry->mLink == *mTargetActor_d) {
                            found = true;
                            break;
                        }
                    }
                }
            }
        }
        if (found) {
            ksys::act::ai::InlineParamPack params;
            params.addVec3(*mTargetPos_d, "TargetPos", -1);
            changeChild("見まわす", &params);
            return;
        }
        setFinished();
    } else if (child->isChangeable()) {
        if (isCurrentChild("待機"))
            return;
        bool found = false;
        if (mTargetActor_d->hasProc()) {
            if (auto* awareness = mActor->getAwareness()) {
                if (auto* sensor = awareness->_260[3]) {
                    const s32 num = sensor->_8.size();
                    for (s32 i = 0; i < num; ++i) {
                        auto* current = awareness->_260[3];
                        if (!current || current->_8.size() <= i)
                            continue;
                        auto* entry = ksys::act::sub_7100D78E30(&current->_8, i);
                        if (entry && entry->mLink == *mTargetActor_d) {
                            found = true;
                            break;
                        }
                    }
                }
            }
        }
        if (found)
            return;
        changeChild("待機");
    }
}

void GolemNoticeWorry::leave_() {
    ksys::act::ai::Ai::leave_();
}

void GolemNoticeWorry::loadParams_() {
    getStaticParam(&mTurnStartAngle_s, "TurnStartAngle");
    getDynamicParam(&mTargetPos_d, "TargetPos");
    getDynamicParam(&mTargetActor_d, "TargetActor");
}

}  // namespace uking::ai
