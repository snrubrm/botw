#include "Game/AI/Query/queryCheckReceiveTerrorLevel.h"
#include <evfl/Query.h>
#include "KingSystem/ActorSystem/Awareness/actAwarenessInstance.h"
#include "KingSystem/ActorSystem/actActor.h"

namespace uking::query {

CheckReceiveTerrorLevel::CheckReceiveTerrorLevel(const InitArg& arg) : ksys::act::ai::Query(arg) {}

CheckReceiveTerrorLevel::~CheckReceiveTerrorLevel() = default;

int CheckReceiveTerrorLevel::doQuery() {
    if (auto* awareness = mActor->getAwareness()) {
        if (auto* sensor = awareness->_260[2]) {
            if (sensor->_8.size() >= 1) {
                if (auto* entry = ksys::act::sub_7100D78E30(&sensor->_8, 0)) {
                    const s32 level = s32(entry->_a4);
                    if (u32(level) < 6)
                        return level;
                }
            }
        }
    }
    return 0;
}

void CheckReceiveTerrorLevel::loadParams(const evfl::QueryArg& arg) {}

void CheckReceiveTerrorLevel::loadParams() {}

}  // namespace uking::query
