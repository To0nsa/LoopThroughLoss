# 🎮 LoopThroughLoss

[View on Itch.io](https://to0nsa.itch.io/loopthroughloss)

**LoopThroughLoss** is a first-person narrative game exploring the emotional journey through grief, developed during a game jam organized by students at Hive Helsinki. The theme of the jam was **"Time Loop"**.

This short psychological experience takes you through looping inner thoughts, representing the five stages of grief:  
**Denial**, **Anger**, **Bargaining**, **Depression**, and **Acceptance**.

---

## 🎬 Gameplay

[![LoopThroughLoss](https://img.youtube.com/vi/3mGU6aDea5c/0.jpg)](https://www.youtube.com/watch?v=3mGU6aDea5c)&#8203;

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
