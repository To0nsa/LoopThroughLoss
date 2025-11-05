# 🎮 LoopThroughLoss

[View on Itch.io](https://to0nsa.itch.io/loopthroughloss)

**LoopThroughLoss** is a first-person narrative game exploring the emotional journey through grief, developed during a game jam organized by students at Hive Helsinki. The theme of the jam was **"Time Loop"**.

This short psychological experience takes you through looping inner thoughts, representing the five stages of grief:  
**Denial**, **Anger**, **Bargaining**, **Depression**, and **Acceptance**.

---

## 🎬 Gameplay video

[![LoopThroughLoss](https://img.youtube.com/vi/GJaF5zaGVMs/0.jpg)](https://www.youtube.com/watch?v=GJaF5zaGVMs)

Click the image above to watch a the full playthrough of the game on Youtube!

---

## 🛠️ Project Overview

The game reuses the raycasting engine from my [Cub3D](https://github.com/To0nsa/cub3d), adapted to work with the powerful [Raylib](https://www.raylib.com) graphics library.  
While the rendering was based on existing techniques, the team focused their efforts on:

- Game logic and mechanics  
- Atmosphere and emotional storytelling  
- Custom textures and sound design

---

## 🚀 Installation Guide

### 🪟 Windows

**1.** Download the game from [the Itch.io page](https://to0nsa.itch.io/loopthroughloss)
**2.** Unzip the folder
**3.** Open a terminal and navigate to the game folder:

```bash
cd path/to/LoopThroughLoss
LoopThroughLoss maps/LoopThroughLoss.cub
```

**4.** ⚠️ Ensure the assets/, maps/, and .exe file remain in the same directory

### 🍎 macOS & 🐧 Linux

**1.** Open a terminal.
**2.** Clone the repository with submodules:

```bash
git clone --recurse-submodules https://github.com/To0nsa/LoopThroughLoss.git
cd LoopThroughLoss
```

**3.** Build and run:

```bash
make check-deps   # Verify required packages are installed
make setup        # Install system dependencies (if needed)
make              # Build the executable
./LoopThroughLoss maps/LoopThroughLoss.cub
```

**4.** Optional cleanup:

```bash
make clean        # Remove object files and dependencies
make fclean       # Clean everything including the binary
make re           # Full rebuild from scratch
```

---

## 🌐 Web Build

Build the game for the browser using Emscripten + CMake. The repository ships with a `CMakeLists.txt` that supports both native and Web builds.

1) Install Emscripten (emsdk):

```bash
git clone https://github.com/emscripten-core/emsdk.git
cd emsdk
./emsdk install latest
./emsdk activate latest
source ./emsdk_env.sh
```

2) Configure the Web build with CMake via `emcmake`:

```bash
cd /path/to/LoopThroughLoss
emcmake cmake -S . -B build-web -DCMAKE_BUILD_TYPE=Release
```

3) Build:

```bash
cmake --build build-web -j
```

This produces `build-web/index.html` (plus `.js`, `.wasm`, and `.data` files). Assets in `assets/` and maps in `maps/` are preloaded automatically.

4) Test locally (optional):

```bash
emrun build-web/index.html
```

Or use Python's HTTP server:

```bash
python3 -m http.server -d build-web 8000
```

Then open `http://localhost:8000` in your browser.

---

## 📜 License

This project is licensed under the MIT License.
You're free to use, modify, and distribute this code for academic, personal, or professional purposes.
Attribution is appreciated but not required.

---

## 👥 Team & Contact

**Developper:**

- [github.com/to0nsa](https://github.com/to0nsa)

**Graphic designers:**

- [github.com/Emihaa](https://github.com/Emihaa)
- [github.com/a-havu](https://github.com/a-havu)

**Sound designer:**

- [github.com/aapadill](https://github.com/aapadill)

**Feedback or questions?**
Feel free to reach out via email: nicolas.lovis@hotmail.fr
Or open an issue / leave a comment on the GitHub repository.
