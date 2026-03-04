# Phase 1: RHI

For this phase, i use the immediate modes of OpenGL for the different projects

TODOs:

- Support all atributte types
- There are some type unconsistancing with std::string and char*, fix this!
- Buffer class on render side
- Texture release
- Mesh release
- Shader release
- ✅Load shader from file

    I use some old code to load the shaders (probably from Hazel or learnopengl.com). This should be change for now it is good enough.

- ✅ Pipeline state object (move to next phase)
- ✅ state caching and lazy update (move to next phase)
- glEnable on init device
- GPU Resource Views
- Descriptors