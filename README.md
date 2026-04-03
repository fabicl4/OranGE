# 🍊 OranGE

**OranGE** is a custom game engine being developed as a learning project and a practical exercise in modern C++ and real-time rendering. The engine follows a **data‑oriented design** philosophy and a **layered architecture** to keep the core modular, efficient, and portable.

> ⚠️ **Alpha Stage** – The engine is under active development. APIs are subject to change, and many features are still incomplete.

Feel free to copy or modify my code! :)

---

## 🏗️ Architecture Overview

The engine is divided into several independent modules:

| Module        | Responsibility                                      |
|---------------|-----------------------------------------------------|
| **Core**      | Event interface, type definitions, logging, service locator |
| **Platform**  | Window management (GLFW), Vulkan context, OS specific code |
| **Resources** | Asset loading and management (planned)              |
| **Render**    | RHI, shader compilation, pipeline state objects     |
| **Scene**     | ECS, `Scene` & `SceneManager`, `GameObject`  |
| **Application** | Main loop, layer stacking, initialization/shutdown |

Dependencies flow inward: all modules depend on `Core`, but not vice‑versa.

---

## Technologies

- **Language** – C++20
- **Build system** – CMake (3.20+)
- **Windowing** – [GLFW](https://github.com/glfw/glfw)
- **Graphics** – Vulkan / GLAD (OpenGL)
- **UI** – ImGui (for debugging / editor)
- **ECS** – EnTT
- **Audio** – OpenAL
- **Math** – GLM](https://github.com/g-truc/glm)
- **Logging** – [spdlog](https://github.com/gabime/spdlog)
- [stb](https://github.com/nothings/stb)

---

## Structure

```text
/OranGE
├── OranGE/                     # Engine library header/source files
├── sandbox/                    # Test application
│   └── src/
├── editor/                     # Editor application (future)
├── external/                   # Third-party libraries
├── assets/                     # Shaders, textures, models
├── docs/                       # Architecture notes
├── scripts/                    # Build helpers
└── CMakeLists.txt
```

---

## Repository

- _main_

    Last stable version

- _feature/xxx_

    Implementation of the feature _xxx_

- _development/xxx_

    Current development branch

---

## Contributing
This is primarily a personal learning project, but suggestions and discussions are welcome. Feel free to open an issue to propose ideas or report bugs.

---

## License
Distributed under the MIT License. See LICENSE for more information.

---

## Resources

### Books

- _Game Engine Architecture_ (Jason Gregory)
- _Real-Time Rendering_ (Akenine-Möller)

### Technical Resources

- Godot Engine
- [bdfx](https://github.com/bkaradzic/bgfx)
