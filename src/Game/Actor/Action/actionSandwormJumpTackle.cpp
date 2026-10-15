#include "Game/Actor/Action/actionSandwormJumpTackle.h"
#include <gsys/gsysModel.h>
#include <gsys/gsysModelUnit.h>
#include "Game/Actor/actSandworm.h"
#include "KingSystem/ActorSystem/AS/ASList.h"
#include "Game/Actor/aiUnk_7102451120.h"
#include "Game/Actor/aiUnk_71007377D4.h"
#include "KingSystem/ActorSystem/actLodState.h"
#include "KingSystem/ActorSystem/actActorSensorUtil.h"
#include "KingSystem/ActorSystem/actCCAccessor.h"
#include "KingSystem/ActorSystem/actActor.h"
#include "KingSystem/Physics/CharacterController/physCharacterController.h"
#include "KingSystem/Terrain/teraSystem.h"

// Declaration-only native helpers; source namespaces are unknown.
void sub_71007201C8(ksys::act::Actor* actor, const sead::SafeString& name);
void sub_71007201FC(ksys::act::Actor* actor, const sead::SafeString& name);
void sub_710072027C(ksys::act::Actor* actor, bool a1, u32 a2);
void sub_7100720330(ksys::act::Actor* actor);
// 0x71007209e8 / 0x7100720a18: xlinkSearchAndEmit(actor, "BombEat" / "BombNotEat", 2, arg).
void sub_71007209E8(ksys::act::Actor* actor, Unk_71012419b4* arg);
void sub_7100720A18(ksys::act::Actor* actor, Unk_71012419b4* arg);

