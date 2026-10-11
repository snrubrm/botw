#include "Game/AI/Action/actionSetChallengeIcon.h"
#include "Game/UI/uiUtils.h"
#include "KingSystem/Quest/qstManager.h"

namespace uking::action {

SetChallengeIcon::SetChallengeIcon(const InitArg& arg) : ksys::act::ai::Action(arg) {}

SetChallengeIcon::~SetChallengeIcon() = default;

bool SetChallengeIcon::init_(sead::Heap* heap) {
    return ksys::act::ai::Action::init_(heap);
}

bool SetChallengeIcon::oneShot_() {
    if (mChallengeName_d.isEmpty()) {
        ui::sub_7100A9A6C4(nullptr);
    } else if (auto* mgr = ksys::qst::Manager::instance()) {
        const s32 count = mgr->mQuests.size();
        for (s32 i = 0; i < count; ++i) {
            if (mChallengeName_d.isEqual(mgr->mQuests[i]->mName)) {
                ui::sub_7100A9A6C4(mgr->mQuests[i]);
                break;
            }
        }
    }
    return true;
}

void SetChallengeIcon::loadParams_() {
    getDynamicParam(&mChallengeName_d, "ChallengeName");
}

}  // namespace uking::action
