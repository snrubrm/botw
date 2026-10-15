#include "Game/Actor/Action/actionAnmUpDownMove.h"
#include <prim/seadStringUtil.h>
#include "Game/Actor/aiUnk_71005D6D10.h"
#include "Game/Actor/aiUnk_71007377D4.h"
#include "KingSystem/ActorSystem/AS/ASList.h"
#include "KingSystem/ActorSystem/actActor.h"
#include "KingSystem/ActorSystem/actCCAccessor.h"
#include "KingSystem/Physics/CharacterController/physCharacterController.h"
#include "KingSystem/System/VFR.h"

namespace uking::action {

AnmUpDownMove::AnmUpDownMove(const InitArg& arg) : ksys::act::ai::Action(arg) {}

AnmUpDownMove::~AnmUpDownMove() = default;

bool AnmUpDownMove::init_(sead::Heap* heap) {
    return ksys::act::ai::Action::init_(heap);
}

void AnmUpDownMove::enter_(ksys::act::ai::InlineParamPack* params) {
    auto* cc = mActor->getCharacterController();
    if (!cc) {
        setFailed();
        return;
    }
    mFlags.reset(Flag::Changeable);
    playAS(mASName_s.cstr(), false, 0, 0, -1.0f);
    _54.changeMotionType(cc, ksys::act::MotionType::Hover);
}

void AnmUpDownMove::leave_() {
    _54.resetMotionType(_54.sub_710072ACF8(mActor));
}

void AnmUpDownMove::loadParams_() {
    getStaticParam(&mPosReduceRatio_s, "PosReduceRatio");
    getStaticParam(&mRotReduceRatio_s, "RotReduceRatio");
    getStaticParam(&mAccRatio_s, "AccRatio");
    getStaticParam(&mASName_s, "ASName");
}

// NON_MATCHING: event/movement branch layout, float spills and damping register allocation.
void AnmUpDownMove::calc_() {
    auto* controller = mActor->getCharacterController();
    if (!controller) {
        setFailed();
        return;
    }
    auto* as_list = mActor->getASList();
    ksys::as::ASList::Unk4 query;
    if (sub_71005DD5B0(mActor, 0x2f, &query, 0, 0)) {
        const f32 distance = sead::StringUtil::parseF32(query.name);
        _48 = distance / query._10;
        _4c = *mAccRatio_s * sead::Mathf::abs(_48 - mActor->getVelocity().y);
        _50 = distance + mActor->getMtx().m[1][3];
    }
    const f32 position_ratio = *mPosReduceRatio_s;
    const f32 rotation_ratio = *mRotReduceRatio_s;
    const bool active = as_list->x(0x2f, nullptr, 0, 0,
                                   &ksys::as::ASList::Unk2::sub_71011638DC, true);
    if (!active) {
        sub_71007377D4(controller, position_ratio);
        sub_7100738660(controller, rotation_ratio);
    } else {
        const f32 height = mActor->getMtx().m[1][3];
        if ((_48 >= 0.0f && height < _50) || (_48 < 0.0f && height > _50)) {
            sead::Vector3f velocity;
            controller->sub_7100F5F598(&velocity);
            velocity *= 1.0f / 30.0f;
            ksys::VFR::chase(&velocity.y, _48, _4c);
            const f32 remaining_step = (_50 - height) * ksys::VFR::instance()->getDeltaFrame();
            if (_48 < 0.0f) {
                if (velocity.y < remaining_step)
                    velocity.y = remaining_step;
            } else if (velocity.y > remaining_step) {
                velocity.y = remaining_step;
            }
            if (position_ratio >= 0.0f) {
                ksys::VFR::multiply(&velocity.x, position_ratio);
                ksys::VFR::multiply(&velocity.z, position_ratio);
            } else {
                ksys::VFR::multiply(&velocity.x, -position_ratio);
                velocity.x = -velocity.x;
                ksys::VFR::multiply(&velocity.z, -position_ratio);
                velocity.z = -velocity.z;
            }
            sub_7100737710(controller, velocity);
            sub_7100738660(controller, rotation_ratio);
        }
    }
    if (isFinishedAS(0, 0))
        setFinished();
}

bool AnmUpDownMove::isFinished() const {
    return isFinishedAS(0, 0);
}

}  // namespace uking::action
