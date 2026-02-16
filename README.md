# 🍊 OranGE

## Table of Contents

- [Description](#description)
- [Architecture Overview](#architecture-overview)
- [Libraries](#libraries)
- [Build and Installation](#build-and-installation)
- [Structure](#structure)
- [Repository](#repository)
- [Roadmap](#roadmap)
- [Future Integration](#future-integration)  
- [Future Work](#future-work)
- [Projects Using OranGE](projects-using-oranGE)
- [Resources](#resources)

## Description
<!-- Description -->

OranGE is a learning-focused game engine project designed for experimentation and modification. Built incrementally from the ground up, it prioritizes clean architecture and educational value over production readiness.

The goals are:

The project goals are:

**Architecture**

- Render Hardware Interface (RHI) for API abstraction
- Data-oriented design principles
- Modular component-based architecture

**Rendering**

- Minimized OpenGL state changes through caching
- Render Command architecture with sorting/batching
- Frame Graph for render pass management

**Learning**

- Understand game engine architecture patterns
- Implement industry techniques (PBR, GPU-driven rendering)
- Build tooling for shader development and debugging

Feel free to copy or modify my code! :)

## Architecture Overview

### Core Components

#### Application

Owns and manages subsystem lifetime: Window, Renderer (Front/Back), ResourceManager, and Scene.

#### Render Front (High-Level)

- Builds the frame by collecting RenderCommands from subsystems
- Sorts and batches commands by state (material, shader, texture)
- Manages frame data and render passes
- API-agnostic

```text
SpriteRenderer → Push RenderCommand
RendererSystem → Sort/Batch
Backend → Execute Commands
```

#### Render Back (Low-Level)

- Owns GPU resources (buffers, textures, shaders)
- Manages the OpenGL state machine
- Executes sorted command streams
- Implements state caching and lazy updates
- OpenGL-specific (but designed for future backends)

#### 3. **Resources**

```text
Subsystem → Handle → ResourceManager → Backend → OpenGL
```

Resource Manager:

- CPU-side metadata ownership
- Stable handles (not raw OpenGL IDs)
- Asynchronous loading pipeline

### Frame Flow

```text
Application
    ↓
RendererSystem.BeginFrame()
    ↓
Subsystem.Submit()
    ↓
RendererSystem.BuildRenderQueue()
    ↓
RendererBackend.Execute()
    ↓
RendererSystem.EndFrame()
```

**Advantages of this approach:**

- Centralized execution enables automatic batching
- Sorting by state minimizes driver overhead
- Command generation can be multithreaded
- Backend becomes a pure executor, simplifying debugging

## Libraries

### Core Libraries

| Library | Purpose | Integration |
|---------|---------|-------------|
| GLAD | OpenGL function loading | Core profile 4.1 |
| GLFW | Window creation and input | Single window, event loop |
| GLM | Mathematics | Header-only, wrapped in engine math layer |
| stb | Image loading | stb_image for textures |
| spdlog | Logging | Compiled into engine |

**Links:**

- [GLFW](https://github.com/glfw/glfw)
- [stb](https://github.com/nothings/stb)
- [GLM](https://github.com/g-truc/glm)
- [spdlog](https://github.com/gabime/spdlog)

## Build and Installation

```console
$ git clone OranGE
$ cd OranGE && mkdir build && cd build
$ cmake .. && cmake --build .
```

## Structure

```text
/OranGE
├── engine/                    # Engine library source
│   ├── core/                  # Application, logging, time, events
│   ├── platform/              # Window, input (GLFW wrapper)
│   ├── render/                # Render Front, Back, RHI
│   │   ├── front/             # Command generation, sorting
│   │   ├── backends/          # OpenGL implementation
│   │   └── resources/         # Textures, buffers, shaders
│   ├── scene/                 # ECS, transforms, cameras
│   └── tools/                 # Debug visualizers
├── sandbox/                    # Test application
│   └── src/
├── editor/                     # Editor application (future)
├── external/                   # Third-party libraries
├── assets/                     # Shaders, textures, models
├── docs/                       # Architecture notes
├── scripts/                    # Build helpers
└── CMakeLists.txt
```

## Repository

- _main_

    Last stable version

- _feature/xxx_

    Implementation of the feature _xxx_

- _development/xxx_

    Current development branch

## Roadmap

### Phase 0: Foundation
<!-- Description -->

*Core infrastructure before any rendering*

<!-- List of Features -->
- [x] Engine as static library
- [x] Set up GitHub repo (what you are seeing :))
- [x] Logging system
- [x] Window system (GLFW abstraction)
- [x] Event system (input, window events) (Basic implementation, need more work)
- [x] Time system (delta time, timers)
- [x] Main loop
- [x] Application class with subsystem lifecycle

### Phase 1: Render Hardware Interface

*Abstract OpenGL behind a clean API*

- [ ] Renderer Front & Back separation
- [ ] Buffer abstraction with vertex layouts
- [ ] Texture abstraction (stb_image integration)
- [ ] Shader system with file loading
- [ ] Pipeline State Object (encapsulates OpenGL state)
- [ ] State caching and lazy updates
- [ ] Resource handles (not raw OpenGL IDs)
- [ ] Resource Descriptors
- [ ] Resource Views (Texture, buffers)
- [ ] Buffer Management

### Phase 2: Command-Based Rendering

- [ ] RenderCommand type hierarchy
- [ ] CommandStream/CommandBuffer
- [ ] Sort by material/shader/texture
- [ ] Batch rendering for sprites/meshes
- [ ] Multithreaded command generation (future)

### Phase 3: Resource Management

*Efficient asset handling*

- [ ] Structure **Mesh Data**
- [ ] Resources Lifetime
- [ ] Texture and mesh loaders
- [ ] Material system
- [ ] Serialization for assets
- [ ] Hot reloading for shaders

### Phase 4: Render Pass

*Structured frame rendering*

- [ ] RenderPass abstraction
- [ ] Forward rendering
- [ ] Deferred rendering (G-Buffer + lighting)
- [ ] Shadow mapping
- [ ] Frame Graph for pass dependencies

### Phase 5: Scene

*Handle complex scenes*

- [ ] Camera system (multiple views)
- [ ] Transform hierarchy
- [ ] Static geometry batching
- [ ] Instanced rendering
- [ ] Frustum culling
- [ ] Static geometry batching

### Phase 6: Post-Processing and Effects

*Visual polish*

- [ ] Post-processing pipeline
- [ ] Bloom
- [ ] FXAA/TAA
- [ ] Particle system (CPU/GPU)
- [ ] Compute shaders

### Phase 7: Optimization

- [ ] ECS integration (EnTT)
- [ ] Static/Dynamic Geometry
- [ ] Multi-thread
- [ ] Staging Buffers
- [ ] Persistant Buffer

### Phase 8: Tooling

*Developer experience*

- [ ] ImGUI integration
- [ ] Material editor
- [ ] Shader inspector/profiler
- [ ] G-buffer visualizer
- [ ] Performance overlay

### Phase 9: Advanced Techniques

*Portfolio-ready features*

- [ ] PBR materials
- [ ] GPU-driven rendering
- [ ] Screen Space Reflections
- [ ] Volumetric lighting
- [ ] Temporal Anti-Aliasing

## Future Integration

**Physics**

- Box2D (2D physics)

**Filesystem**

- PhysFS (file system abstraction)

**Audio**

- OpenAL (3D audio)

**Scripting**

- Lua (runtime behavior)

**Tools & Debugging**

- Tracy Profiler (performance analysis)
- Unity Test Framework (unit tests)
- Assimp

**Rendering**

- Transition to Vulkan backend
- AZDO patterns
- Texture streaming

## Future Work

- Engine divided on layers (based on [Hazel Engine](https://github.com/TheCherno/Hazel)).
- TileMap
- GPU Rendering (Compute Shaders)
- PBR
- Shadow mapping Tecniques (CSM, VSM, ESM)
- Particle System (CPU and GPU)
- TAA (Temporal Anti-Aliasing)
- Compute Shaders

    Simulation (partículas, culling) and  post-processing (blur, downsampling)

- Screen Space Reflections (SSR)
- Parallax Occlusion Mapping
- Volumetric Lighting (God Rays)

## Projects Using OranGE

**Sandbox**

- Test harness for engine features
- Rapid prototyping of rendering techniques
- Located in `/sandbox`

**Editor** (planned)

- ImGUI-based level editor
- Asset preview and material editing
- Located in `/editor`

**Runtime** (future)

- Standalone game player
- Minimal overhead, release build

## Resources

### Books

- _Game Engine Architecture_ (Jason Gregory)
- _Real-Time Rendering_ (Akenine-Möller)

### Technical Resources

- Godot Engine
- [bdfx](https://github.com/bkaradzic/bgfx)
