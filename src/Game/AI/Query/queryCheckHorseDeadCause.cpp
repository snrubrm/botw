#include "Game/AI/Query/queryCheckHorseDeadCause.h"
#include <evfl/Query.h>
#include "KingSystem/GameData/gdtManager.h"

namespace uking::query {

CheckHorseDeadCause::CheckHorseDeadCause(const InitArg& arg) : ksys::act::ai::Query(arg) {}

CheckHorseDeadCause::~CheckHorseDeadCause() = default;

// NON_MATCHING: same logic; the original computes `(cause >> 16) - 1` with a separate lsr / sub and
// compares with `hi #2`, ours folds it to `add w8, 0xffff, cause >> 16` and compares with `hs #3`.
int CheckHorseDeadCause::doQuery() {
    auto* gdm = ksys::gdt::Manager::instance();
    if (gdm != nullptr) {
        s32 index = -1;
        if (gdm->getParam().get().getS32(&index, "Horse_SelectedIndex") && index != -1) {
            s32 cause = 0;
            if (gdm->getParam().get().getS32(&cause, "DeadHorse_DeadCause", index)) {
                if ((cause & 0xffff) == 7)
                    return 4;
                const u16 kind = u32(cause) >> 16;
                const u16 type = kind - 1;
                if (type < 3)
                    return type + 1;
            }
        }
    }
    return 0;
}

void CheckHorseDeadCause::loadParams(const evfl::QueryArg& arg) {}

void CheckHorseDeadCause::loadParams() {}

}  // namespace uking::query
