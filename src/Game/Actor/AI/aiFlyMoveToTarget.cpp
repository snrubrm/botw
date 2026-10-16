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
    _a8.value = 0;
    _a8.previous_value = 0;
    _98 = target;
    _a8.rate = 1.0f;
    sub_71003D4414();
}

// NON_MATCHING: the height add operand order (as in the helpers above) and the load order of the distance checks
void FlyMoveToTarget::calc_() {
    auto* child = getCurrentChild();
    if (!isCurrentChild("遠距離移動") && _a8.value >= 15.0f) {
        sub_71003D4C84();
        _a8.reset(0.0f, 1.0f);
    } else {
        _a8.update();
    }

    const auto targetDist = [this] {
        const sead::Vector3f pos = mActor->getMtx().getTranslation();
        const sead::Vector3f& target = *mTargetPos_d;
        const sead::Vector3f diff(pos.x - target.x, pos.y - (target.y + *mOffsetHeight_s), pos.z - target.z);
        return diff.length();
    };

    if (child->isFinished() || child->isFailed()) {
        if (isCurrentChild("目標位置移動")) {
            if (child->isFinished()) {
                _b4 = 0;
                setFinished();
                return;
            }
            ++_b4;
            _a4 = false;
            _60.clear();
            if (*mMoveFailCount_s >= 1 && s32(_b4) >= *mMoveFailCount_s) {
                setFailed();
                return;
            }
            changeChild("見回し");
            return;
        }

        if (isCurrentChild("経由点移動")) {
            _60.popFront();
            if (child->isFailed())
                _60.clear();
            sead::Vector3f pos;
            mActor->getMtx().getTranslation(pos);
            sead::Vector3f target;
            target = *mTargetPos_d;
            target.y += *mOffsetHeight_s;
            const bool hit = sub_710072E5F8(pos, target, 0, nullptr, nullptr, nullptr, 0.0f);
            _a4 = !hit;
            if (!hit) {
                changeToTargetPosMove();
                return;
            }
            if (_60.size() == 0) {
                changeChild("見回し");
                return;
            }
            changeToViaPointMove();
            return;
        }

        if (isCurrentChild("上昇")) {
            if (targetDist() > *mFarDist_s)
                changeToMoveFar();
            else
                changeChild("見回し");
            return;
        }

        if (isCurrentChild("下降")) {
            auto* nav = mActor->m45();
            if (nav && (nav->_2a4 & 0xffff) != 0x17)
                changeToMoveOnNavMesh();
            else
                changeChild("見回し");
            return;
        }

        if (isCurrentChild("遠距離移動")) {
            if (child->isFinished())
                sub_71003D4414();
            else
                changeChild("上昇");
            return;
        }

        if (isCurrentChild("見回し")) {
            changeChild("待機");
            return;
        }

        if (isCurrentChild("ナビメッシュ移動")) {
            if (child->isFinished())
                setFinished();
            else
                changeChild("上昇");
            return;
        }

        if (isCurrentChild("待機"))
            setFailed();
        return;
    }

    if (child->isChangeable()) {
        if (isCurrentChild("目標位置移動")) {
            if (!_a4) {
                if (_60.size() == 0) {
                    changeChild("見回し");
                    return;
                }
                changeToViaPointMove();
                return;
            }
        } else if (_a4) {
            changeToTargetPosMove();
            return;
        }

        if (isCurrentChild("遠距離移動")) {
            if (targetDist() > *mOutDist_s)
                setFailed();
        } else if (!isCurrentChild("上昇") && !isCurrentChild("下降") && !isCurrentChild("ナビメッシュ移動")) {
            if (targetDist() > *mFarDist_s)
                changeToMoveFar();
        }
    }

    if (isCurrentChild("目標位置移動")) {
        sead::Vector3f target;
        target = *mTargetPos_d;
        target.y += *mOffsetHeight_s;
        child->setDynamicParam(target, "TargetPos");
    }
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
// NON_MATCHING: stack layout (our distance temporary takes an extra slot), the height add operand order and the
// copy into the via point buffer
void FlyMoveToTarget::sub_71003D4C84() {
    sead::Vector3f target;
    target = *mTargetPos_d;
    target.y += *mOffsetHeight_s;
    sead::Vector3f pos;
    mActor->getMtx().getTranslation(pos);
    sead::Vector3f raised;
    raised = *mTargetPos_d;
    raised.y += *mOffsetHeight_s;
    const bool hit = sub_710072E5F8(pos, raised, 0, nullptr, nullptr, nullptr, 0.0f);
    _a4 = !hit;
    if (!hit) {
        if (isCurrentChild("目標位置移動"))
            _60[0] = target;
        return;
    }
    if (_60.size() == 0 || _60.size() >= _60.capacity())
        return;
    if (!((_60.back() - target).length() > 0.5f))
        return;
    if (sub_710072E5F8(_60.back(), target, 0, nullptr, nullptr, nullptr, 0.0f))
        return;
    _60.pushBack(target);
}

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
