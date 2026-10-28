#pragma once

namespace gsys {

class Model;

// Releases a light rig created for a Model. Only the release path that ModelSceneGI::free
// 0x7100c33a70 / 0x7100c33c04 / 0x7100c33d8c calls is modelled.
template <typename T>
class LightResMgr {
public:
    // 0x7100c33a80 / 0x7100c33c14 / 0x7100c33d9c
    void free(T* rig, Model* model, int index);
};

}  // namespace gsys
