#include "Game/AI/AI/aiHiddenOctarockSearchTarget.h"
#include "Game/AI/aiUnk_71005D6D10.h"
#include "Game/AI/aiAwarenessFilters.h"
#include "KingSystem/ActorSystem/actActor.h"
#include "KingSystem/ActorSystem/actAiInlineParam.h"
#include "KingSystem/ActorSystem/Awareness/actAwarenessInstance.h"
#include "KingSystem/ActorSystem/Awareness/actAwarenessRequest.h"

namespace uking::ai {

HiddenOctarockSearchTarget::HiddenOctarockSearchTarget(const InitArg& arg)
    : ksys::act::ai::Ai(arg) {}

HiddenOctarockSearchTarget::~HiddenOctarockSearchTarget() = default;

bool HiddenOctarockSearchTarget::init_(sead::Heap* heap) {
    return ksys::act::ai::Ai::init_(heap);
}

void HiddenOctarockSearchTarget::enter_(ksys::act::ai::InlineParamPack* params) {
    changeChild("飛び出す", params);
}

void HiddenOctarockSearchTarget::leave_() {
    mActor->m93(0, 0.0f);
}

// NON_MATCHING: the output vector and parameter pack occupy different stack locations.
void HiddenOctarockSearchTarget::calc_() {
    auto* child = getCurrentChild();
    if (child->isFinished() || child->isFailed()) {
        if (isCurrentChild("飛び出す")) {
            mActor->m93(2, 0.0f);
            changeChild("出現待機");
        } else if (isCurrentChild("出現待機")) {
            setFailed();
        } else if (isCurrentChild("気づき")) {
            setFinished();
        }
    } else if (child->isChangeable() && !isCurrentChild("気づき")) {
        sead::Vector3f position;
        if (sub_7100432B0C(&position)) {
            mActor->m93(4, 0.0f);
            ksys::act::ai::InlineParamPack params;
            params.addVec3(position, "TargetPos", -1);
            changeChild("気づき", &params);
        }
    }

    if (sub_71005DD780(mActor, 59, nullptr, 0, 0) && isCurrentChild("飛び出す"))
        mActor->m93(2, 0.0f);
}

void HiddenOctarockSearchTarget::loadParams_() {
    getStaticParam(&mNoticeTerrorLevel_s, "NoticeTerrorLevel");
    getStaticParam(&mNoticeWorryRange_s, "NoticeWorryRange");
}

// 0x7100432b0c
// NON_MATCHING: register allocation and tail sharing only (bool via w19, filter address kept in x20,
// request zero-store position, 4a branch layout). All four scan blocks, both thresholds, the sensor
// request and every call match.
bool HiddenOctarockSearchTarget::sub_7100432B0C(sead::Vector3f* out) {
    auto* awareness = mActor->getAwareness();
    if (!awareness)
        return false;

    if (auto* sensor = awareness->_260[0]) {
        if (sensor->_8.isBufferReady() && sensor->_8.size() >= 1) {
            auto* check = ksys::act::sub_7100D78E30(&sensor->_8, 0);
            if (u32(check->_a0) >= 2) {
                Unk_71024514c0 filter(mActor);
                if (auto* sensor2 = awareness->_260[0]) {
                    if (auto* entry = ksys::act::sub_7100D7EEE8(&sensor2->_8, &filter)) {
                        if (out)
                            *out = entry->_88;
                        return true;
                    }
                }
            }
        }
    }

    if (auto* sensor = awareness->_260[2]) {
        if (sensor->_8.size() >= 1) {
            if (auto* entry = ksys::act::sub_7100D78E30(&sensor->_8, 0)) {
                if (*mNoticeTerrorLevel_s <= entry->_a4) {
                    if (out)
                        *out = entry->_88;
                    return true;
                }
            }
        }
    }

    if (auto* sensor = awareness->_260[1]) {
        if (sensor->_8.isBufferReady() && sensor->_8.size() >= 1) {
            auto* check = ksys::act::sub_7100D78E30(&sensor->_8, 0);
            if (u32(check->_a0) >= 2) {
                Unk_71024514e8 filter(mActor, nullptr);
                if (auto* sensor2 = awareness->_260[1]) {
                    if (auto* entry = ksys::act::sub_7100D7EEE8(&sensor2->_8, &filter)) {
                        if (out)
                            *out = entry->_88;
                        return true;
                    }
                }
            }
        }
    }

    f32 range = *mNoticeWorryRange_s;
    if (range < 0.0f) {
        auto* awareness2 = mActor->getAwareness();
        if (!awareness2)
            return false;
        Unk_71023e2780 request;
        f32 value;
        if (auto* sensor = awareness2->_260[3]) {
            value = sensor->m4(&request) ? request._8 : 0.0f;
            if (value > 0.0f)
                range = value;
            else
                return false;
        } else {
            value = 0.0f;
        }
    }
    if (range <= 0.0f)
        return false;

    Unk_7102451510 filter;
    filter._28 = mActor;
    auto* sensor = awareness->_260[3];
    if (!sensor)
        return false;
    if (auto* entry = ksys::act::sub_7100D7EEE8(&sensor->_8, &filter)) {
        if (entry->_a8 <= range) {
            if (out)
                *out = entry->_88;
            return true;
        }
    }
    return false;
}

}  // namespace uking::ai
