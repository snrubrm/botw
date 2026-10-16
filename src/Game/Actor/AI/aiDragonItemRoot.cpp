#include "Game/Actor/AI/aiDragonItemRoot.h"
#include "KingSystem/ActorSystem/actActor.h"
#include "Game/Actor/aiUnk_71007377D4.h"
#include "KingSystem/GameData/gdtManager.h"
#include "KingSystem/System/Timer.h"
#include "KingSystem/XLink/xlinkActorUtil.h"
#include "Game/Actor/actDragon.h"
#include "KingSystem/Utils/Thread/Message.h"
#include "KingSystem/ActorSystem/actAiInlineParam.h"
#include "KingSystem/Physics/RigidBody/physRigidBody.h"

namespace uking::ai {

DragonItemRoot::DragonItemRoot(const InitArg& arg) : ItemRoot(arg) {}

// The original keeps the vtable store that a defaulted destructor drops (same form as upstream's
// GameDataFlagSelector::~GameDataFlagSelector() { ; }, commit 96101229).
DragonItemRoot::~DragonItemRoot() {
    ;
}

bool DragonItemRoot::init_(sead::Heap* heap) {
    return ItemRoot::init_(heap);
}

void DragonItemRoot::enter_(ksys::act::ai::InlineParamPack* params) {
    ItemRoot::enter_(params);
    auto* actor = mActor;
    _128 = actor->getMainBody();
    _130 = actor->getMtx().getTranslation();
    _13c.x = 0;
    _13c.y = 0;
    _13c.z = 0;
    _148 = *mFlyStartTime_s;
    _14c.reset(0x2f);
    _150 = 0;
    _154 = 0;
    if (!*mIsInitFromCarryBox_a) {
        auto* parent = sead::DynamicCast<act::Dragon>(sead::DynamicCast<ksys::act::Actor>(
            actor->getCreateArgBaseProcLink().getProc(nullptr, nullptr)));
        if (parent) {
            _14c.change(1, parent->_1e0c == 3);
            if (!mActor->getModelBindInfo()) {
                actor->setConnectedCalcParent(parent, false);
                _14c.set(8);
            }
        }
    }
    mActor->get689() = true;
}

// NON_MATCHING: block layout and scheduling (stack slot of the terrain query position, the get689 store)
void DragonItemRoot::calc_() {
    ItemRoot::calc_();
    auto* actor = mActor;

    if (*mIsInsideObserverArea_a && !_14c.isOnBit(4)) {
        _14c.setBit(4);
        _15c = 40;
        xlinkSearchAndEmit(actor, mActivateXlinkEventName_s.cstr(), 2, nullptr);
        mActor->get689() = true;
    }

    if (isCurrentChild("通常") && mActor->getVelocity().squaredLength() < 0.01f) {
        bool played = true;
        if ((_14c.getDirect() & 0x21) == 1) {
            auto* gdm = ksys::gdt::Manager::instance();
            auto& param = gdm->getParam();
            const bool found = param.get().getBuffer()->getBool(&played, "IsPlayed_Demo480_3",
                                                                param.shouldCheckPermissions(), true);
            if (played && found)
                _14c.setBit(5);
        }
        if (played) {
            flyingObjectEmitXlink(actor, mLightShaftXLinkEventName_s.cstr(), 2, nullptr);
            flyingObjectEmitXlink(actor, mAuraXLinkEventName_s.cstr(), 2, nullptr);
        }
    }

    if (_154 > 0.0f) {
        ksys::Timer::update(&_154, -1.0f);
        if (_154 <= 0.0f) {
            if (auto* gdm = ksys::gdt::Manager::instance())
                gdm->setBool(true, mClearFlagLabel_s);
        }
    }

    auto* child = getCurrentChild();
    mActor->get689() = isCurrentChild("体に貼り付く") || isCurrentChild("打ち上がる") || _14c.isOnBit(4) ||
                       _158 < 15.0f;
    ksys::Timer::update(&_158, 1.0f);

    if (child->isFinished() || child->isFailed()) {
        if (isCurrentChild("打ち上がる")) {
            xlinkSearchAndEmit(actor, mHitGroundXLinkEventName_s.cstr(), 2, nullptr);
            if (child->isFailed())
                _14c.resetBit(1);
            if (_14c.isOnBit(0)) {
                const auto& velocity = mActor->getVelocity();
                _128->applyLinearImpulse({velocity.x * -30.0f, -0.0f, velocity.z * -30.0f});
            }
            _14c.setBit(2);
            if (auto* gdm = ksys::gdt::Manager::instance()) {
                bool dropped = false;
                auto& param = gdm->getParam();
                param.get().getBuffer()->getBool(&dropped, mDropItemFlagLabel_s, param.shouldCheckPermissions(),
                                                 true);
                if (!dropped)
                    gdm->setBool(true, mDropItemFlagLabel_s);
            }
            changeChild("通常");
        }
    } else if (child->isChangeable()) {
        bool fly = false;
        if (isCurrentChild("体に貼り付く")) {
            if (!_14c.isOnBit(0)) {
                ksys::Timer::update(&_150, 1.0f);
                fly = _150 > _148;
            } else {
                fly = *mFlyStartHeightAtRunel_s > 0.0f &&
                      actor->getMtx()(1, 3) > *mFlyStartHeightAtRunel_s;
            }
        } else if (_14c.isOnBit(3)) {
            if (sead::DynamicCast<ksys::act::Actor>(mActor->getConnectedCalcParent())) {
                sub_710036CE54(sead::DynamicCast<ksys::act::Actor>(mActor->getConnectedCalcParent()));
                _14c.resetBit(3);
            }
        }

        if (fly) {
            f32 height1 = -1.0f;
            f32 height2 = -1.0f;
            sead::Vector3f pos = actor->getMtx().getTranslation();
            const bool found1 = sub_710072C21C(&height1, &pos);
            pos = actor->getMtx().getTranslation();
            const bool found2 = sub_710072C494(&height2, &pos);
            if (!found1 || !found2 || !(actor->getMtx()(1, 3) < sead::Mathf::max(height1, height2))) {
                mActor->getTgtBody()->setContactNone();
                xlinkSearchAndEmit(actor, mFlyStartXinkEventName_s.cstr(), 2, nullptr);
                actor->resetConnectedCalcParent(false);
                _14c.resetBit(1);
                if (mTargetPosition_m && (mTargetPosition_m->x != 0.0f || mTargetPosition_m->y != 0.0f ||
                                          mTargetPosition_m->z != 0.0f)) {
                    _13c = *mTargetPosition_m;
                    _14c.setBit(1);
                } else {
                    sead::Vector3f target = sead::Vector3f::zero;
                    const sead::Vector3f current = actor->getMtx().getTranslation();
                    if (act::getDragonItemDropPosition(&target, current) &&
                        (target - actor->getMtx().getTranslation()).length() < 1000.0f) {
                        _13c = target;
                        _14c.setBit(1);
                    }
                }
                if (!_14c.isOnBit(1)) {
                    sead::Vector3f dir = mActor->getMtx().getTranslation() - _130;
                    dir.normalize();
                    dir.y = -1.0f;
                    const sead::Vector3f start = mActor->getMtx().getTranslation();
                    if (somePositionCalc(&_13c, start, dir, 1000.0f))
                        _14c.setBit(1);
                }
                if (_14c.isOnBit(0) && *mFlyStartHeightAtRunel_s > 0.0f)
                    _154 = *mClearFlagTimeAtRunel_s;
                ksys::act::ai::InlineParamPack pack;
                pack.addVec3(_13c, "TargetPos", -1);
                changeChild("打ち上がる", &pack);
            }
        }
    }

    _128->setGravityFactor(*mGravity_s);
    _128->setLinearDamping(0.1f);
    if ((~_14c.getDirect() & 7) == 0) {
        sead::Vector3f hit = sead::Vector3f::zero;
        const sead::Vector3f start = actor->getMtx().getTranslation();
        const sead::Vector3f dir = sead::Vector3f::ey * -0.25f;
        const bool found = somePositionCalc(&hit, start, dir, 10.0f);
        const sead::Vector3f diff = _13c - actor->getMtx().getTranslation();
        if (diff.length() <= 2.0f && found) {
            _128->applyLinearImpulse(diff * 30.0f);
            _128->applyLinearImpulse((_130 - actor->getMtx().getTranslation()) * 300.0f);
            _128->setLinearDamping(0.95f);
        } else {
            _14c.resetBit(1);
        }
    }

    _128->enableGroundCollision(!isCurrentChild("体に貼り付く"));
    flyingObjectEmitXlink(actor,
                          (isCurrentChild("体に貼り付く") ? mFlyPrepareXinkEventName_s : mTailXLinkEventName_s)
                              .cstr(),
                          2, nullptr);

    if (_15c > 0 && --_15c == 0)
        mActor->deleteLater(ksys::act::BaseProc::DeleteReason::_0);
    if ((_14c.getDirect() & 5) == 1 && !mActor->getCreateArgBaseProcLink().hasProc())
        mActor->deleteLater(ksys::act::BaseProc::DeleteReason::_0);

    _130 = actor->getMtx().getTranslation();
}

void DragonItemRoot::leave_() {
    ItemRoot::leave_();
}

void DragonItemRoot::loadParams_() {
    ItemRoot::loadParams_();
    getStaticParam(&mFlyStartTime_s, "FlyStartTime");
    getStaticParam(&mClearFlagTimeAtRunel_s, "ClearFlagTimeAtRunel");
    getStaticParam(&mGravity_s, "Gravity");
    getStaticParam(&mFlyStartHeightAtRunel_s, "FlyStartHeightAtRunel");
    getStaticParam(&mTailXLinkEventName_s, "TailXLinkEventName");
    getStaticParam(&mAuraXLinkEventName_s, "AuraXLinkEventName");
    getStaticParam(&mFlyPrepareXinkEventName_s, "FlyPrepareXinkEventName");
    getStaticParam(&mFlyStartXinkEventName_s, "FlyStartXinkEventName");
    getStaticParam(&mHitGroundXLinkEventName_s, "HitGroundXLinkEventName");
    getStaticParam(&mLightShaftXLinkEventName_s, "LightShaftXLinkEventName");
    getStaticParam(&mActivateXlinkEventName_s, "ActivateXlinkEventName");
    getStaticParam(&mDestroySwitchGameData_s, "DestroySwitchGameData");
    getStaticParam(&mClearFlagLabel_s, "ClearFlagLabel");
    getStaticParam(&mDropItemFlagLabel_s, "DropItemFlagLabel");
    getMapUnitParam(&mTargetPosition_m, "TargetPosition");
    getAITreeVariable(&mIsInitFromCarryBox_a, "IsInitFromCarryBox");
    getAITreeVariable(&mIsInsideObserverArea_a, "IsInsideObserverArea");
}

// NON_MATCHING: parameter-pack count and string-call preparation are scheduled differently.
void DragonItemRoot::sub_710036CE54(ksys::act::Actor* actor) {
    if (auto* dragon = sead::DynamicCast<act::Dragon>(actor)) {
        ksys::act::ai::InlineParamPack params;
        params.addString(dragon->_1f78.cstr(), "NodeName", -1);
        params.addVec3(sead::Vector3f::zero, "RotOffset", -1);
        params.addVec3({dragon->_1fac, dragon->_1fbc, dragon->_1fcc}, "TransOffset", -1);
        mActor->getMainBody()->enableContactLayer(ksys::phys::ContactLayer::SensorAttackEnemy);
        changeChild("体に貼り付く", &params);
    }
}

bool DragonItemRoot::handleMessage_(const ksys::Message* message) {
    if (message->getType() == 0x3000009) {
        *mIsInsideObserverArea_a = true;
        return true;
    }
    return false;
}

}  // namespace uking::ai
