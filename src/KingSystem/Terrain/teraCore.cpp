#include "KingSystem/Terrain/teraSystem.h"
#include <gsys/gsysModel.h>
#include "Game/gameUnkRttiPlaceholders.h"

namespace ksys::tera {

ExtraInfoLayerMaybe* ExtraInfoMaybe::createLayer(s32 name_id, f32 ratio, f32 scale_min,
                                                 f32 scale_max) {
    const s32 index = layers.size();
    ExtraInfoLayerMaybe* layer = layers.emplaceBack();
    const ExtraInfoNamePoolMaybe* pool = Terrain::instance()->_370->_4ae8;
    if (u32(name_id) < pool->count) {
        const char* name = pool->names[name_id].name.cstr();
        layer->name_id = name_id;
        layer->name = name;
    } else {
        layer->name_id = -1;
        layer->name = sead::SafeString::cEmptyString;
    }
    layers[index]->ratio = ratio;
    layers[index]->scale_min = scale_min;
    layers[index]->range = scale_max - scale_min;
    layers[index]->_24 = 0;
    return layer;
}

ExtraInfoLayerMaybe* ExtraInfoMaybe::addLayer(f32 ratio, f32 scale_min, f32 scale_max,
                                              const sead::SafeString& name) {
    s32 name_id = -1;
    if (Terrain::instance()->_370->_4ae8->count != 0) {
        for (u32 i = 0; i < Terrain::instance()->_370->_4ae8->count; ++i) {
            const sead::SafeString entry_name =
                Terrain::instance()->_370->_4ae8->names[s32(i)].name.cstr();
            if (name == entry_name) {
                name_id = i;
                break;
            }
        }
    }
    return createLayer(name_id, ratio, scale_min, scale_max);
}

s32 ExtraInfoMaybe::findLayerIndex(const ExtraInfoLayerMaybe* layer) const {
    s32 index = -1;
    for (u32 i = 0; i < u32(layers.size()); ++i) {
        if (layers.at(i) == layer) {
            index = i;
            break;
        }
    }
    return index;
}

void Core::sub_710130085C() {
    if (_37c & 1)
        _f8->requestUpdate(6);
    _360.exchange(0);
}

// NON_MATCHING: the compiler moves the flag load across the relaxed atomic exchange.
void Core::sub_710130089C() {
    if (_37c & 1)
        _f8->requestDraw();
    _360.exchange(0);
    _37c |= 4;
}

void Core::sub_7101300B4C(u32 index, const sead::Vector3f* position, bool update) {
    if (_37c & 2) {
        sub_7101300BF0();
        _37c &= ~2;
    }
    mPositions[index].mPosition = *position;
    if (update)
        sub_7101300D50(index, true, true);
}

void Core::sub_71013010D4(const Unk_71013010d4& state, s32 index) {
    mStates[index] = state;
    _37c |= 2;
}

}  // namespace ksys::tera

// NON_MATCHING: placeholder destructor; the original (0x71012ff93c) also destroys members or bases
// this class does not declare yet.
Unk_710251f878::~Unk_710251f878() = default;

namespace ksys::tera {

void Core::sub_7101301068(bool update) {
    for (auto& system : mSystems)
        system.sub_7101115158(update);
}

void Core::releaseAllNodeGroups() {
    for (auto& system : mSystems)
        system.sub_7101117874();
}

}  // namespace ksys::tera
