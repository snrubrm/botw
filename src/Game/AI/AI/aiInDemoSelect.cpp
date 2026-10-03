#include "Game/AI/AI/aiInDemoSelect.h"
#include <random/seadGlobalRandom.h>
#include <math/seadMathCalcCommon.h>
#include "KingSystem/ActorSystem/actActor.h"
#include "KingSystem/Event/evtUnk_7100dc816c.h"
#include "KingSystem/Map/mapObject.h"

namespace uking::ai {

InDemoSelect::InDemoSelect(const InitArg& arg) : ksys::act::ai::Ai(arg) {}

// The original keeps the vtable store that a defaulted destructor drops (same form as upstream's
// GameDataFlagSelector::~GameDataFlagSelector() { ; }, commit 96101229).
InDemoSelect::~InDemoSelect() {
    ;
}

bool InDemoSelect::init_(sead::Heap* heap) {
    return ksys::act::ai::Ai::init_(heap);
}

void InDemoSelect::enter_(ksys::act::ai::InlineParamPack* params) {
    if (ksys::evt::sub_7100DC8684(mDemoFile_s, mDemoEntryPoint_s)) {
        const s32 delay_max = *mDemoRetDelayMax_s;
        _74 = sead::Mathi::min(delay_max, 0);
        _78 = sead::Mathi::max(delay_max, 0);
        _70 = _74 == _78 ? _74 : sead::GlobalRandom::instance()->getS32Range(_74, _78);
        _7c = false;
        auto* map_object = mActor->getMapObject();
        if (mActor->get1a0() ||
            (map_object && map_object->getFlags0().isOn(ksys::map::Object::Flag0::_20000))) {
            changeChild("デモ中", params);
            return;
        }
        if (*mOtherDemoNoRun_s) {
            changeChild("非参加デモ", params);
            return;
        }
    }
    changeChild("デモ終了", params);
}

void InDemoSelect::leave_() {
    ksys::act::ai::Ai::leave_();
}

void InDemoSelect::loadParams_() {
    getStaticParam(&mDemoRetDelayMax_s, "DemoRetDelayMax");
    getStaticParam(&mOtherDemoNoRun_s, "OtherDemoNoRun");
    getStaticParam(&mForceChangeDemo_s, "ForceChangeDemo");
    getStaticParam(&mDemoFile_s, "DemoFile");
    getStaticParam(&mDemoEntryPoint_s, "DemoEntryPoint");
}

}  // namespace uking::ai
