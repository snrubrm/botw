#include "Game/AI/AI/aiDragonRootBase.h"
#include "KingSystem/Map/mapRail.h"

namespace uking::ai {

DragonRootBase::DragonRootBase(const InitArg& arg) : ksys::act::ai::Ai(arg) {}

DragonRootBase::~DragonRootBase() = default;

bool DragonRootBase::init_(sead::Heap* heap) {
    return ksys::act::ai::Ai::init_(heap);
}

void DragonRootBase::enter_(ksys::act::ai::InlineParamPack* params) {
    if (sub_7100EEF034(mActor, 0))
        sub_7100356764(m35(), 0.0f);
    m37();
}

void DragonRootBase::sub_7100356764(ksys::map::Rail* rail, f32 progress) {
    _38.sub_7100EEBAE0(rail ? rail : m35(), progress);
    _38.sub_7100EEBE9C(1);
}

bool DragonRootBase::reenter_(ksys::act::ai::ActionBase* other, bool x) {
    if (!ksys::act::ai::ActionBase::reenter_(other, true))
        return false;
    auto* root = sead::DynamicCast<DragonRootBase>(other);
    if (!root)
        return false;
    _38.sub_7100EEBAE0(root->_38._8.rail, root->_38._30.progress);
    return true;
}

void DragonRootBase::sub_7100356CFC() {
    m36();
    if (_38._8.rail && _38._8.rail->isBezier())
        sub_7100356D48();
    else
        sub_7100356F30();
}

void DragonRootBase::leave_() {
    ksys::act::ai::Ai::leave_();
}

void DragonRootBase::loadParams_() {}

bool DragonRootBase::sub_7100357414(f32 progress) {
    if (!_38._8.rail)
        return false;
    _38.sub_7100EEBAE0(_38._8.rail, progress);
    return true;
}

ksys::map::Rail* DragonRootBase::m35() {
    return sub_7100EEF264(mActor, 0);
}

bool DragonRootBase::sub_710035797C(f32* out_progress, sead::Vector3f* out_pos,
                                    const sead::Vector3f& pos) {
    auto* rail = _38._8.rail;
    if (!rail)
        return false;
    const f32 progress = sub_7100EEF7AC(rail, pos, false, 0.2f, -0.0f);
    if (out_progress)
        *out_progress = progress;
    if (out_pos)
        rail->calcTranslate(out_pos, progress);
    return true;
}

void DragonRootBase::m37() {
    if (_38.sub_7100EEBB74()) {
        m36();
        if (_38._8.rail && _38._8.rail->isBezier())
            sub_7100356D48();
        else
            sub_7100356F30();
    } else {
        sub_7100357A5C();
    }
}

void DragonRootBase::m38() {
    sub_7100357440(sub_7100EEF078(_38._8.rail, _38._30.progress));
}

bool DragonRootBase::m39() {
    return false;
}

}  // namespace uking::ai
