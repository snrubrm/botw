#include "Game/AI/Action/actionSoundShieldingAreaTagAction.h"
#include "KingSystem/Sound/sndMgr.h"

namespace uking::action {

SoundShieldingAreaTagAction::SoundShieldingAreaTagAction(const InitArg& arg) : AreaTagAction(arg) {}

SoundShieldingAreaTagAction::~SoundShieldingAreaTagAction() {
    ksys::snd::SoundMgr::instance()->_a8->sub_710104B554(_a0);
    _a0 = nullptr;
}

bool SoundShieldingAreaTagAction::init_(sead::Heap* heap) {
    return AreaTagAction::init_(heap);
}

void SoundShieldingAreaTagAction::enter_(ksys::act::ai::InlineParamPack* params) {
    AreaTagAction::enter_(params);
    if (!_a0->sub_710104ACB4())
        _a0->_490 = true;
}

void SoundShieldingAreaTagAction::leave_() {
    _a0->_490 = false;
}

void SoundShieldingAreaTagAction::loadParams_() {
    getMapUnitParam(&mMerginDistance_m, "MerginDistance");
    getMapUnitParam(&mIsShieldChemicalWind_m, "IsShieldChemicalWind");
}

void SoundShieldingAreaTagAction::calc_() {
    AreaTagAction::calc_();
    f32 value = 0.0f;
    if (_9c) {
        value = _98;
        --_9c;
    }
    _a0->_440 = value;
}

}  // namespace uking::action
