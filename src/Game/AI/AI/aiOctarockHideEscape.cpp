#include "Game/AI/AI/aiOctarockHideEscape.h"
#include "KingSystem/ActorSystem/actAiInlineParam.h"

namespace uking::ai {

OctarockHideEscape::OctarockHideEscape(const InitArg& arg) : OctarockEscape(arg) {}

OctarockHideEscape::~OctarockHideEscape() = default;

bool OctarockHideEscape::init_(sead::Heap* heap) {
    return OctarockEscape::init_(heap);
}

void OctarockHideEscape::enter_(ksys::act::ai::InlineParamPack* params) {
    OctarockEscape::enter_(params);
}

void OctarockHideEscape::calc_() {
    OctarockEscape::calc_();
}

void OctarockHideEscape::leave_() {
    OctarockEscape::leave_();
}

void OctarockHideEscape::loadParams_() {
    OctarockEscape::loadParams_();
    getStaticParam(&mEscapeDist_s, "EscapeDist");
}

void OctarockHideEscape::m35() {
    sub_71004ECB04();
    sead::Vector3f pos;
    sub_71004EBE08(&pos, *mEscapeDist_s, *mTargetPos_d);
    _68 = pos;
    ksys::act::ai::InlineParamPack params;
    params.addVec3(pos, "TargetPos", -1);
    changeChild("移動", &params);
}

}  // namespace uking::ai
