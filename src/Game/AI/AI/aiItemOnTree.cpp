#include "Game/AI/AI/aiItemOnTree.h"
#include "KingSystem/ActorSystem/actActor.h"
#include "Game/AI/aiUnk_71007377D4.h"
#include "KingSystem/ActorSystem/actActorUtil.h"
#include "KingSystem/ActorSystem/actPhysicsConstraints.h"
#include "KingSystem/Map/mapObject.h"
#include "KingSystem/Map/mapPlacementActors.h"
#include "KingSystem/Physics/RigidBody/physRigidBody.h"
#include "KingSystem/System/VFR.h"
#include "KingSystem/Utils/Thread/Message.h"
#include <random/seadGlobalRandom.h>

namespace uking::ai {

ItemOnTree::ItemOnTree(const InitArg& arg) : ItemRoot(arg) {}

bool ItemOnTree::init_(sead::Heap* heap) {
    return ItemRoot::init_(heap);
}

void ItemOnTree::enter_(ksys::act::ai::InlineParamPack* params) {
    _a8 = 0;
    _ac = 0;
    _b0 = 0;
    _b4 = false;
    _b5 = false;
    ItemRoot::enter_(params);
}

void ItemOnTree::leave_() {
    ItemRoot::leave_();
}

void ItemOnTree::loadParams_() {
    ItemRoot::loadParams_();
    getStaticParam(&mFallPowerMin_s, "FallPowerMin");
    getStaticParam(&mFallPowerMax_s, "FallPowerMax");
    getStaticParam(&mFallOddsMin_s, "FallOddsMin");
    getStaticParam(&mFallOddsMax_s, "FallOddsMax");
    getStaticParam(&mFallIntervalRange_s, "FallIntervalRange");
    getStaticParam(&mFallCheckSpeedTh_s, "FallCheckSpeedTh");
    getStaticParam(&mAttOnTree_s, "AttOnTree");
    getStaticParam(&mAttOnGround_s, "AttOnGround");
}

bool ItemOnTree::handleMessage_(const ksys::Message* message) {
    if (isCurrentChild("通常") && message->getType() == 0x800001c) {
        if (message->getUserData())
            _a8 = *static_cast<const int*>(message->getUserData());
        _b4 = true;
    }
    return false;
}

// NON_MATCHING: the original keeps separate LOW/HIGH diamonds (w21 set in each arm, _48
// tested in both arms, shared A/B blocks); ours flattens the flag routing (cset) and uses
// different registers (no x23, actor in x21). Velocity/length, VFR per-core block, atomic
// revival flag + setRevivalFlagValueIf + m36() tail all match. The two FALLROLL copies do not
// merge in ours (extra tails); manual (u64*100)>>32 reduction matches the getU32(100) lowering.
void ItemOnTree::calc_() {
    ItemRoot::calc_();
    auto* actor = mActor;
    if (!isCurrentChild("通常"))
        return;

    sead::Vector3f vel = sead::Vector3f::zero;
    bool flag;
    if (auto* body = actor->getMainBody();
        body && (body->getLinearVelocity(&vel), vel.length() >= *mFallCheckSpeedTh_s * 30.0f)) {
        flag = true;
    } else {
        flag = false;
        if (_48)
            flag = true;
    }
    if (!_48 && _b4 && !_b5) {
        if (_a8 < *mFallPowerMin_s) {
            _a8 = 0;
            _b4 = false;
        } else {
            auto* random = sead::GlobalRandom::instance();
            const s32 odds_range = *mFallOddsMax_s - *mFallOddsMin_s;
            const f32 min_pow = *mFallPowerMin_s;
            const f32 min_odds = *mFallOddsMin_s;
            const s32 pow_range = *mFallPowerMax_s - *mFallPowerMin_s;
            const f32 slope = f32(odds_range) / f32(pow_range);
            const f32 intercept = min_odds - min_pow * slope;
            const u32 rand = random->getU32();
            const s32 odds = s32(f32(_a8) * slope + intercept);
            if (odds <= s32((u64(rand) * 100) >> 32)) {
                _b5 = false;
            } else {
                _b0 = *mFallIntervalRange_s * random->getF32();
                _b5 = true;
            }
            _a8 = 0;
            _b4 = false;
        }
    }

    int outcome;
    if (_b5) {
        f32 f15 = _ac;
        f32 f14 = _b0;
        f32 f16 = ksys::VFR::instance()->getDeltaFrame();
        if (f15 < f14) {
            f16 += f15;
            outcome = (f16 >= f14) || (f16 < f15);
            if (outcome)
                f14 = f16;
            _ac = f14;
        } else if (f15 > f14) {
            f16 = f15 - f16;
            outcome = (f16 <= f14) || (f15 < f16);
            if (outcome)
                f14 = f16;
            _ac = f14;
        }
    }
    if ((flag || outcome) == 1) {
        if (auto* map_obj = actor->getMapObject()) {
            map_obj->setFlags0(ksys::map::Object::Flag0::_400000);
            map_obj->setRevivalFlagValueIf(ksys::map::ActorData::Flag::RevivalEnable, true);
        }
        m36();
    }
}

void ItemOnTree::m34() {
    if (mActor->getMapObject()) {
        if (*mInitMotionStatus_m != 1)
            m35();
        else
            m36();
    } else {
        m36();
    }
}

void ItemOnTree::m35() {
    auto* actor = mActor;
    ksys::act::enableAttClient(actor, mAttOnTree_s);
    ksys::act::disableAttClient(actor, mAttOnGround_s);
    changeChild("通常");
}

void ItemOnTree::m36() {
    auto* actor = mActor;
    if (auto* body = actor->getMainBody()) {
        body->changeMotionType(ksys::phys::MotionType::Dynamic);
        actor->getConstraints().sub_7100D40338();
    }
    sub_7100731000(actor, true);
    ksys::act::disableAttClient(actor, mAttOnTree_s);
    ksys::act::enableAttClient(actor, mAttOnGround_s);
    changeChild("もげる");
}

}  // namespace uking::ai
