#include "Game/AI/AI/aiFishRoot.h"
#include <gsys/gsysModel.h>
#include <gsys/gsysModelUnit.h>
#include <random/seadGlobalRandom.h>
#include <limits>
#include "KingSystem/Resource/Actor/resResourceGParamList.h"
#include "KingSystem/ActorSystem/AS/ASList.h"
#include "Game/Actor/actUnk_71025ae680.h"
#include "KingSystem/ActorSystem/Profiles/actPlayerOrEnemy.h"
#include "KingSystem/Physics/CharacterController/physCharacterController.h"
#include "KingSystem/Physics/System/physInstanceSet.h"
#include "KingSystem/Physics/System/physRayCastForRequest.h"
#include "KingSystem/ActorSystem/actActor.h"
#include "KingSystem/ActorSystem/actActorParam.h"
#include "KingSystem/ActorSystem/actActorConstDataAccess.h"
#include "KingSystem/ActorSystem/actPlayerInfo.h"
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
FishRoot::FishRoot(const InitArg& arg) : SimpleWildlifeRoot(arg) {}

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
    if (!SimpleWildlifeRoot::init_(heap))
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

void FishRoot::enter_(ksys::act::ai::InlineParamPack* params) {
    SimpleWildlifeRoot::enter_(params);
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
    SimpleWildlifeRoot::calc_();
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
    SimpleWildlifeRoot::leave_();
}

void FishRoot::loadParams_() {
    SimpleWildlifeRoot::loadParams_();
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
    return SimpleWildlifeRoot::m34();
}

bool FishRoot::m35() {
    if (SimpleWildlifeRoot::m35())
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
    SimpleWildlifeRoot::m40();
}

void FishRoot::changeToDiscoverInterest() {
    if (!isCurrentChild("興味対象発見")) {
        ksys::act::ActorConstDataAccess accessor;
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

}  // namespace uking::ai
