#include "Game/Actor/AI/aiFlyMoveToTarget.h"
#include "KingSystem/ActorSystem/actActor.h"
#include "KingSystem/ActorSystem/actAiInlineParam.h"
#include "Game/Actor/aiUnk_71007377D4.h"
#include "KingSystem/Physics/System/physHavokAI.h"
#include "KingSystem/Physics/System/physNavMeshCharacter.h"

namespace uking::ai {

FlyMoveToTarget::FlyMoveToTarget(const InitArg& arg) : ksys::act::ai::Ai(arg) {}

FlyMoveToTarget::~FlyMoveToTarget() = default;

bool FlyMoveToTarget::init_(sead::Heap* heap) {
    return ksys::act::ai::Ai::init_(heap);
}

void FlyMoveToTarget::enter_(ksys::act::ai::InlineParamPack* params) {
    _b4 = 0;
    sead::Vector3f target = *mTargetPos_d;
    target.y += *mOffsetHeight_s;
    _60.clear();
    _a4 = false;
    _a8 = 0;
    _ac = 0;
    _98 = target;
    _b0 = 1.0f;
    sub_71003D4414();
}

void FlyMoveToTarget::leave_() {
    ksys::act::ai::Ai::leave_();
}

void FlyMoveToTarget::loadParams_() {
    getStaticParam(&mMoveFailCount_s, "MoveFailCount");
    getStaticParam(&mFarDist_s, "FarDist");
    getStaticParam(&mOutDist_s, "OutDist");
    getStaticParam(&mOffsetHeight_s, "OffsetHeight");
    getDynamicParam(&mTargetPos_d, "TargetPos");
}

// NON_MATCHING: the original adds in the other operand order (fadd y, h) with the height loaded first
void FlyMoveToTarget::changeToTargetPosMove() {
    sead::Vector3f target;
    target = *mTargetPos_d;
    target.y += *mOffsetHeight_s;
    _60.clear();
    _60.pushBack(target);
    ksys::act::ai::InlineParamPack pack;
    pack.addVec3(target, "TargetPos", -1);
    changeChild("目標位置移動", &pack);
}

void FlyMoveToTarget::changeToDescend(f32 height) {
    sead::Vector3f position = mActor->getMtx().getTranslation();
    position.y = height;
    ksys::act::ai::InlineParamPack pack;
    pack.addVec3(position, "TargetPos", -1);
    pack.addFloat(height, "TargetHeight", -1);
    changeChild("下降", &pack);
}

void FlyMoveToTarget::changeToViaPointMove() {
    ksys::act::ai::InlineParamPack pack;
    pack.addVec3(_60[0], "TargetPos", -1);
    changeChild("経由点移動", &pack);
}

// NON_MATCHING: the original adds in the other operand order (fadd y, h)
void FlyMoveToTarget::changeToMoveFar() {
    const sead::Vector3f& target = *mTargetPos_d;
    sead::Vector3f pos;
    pos.x = target.x;
    pos.y = target.y;
    pos.z = target.z;
    const f32 height = *mOffsetHeight_s;
    pos.y += height;

    ksys::act::ai::InlineParamPack pack;
    pack.addVec3(pos, "TargetPos", -1);
    changeChild("遠距離移動", &pack);
}

// NON_MATCHING: the original adds in the other operand order (fadd y, h)
// NON_MATCHING: the position / target copies are scheduled differently (the original copies them element by
// element into other stack slots) and the changeToMoveOnNavMesh tail is laid out elsewhere.
void FlyMoveToTarget::sub_71003D4414() {
    bool hit;
    {
        const sead::Vector3f& pos = mActor->getMtx().getTranslation();
        sead::Vector3f target(mTargetPos_d->x, mTargetPos_d->y, mTargetPos_d->z);
        sead::Vector3f from(pos.x, pos.y, pos.z);
        target.y += *mOffsetHeight_s;
        hit = sub_710072E5F8(from, target, 0, nullptr, nullptr, nullptr, 0.0f);
    }
    _a4 = !hit;
    if (!hit) {
        changeToTargetPosMove();
        return;
    }
    if (_60.size() != 0) {
        changeToViaPointMove();
        return;
    }

    auto* nav = mActor->m45();
    if (!nav) {
        changeChild("待機");
        return;
    }

    nav->_1e0.lock();
    if ((nav->_2a4 & 0xffff) != 0x17) {
        const f32 height = nav->_29c;
        nav->_1e0.unlock();
        if (mActor->getMtx().getTranslation().y > height + 1.0f)
            changeToDescend(height + 1.0f);
        else
            changeToMoveOnNavMesh();
        return;
    }
    nav->_1e0.unlock();

    const sead::Vector3f pos = mActor->getMtx().getTranslation();
    sead::Vector3f to(pos.x, pos.y + -10.0f, pos.z);
    sead::Vector3f ground = pos;
    sead::Vector3f hit_pos;
    sead::Vector3f from(pos.x, pos.y + 3.0f, pos.z);
    if (sub_710072E500(from, to, &hit_pos, nullptr, nullptr, 0.0f))
        ground = hit_pos;
    else
        ground = to;

    if (ksys::phys::HavokAI::instance()->sub_7100F87ED0(&to, ground, 0.5f).sub_7100F7EB40()) {
        changeToDescend(to.y + 1.0f);
        return;
    }
    if (pos.y < mTargetPos_d->y + *mOffsetHeight_s) {
        changeChild("上昇");
        return;
    }
    changeToDescend(ground.y);
}

void FlyMoveToTarget::changeToMoveOnNavMesh() {
    const sead::Vector3f& target = *mTargetPos_d;
    sead::Vector3f pos;
    pos.x = target.x;
    pos.y = target.y;
    pos.z = target.z;
    const f32 height = *mOffsetHeight_s;
    pos.y += height;

    ksys::act::ai::InlineParamPack pack;
    pack.addVec3(pos, "TargetPos", -1);
    changeChild("ナビメッシュ移動", &pack);
}

}  // namespace uking::ai
