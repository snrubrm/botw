#include "Game/AI/AI/aiRemainsWindRoot.h"
#include "KingSystem/GameData/gdtCommonFlagsUtils.h"

namespace uking::ai {

RemainsWindRoot::RemainsWindRoot(const InitArg& arg) : RemainsRoot(arg) {}

RemainsWindRoot::~RemainsWindRoot() = default;

bool RemainsWindRoot::init_(sead::Heap* heap) {
    return RemainsRoot::init_(heap);
}

void RemainsWindRoot::enter_(ksys::act::ai::InlineParamPack* params) {
    RemainsRoot::enter_(params);
}

bool RemainsWindRoot::reenter_(ksys::act::ai::ActionBase* other, bool x) {
    if (!RemainsRoot::reenter_(other, true))
        return false;

    auto* other_root = sead::DynamicCast<RemainsWindRoot>(other);
    if (!other_root)
        return false;

    _70 = other_root->_70;
    return true;
}

void RemainsWindRoot::calc_() {
    RemainsRoot::calc_();
    m35(false);
}

void RemainsWindRoot::leave_() {
    RemainsRoot::leave_();
}

void RemainsWindRoot::loadParams_() {
    RemainsRoot::loadParams_();
}

void RemainsWindRoot::m34() {
    if (ksys::gdt::getFlag_Wind_Relic_BattleStart() || hasPendingChildChange())
        return;
    RemainsRoot::m34();
}

void RemainsWindRoot::m35(bool x) {
    if (_49) {
        if (!isCurrentChild("通常行動"))
            m36();
        return;
    }

    if (ksys::gdt::getFlag_Wind_Relic_BattleStart()) {
        if (x || !_70)
            m37();
    } else {
        if (x || _70)
            m36();
    }
}

void RemainsWindRoot::m36() {
    _70 = false;
    RemainsRoot::m36();
}

void RemainsWindRoot::m37() {
    _70 = true;
    changeChild("遺物チャレンジ中");
}

}  // namespace uking::ai
