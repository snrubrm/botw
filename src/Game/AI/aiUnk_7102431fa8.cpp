#include "Game/AI/aiUnk_7102431fa8.h"
#include "Game/Damage/dmgInfoManager.h"

void Unk_7102431fa8::sub_7100741E14() {
    uking::dmg::DamageInfoMgr::instance()->get790().sub_7100672888(_d0);
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
