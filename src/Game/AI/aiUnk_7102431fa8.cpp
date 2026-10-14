#include "Game/AI/aiUnk_7102431fa8.h"
#include "Game/Damage/dmgInfoManager.h"
#include "Game/AI/aiUnk_71005D6D10.h"
#include "Game/Actor/actEnemy.h"
#include "KingSystem/ActorSystem/AS/ASList.h"

// NON_MATCHING: cancellation and animation-state stores are scheduled differently.
void Unk_7102431fa8::sub_7100741C24() {
    if (_10) {
        const auto* life = _d0->getLife();
        if ((life && *life < 1) || !sub_71005D8F28(_d0) ||
            !uking::act::DamageInfoMgr::instance()->get790().sub_71006726DC(_14[0]) ||
            !uking::act::DamageInfoMgr::instance()->get790().sub_7100672B00(_d0))
            sub_7100741E14();
    }
    if (_8 == 2)
        _8 = 0;
    if (_c == 0)
        return;
    if (auto* enemy = sead::DynamicCast<uking::act::Enemy>(_d0)) {
        if (enemy->m151(3))
            return;
    }
    auto* as_list = _d0->getASList();
    if (!as_list)
        return;
    if (_c == 1) {
        switch (_8) {
        case 0:
            _8 = 1;
            _c = 0;
            as_list->startAnimationMaybe(-1.0f, -1.0f, _20, _14[1], 0, true);
            break;
        case 1:
            _c = 0;
            break;
        }
    }
    if (_c == 2) {
        switch (_8) {
        case 0:
        case 2:
            _c = 0;
            break;
        case 1:
            _8 = 2;
            _c = 0;
            as_list->startAnimationMaybe(-1.0f, -1.0f, _78, _14[1], 0, true);
            break;
        }
    }
}

void Unk_7102431fa8::sub_7100741E14() {
    uking::act::DamageInfoMgr::instance()->get790().sub_7100672888(_d0);
    _c = 2;
    _10 = false;
}

void Unk_7102431fa8::sub_71007420B8(const sead::SafeString& start_as_name,
                                   const sead::SafeString& stop_as_name, s32 target_idx) {
    _20.copy(start_as_name);
    _78.copy(stop_as_name);
    _14[1] = target_idx;
    _8 = 0;
    _c = 0;
}
