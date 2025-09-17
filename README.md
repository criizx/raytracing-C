# Raytracing Visualization

A real-time 2D ray casting visualization built with SDL2 that demonstrates light ray propagation and shadow casting.

## Description

This application creates an interactive visualization where rays are cast from a light source (controllable circle) and interact with obstacles to create realistic shadow effects. The program uses mathematical ray-circle intersection algorithms to compute accurate light behavior.

## Features

- **Real-time Raytracing**: 100 rays cast simultaneously from a light source
- **Interactive Light Source**: Mouse-controlled light positioning
- **Shadow Casting**: Realistic shadows created by circular obstacles
- **Smooth Rendering**: Uses Bresenham's line algorithm for efficient ray drawing
- **Mathematical Precision**: Accurate ray-geometry intersection calculations

## Technologies

- **SDL2**: Graphics rendering and event handling
- **C**: Core implementation language
- **Mathematical Libraries**: `math.h` for trigonometric calculations

## Architecture

The project is structured as a modular C application:

### Core Components

- **Ray Casting Engine**: `limits_to_ray.c/h` - Handles ray-geometry intersections
- **Line Drawing**: `line_drawing_alg.c/h` - Implements Bresenham's algorithm
- **Data Structures**: `structs.h` - Defines Ray and Circle structures
- **Main Loop**: `main.c` - SDL2 event loop and rendering

### Key Algorithms

- **Ray-Circle Intersection**: Quadratic equation solving for precise collision detection
- **Ray-Screen Boundary**: Parametric line intersection with screen edges
- **Bresenham's Line Algorithm**: Efficient pixel-perfect line rasterization

## Build

### Requirements

- **SDL2**: Graphics library
- **GCC**: C compiler with math library support
- **Make**: Build system (optional)

### Compilation

```bash
gcc -o raytracing main.c limits_to_ray.c line_drawing_alg.c -lSDL2 -lm
```

## Usage

1. **Run the application**:
   ```bash
   ./raytracing
   ```

2. **Controls**:
   - **Mouse Movement**: Move the light source (white circle)
   - **Mouse Click + Drag**: Continuous light source positioning
   - **Close Window**: Exit application

3. **Visualization**:
   - White circle: Light source (follows mouse)
   - White rays: Light beams cast from source
   - Large white circle: Obstacle casting shadows
   - Black areas: Shadow regions

## Configuration

Key parameters in `main.c`:

```c
#define RAYS_NUMBER 100    // Number of rays cast
#define WIDTH 1500         // Screen width
#define HEIGHT 600         // Screen height
```

## Mathematical Foundation

The raytracing uses parametric ray equations:
- Ray: `P(t) = Origin + t * Direction`
- Circle intersection via discriminant: `B² - 4AC`
- Screen boundary intersection with parameter bounds checking
