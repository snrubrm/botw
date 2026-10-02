#include "Game/AI/AI/aiPriestBossPhaseSelector.h"

namespace uking::ai {

PriestBossPhaseSelector::PriestBossPhaseSelector(const InitArg& arg) : PriestBossMode(arg) {}

PriestBossPhaseSelector::~PriestBossPhaseSelector() = default;

bool PriestBossPhaseSelector::init_(sead::Heap* heap) {
    return PriestBossMode::init_(heap);
}

void PriestBossPhaseSelector::enter_(ksys::act::ai::InlineParamPack* params) {
    PriestBossMode::enter_(params);
    auto* unit = sub_7100505BE4();
    if (!unit)
        return;

    _48 = unit->_3c;
    _4c = _48;
    const Unk_7102450fa8::Phase phase = _48;
    switch (phase) {
    case Unk_7102450fa8::Phase::_0:
        changeChild("第一段階");
        break;
    case Unk_7102450fa8::Phase::_1:
        changeChild("第二段階");
        break;
    case Unk_7102450fa8::Phase::_2:
        changeChild("第三段階");
        break;
    case Unk_7102450fa8::Phase::_3:
        changeChild("第四段階");
        break;
    }
    _50 = true;
}

// NON_MATCHING: the original reloads _48 and _4c for the comparison (as with SEAD_ENUM's volatile
// operator int on both sides); the member operator!= compares the stored values directly
void PriestBossPhaseSelector::calc_() {
    PriestBossMode::calc_();
    auto* unit = sub_7100505BE4();
    if (!unit)
        return;

    _4c = _48;
    _48 = unit->_3c;
    if (_48 != _4c && (!*mIsSelectOnlyOnce_s || !_50)) {
        const Unk_7102450fa8::Phase phase = _48;
        switch (phase) {
        case Unk_7102450fa8::Phase::_0:
            changeChild("第一段階");
            break;
        case Unk_7102450fa8::Phase::_1:
            changeChild("第二段階");
            break;
        case Unk_7102450fa8::Phase::_2:
            changeChild("第三段階");
            break;
        case Unk_7102450fa8::Phase::_3:
            changeChild("第四段階");
            break;
        }
        _50 = true;
    }

    auto* child = getCurrentChild();
    if (!child)
        return;
    if (child->isFinished())
        setFinished();
    else if (child->isFailed())
        setFailed();
}

void PriestBossPhaseSelector::leave_() {
    PriestBossMode::leave_();
}

void PriestBossPhaseSelector::loadParams_() {
    PriestBossMode::loadParams_();
    getStaticParam(&mIsSelectOnlyOnce_s, "IsSelectOnlyOnce");
}

}  // namespace uking::ai
