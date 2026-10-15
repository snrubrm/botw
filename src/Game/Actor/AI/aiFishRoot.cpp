#include "Game/Actor/AI/aiFishRoot.h"
#include <gsys/gsysModel.h>
#include <gsys/gsysModelUnit.h>
#include <random/seadGlobalRandom.h>
#include <limits>
#include "KingSystem/System/VFR.h"
#include "KingSystem/Resource/Actor/resResourceGParamList.h"
#include "KingSystem/ActorSystem/AS/ASList.h"
#include "Game/Actor/actUnk_71025ae680.h"
#include "KingSystem/ActorSystem/Profiles/actPlayerOrEnemy.h"
#include "KingSystem/Physics/CharacterController/physCharacterController.h"
#include "KingSystem/Physics/System/physInstanceSet.h"
#include "KingSystem/Physics/System/physRayCastForRequest.h"
#include "KingSystem/ActorSystem/actActor.h"
#include "KingSystem/ActorSystem/Awareness/actAwarenessInstance.h"
#include "KingSystem/Map/mapObject.h"
#include "KingSystem/Physics/RigidBody/physRigidBody.h"
#include "KingSystem/ActorSystem/actActorParam.h"
#include "KingSystem/ActorSystem/actActorLinkConstDataAccess.h"
#include "Game/Actor/Player/actPlayerInfo.h"
#include "KingSystem/ActorSystem/actAiInlineParam.h"
#include "KingSystem/ActorSystem/actChemical.h"
#include "KingSystem/Resource/GeneralParamList/resGParamListObjectFish.h"

