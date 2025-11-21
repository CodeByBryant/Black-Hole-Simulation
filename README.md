<div align="center">

# Black Hole Simulation

Watch objects orbit, collide, and get sucked into a black hole—all in real-time 3D with interactive controls.

[![Made with C++](https://img.shields.io/badge/Made%20with-C%2B%2B-blue?style=for-the-badge&logo=cplusplus)](https://cplusplus.com/)
[![OpenGL](https://img.shields.io/badge/OpenGL-3.3-darkgreen?style=for-the-badge&logo=khronos)](https://www.khronos.org/opengl/)
[![License](https://img.shields.io/github/license/CodeByBryant/Portfolio?style=for-the-badge)](LICENSE)

![Status](https://img.shields.io/badge/Status-Live-success?style=flat-square)
![Build](https://img.shields.io/badge/Build-Passing-success?style=flat-square)
![Maintained](https://img.shields.io/badge/Maintained-Yes-success?style=flat-square)

</div>

---

## Quick Start

Simply run:
```bash
./run.sh
```

The script will build everything and launch the simulation automatically.

## How to Use It

**Camera:**
- Click and drag the left mouse button to rotate your view
- Right click and drag to move the camera around
- Scroll to zoom in and out
- Press ESC to quit

**Add Objects:**
- Use the on-screen menu to create objects with custom:
  - Position and velocity (where it starts and how fast it moves)
  - Mass (affects gravity)
  - Size and color
  - Optional glow effect

**Simulation Controls:**
- Pause/resume the simulation
- Speed it up or slow it down (0.1x to 5.0x)
- Clear all objects and start fresh

## What's Inside

```
├── src/           # The actual code
├── shaders/       # Graphics effects
├── imgui/         # User interface library
├── include/       # Header files
└── CMakeLists.txt # Build configuration
```

## How It Works

The simulation uses real Newtonian gravity to calculate how objects move. Objects orbit the black hole, and if they get too close to the event horizon (the point of no return), they disappear. Everything is rendered with OpenGL for smooth, real-time animation.

## What It Doesn't Do (Yet)

- It's using simplified physics, not full Einstein's General Relativity
- Only non-rotating black holes are supported
- Can't save or load simulations
- No collisions between objects (they pass through each other)

## Want to Help?

Found a bug or have an idea? Pull requests and issues are welcome!

## License

MIT License - see [LICENSE](LICENSE) for details.
