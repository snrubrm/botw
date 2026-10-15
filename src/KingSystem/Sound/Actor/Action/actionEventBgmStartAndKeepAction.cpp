#include "KingSystem/Sound/Actor/Action/actionEventBgmStartAndKeepAction.h"
#include "KingSystem/Sound/sndBgmMgr.h"

namespace ksys::snd {

EventBgmStartAndKeepAction::EventBgmStartAndKeepAction(const InitArg& arg)
    : ksys::act::ai::Action(arg) {}

EventBgmStartAndKeepAction::~EventBgmStartAndKeepAction() = default;

bool EventBgmStartAndKeepAction::init_(sead::Heap* heap) {
    return ksys::act::ai::Action::init_(heap);
}

void EventBgmStartAndKeepAction::enter_(ksys::act::ai::InlineParamPack* params) {
    ksys::snd::sub_7100FFD784()->sub_71010078A0(mBgmName_d);
    _30 = false;
}

void EventBgmStartAndKeepAction::leave_() {
    ksys::act::ai::Action::leave_();
}

void EventBgmStartAndKeepAction::loadParams_() {
    getDynamicParam(&mBgmName_d, "BgmName");
}

// NON_MATCHING: the original reads _30 before the getAliveAssetNum call (ours after it).
void EventBgmStartAndKeepAction::calc_() {
    if (isFinishedOrFailed())
        return;

    auto* bgm = sub_7100FFD784()->find(mBgmName_d);
    if (!bgm) {
        setFinished();
        return;
    }
    if (!sead::IsDerivedFrom<Unk_710260ecf8>(bgm)) {
        setFailed();
        return;
    }
    if (bgm->_124 == 1)
        return;

    if (bgm->mEntries.size() >= 1) {
        auto* entry = bgm->mEntries.front();
        if (entry && entry->mHandle.isActive()) {
            const s32 num = entry->mHandle.getEvent()->getAliveAssetNum();
            if (!_30) {
                if (num != 0)
                    _30 = true;
                return;
            }
            if (num != 0)
                return;
        }
    }
    setFinished();
}

}  // namespace ksys::snd
