#include "Game/Actor/Action/actionAnimalMoveStraightTimed.h"
#include <random/seadGlobalRandom.h>
#include <limits>
#include "Game/Actor/actRideable.h"
#include "Game/Actor/aiUnk_71007377D4.h"
#include "KingSystem/Physics/CharacterController/physCharacterController.h"
#include "KingSystem/Physics/System/physNavMeshCharacter.h"
#include "KingSystem/ActorSystem/actActor.h"

namespace uking::action {

AnimalMoveStraightTimed::AnimalMoveStraightTimed(const InitArg& arg) : ksys::act::ai::Action(arg) {}

AnimalMoveStraightTimed::~AnimalMoveStraightTimed() = default;

bool AnimalMoveStraightTimed::init_(sead::Heap* heap) {
    return ksys::act::ai::Action::init_(heap);
}

void AnimalMoveStraightTimed::enter_(ksys::act::ai::InlineParamPack* params) {
    _68.reset(*mFramesUntilFinish_s);
    if (auto* rideable = mActor->m132()) {
        const s32 min_gear = *mMinUseGear_s;
        const s32 max_gear = *mMaxUseGear_s;
        const s32 gear = sead::GlobalRandom::instance()->getS32Range(min_gear, max_gear);
        rideable->sub_7100E63224(u32(*mUseGearType_s), u32(gear));
    } else {
        setFailed();
    }
}

void AnimalMoveStraightTimed::leave_() {
    if (auto* navmesh = mActor->m45())
        navmesh->sub_7100F76314();
}

void AnimalMoveStraightTimed::loadParams_() {
    getStaticParam(&mFramesUntilFinish_s, "FramesUntilFinish");
    getStaticParam(&mMinUseGear_s, "MinUseGear");
    getStaticParam(&mMaxUseGear_s, "MaxUseGear");
    getStaticParam(&mUseGearType_s, "UseGearType");
    getStaticParam(&mMinGearAtAutoGearDown_s, "MinGearAtAutoGearDown");
    getStaticParam(&mLOSCheckTimeAhead_s, "LOSCheckTimeAhead");
    getStaticParam(&mIsFinishOnLOSCheckFail_s, "IsFinishOnLOSCheckFail");
    getStaticParam(&mUseDesiredMoveDir_s, "UseDesiredMoveDir");
    getStaticParam(&mIsAutoGearDownEnabled_s, "IsAutoGearDownEnabled");
}

// NON_MATCHING: speed-table/vector scheduling and stack allocation.
void AnimalMoveStraightTimed::calc_() {
    _68.update();
    if (_68.value <= std::numeric_limits<f32>::epsilon())
        setFinished();
    auto* rideable = mActor->m132();
    auto* as_list = mActor->getASList();
    auto* controller = mActor->getCharacterController();
    auto* navmesh = mActor->m45();
    if (!rideable || !as_list || !controller || !navmesh) {
        setFailed();
        return;
    }
    if (*mIsFinishOnLOSCheckFail_s) {
        const act::Rideable::Gear gear(rideable->_18._b == 0 ? rideable->_18._9 : rideable->_18._b);
        s32 row = rideable->_18._a;
        const auto* speed = &act::sUnk_7102603058;
        if (gear != act::Rideable::Gear::_0 && rideable->_170) {
            if (row >= rideable->_178)
                row = 0;
            speed = &rideable->_170->mGears[row][int(gear) - 1];
        }
        const f32 distance = speed->mSpeed * rideable->_164 * *mLOSCheckTimeAhead_s / 30.0f;
        const sead::Vector3f from = mActor->getMtx().getTranslation();
        const sead::Vector3f to = from + controller->get64() * distance;
        sead::Vector3f position;
        if (!sub_710072FBD4(mActor, from, to, &position, -1, 0.0f, -1.0f))
            setFinished();
    }
    act::sub_7100E7F698(rideable, as_list, controller);
    const act::Rideable::Gear gear(sead::Mathi::max(
        rideable->_18._b == 0 ? rideable->_18._9 : rideable->_18._b, 1));
    s32 row = *mUseGearType_s;
    const auto* speed = &act::sUnk_7102603058;
    if (gear != act::Rideable::Gear::_0 && rideable->_170) {
        if (row >= rideable->_178)
            row = 0;
        speed = &rideable->_170->mGears[row][int(gear) - 1];
    }
    const f32 value = speed->mSpeed * rideable->_164;
    navmesh->inlineSetField2C0(value);
    navmesh->inlineSetField2BC(value);
    sead::Vector3f direction = *mUseDesiredMoveDir_s ? rideable->_148 : sead::Vector3f::zero;
    if (direction == sead::Vector3f::zero)
        direction = controller->get64();
    navmesh->sub_7100F76260(direction * value);
    rideable->sub_7100E63224(u32(*mUseGearType_s), u32(int(gear)));
}

}  // namespace uking::action
