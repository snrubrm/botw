#include "Game/Actor/AI/aiAnimalBattleMoveLeave.h"
#include "Game/Actor/aiUnk_71007377D4.h"
#include "KingSystem/ActorSystem/actActor.h"
#include "KingSystem/ActorSystem/actAiInlineParam.h"

namespace uking::ai {

namespace {
const f32 sLeaveAngles[] = {sead::Mathf::deg2rad(-135.0f), sead::Mathf::deg2rad(135.0f)};
}


AnimalBattleMoveLeave::AnimalBattleMoveLeave(const InitArg& arg) : ksys::act::ai::Ai(arg) {}

AnimalBattleMoveLeave::~AnimalBattleMoveLeave() = default;

bool AnimalBattleMoveLeave::init_(sead::Heap* heap) {
    return ksys::act::ai::Ai::init_(heap);
}

// NON_MATCHING: store scheduling of the first three members only (the original stores _50 right after the `this`
// move and builds the _48 / _4c pair afterwards)
void AnimalBattleMoveLeave::enter_(ksys::act::ai::InlineParamPack* params) {
    _48 = ksys::Timer(0.0f, -1.0f, 0.0f);
    _54 = *mTargetPos_d;
    _60 = ksys::Timer(-1.0f, -1.0f, 0.0f);
    _6c = 0;
    if (sub_710072FEC4(mActor, mActor->getMtx().getBase(2), *mCheckForwardDist_s, nullptr, true,
                       nullptr)) {
        sub_7100303A90();
    } else {
        ksys::act::ai::InlineParamPack pack;
        pack.addVec3(_54, "TargetPos", -1);
        changeChild("移動", &pack);
    }
}

// NON_MATCHING: the original loads all vector components and the distance parameter before the sqrt and
// scales the direction in a different register order
void AnimalBattleMoveLeave::sub_7100303A90() {
    sead::Vector3f dir = -mActor->getMtx().getBase(2);
    const f32 length = dir.length();
    if (length > 0.0f)
        dir *= *mCheckForwardDist_s * 3.0f / length;
    sead::Vector3f position;
    mActor->getMtx().getTranslation(position);
    _48 = ksys::Timer(70.0f, 70.0f);
    _54 = position + dir;
    _60 = ksys::Timer(-1.0f, -1.0f, 0.0f);
    ++_6c;
    ksys::act::ai::InlineParamPack pack;
    pack.addVec3(_54, "TargetPos", -1);
    changeChild("旋回", &pack);
}

// NON_MATCHING: stack slot of the front-axis temporary in the changeable branch only.
void AnimalBattleMoveLeave::calc_() {
    if (isCurrentChild("旋回") || !(_48.value <= sead::Mathf::epsilon()) ||
        !(_60.value <= sead::Mathf::epsilon())) {
        _48.update();
        if (_48.value <= sead::Mathf::epsilon())
            _48 = ksys::Timer(-1.0f, -1.0f, 0.0f);
    } else {
        _54 = sub_7100304170();
    }
    getCurrentChild()->setDynamicParam(_54, "TargetPos");
    _60.update();
    if (_60.value <= sead::Mathf::epsilon())
        _60 = ksys::Timer(-1.0f, -1.0f, 0.0f);

    const auto changeToMove = [this] {
        ksys::act::ai::InlineParamPack pack;
        pack.addVec3(_54, "TargetPos", -1);
        changeChild("移動", &pack);
    };

    auto* child = getCurrentChild();
    if (child->isFinished() || child->isFailed()) {
        if (!sub_710072FEC4(mActor, mActor->getMtx().getBase(2), *mCheckForwardDist_s, nullptr,
                            true, nullptr)) {
            if (isCurrentChild("旋回")) {
                changeToMove();
                return;
            }
            if (child->isFinished())
                setFinished();
            changeToMove();
            return;
        }
        sead::Vector3f pos;
        mActor->getMtx().getTranslation(pos);
        const sead::Vector3f ahead = mActor->getMtx().getBase(2) * 3.0f + pos;
        if (sub_710072EC90(pos, ahead, nullptr, 1.0f, 2.0f)) {
            _60 = ksys::Timer(10, 10);
            _54 = ahead;
            changeToMove();
            return;
        }
        if (_6c > 2) {
            setFailed();
            changeToMove();
            return;
        }
    } else {
        if (!child->isChangeable() || isCurrentChild("旋回") ||
            !(_60.value <= sead::Mathf::epsilon()))
            return;
        if (!sub_710072FEC4(mActor, mActor->getMtx().getBase(2), *mCheckForwardDist_s, nullptr,
                            true, nullptr))
            return;
    }
    sub_7100303A90();
}

// NON_MATCHING: vector load/register scheduling, temporary stack slots and probe-return layout differ.
sead::Vector3f AnimalBattleMoveLeave::sub_7100304170() {
    auto* actor = mActor;
    const auto position = actor->getMtx().getTranslation();
    const auto target = *mTargetPos_d;
    sead::Vector3f front = actor->getMtx().getBase(2);
    front.normalize();
    sead::Vector3f direction = target - position;
    direction.y = 0.0f;
    direction.normalize();
    const f32 angle = sLeaveAngles[front.cross(direction).y >= 0.0f];
    sead::Matrix34f rotation;
    rotation.makeR({0.0f, angle, 0.0f});
    sead::Vector3f offset;
    offset.setRotated(rotation, -direction);
    offset.normalize();
    offset *= 5.0f;
    sead::Vector3f destination = target + offset;
    sead::Vector3f hit_position;
    if (!sub_710072FAB0(actor, destination, &hit_position, -1, -1.0f, -1.0f)) {
        destination = target + offset * 0.9f;
        direction = destination - position;
        direction.normalize();
        if (!sub_710072FAB0(actor, destination + direction, &hit_position, -1, -1.0f, -1.0f)) {
            destination = target + offset * 1.6f;
            direction = destination - position;
            direction.normalize();
            if (!sub_710072FAB0(actor, destination + direction, &hit_position, -1, -1.0f, -1.0f))
                destination = *mTargetPos_d;
        }
        _48 = ksys::Timer(70.0f, 70.0f);
    }
    return destination;
}

void AnimalBattleMoveLeave::leave_() {
    ksys::act::ai::Ai::leave_();
}

void AnimalBattleMoveLeave::loadParams_() {
    getStaticParam(&mCheckForwardDist_s, "CheckForwardDist");
    getDynamicParam(&mTargetPos_d, "TargetPos");
}

}  // namespace uking::ai
