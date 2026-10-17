#include <gsys/gsysResourceEditor.h>

namespace gsys {

ResourceEditor* ResourceEditor::sInstance = nullptr;

void ResourceEditor::sub_7100C5D3E0(ModelScene* scene, bool) {
    if (mScene != scene)
        mScene = scene;
}

}  // namespace gsys
