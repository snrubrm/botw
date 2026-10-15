#include "Game/Actor/Behavior/behaviorGuardTgtControl.h"
#include "KingSystem/ActorSystem/actActorSensorUtil.h"
#include "Game/Actor/aiUnk_71007377D4.h"
#include "KingSystem/ActorSystem/actActor.h"
#include "KingSystem/ActorSystem/actBaseProcLink.h"
#include "KingSystem/ActorSystem/AS/ASList.h"

namespace uking::behavior {

GuardTgtControl::GuardTgtControl(const InitArg& arg) : ksys::act::ai::Behavior(arg) {}

// Empty-statement body as in upstream's GameDataFlagSelector::~GameDataFlagSelector() (96101229):
// the original keeps the vtable store that a defaulted destructor drops (SafeString member).
GuardTgtControl::~GuardTgtControl() {
    ;
}

void GuardTgtControl::loadParams() {
    getStaticParam(&mGuardTgtName_s, "GuardTgtName");
}

void GuardTgtControl::m8() {
    _38 = false;
    sub_71007A3910(mActor, mGuardTgtName_s.cstr());
}

void GuardTgtControl::m7() {
    bool guarding = false;
    {
        ksys::act::BaseProcLink link;
        sub_7100736114(&link, mActor);
        if (link.hasProc()) {
            guarding = mActor->getASList()->x(
                14, nullptr, 0, 0, &ksys::as::ASList::Unk2::sub_71011638DC, true);
        }
    }
    if (guarding) {
        if (!_38) {
            _38 = true;
            sub_71007A3778(mActor, mGuardTgtName_s.cstr());
        }
    } else if (_38) {
        _38 = false;
        sub_71007A3910(mActor, mGuardTgtName_s.cstr());
    }
}

void GuardTgtControl::m9() {
    sub_71007A3910(mActor, mGuardTgtName_s.cstr());
}

}  // namespace uking::behavior
