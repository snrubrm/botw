#include "Game/Actor/actUnk_710244eb00.h"
#include <basis/seadNew.h>
#include <gsys/gsysModel.h>
#include <gsys/gsysModelUnit.h>
#include "KingSystem/ActorSystem/Awareness/actAITerror.h"
#include "KingSystem/ActorSystem/actGlobalParameter.h"
#include "KingSystem/ActorSystem/actActor.h"
#include "KingSystem/Resource/GeneralParamList/resGParamListObjectGlobal.h"

namespace uking::act {

Unk_710244eb00::Unk_710244eb00() = default;

Unk_710244eb00::~Unk_710244eb00() {
    clear();
}

void Unk_710244eb00::clear() {
    if (_8)
        _8 = nullptr;
    if (_10) {
        _10->sub_7100D786EC();
        delete _10;
        _10 = nullptr;
    }
}

bool Unk_710244eb00::m5() {
    return _10 && _10->sub_7100D786D8();
}

bool Unk_710244eb00::init(sead::Heap* heap, ksys::act::Actor* actor) {
    if (!actor)
        return false;
    _10 = new (heap, 8) ksys::act::AITerror(actor);
    if (!_10 || !_10->sub_7100D78564(heap))
        return false;
    _8 = actor;
    m3();
    return true;
}

void Unk_710244eb00::sub_71006E24B0(const sead::Vector3f& offset) {
    if (_10)
        _10->_94 = offset;
}

void Unk_710244eb00::sub_71006E2420() {
    auto* owner = _8->get548();
    if (owner && _10)
        owner->sub_7100D78444(_10);
}

f32 Unk_710244eb00::sub_71006E24D4() {
    // fstr 0x7101da24a8: IEEE float 0x3727c5ac.
    return _10 ? _10->sub_7100D78800() : 0.00001f;
}

// NON_MATCHING: the literal entry index is stored before loading the parameter value.
void Unk_710244eb00::sub_71006E2024() {
    if (_10 && ksys::act::GlobalParameter::instance()) {
        const auto* param = ksys::act::GlobalParameter::instance()->getGlobalParam();
        if (param)
            _10->x(2, 0x10, param->mSpeedTerrorLevel.ref());
    }
}

// NON_MATCHING: the literal entry index is stored before loading the parameter value.
void Unk_710244eb00::sub_71006E1FD0() {
    if (_10 && ksys::act::GlobalParameter::instance()) {
        const auto* param = ksys::act::GlobalParameter::instance()->getGlobalParam();
        if (param)
            _10->x(2, 0x10, param->mSpeedTerrorLevelHuge.ref());
    }
}

// NON_MATCHING: inline terror-level updates schedule their small enum temporaries before the tuning loads.
void Unk_710244eb00::m3() {
    if (!_10)
        return;
    _18 = 0;
    const auto* global = ksys::act::GlobalParameter::instance();
    const auto* param = global ? global->getGlobalParam() : nullptr;
    f32 radius = 1.0f;
    if (auto* model = _8->getModel()) {
        if (auto* unit = model->getUnits().unsafeAt(0)->mModelUnit)
            radius = _8->getScale().x * unit->getBoundSphere()->getRadius();
    }
    if (param) {
        // 2026-10-07: original b.ge selects the huge level; an unordered radius takes the small branch.
        if (radius >= param->mSpeedTerrorLevelCheckRadius.ref())
            sub_71006E1FD0();
        else
            sub_71006E2024();
    }
    _10->setRadius(radius + (param ? param->mTerrorRadiusOffset.ref() : 0.0f));
    _10->_b0.set(1);
}

void Unk_710244eb00::sub_71006E2440(bool value) {
    if (!_10)
        return;
    const auto* global = ksys::act::GlobalParameter::instance();
    const auto* param = global ? global->getGlobalParam() : nullptr;
    f32 radius = 1.0f;
    if (auto* model = _8->getModel()) {
        if (auto* unit = model->getUnits().unsafeAt(0)->mModelUnit)
            radius = _8->getScale().x * unit->getBoundSphere()->getRadius();
    }
    _10->setRadius(radius + (param && value ? param->mTerrorRadiusOffset.ref() : 0.0f));
}

}  // namespace uking::act
