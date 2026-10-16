#include "Game/Actor/Behavior/behaviorBgmCtrlBehavior.h"
#include "Game/gameUnkRttiPlaceholders.h"
#include "KingSystem/Sound/sndBgmMgr.h"

namespace uking::behavior {

BgmCtrlBehavior::BgmCtrlBehavior(const InitArg& arg) : ksys::act::ai::Behavior(arg) {}

// Empty-statement body as in upstream's GameDataFlagSelector::~GameDataFlagSelector() (96101229):
// the original keeps the vtable store that a defaulted destructor drops (SafeString member).
BgmCtrlBehavior::~BgmCtrlBehavior() {
    ;
}

bool BgmCtrlBehavior::init_(sead::Heap* heap) {
    return true;
}

void BgmCtrlBehavior::calc() {}

void BgmCtrlBehavior::enter() {
    using ksys::snd::RemainsBossBgmType;
    if (mBgmName_s == "RemainsBoss_Wind")
        ksys::snd::sub_7100FFEBE0(RemainsBossBgmType::Wind);
    else if (mBgmName_s == "RemainsBoss_Fire")
        ksys::snd::sub_7100FFEBE0(RemainsBossBgmType::Fire);
    else if (mBgmName_s == "RemainsBoss_Water")
        ksys::snd::sub_7100FFEBE0(RemainsBossBgmType::Water);
    else if (mBgmName_s == "RemainsBoss_Elec")
        ksys::snd::sub_7100FFEBE0(RemainsBossBgmType::Elec);
    else
        return;

    if (auto* bgm = ksys::snd::sub_7100FFE7A4())
        bgm->_20c |= 2;
    if (auto* bgm = ksys::snd::sub_7100FFEA3C())
        bgm->_1d4 |= 2;
}

void BgmCtrlBehavior::leave() {}

void BgmCtrlBehavior::loadParams() {
    getStaticParam(&mFadeTime_s, "FadeTime");
    getStaticParam(&mCtrlType_s, "CtrlType");
    getStaticParam(&mBgmName_s, "BgmName");
}

}  // namespace uking::behavior
