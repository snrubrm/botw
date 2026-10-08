#include "Game/AI/AI/aiKeepBackSelect.h"
#include <cmath>
#include <gsys/gsysModel.h>
#include <gsys/gsysModelUnit.h>
#include <random/seadGlobalRandom.h>
#include "Game/AI/aiUnk_71005D6D10.h"
#include "KingSystem/ActorSystem/actActor.h"
#include "KingSystem/System/Timer.h"

namespace uking::ai {

KeepBackSelect::KeepBackSelect(const InitArg& arg) : ksys::act::ai::Ai(arg) {}

KeepBackSelect::~KeepBackSelect() = default;

bool KeepBackSelect::init_(sead::Heap* heap) {
    if (!mNodeName_s.isEmpty()) {
        auto* model = mActor->getModel();
        const sead::SafeString& name = mNodeName_s;
        _70.search(model, name);
    }
    return true;
}

void KeepBackSelect::enter_(ksys::act::ai::InlineParamPack* params) {
    const s32 keep_time = *mKeepTime_s;
    _ac = keep_time;
    _b0 = keep_time;
    _a8 = keep_time;
    changeChild("角度内", params);
}

// NON_MATCHING: the original takes &_a8 into a register ahead of the branch (the natural form re-materialises it)
void KeepBackSelect::calc_() {
    if (isCurrentChild("角度内")) {
        if (sub_710045134C()) {
            ksys::Timer::update(&_a8, -1.0f);
        } else {
            s32 value = _ac;
            if (_b0 != _ac)
                value = sead::GlobalRandom::instance()->getS32Range(_ac, _b0);
            _a8 = value;
        }
    }

    auto* child = getCurrentChild();
    if (child->isFinished() || child->isFailed()) {
        s32 value = _ac;
        if (_b0 != _ac)
            value = sead::GlobalRandom::instance()->getS32Range(_ac, _b0);
        _a8 = value;
        changeChild("角度内", nullptr);
    } else if (child->isChangeable()) {
        if (isCurrentChild("角度内") && _a8 <= 0.0f)
            changeChild("角度外", nullptr);
    }
}

void KeepBackSelect::leave_() {
    ksys::act::ai::Ai::leave_();
}

bool KeepBackSelect::sub_710045134C() {
    auto* model = mActor->getModel();
    sead::Matrix34f mtx;
    sead::Vector3f pos;
    if (model == nullptr || mNodeName_s.isEmpty()) {
        const sead::Matrix34f& actor_mtx = mActor->getMtx();
        pos.x = actor_mtx.m[0][3];
        pos.y = actor_mtx.m[1][3];
        pos.z = actor_mtx.m[2][3];
    } else {
        model->getUnits()(_70.getKey().model_unit_index)->mModelUnit->getBoneWorldMatrix(
            &mtx, _70.getKey().bone_index);
        const sead::Vector3f off = *mLocalOffset_s;
        pos.x = off.x * mtx.m[0][0] + off.y * mtx.m[0][1] + off.z * mtx.m[0][2];
        pos.y = off.x * mtx.m[1][0] + off.y * mtx.m[1][1] + off.z * mtx.m[1][2];
        pos.z = off.x * mtx.m[2][0] + off.y * mtx.m[2][1] + off.z * mtx.m[2][2];
        pos.x += mtx.m[0][3];
        pos.y += mtx.m[1][3];
        pos.z += mtx.m[2][3];
    }

    const sead::Vector3f& target = sub_71005D9330(mActor);
    sead::Vector3f dir;
    dir.x = target.x - pos.x;
    dir.z = target.z - pos.z;
    if (*mXZOnly_s) {
        dir.y = 0.0f;
        dir.normalize();
    } else {
        dir.y = target.y - pos.y;
    }

    sead::Vector3f fwd;
    if (model != nullptr && !mNodeName_s.isEmpty()) {
        switch (*mBaseAxis_s) {
        default: {
            const sead::Matrix34f& actor_mtx = mActor->getMtx();
            fwd.x = actor_mtx.m[0][2];
            fwd.y = actor_mtx.m[1][2];
            fwd.z = actor_mtx.m[2][2];
            break;
        }
        case -1: {
            const sead::Matrix34f& actor_mtx = mActor->getMtx();
            fwd.x = actor_mtx.m[0][2];
            fwd.y = actor_mtx.m[1][2];
            fwd.z = actor_mtx.m[2][2];
            break;
        }
        case 0:
        case 1:
        case 2: {
            model->getUnits()(_70.getKey().model_unit_index)->mModelUnit->getBoneWorldMatrix(
                &mtx, _70.getKey().bone_index);
            fwd.x = mtx.m[0][*mBaseAxis_s];
            fwd.y = mtx.m[1][*mBaseAxis_s];
            fwd.z = mtx.m[2][*mBaseAxis_s];
            break;
        }
        case 3:
        case 4:
        case 5: {
            model->getUnits()(_70.getKey().model_unit_index)->mModelUnit->getBoneWorldMatrix(
                &mtx, _70.getKey().bone_index);
            fwd.x = -mtx.m[0][*mBaseAxis_s];
            fwd.y = -mtx.m[1][*mBaseAxis_s];
            fwd.z = -mtx.m[2][*mBaseAxis_s];
            break;
        }
        }
    } else {
        const sead::Matrix34f& actor_mtx = mActor->getMtx();
        fwd.x = actor_mtx.m[0][2];
        fwd.y = actor_mtx.m[1][2];
        fwd.z = actor_mtx.m[2][2];
    }

    if (*mXZOnly_s) {
        fwd.y = 0.0f;
        fwd.normalize();
    }
    return !(dir.y * fwd.y + dir.x * fwd.x + dir.z * fwd.z >= std::cos(*mBackAngle_s));
}

void KeepBackSelect::loadParams_() {
    getStaticParam(&mKeepTime_s, "KeepTime");
    getStaticParam(&mBaseAxis_s, "BaseAxis");
    getStaticParam(&mBackAngle_s, "BackAngle");
    getStaticParam(&mXZOnly_s, "XZOnly");
    getStaticParam(&mNodeName_s, "NodeName");
    getStaticParam(&mLocalOffset_s, "LocalOffset");
}

}  // namespace uking::ai