namespace uking::ai {

// NON_MATCHING: the bone-key search is out of line in the current library.
void FishRootBoneEntry::sub_71003CC014(const ksys::res::GParamListObjectFish* params,
                                    gsys::Model* model, const sead::SafeString& name, s32 index) {
    if (!model)
        return;

    if (name.isEmpty())
        _0.getKey().reset();
    else
        _0.search(model, model->searchBone(name));

    _38.copy(name);
    _dc = params->mRestoreSpeedRate.ref() + index * params->mRestoreSpeedRateAdd.ref();
    _e0 = params->mLimitAngle.ref() + index * params->mLimitAngleAdd.ref();
}

// NON_MATCHING: previous-entry index arithmetic and the model load schedule differ.
void FishRoot::sub_71003CC1AC(gsys::Model* model) {
    if (!model)
        return;
    const int last = _1d0.size() - 1;
    for (int i = 0; i <= last; ++i) {
        auto& entry = _1d0[i];
        if (i == last) {
            const auto& previous = _1d0[last - 1];
            entry._0.getKey().reset();
            entry._38.clear();
            entry._a0 = previous._a0;
            entry._70 = previous._70;
            entry._d0.set(0.0f, 0.0f, 0.0f);
            entry._e4 = previous._e4;
        } else if (entry._0.isValid()) {
            sead::Vector3f scale;
            model->getUnits()(entry._0.getKey().model_unit_index)->mModelUnit->getBoneLocalMatrix(
                &entry._a0, &scale, entry._0.getKey().bone_index);
            model->getUnits()(entry._0.getKey().model_unit_index)->mModelUnit->getBoneWorldMatrix(
                &entry._70, entry._0.getKey().bone_index);
            entry._d0.set(0.0f, 0.0f, 0.0f);
            entry._e4 = entry._a0.getTranslation().length();
        }
    }
}

// NON_MATCHING: interpolation registers and the final minimum-step branch differ.
void FishRoot::sub_71003CC878() {
    if (auto* controller = mActor->getCharacterController()) {
        sead::Vector3f velocity = controller->get64() * (controller->sub_7100F5EF00() / 30.0f);
        if (controller->isBit2Of116())
            velocity -= controller->get180() * 0.5f;
        const f32 target = velocity.length() + sead::Mathf::abs(mActor->getVelocity().y) * 0.5f;
        const f32 diff = target - _1a0;
        const f32 distance = sead::Mathf::abs(diff);
        if (_1a0 < target) {
            if (distance <= 0.005f) {
                _1a0 = target;
            } else {
                const f32 step = distance * 0.8f;
                if (step > 0.2f)
                    _1a0 += diff < 0.0f ? -0.2f : 0.2f;
                else if (step < 0.005f)
                    _1a0 += diff < 0.0f ? -0.005f : 0.005f;
                else
                    _1a0 += diff * 0.8f;
            }
        } else {
            if (distance <= 0.001f) {
                _1a0 = target;
            } else {
                const f32 step = distance * 0.2f;
                if (step > 0.02f)
                    _1a0 += diff < 0.0f ? -0.02f : 0.02f;
                else if (step < 0.001f)
                    _1a0 += diff < 0.0f ? -0.001f : 0.001f;
                else
                    _1a0 += diff * 0.2f;
            }
        }
        mActor->getASList()->x_6(10, 0, _1a0);
    }
    sub_71003CD268();
}

// NON_MATCHING: initialization of the vector/counter block is not aggregated into one clear.
FishRoot::FishRoot(const InitArg& arg) : CapturedActorRoot(arg) {}

// NON_MATCHING: regalloc of the element destructor loop (we hoist the element address `end - 0xe8` into x21 for the two
// calls; the original recomputes it in each branch).
FishRoot::~FishRoot() {
    _1d0.freeBuffer();
    if (_1b8)
        _1b8->release();
    _1b8 = nullptr;
    if (_1c0)
        _1c0->release();
    _1c0 = nullptr;
}

// NON_MATCHING: the original moves `start` into x1 after negating the height (scheduling only).
bool FishRoot::sub_71003CE608(const sead::Vector3f& start) {
    _1c0 = ksys::phys::RayCastForRequest::allocRequest(mActor->getPhysics()->get188(0),
                                                       ksys::phys::GroundHit::HitAll);
    if (_1c0) {
        _1c0->enableLayer(ksys::phys::ContactLayer::EntityGroundObject);
        _1c0->enableLayer(ksys::phys::ContactLayer::EntityGround);
        _1c0->enableLayer(ksys::phys::ContactLayer::EntityGroundSmooth);
        _1c0->enableLayer(ksys::phys::ContactLayer::EntityGroundRough);
        _1c0->setStartAndDisplacementScaled(start, sead::Vector3f::ey, -mActor->getAabb().getSizeY());
        _1c0->submitRequest(ksys::phys::ContactLayerType::Entity);
    }
    return true;
}

// NON_MATCHING: common timer reset and vector snapshots retain different branches and stores.
bool FishRoot::sub_71003CD93C() {
    _160.update();
    if (!(_160.value <= std::numeric_limits<f32>::epsilon()))
        return false;

    bool clear = false;
    if (_1b8) {
        if (_1b8->get70() != 1)
            return false;
        clear = !_1b8->hasHit();
        _1b8->release();
        _1b8 = nullptr;
    } else {
        _1b8 = ksys::phys::RayCastForRequest::allocRequest(mActor->getPhysics()->get188(0),
                                                         ksys::phys::GroundHit::HitAll);
        if (_1b8) {
            const sead::Vector3f start = mActor->getMtx().getTranslation();
            _1b8->enableLayer(ksys::phys::ContactLayer::EntityObject);
            _1b8->enableLayer(ksys::phys::ContactLayer::EntityGroundObject);
            _1b8->enableLayer(ksys::phys::ContactLayer::EntityGround);
            _1b8->enableLayer(ksys::phys::ContactLayer::EntityGroundSmooth);
            _1b8->enableLayer(ksys::phys::ContactLayer::EntityGroundRough);
            const sead::Vector3f direction = mActor->getMtx().getBase(2);
            _1b8->setStartAndDisplacementScaled(start, direction, 3.5f);
            _1b8->submitRequest(ksys::phys::ContactLayerType::Entity);
            return false;
        }
    }

    const f32 base = *mParams.mNextJumpTimeBase_s;
    if (base < 0.0f)
        _160.reset(1.0f, 0.0f);
    else
        _160.reset(base + *mParams.mNextJumpTimeRand_s * sead::GlobalRandom::instance()->getF32());
    return clear;
}

// NON_MATCHING: stack/register allocation and buffer cleanup block placement differ.
bool FishRoot::init_(sead::Heap* heap) {
    if (!CapturedActorRoot::init_(heap))
        return false;
    auto* model = mActor->getModel();
    if (!model)
        return true;
    s32 spine_count = 0;
    for (s32 i = 1;; ++i) {
        sead::FixedSafeString<32> name;
        name.format("Spine_%d", i);
        if (!model->searchBone(name).isValid())
            break;
        ++spine_count;
    }
    s32 tail_count = 0;
    for (s32 i = 1;; ++i) {
        sead::FixedSafeString<32> name;
        name.format("tail%02d", i);
        if (!model->searchBone(name).isValid())
            break;
        ++tail_count;
    }
    if (spine_count + tail_count <= 0)
        return true;
    _1d0.tryAllocBuffer(spine_count + tail_count + 1, heap);
    if (!_1d0.getBufferPtr())
        return false;
    const auto* params = mActor->getParam()->getRes().mGParamList->getFish();
    if (!params) {
        _1d0.freeBuffer();
        return false;
    }
    for (s32 i = 0; i < spine_count; ++i) {
        sead::FixedSafeString<32> name;
        name.format("Spine_%d", i + 1);
        _1d0[i].sub_71003CC014(params, model, name.cstr(), i);
    }
    for (s32 i = 0; i < tail_count; ++i) {
        sead::FixedSafeString<32> name;
        name.format("tail%02d", i + 1);
        _1d0[spine_count + i].sub_71003CC014(params, model, name.cstr(), spine_count + i);
    }
    _1d0[spine_count + tail_count].sub_71003CC014(params, model, "", spine_count + tail_count);
    sub_71003CC1AC(model);
    return true;
}

// NON_MATCHING: timer resets, home-position snapshots and vector copies retain different scheduling.
void FishRoot::enter_(ksys::act::ai::InlineParamPack* params) {
    CapturedActorRoot::enter_(params);
    if (auto* body = mActor->findPhysicsBodyByName("Body", "FoodMover")) {
        if (body->isAddedToWorld() || body->isAddingBodyToWorld())
            body->removeFromWorld();
    }
    auto* actor = mActor;
    if (auto* controller = actor->getCharacterController()) {
        controller->_140 = *mParams.mInWaterDepth_s * 0.9f;
        controller->sub_7100F5E754(true);
        controller->sub_7100F60E80(false);
        controller->sub_7100F5F07C(30.0f);
    }
    _1ac = 0;
    if (_1b8)
        _1b8->release();
    _1b8 = nullptr;
    if (_1c0)
        _1c0->release();
    _1c0 = nullptr;
    _150.reset();
    const f32 base = *mParams.mNextJumpTimeBase_s;
    if (base < 0.0f)
        _160.reset(1.0f, 0.0f);
    else
        _160.reset(base + *mParams.mNextJumpTimeRand_s * sead::GlobalRandom::instance()->getF32());
    _178.reset(*mParams.mIgnoreFoodBase_s +
               *mParams.mIgnoreFoodRand_s * sead::GlobalRandom::instance()->getF32());
    _1b0 = 0;
    _19c = 0.5f;
    _1a0 = 0.0f;
    if (auto* model = actor->getModel(); model && _1d0.getBufferPtr()) {
        model->applyAnimationTo(model, 3);
        sub_71003CC1AC(model);
        _1e0._10 = _19c;
        _1e0._14 = actor->getParam()->getRes().mGParamList->getFish()->mPrevSpeedRate.ref();
        model->mUpdateHook = &_1e0;
    }
    actor = mActor;
    sead::Vector3f home;
    if (auto* object = actor->getMapObject())
        home = object->getTranslate();
    else
        actor->getHomePos(&home);
    const bool in_water = actor->get68f().load();
    const f32 depth = in_water ? actor->get6f0() - actor->getMtx().getTranslation().y : 0.0f;
    if (depth > *mParams.mInWaterDepth_s)
        home.y -= sead::Mathf::abs(depth - *mParams.mInWaterDepth_s);
    _190 = home;
    _1c9 = false;
    _1ca = false;
    if (_184 == sead::Vector3f::zero)
        _184 = _190;
    _1a8 = mActor->getScale().y * (mActor->getAabb().getSizeY() * 0.5f);
    sub_71003CC69C();
    if (auto* awareness = mActor->get548())
        awareness->_18._50 = 1;
}

void FishRoot::sub_71003CD268() {
    const auto updateBlend = [this](f32 change, f32 minimum) {
        _19c = sead::Mathf::clamp(ksys::VFR::instance()->getDeltaFrame() * change + _19c,
                                minimum, 1.0f);
        if (sead::Mathf::equalsEpsilon(_19c, 0.0f))
            _1e0._10 = 0.0f;
        else if (sead::Mathf::equalsEpsilon(_19c, 1.0f))
            _1e0._10 = 1.0f;
        else
            _1e0._10 = sead::Mathf::clamp((std::cos((1.0f - _19c) * sead::Mathf::pi()) + 1.0f) * 0.5f,
                                        0.0f, 1.0f);
    };
    if (isCurrentChild("地上待機"))
        updateBlend(-1.0f / 30.0f, 0.0f);
    else if (isCurrentChild("ジャンプ")) {
        if (mActor->get68f().load())
            updateBlend(2.0f / 30.0f, 0.0f);
        else
            updateBlend(-4.0f / 30.0f, 0.1f);
    } else {
        updateBlend(1.0f / 30.0f, 0.0f);
    }
}

void FishRoot::sub_71003CC69C() {
    auto* actor = sead::DynamicCast<ksys::act::PlayerOrEnemy>(mActor);
    if (!actor)
        return;
    auto* controller = sead::DynamicCast<act::Unk_710244edc0>(actor->m159());
    if (!controller)
        return;
    controller->_68 = !isCurrentChild("地上待機") && !isCurrentChild("死亡");
}

void FishRoot::calc_() {
    sub_71003CC878();
    CapturedActorRoot::calc_();
    const sead::Vector3f position = mActor->getMtx().getTranslation();
    _1a4 = (position - getPlayerPosition()).squaredLength();
    sub_71003CCA34();
}

void FishRoot::leave_() {
    if (_1b8)
        _1b8->release();
    _1b8 = nullptr;
    if (_1c0)
        _1c0->release();
    _1c0 = nullptr;
    CapturedActorRoot::leave_();
}

void FishRoot::loadParams_() {
    CapturedActorRoot::loadParams_();
    getStaticParam(&mParams.mInWaterDepth_s, "InWaterDepth");
    getStaticParam(&mParams.mOnGroundDepth_s, "OnGroundDepth");
    getStaticParam(&mParams.mNextJumpTimeBase_s, "NextJumpTimeBase");
    getStaticParam(&mParams.mNextJumpTimeRand_s, "NextJumpTimeRand");
    getStaticParam(&mParams.mAllowReturnThreatDist_s, "AllowReturnThreatDist");
    getStaticParam(&mParams.mFrameUntilOutOfWater_s, "FrameUntilOutOfWater");
    getStaticParam(&mParams.mDistRunFromPlayerOnReturn_s, "DistRunFromPlayerOnReturn");
    getStaticParam(&mParams.mIgnoreFoodBase_s, "IgnoreFoodBase");
    getStaticParam(&mParams.mIgnoreFoodRand_s, "IgnoreFoodRand");
    getStaticParam(&mParams.mIgnoreFoodAfterSuccessBase_s, "IgnoreFoodAfterSuccessBase");
    getStaticParam(&mParams.mIgnoreFoodAfterSuccessRand_s, "IgnoreFoodAfterSuccessRand");
}

bool FishRoot::m34() {
    return CapturedActorRoot::m34();
}

bool FishRoot::m35() {
    if (CapturedActorRoot::m35())
        return true;
    auto* chemical = mActor->sub_71011D8A34(0);
    if (chemical && chemical->_1b8 > 0.0f)
        return true;
    auto* cc = mActor->getCharacterController();
    if (cc && mActor->get68f().load()) {
        if ((cc->_116 & 0x14) == 0x10)
            return true;
    }
    return false;
}

bool FishRoot::m36() {
    return false;
}

// NON_MATCHING: water-test branch layout and vector/float scheduling differ.
void FishRoot::m38() {
    if (auto* controller = mActor->getCharacterController())
        controller->sub_7100F63700(false);
    mActor->getActorFlags2().reset(ksys::act::Actor::ActorFlag2::_8000000);
    const f32 base = *mParams.mNextJumpTimeBase_s;
    if (base < 0.0f) {
        _160 = ksys::Timer(1.0f, 1.0f, 0.0f);
    } else {
        const f32 time = base + *mParams.mNextJumpTimeRand_s *
                                    sead::GlobalRandom::instance()->getF32();
        _160 = ksys::Timer(time, time);
    }
    sead::Vector3f position;
    mActor->getMtx().getTranslation(position);
    const bool in_water = mActor->get68f().load();
    const f32 depth = in_water ? mActor->get6f0() - position.y : 0.0f;
    if (in_water && depth < mActor->getScale().x)
        position.y -= mActor->getScale().x - depth;
    sead::Vector3f direction = mActor->getMtx().getBase(2);
    direction.y = 0.0f;
    direction.normalize();
    position += direction * 0.2f;
    ksys::act::ai::InlineParamPack pack;
    pack.addVec3(position, "TargetPos", -1);
    changeChild("通常行動", &pack);
}

void FishRoot::m39() {
    if (_c4.value <= sead::Mathf::epsilon()) {
        if (!isCurrentChild("初期配置帰還") && !isCurrentChild("ジャンプ") && sub_710034342C()) {
            if (!isCurrentChild("帰還"))
                mActor->getMtx().getTranslation(_184);
            ksys::act::ai::InlineParamPack pack;
            pack.addVec3(_b8, "TargetPos", -1);
            changeChild("逃走", &pack);
        }
    }
}

void FishRoot::m41() {
    if (!isCurrentChild("地上待機")) {
        if (auto* controller = mActor->getCharacterController()) {
            controller->sub_7100F60604();
            controller->sub_7100F63700(true);
        }
        _1b0 = 0;
        changeChild("地上待機");
    }
}

void FishRoot::m40() {
    if (auto* controller = mActor->getCharacterController())
        controller->sub_7100F60604();
    CapturedActorRoot::m40();
}

void FishRoot::changeToDiscoverInterest() {
    if (!isCurrentChild("興味対象発見")) {
        ksys::act::ActorLinkConstDataAccess accessor;
        if (ksys::act::acquireActor(&_150, &accessor)) {
            ksys::act::ai::InlineParamPack pack;
            sead::Vector3f pos;
            accessor.getActorMtx().getTranslation(pos);
            pack.addVec3(pos, "TargetPos", -1);
            pack.addActor(_150, "TargetActor", -1);
            changeChild("興味対象発見", &pack);
        }
    }
}

void FishRoot::changeToReturn() {
    ksys::act::ai::InlineParamPack pack;
    pack.addVec3(_190, "TargetPos", -1);
    pack.addVec3(_184, "MoveAwayFromPos", -1);
    changeChild("帰還", &pack);
}

void FishRoot::changeToReturnToInitialPlacement(bool is_escape) {
    if (!isCurrentChild("初期配置帰還")) {
        mActor->getCharacterController();
        ksys::act::ai::InlineParamPack pack;
        pack.addVec3(_190, "TargetPos", -1);
        pack.addBool(is_escape, "IsEscape", -1);
        changeChild("初期配置帰還", &pack);
    }
}

// NON_MATCHING: vector and matrix temporaries, quaternion scheduling and loop layout differ.
void FishRoot::Unk_71023ee000::m2(gsys::Model* model) {
    if (_10 < std::numeric_limits<f32>::epsilon() || _8->size() < 2)
        return;
    const auto& model_scale = model->getScale();
    const sead::Vector3f scale(model_scale.x * model->_94.x, model_scale.y * model->_94.y,
                               model_scale.z * model->_94.z);
    sead::Vector3f offset{0.0f, 0.0f, 0.0f};
    sead::Vector3f translation{0.0f, 0.0f, 0.0f};
    sead::Quatf correction;
    correction.makeUnit();
    const s32 last = _8->size() - 2;
    for (s32 i = 0; i <= last; ++i) {
        auto& current = (*_8)[i];
        auto& next = (*_8)[i + 1];
        const auto current_key = current._0.getKey();
        const auto next_key = next._0.getKey();
        sead::Matrix34f current_matrix;
        model->getUnits()(current_key.model_unit_index)->mModelUnit->getBoneWorldMatrix(
            &current_matrix, current_key.bone_index);
        sead::Matrix34f next_matrix;
        if (next_key.isValid()) {
            model->getUnits()(next_key.model_unit_index)->mModelUnit->getBoneWorldMatrix(
                &next_matrix, next_key.bone_index);
        } else {
            next_matrix = current_matrix;
            const auto axis = current_matrix.getBase(0);
            next_matrix.setTranslation(current_matrix.getTranslation() +
                sead::Vector3f(scale.x * (next._e4 * axis.x), scale.y * (next._e4 * axis.y),
                               scale.z * (next._e4 * axis.z)));
        }
        if (i == 0)
            translation = current_matrix.getTranslation() - current._70.getTranslation();
        const auto current_pos = translation + current._70.getTranslation();
        const auto next_pos = translation + next._70.getTranslation();
        const auto animated_pos = offset + next_matrix.getTranslation();
        const f32 restore = sead::lerp(1.0f, next._dc, _10);
        const f32 inertia = sead::lerp(0.0f, _14, _10);
        const auto desired_pos = next_pos + (animated_pos - next_pos) * restore + next._d0 * inertia;
        sead::Vector3f direction = desired_pos - current_pos;
        direction.rotate(correction);
        direction.normalize();
        sead::Vector3f previous_direction = current_matrix.getBase(0);
        if (i == 0) {
            sead::Matrix34f root_matrix;
            model->getUnits()(current_key.model_unit_index)->mModelUnit->getBoneWorldMatrix(
                &root_matrix, 0);
            previous_direction = -root_matrix.getBase(2);
        }
        const f32 angle = std::atan2(direction.cross(previous_direction).length(),
                                     direction.dot(previous_direction));
        const f32 limit = sead::lerp(sead::Mathf::pi(), current._e0, _10);
        // An unordered angle also resets the correction to the unit quaternion.
        if (!(angle > limit)) {
            correction.makeUnit();
        } else {
            const f32 weight = sead::Mathf::clamp(limit / angle, 0.0f, 1.0f);
            previous_direction += (direction - previous_direction) * weight;
            previous_direction.normalize();
            correction.makeVectorRotation(previous_direction, direction);
            direction = previous_direction;
        }
        const auto end_pos = current_pos +
            sead::Vector3f(direction.x * (scale.x * next._e4),
                           direction.y * (scale.y * next._e4),
                           direction.z * (scale.z * next._e4));
        next._d0 = desired_pos - next_pos;
        auto adjusted_current = current_matrix;
        auto adjusted_next = next_matrix;
        sead::Vector3f front = end_pos - current_matrix.getTranslation();
        front.normalize();
        if (front != sead::Vector3f::zero) {
            auto up = front.cross(current_matrix.getBase(1));
            up.normalize();
            auto side = -front.cross(up);
            side.normalize();
            adjusted_current.setBase(0, front);
            adjusted_current.setBase(1, side);
            adjusted_current.setBase(2, up);
        }
        adjusted_next.setBase(0, adjusted_current.getBase(0));
        adjusted_next.setBase(1, adjusted_current.getBase(1));
        adjusted_next.setBase(2, adjusted_current.getBase(2));
        adjusted_next.setTranslation(end_pos);
        adjusted_current.scaleBases(scale.x, scale.y, scale.z);
        model->setBoneWorldMatrix(current_key, adjusted_current);
        current._70 = adjusted_current;
        if (i == last) {
            sead::Quatf orientation;
            adjusted_next.toQuat(orientation);
            adjusted_next.makeSQT(scale, orientation * correction, end_pos);
            next._70 = adjusted_next;
        } else {
            adjusted_next.scaleBases(scale.x, scale.y, scale.z);
            model->setBoneWorldMatrix(next_key, adjusted_next);
            offset = end_pos - animated_pos;
        }
    }
}

}  // namespace uking::ai
