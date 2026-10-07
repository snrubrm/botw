#include <g3d/aglNW4FToNN.h>
#include <nn/g3d/ResFile.h>

namespace ksys::res {

nn::g3d::ResFile* sub_7100FDDB40(void* data) {
    auto* file = nn::g3d::ResFile::ResCast(data);
    if (file)
        agl::g3d::ResFile::getResTextureFile(file);
    return file;
}

}  // namespace ksys::res
