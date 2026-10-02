#include "Game/AI/AI/aiAroundEnemyCheckSelect.h"
#include "KingSystem/ActorSystem/actActor.h"
#include "Game/AI/aiAwarenessFilters.h"

namespace uking::ai {

AroundEnemyCheckSelect::AroundEnemyCheckSelect(const InitArg& arg) : ksys::act::ai::Ai(arg) {}

AroundEnemyCheckSelect::~AroundEnemyCheckSelect() = default;

bool AroundEnemyCheckSelect::isFailed() const {
    return getCurrentChild()->isFailed();
}

bool AroundEnemyCheckSelect::isFinished() const {
    return getCurrentChild()->isFinished();
}

// NON_MATCHING: the original destroys the filter and picks the child name in each exit path
// (no csel); tried a flag and a name variable
void AroundEnemyCheckSelect::enter_(ksys::act::ai::InlineParamPack* params) {
    bool found = false;
    if (mActor) {
        if (auto* awareness = mActor->getAwareness()) {
            Unk_7102451448 filter;
            while (auto* entry = ksys::act::sub_7100D7EEE8(&awareness->_8, &filter)) {
                if (entry->_a8 < *mCheckDist_s) {
                    found = true;
                    break;
                }
            }
        }
    }
    changeChild(found ? "いる" : "いない", params);
}

void AroundEnemyCheckSelect::calc_() {
    if (getCurrentChild()->isFinished())
        setFinished();
    else if (getCurrentChild()->isFailed())
        setFailed();
}

void AroundEnemyCheckSelect::leave_() {
    ksys::act::ai::Ai::leave_();
}

void AroundEnemyCheckSelect::loadParams_() {
    getStaticParam(&mCheckDist_s, "CheckDist");
}

}  // namespace uking::ai
