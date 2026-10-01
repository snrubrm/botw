#include "Game/AI/Action/actionDefeatedHugeEnemyCount.h"
#include "KingSystem/GameData/gdtCommonFlagsUtils.h"
#include "KingSystem/GameData/gdtManager.h"

namespace uking::action {

DefeatedHugeEnemyCount::DefeatedHugeEnemyCount(const InitArg& arg) : ksys::act::ai::Action(arg) {}

DefeatedHugeEnemyCount::~DefeatedHugeEnemyCount() = default;

bool DefeatedHugeEnemyCount::init_(sead::Heap* heap) {
    return ksys::act::ai::Action::init_(heap);
}

void DefeatedHugeEnemyCount::enter_(ksys::act::ai::InlineParamPack* params) {
    auto* gdm = ksys::gdt::Manager::instance();
    if (gdm) {
        const s32 type = *mEnemyType_d;
        s32 category;
        switch (type) {
        case 0:
            category = 7;
            break;
        case 1:
            category = 9;
            break;
        case 2:
            category = 8;
            break;
        default:
            category = 7;
            break;
        }
        const s32 num = gdm->getParam().get().getBuffer0()->getNumBoolFlagsPerCategory0(category);
        switch (type) {
        case 0:
            ksys::gdt::setFlag_DefeatedForestGiantNum(num);
            break;
        case 1:
            ksys::gdt::setFlag_DefeatedGolemNum(num);
            break;
        case 2:
            ksys::gdt::setFlag_DefeatedSandwormNum(num);
            break;
        }
    }
    _28 = true;
}

void DefeatedHugeEnemyCount::leave_() {
    ksys::act::ai::Action::leave_();
}

void DefeatedHugeEnemyCount::loadParams_() {
    getDynamicParam(&mEnemyType_d, "EnemyType");
}

void DefeatedHugeEnemyCount::calc_() {
    if (_28) {
        _28 = false;
        return;
    }
    setFinished();
}

}  // namespace uking::action
