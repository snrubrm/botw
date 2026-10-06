#include "Game/AI/Action/actionSiteBossSwordMove.h"
#include "Game/Actor/actSiteBoss.h"
#include "KingSystem/ActorSystem/actActor.h"
#include "KingSystem/ActorSystem/actActorSensorUtil.h"
#include "Game/AI/aiUnk_71005D6D10.h"
#include "Game/AI/aiUnk_710073fa90.h"
#include "KingSystem/Utils/MathUtil.h"
#include "KingSystem/Physics/CharacterController/physCharacterController.h"

namespace uking::action {

SiteBossSwordMove::SiteBossSwordMove(const InitArg& arg) : ksys::act::ai::Action(arg) {}

SiteBossSwordMove::~SiteBossSwordMove() = default;

bool SiteBossSwordMove::init_(sead::Heap* heap) {
    return ksys::act::ai::Action::init_(heap);
}

// NON_MATCHING: the original loads the three translation words into registers before the sqrt of the
// front vector (and stores `front` as one block after it); here they are loaded and converted later
void SiteBossSwordMove::enter_(ksys::act::ai::InlineParamPack* params) {
    auto* controller = mActor->getCharacterController();
    if (!controller) {
        setFailed();
        return;
    }
    controller->enableContactLayer(ksys::phys::ContactLayer::EntityNPC);
    controller->enableContactLayer(ksys::phys::ContactLayer::EntityNPC_NoHitPlayer);
    controller->enableContactLayer(ksys::phys::ContactLayer::EntityObject);
    controller->enableContactLayer(ksys::phys::ContactLayer::EntityGroundObject);
    controller->sub_7100F5E764(false);
    controller->sub_7100F62CA8(false);

    sead::Vector3f front;
    mActor->getMtx().getBase(front, 2);
    front.y = 0;
    const sead::Vector3f pos = mActor->getMtx().getTranslation();
    front.normalize();
    const sead::Vector3f up = sead::Vector3f::ey;
    sead::Vector3f to_dst = *mMoveDstPos_d;
    to_dst -= pos;
    ksys::util::sub_71011EFA00(&to_dst, to_dst, up);
    to_dst.normalize();
    sead::Vector3f axis;
    f32 angle;
    ksys::util::sub_71011EEB08(&axis, &angle, front, to_dst, sead::Vector3f::ey);
    angle = sead::Mathf::rad2deg(angle) * axis.y;
    playAS("Run_Loop_R", false, 0, 0, -1.0f);

    sub_710073FA90(&_a0, mActor);
    _6c.reset(*mCurrentFrame_d, 1.0f);
    _78.reset(*mAfterImage0AppearFrame_s);
    _84.reset(*mAfterImage1AppearFrame_s);
    _90 = 0;
    sub_71007A3540(mActor);
    if (*mCurrentFrame_d < *mAfterImage0AppearFrame_s) {
        if (auto* boss = sead::DynamicCast<act::SiteBoss>(mActor)) {
            if (*mIsCloseMove_d) {
                if (boss->_14c8._30.isOnBit(2))
                    sub_710026B5D8(1, &pos, &pos, 0.0f);
                else
                    sub_710026B5D8(0, &pos, &pos, 0.0f);
            } else {
                if (boss->_14c8._30.isOnBit(2))
                    sub_710026B5D8(6, &pos, &pos, 0.0f);
                else
                    sub_710026B5D8(5, &pos, &pos, 0.0f);
            }
        }
    }
    _94 = pos;
    _68 = 2;
}

void SiteBossSwordMove::sub_710026B5D8(int idx, const sead::Vector3f* front, const sead::Vector3f* pos,
                                       f32 value) {
    auto* boss = sead::DynamicCast<act::SiteBoss>(mActor);
    if (!boss)
        return;
    auto& mgr = boss->_1560;
    sead::Matrix34f mtx;
    sead::Vector3f dir = *mTargetPos_d;
    dir -= *pos;
    dir.y = 0;
    dir.normalize();
    const sead::Vector3f up = sead::Vector3f::ey;
    ksys::util::sub_71011F00EC(&mtx, dir, up, *front, false);
    act::SiteBoss::Unk_71002cf2ac::SpawnArg arg;
    arg.pos = *pos;
    arg._14 = value;
    arg._18 = idx != 4;
    arg._19 = !boss->_14c8._30.isOnBit(2);
    arg._1a = boss->_1558.isOnBit(4);
    arg._1b = boss->_1558.isOnBit(5);
    mgr.sub_710066CDF8(mActor, mtx, idx, arg);
    _90 |= 1 << idx;
}

void SiteBossSwordMove::leave_() {
    if (auto* controller = mActor->getCharacterController()) {
        controller->sub_7100F60604();
        controller->sub_7100F5E764(true);
        controller->sub_7100F62CA8(true);
    }
    mActor->getActorFlags2().reset(ksys::act::Actor::ActorFlag2::_20);
    sead::DynamicCast<act::SiteBoss>(mActor);
}

void SiteBossSwordMove::loadParams_() {
    getStaticParam(&mAfterImage0AppearFrame_s, "AfterImage0AppearFrame");
    getStaticParam(&mAfterImage1AppearFrame_s, "AfterImage1AppearFrame");
    getStaticParam(&mAppearFrame_s, "AppearFrame");
    getDynamicParam(&mCurrentFrame_d, "CurrentFrame");
    getDynamicParam(&mIsCloseMove_d, "IsCloseMove");
    getDynamicParam(&mTargetPos_d, "TargetPos");
    getDynamicParam(&mMoveDstPos_d, "MoveDstPos");
    getDynamicParam(&mAfterImage0Pos_d, "AfterImage0Pos");
    getDynamicParam(&mAfterImage1Pos_d, "AfterImage1Pos");
}

// NON_MATCHING: the original keeps the (unused) sqrt of (MoveDstPos - pos) after sub_710074006C; the
// compiler drops it here (everything else is the same)
void SiteBossSwordMove::calc_() {
    auto* controller = mActor->getCharacterController();
    if (!controller) {
        setFailed();
        return;
    }
    if (_68 > 0) {
        if (--_68 == 0) {
            mActor->getActorFlags2().set(ksys::act::Actor::ActorFlag2::_20);
            sub_71007A36BC(mActor);
        }
        return;
    }

    sub_710073FA94(&_a0, mActor);
    const sead::Vector3f pos = mActor->getMtx().getTranslation();
    const sead::Vector3f up = sead::Vector3f::ey;
    sead::Vector3f to_dst = *mTargetPos_d;
    to_dst -= *mMoveDstPos_d;
    ksys::util::sub_71011EFA00(&to_dst, to_dst, up);
    to_dst.normalize();
    sub_710074006C(&_a0, to_dst, up, true, 0.66f, 0.36f, 0.001f);
    [[maybe_unused]] const f32 dist = (*mMoveDstPos_d - pos).length();

    _6c.update();
    if (_6c.value >= *mAppearFrame_s) {
        setFinished();
    } else {
        const sead::Matrix34f mtx(_a0, *mMoveDstPos_d);
        controller->sub_7100F5F938(mtx);
    }

    if (*mCurrentFrame_d < *mAfterImage0AppearFrame_s && !(_90 & 4) &&
        _6c.value >= *mAfterImage0AppearFrame_s - 5.0f) {
        sub_710026B5D8(2, &_94, mAfterImage0Pos_d, *mAfterImage0AppearFrame_s - _6c.value);
    }
    if (*mCurrentFrame_d < *mAfterImage1AppearFrame_s && !(_90 & 8) &&
        _6c.value >= *mAfterImage1AppearFrame_s - 5.0f) {
        sub_710026B5D8(3, mAfterImage0Pos_d, mAfterImage1Pos_d,
                       *mAfterImage1AppearFrame_s - *mCurrentFrame_d);
    }
    if (*mCurrentFrame_d < *mAppearFrame_s && !(_90 & 0x10) &&
        _6c.value >= *mAppearFrame_s - 5.0f) {
        sub_710026B5D8(4, mAfterImage1Pos_d, mMoveDstPos_d, *mAppearFrame_s - *mCurrentFrame_d);
    }
}

bool SiteBossSwordMove::isFinished() const {
    return _6c.value >= *mAppearFrame_s || ActionBase::isFinished();
}

}  // namespace uking::action
