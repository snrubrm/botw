#include "Game/AI/Action/actionSpotBgmTriggerAction.h"
#include "KingSystem/Sound/sndBgmMgr.h"

void Unk_SpotBgmHandle::sub_710101D970() {
    if (auto* mgr = ksys::snd::sub_7100FFD754())
        mgr->sub_710101D5EC(this);
}

void Unk_SpotBgmHandle::sub_710101D9A4() {
    if (auto* mgr = ksys::snd::sub_7100FFD754())
        mgr->sub_710101D718(this);
}

void Unk_SpotBgmInstance::sub_71010242F0() {
    _308 = 1;
    _368 |= 0x200;
    _310.setValueImmediate(0.0f);
}
