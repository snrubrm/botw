#include "KingSystem/Event/evtS7.h"
#include "Game/gameRoot38.h"
#include "Game/UI/uiUnkSingletons.h"
#include "Game/UI/uiUI.h"
#include "KingSystem/ActorSystem/Profiles/actPlayerBase.h"
#include "KingSystem/Event/evtEventSystem.h"
#include "KingSystem/Event/evtManager.h"
#include "KingSystem/Physics/System/physSystem.h"

namespace ksys::evt {

const char* sub_71008B84F0(s32 state);

// 0x71008afb38
void S7EventFlow::m4() {
    mState = 1;
    _24 = 0;
    _28 = 0;
    mStatus.copy(sub_71008B84F0(1));
    _28 = 0;
    _2c = -1;
    _30 = 0;
    _1c = 0;
    _38 = 0;
    _3c = -1;
    _64 = -1;
    _68 = 0;
    _40 = false;
    _48 = 0;
    sub_71008AF278();
}

// 0x71008b84e0 (CSV evt::S7EventFlow::isPlaying)
bool S7EventFlow::isPlaying() {
    return mState == 3;
}

// 0x71008b6748
// NON_MATCHING: only the int-conversion spill slot differs (original reuses [sp, #0x8], later reused
// by the accessor; ours uses a separate top-of-frame slot). Tried switch-on-member, switch-on-getType
// (matches in m9), if with !=, by-value local, and orderings - the spill address is the only diff.
void S7EventFlow::setup_1() {
    mFlow->getBaseProcLink();
    if (int(mFlow->getType()) != EventFlowType::MovieWithNoPath) {
        ksys::act::acc::PlayerBase accessor;
        accessor.getPlayerFromPlayerInfo();
        Manager::instance()->sub_7100DB0FB0(*accessor.getMessageTransceiverId(),
                                            MessageType(0x80000b2), nullptr);
        uking::ui::UI* ui = uking::ui::UI::instance();
        if (ui)
            ui->x_0(false);
        EventSystem::instance()->_144 &= ~1;
    }
}
// 0x71008afcdc
bool S7EventFlow::calc() {
    const u32 result = calc_();
    if (_14 & 2)
        uking::sub_7100F41834();
    if (_3c >= 0) {
        if (_3c == 0) {
            phys::System::instance()->sub_71012167EC(false);
            _3c = -1;
        } else {
            _3c += 1;
        }
    }
    return result & 1;
}

// 0x71008b2eb4
void S7EventFlow::m9() {
    setupDemoOverrides(true);
    switch (mFlow->getType()) {
    case EventFlowType::MovieWithNoPath:
        break;
    default:
        mFlow->x_6();
        _1c |= 0x80;
        if (mFlow->_340_bytes[3] & 2) {
            if (uking::ui::UiSubsys1::instance()->sub_71008B43CC()) {
                _1c |= 0x10000;
                uking::ui::UiSubsys1::instance()->set4cc(true);
            }
        }
        break;
    }
    setup_1_1();
    x(0);
}

// 0x71008b6f20 (CSV evt::S7EventFlow::getStatusStr)
const char* S7EventFlow::m7() {
    return mStatus.cstr();
}

}  // namespace ksys::evt
