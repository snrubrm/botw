#include "Game/Actor/Horse/Action/actionHorseSwimAction.h"
#include "KingSystem/Physics/System/physNavMeshCharacter.h"
#include "KingSystem/Physics/System/physHavokAI.h"
#include "KingSystem/ActorSystem/actActor.h"

namespace uking::action {

// NON_MATCHING: the original tests the filter's m4 result in place; ours copies it and zeroes the
// return register before the shared false branch.
bool HorseSwimFaceQuery::m0(const ksys::phys::Unk_7100f7e9f0& face) {
    sead::Vector3f normal = sead::Vector3f::zero;
    if (!(face.sub_7100F7ED6C(&normal) > _34))
        return false;
    if (!(normal.y > _38))
        return false;
    sead::Vector3f position;
    face.sub_7100F7EB60(&position);
    auto* character = mCharacter;
    auto* filter = character->_58;
    const auto type = ksys::phys::NavMeshCharacterType(character->_1d8);
    const s32 material = face.sub_7100F7EEE4();
    if (filter) {
        if (filter->m4(character, material, 0, ksys::phys::NavMeshCharacterType::Player)) {
            _40 = face;
            return true;
        }
        return false;
    }
    if (sead::Mathf::abs(ksys::phys::NavMeshCharacter::sub_7100F74FD8(type, material)) >
        std::numeric_limits<f32>::max())
        return false;
    _40 = face;
    return true;
}

HorseSwimAction::HorseSwimAction(const InitArg& arg) : HorseSwim(arg) {}

HorseSwimAction::~HorseSwimAction() = default;

bool HorseSwimAction::init_(sead::Heap* heap) {
    return HorseSwim::init_(heap);
}

void HorseSwimAction::enter_(ksys::act::ai::InlineParamPack* params) {
    HorseSwim::enter_(params);
}

void HorseSwimAction::leave_() {
    HorseSwim::leave_();
    if (_60) {
        if (auto* nav = mActor->m45())
            nav->sub_7100F75AB8();
        _60 = false;
    }
    if (_58) {
        ksys::phys::HavokAI::instance()->destroyQuery(_58);
        _58 = nullptr;
    }
}

void HorseSwimAction::loadParams_() {
    HorseSwim::loadParams_();
    getStaticParam(&mLandSearchRadius_s, "LandSearchRadius");
    getStaticParam(&mLandSearchNormalCos_s, "LandSearchNormalCos");
    getStaticParam(&mLandSearchMinArea_s, "LandSearchMinArea");
    getStaticParam(&mLandSearchIntervalFrames_s, "LandSearchIntervalFrames");
    getStaticParam(&mResolvePenetrationRadiusScale_s, "ResolvePenetrationRadiusScale");
    getStaticParam(&mResolvePenetrationSearchRadius_s, "ResolvePenetrationSearchRadius");
}

void HorseSwimAction::calc_() {
    HorseSwim::calc_();
}

}  // namespace uking::action
