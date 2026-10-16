#include "Game/Actor/AI/aiSiteBossThrowIceRoot.h"
#include "KingSystem/ActorSystem/actActorLinkConstDataAccess.h"
#include "KingSystem/Utils/MathUtil.h"
#include "KingSystem/Physics/CharacterController/physCharacterController.h"
#include "Game/Actor/aiUnk_710073fa90.h"
#include "Game/Actor/actSiteBoss.h"
#include "KingSystem/ActorSystem/actAiInlineParam.h"

namespace uking::ai {

SiteBossThrowIceRoot::SiteBossThrowIceRoot(const InitArg& arg) : ksys::act::ai::Ai(arg) {}

// The original keeps the vtable store that a defaulted destructor drops (same form as upstream's
// GameDataFlagSelector::~GameDataFlagSelector() { ; }, commit 96101229).
SiteBossThrowIceRoot::~SiteBossThrowIceRoot() {
    ;
}

bool SiteBossThrowIceRoot::init_(sead::Heap* heap) {
    return ksys::act::ai::Ai::init_(heap);
}

void SiteBossThrowIceRoot::enter_(ksys::act::ai::InlineParamPack* params) {
    ksys::act::ai::InlineParamPack child_params;
    child_params.addInt(*mIgnitionNum_s, "IgnitionNum", -1);
    changeChild("弾生成", &child_params);
}

// 0x71005999c4
// NON_MATCHING: stack slots of the up / direction vectors (as in SiteBossLswordTornadoRoot::calc_) and the timer test
// (the original branches with b.hi, i.e. `!(value <= epsilon)`)
void SiteBossThrowIceRoot::calc_() {
    auto* controller = mActor->getCharacterController();
    if (!controller) {
        setFailed();
        return;
    }

    sead::Vector3f up = -controller->get70();
    if (up.normalize() < sead::Mathf::epsilon())
        up = sead::Vector3f::ey;
    sub_710073FA94(&_64, mActor);
    const sead::Vector3f target = *mTargetPos_d;
    sead::Vector3f dir = target;
    dir -= mActor->getMtx().getTranslation();
    ksys::util::sub_71011EFA00(&dir, dir, up);
    dir.normalize();
    sub_710074006C(&_64, dir, up, true, 0.16f, sead::Mathf::pi2(), 0.0f);
    sub_7100740E04(_64, controller);

    if (isCurrentChild("弾生成")) {
        auto* child = getCurrentChild();
        if (child->isFinished() || child->isFailed())
            sub_7100599EF4(target);
        return;
    }

    const bool firing = isCurrentChild("弾発射");
    if (firing) {
        getCurrentChild()->setDynamicParam(target, "TargetPos");
        auto* child = getCurrentChild();
        if (child->isFinished() || child->isFailed()) {
            _60 = true;
            {
                ksys::act::ai::InlineParamPack pack;
                pack.addVec3(target, "TargetPos", -1);
                changeChild("発射後待機", &pack);
            }
            _88 = ksys::Timer(9000, 9000);
            mFlags.set(Flag::Changeable);
        }
        return;
    }

    getCurrentChild()->setDynamicParam(target, "TargetPos");
    if (_60) {
        if (auto* boss = sead::DynamicCast<act::SiteBoss>(mActor)) {
            bool any_calc = false;
            bool any_x = false;
            for (u32 i = 0; i < 9; ++i) {
                auto& link = boss->_1560._1e0[i];
                if (!link.hasProc())
                    continue;
                ksys::act::ActorLinkConstDataAccess accessor;
                ksys::act::acquireActor(&link, &accessor);
                any_calc |= accessor.isStateCalc();
                const bool x = accessor.sub_7100D10FB8();
                any_x |= x;
                if (x)
                    break;
            }
            if (any_calc) {
                if (any_x)
                    return;
                _88.update();
                if (_88.value > sead::Mathf::epsilon())
                    return;
            }
        }
    }

    auto* child = getCurrentChild();
    if (child->isFinished() || child->isFailed())
        setFinished();
}

void SiteBossThrowIceRoot::leave_() {
    if (auto* boss = sead::DynamicCast<act::SiteBoss>(mActor)) {
        for (int i = 0; i < 9; ++i)
            boss->_1560.sub_710066CBD4(i);
    }
}

void SiteBossThrowIceRoot::loadParams_() {
    getStaticParam(&mIgnitionNum_s, "IgnitionNum");
    getStaticParam(&mThrowActorName_s, "ThrowActorName");
    getDynamicParam(&mTargetPos_d, "TargetPos");
    getDynamicParam(&mTargetActor_d, "TargetActor");
}

// 0x7100599ef4
void SiteBossThrowIceRoot::sub_7100599EF4(const sead::Vector3f& pos) {
    ksys::act::ai::InlineParamPack pack;
    pack.addVec3(pos, "TargetPos", -1);
    pack.addActor(*mTargetActor_d, "TargetActor", -1);
    changeChild("弾発射", &pack);
}

}  // namespace uking::ai
