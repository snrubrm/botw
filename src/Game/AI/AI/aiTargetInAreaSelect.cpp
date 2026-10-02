#include "Game/AI/AI/aiTargetInAreaSelect.h"
#include "KingSystem/ActorSystem/actAiInlineParam.h"

namespace uking::ai {

TargetInAreaSelect::TargetInAreaSelect(const InitArg& arg) : ksys::act::ai::Ai(arg) {}

TargetInAreaSelect::~TargetInAreaSelect() = default;

bool TargetInAreaSelect::init_(sead::Heap* heap) {
    return ksys::act::ai::Ai::init_(heap);
}

void TargetInAreaSelect::enter_(ksys::act::ai::InlineParamPack* params) {
    if (m34()) {
        ksys::act::ai::InlineParamPack child_params;
        m35(&child_params);
        changeChild("エリア内", &child_params);
    } else {
        ksys::act::ai::InlineParamPack child_params;
        m35(&child_params);
        changeChild("エリア外", &child_params);
    }
}

void TargetInAreaSelect::calc_() {
    auto* child = getCurrentChild();
    if (child->isFinished() || child->isFailed()) {
        if (child->isFinished())
            setFinished();
        else
            setFailed();
    }

    if (!*mOption_s)
        return;
    if (!child->isChangeable())
        return;

    switch (*mOption_s) {
    case 3: {
        const bool is_inside = isCurrentChild("エリア内");
        const bool is_in_area = m34();
        if (is_inside) {
            if (!is_in_area) {
                ksys::act::ai::InlineParamPack child_params;
                m35(&child_params);
                changeChild("エリア外", &child_params);
            }
        } else if (is_in_area) {
            ksys::act::ai::InlineParamPack child_params;
            m35(&child_params);
            changeChild("エリア内", &child_params);
        }
        break;
    }
    case 2:
        if (isCurrentChild("エリア内") && !m34()) {
            ksys::act::ai::InlineParamPack child_params;
            m35(&child_params);
            changeChild("エリア外", &child_params);
        }
        break;
    case 1:
        if (isCurrentChild("エリア外") && m34()) {
            ksys::act::ai::InlineParamPack child_params;
            m35(&child_params);
            changeChild("エリア内", &child_params);
        }
        break;
    }
}

void TargetInAreaSelect::leave_() {
    ksys::act::ai::Ai::leave_();
}

void TargetInAreaSelect::loadParams_() {
    getStaticParam(&mOption_s, "Option");
}

}  // namespace uking::ai
