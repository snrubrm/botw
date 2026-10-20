#include <gsys/gsysResourceEditor.h>

namespace gsys {

SEAD_SINGLETON_DISPOSER_IMPL(ResourceEditor)

ResourceEditor::CreateArg::CreateArg() = default;

ResourceEditor::ResourceEditor() {
    _1c58[0] = "0:off";
    _1c58[1] = "1:on";
}

ResourceEditor::~ResourceEditor() = default;

void ResourceEditor::sub_7100C5D3E0(ModelScene* scene, bool) {
    if (mScene != scene)
        mScene = scene;
}

void ResourceEditor::cleanup() {
    mScene = nullptr;
}

void ResourceEditor::draw(agl::DrawContext*, const sead::FrameBuffer&, const sead::Viewport&, bool,
                          bool) {}

void ResourceEditor::destroyEditor() {}

void ResourceEditor::setCallback(IResourceEditorCallback* callback) {
    mCallback = callback;
}

}  // namespace gsys