namespace uking::action {

SandwormJumpTackle::SandwormJumpTackle(const InitArg& arg) : JumpTackle(arg) {}

SandwormJumpTackle::~SandwormJumpTackle() {
    _c0.sub_71F858();
}

bool SandwormJumpTackle::init_(sead::Heap* heap) {
    if (!JumpTackle::init_(heap))
        return false;
    return _c0.sub_71F6DC(heap);
}

void SandwormJumpTackle::enter_(ksys::act::ai::InlineParamPack* params) {
    auto* actor = mActor;
    _f4 = false;
    _fc = false;
    if (auto* controller = actor->getCharacterController()) {
        _e8 = controller->get70();
        controller->sub_7100F5EE1C(_e8 * *mGravityScale_s);
    }
    const sead::Vector3f position = actor->getMtx().getTranslation();
    _c0.sub_71FEFC();
    _f4 = _c0.sub_710071F8B0(position, 2.5f);
    if (auto* lod = actor->getLodState())
        lod->mFlags26.set(1);
    JumpTackle::enter_(params);
    sub_71007A3800(actor);
    sub_71007A44E4(actor, true);
    sub_7100720814(actor, 0);
    if (!_f4)
        sub_7100720A18(actor, &_138);
    _f8 = 0;
    mFlags.reset(Flag::Changeable);
    if (auto* model = actor->getModel())
        _100.search(model, "Head");
    if (auto* terrain = ksys::tera::Terrain::instance()) {
        auto* grass = terrain->sub_710114DE4C();
        const sead::Vector3f grass_position = mActor->getMtx().getTranslation();
        grass->sub_7101151064(&grass_position, 5.0f, 10.0f, true, false, false);
    }
}

void SandwormJumpTackle::leave_() {
    auto* actor = mActor;
    _100.getKey().reset();
    JumpTackle::leave_();
    if (auto* lod = actor->getLodState())
        lod->mFlags26.set(1);
    _c0.sub_71FEFC();
    if (auto* controller = actor->getCharacterController()) {
        controller->sub_7100F5EE1C(_e8);
        sead::Vector3f velocity;
        controller->sub_7100F5F598(&velocity);
        if (velocity.y > 0.0f)
            sub_71007377D4(controller, 0.1f);
    }
    sub_71007A397C(actor);
    sub_71007A44E4(actor, false);
    sub_71007208EC(actor);
    if (_138.sub_7101241B6C())
        _138.fadeXLink();
}

void SandwormJumpTackle::loadParams_() {
    JumpTackle::loadParams_();
    getStaticParam(&mPosReduceRate_s, "PosReduceRate");
    getStaticParam(&mGravityScale_s, "GravityScale");
    getStaticParam(&mAtkColName_s, "AtkColName");
    getDynamicParam(&mTargetActor_d, "TargetActor");
}

// NON_MATCHING: bone-offset component stores are paired differently.
void SandwormJumpTackle::calc_() {
    auto* actor = mActor;
    auto* list = actor->getASList();
    switch (_f8) {
    case 0:
        if (actor->getVelocity().y > 0.0f)
            _f8 = 1;
        if (auto* model = actor->getModel(); model && _100.isValid()) {
            const auto& key = _100.getKey();
            sead::Matrix34f matrix;
            model->getUnits().unsafeAt(key.model_unit_index)->mModelUnit->getBoneWorldMatrix(
                &matrix, key.bone_index);
            const sead::Vector3f position = matrix.getTranslation() + sead::Vector3f::ey * 2.5f;
            _c0.sub_710071FAEC(mActor, position, 6.0f);
        }
        break;
    case 1:
        if (auto* model = actor->getModel(); model && _100.isValid()) {
            const auto& key = _100.getKey();
            sead::Matrix34f matrix;
            model->getUnits().unsafeAt(key.model_unit_index)->mModelUnit->getBoneWorldMatrix(
                &matrix, key.bone_index);
            const sead::Vector3f position = matrix.getTranslation() + sead::Vector3f::ey * 2.5f;
            _c0.sub_710071FAEC(mActor, position, 6.0f);
        }
        if (actor->getVelocity().y < 0.0f) {
            if (auto* controller = actor->getCharacterController())
                controller->sub_7100F5EE1C(controller->get70() * 0.8f);
            sub_710072027C(actor, false, 8);
            _f8 = 2;
        }
        break;
    case 2:
        if (!_fc && _100.isValid()) {
            if (auto* model = actor->getModel()) {
                const auto& key = _100.getKey();
                sead::Matrix34f matrix;
                model->getUnits().unsafeAt(key.model_unit_index)->mModelUnit->getBoneWorldMatrix(
                    &matrix, key.bone_index);
                const sead::Vector3f position = actor->getMtx().getTranslation();
                const f32 head_y = matrix(1, 3);
                f32 ground_y;
                if (sub_710072C21C(&ground_y, &position) && head_y - ground_y < 6.0f) {
                    _fc = true;
                    if (auto* sandworm = sead::DynamicCast<uking::act::Sandworm>(actor))
                        sandworm->_163c = 2;
                }
            }
        }
        break;
    }
    if (list && !isFinishedAS(0, 0) &&
        list->x(47, nullptr, 0, 0, &ksys::as::ASList::Unk2::sub_71011638DC, true)) {
        sead::Vector3f gravity;
        sub_710072DC50(&gravity, actor);
        if (auto* controller = actor->getCharacterController())
            sub_71007377D4(controller, *mPosReduceRate_s);
    }
    JumpTackle::calc_();
}

void SandwormJumpTackle::m33() {
    auto* actor = mActor;
    sub_71007201FC(actor, mAtkColName_s);
    sub_7100720330(actor);
}

void SandwormJumpTackle::m32() {
    auto* actor = mActor;
    sub_71007201C8(actor, mAtkColName_s);
    sub_710072027C(actor, true, 8);
}

bool SandwormJumpTackle::m34() const {
    if (!isFinishedAS(0, 0))
        return false;
    if (JumpTackle::m34())
        return true;
    auto* controller = mActor->getCharacterController();
    if (controller && controller->sub_7100F5F0E4() == ksys::act::MotionType::_0)
        return true;
    return false;
}

}  // namespace uking::action

namespace uking::action {

bool SandwormJumpTackle::handleAck_(const ksys::MessageAck* ack) {
    for (s32 i = 0, n = _c0.mTargets.size(); i < n; ++i) {
        if (_c0.mTargets.at(i)->sub_710073E5E0(ack)) {
            if (_f4) {
                if (_c0.mTargets(i)->_58 == 2) {
                    _f4 = false;
                    sub_71007209E8(mActor, &_138);
                } else if (!_c0.sub_71FEB4()) {
                    _f4 = false;
                    sub_7100720A18(mActor, &_138);
                }
            }
            return true;
        }
    }
    return false;
}

}  // namespace uking::action
