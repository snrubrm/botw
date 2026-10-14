#include "Game/Actor/Action/actionSoundShieldingAreaTagAction.h"
#include "KingSystem/Sound/sndSound.h"
#include "KingSystem/ActorSystem/actActor.h"
#include "KingSystem/ActorSystem/actActorCreator.h"
#include "KingSystem/ActorSystem/actActorLinkConstDataAccess.h"
#include "KingSystem/ActorSystem/actActorUtil.h"
#include "KingSystem/ActorSystem/Profiles/actAreaActor.h"
#include "KingSystem/Map/mapObject.h"
#include <math/seadMathCalcCommon.h>

namespace uking::action {

SoundShieldingAreaTagAction::SoundShieldingAreaTagAction(const InitArg& arg) : AreaActionBase(arg) {}

SoundShieldingAreaTagAction::~SoundShieldingAreaTagAction() {
    ksys::snd::SoundMgr::instance()->_a8->sub_710104B554(_a0);
    _a0 = nullptr;
}

bool SoundShieldingAreaTagAction::init_(sead::Heap* heap) {
    _48.tryAllocBuffer(1, heap);
    if (!_48.getBufferPtr())
        return false;
    _48[0]._0 = ksys::phys::ContactLayer::SensorPlayer;
    if (auto* object = mActor->getMapObject()) {
        if (object->getHashId() == u32(-1))
            return false;
        _a0 = ksys::snd::SoundMgr::instance()->_a8->sub_710104B480(object->getHashId());
        if (!_a0->_491) {
            _a0->sub_710104ABE8();
            sub_7100FF3E48();
        }
        return true;
    }
    return ksys::act::ActorCreator::instance()->isBlockSpawns();
}

void SoundShieldingAreaTagAction::sub_7100FF3E48() {
    s32 index = -1;
    auto* sound = _a0;
    sound->_220.clear();
    sound->_0.clear();
    while (true) {
        auto* object = ksys::act::findLinkReferenceObj(mActor, "", "", &index);
        if (index < 0)
            break;
        ++index;
        _a0->sub_710104ACF8(object);
    }
}

void SoundShieldingAreaTagAction::enter_(ksys::act::ai::InlineParamPack* params) {
    AreaActionBase::enter_(params);
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
    AreaActionBase::calc_();
    f32 value = 0.0f;
    if (_9c) {
        value = _98;
        --_9c;
    }
    _a0->_440 = value;
}

// NON_MATCHING: stack allocation and loop block layout differ.
bool SoundShieldingAreaTagAction::m15(const ksys::act::ActorLinkConstDataAccess& accessor) {
    ksys::act::acc::AreaActor area;
    f32 value = -1.0f;
    s32 index = getAreaCol(&area, -1);
    if (index >= 0 && index < 16) {
        f32 max_distance = 0.0f;
        do {
            if (area.hasProc()) {
                auto* collision = area.getField848();
                if (collision && collision->getCollidingBodies().size() != 0) {
                    if (auto* contacts = area.getField850()) {
                        if (contacts->getNumContactPoints() != 0 && !contacts->begin().isEnd()) {
                            f32 distance = 0.0f;
                            for (const auto* point : *contacts)
                                distance = sead::Mathf::max(
                                    sead::Mathf::abs(point->separating_distance), distance);
                            _58[index] = distance;
                        }
                        max_distance = sead::Mathf::max(_58[index], max_distance);
                    }
                } else {
                    _58[index] = 0.0f;
                }
            }
            index = getAreaCol(&area, index);
        } while (index >= 0 && index < 16);
        if (max_distance > 0.0f)
            value = max_distance >= *mMerginDistance_m ? 1.0f : max_distance / *mMerginDistance_m;
    }
    _9c = 1;
    _98 = value;
    if (*mIsShieldChemicalWind_m)
        ksys::snd::SoundMgr::instance()->_a8->_4a72 = 2;
    return true;
}

}  // namespace uking::action
