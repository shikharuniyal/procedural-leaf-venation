# Procedural Leaf Venation

A real-time procedural leaf venation simulation using the Space Colonization Algorithm, built with Raylib in C++.

## Demo


https://github.com/user-attachments/assets/45e98495-34e9-4317-9cc6-8e424d85bc48#t=0.001

## How It Works

This project simulates organic leaf vein growth using a biologically-inspired algorithm called **Space Colonization**. The algorithm mimics how auxins (plant growth hormones) guide vein development in real leaves.

### Core Algorithm

1. **Initialization**
   - Start with a single vein node at the bottom-center of the screen (representing the petiole/leaf stem)
   - Scatter 700 auxin points randomly across the canvas

2. **Growth Iteration** (Press and hold `T`)
   - **For each auxin**: Find its closest vein node
   - **For each vein node**: Accumulate normalized direction vectors from all auxins that chose it
   - **Generate new veins**: Each active vein node grows in its accumulated direction
   - **Proximity check**: Remove auxins that are within 2×PROXIMITY distance of any vein (they've been "consumed")

3. **Visualization**
   - **Blue circles**: Vein nodes with red proximity rings
   - **Green circles**: Auxin points with purple proximity rings  
   - **Orange outline**: Convex hull showing the leaf boundary
   - **Growth vectors**: White lines (optional) showing growth directions

### Key Parameters

```cpp
#define AUXIN_RATE 700      // Number of auxin points
#define PROXIMITY 10        // Kill distance for auxins
#define VEIN_RAD 2         // Visual radius of vein nodes
```

## What Makes This Different from Tsoding's Implementation

While both projects implement leaf venation, this implementation has several unique features:

### 1. **Graphics Framework: Raylib vs Custom**
- **This project**: Uses [Raylib](https://www.raylib.com/), a modern game development library with hardware acceleration
- **Tsoding's**: Typically uses SDL or custom terminal-based rendering
- **Advantage**: Smoother rendering, easier vector math with `raymath.h`, cross-platform support

### 2. **Convex Hull Visualization**
- **This project**: Implements Andrew's Monotone Chain algorithm to compute and display the convex hull in real-time
- **Tsoding's**: Focuses on the vein network itself without boundary visualization
- **Implementation**:
  ```cpp
  std::vector<Vector2> convexHull(std::vector<Vector2> pts) {
      // Andrew's monotone chain algorithm
      // Builds lower hull, then upper hull
      // Returns the boundary polygon
  }
  ```

### 3. **Interactive Controls**
- **This project**:
  - `T` (hold): Step-by-step growth animation
  - `W`: Refresh/regenerate all auxin points
  - `Space`: Manually remove individual auxins
  - Real-time visualization of proximity rings
- **Tsoding's**: Typically runs continuously without interactive manipulation

### 4. **Data Structure Approach**
- **This project**: Uses separate vectors for direction mapping (`CVmap`) and closest vein tracking (`closest_vein`)
  ```cpp
  std::vector<Vector2> CVmap;          // Direction accumulator per vein
  std::vector<Vector2> closest_vein;    // Closest vein per auxin
  ```
- **Benefit**: Clearer separation of concerns, easier to debug

### 5. **Proximity System**
- **This project**: Dual proximity rings (visual red ring around veins, purple around auxins) showing influence zones
- Uses `2×PROXIMITY` for actual removal distance
- Backwards iteration when removing to avoid index shifting bugs:
  ```cpp
  for(int i = auxins.size(); i-- > 0;) {
      // Safe removal during iteration
  }
  ```

## Building and Running

### Prerequisites

- C++ compiler (g++, clang, or MSVC)
- Raylib library installed
- CMake (optional) or Make

### Compilation

#### Linux/macOS
```bash
g++ main.cpp -o lf -lraylib -lm -lpthread -ldl
./lf
```

#### Windows (MinGW)
```bash
g++ main.cpp -o lf.exe -lraylib -lgdi32 -lwinmm
.\lf.exe
```

#### Using CMake
```bash
cmake -B build
cmake --build build
./build/lf
```

## Controls

| Key | Action |
|-----|--------|
| `T` (hold) | Grow veins toward auxins (step-by-step) |
| `W` | Regenerate all auxin points |
| `Space` | Remove individual auxins manually |
| `ESC` | Exit application |

## Technical Details

### Algorithm Complexity
- **Per frame** (when growing):
  - Finding closest veins: O(n × m) where n = auxins, m = veins
  - Convex hull: O(v log v) where v = number of vein nodes
  - Proximity check: O(n × m)

### Memory Layout
- Contiguous vectors for cache efficiency
- Pre-allocated `CVmap` and `closest_vein` arrays to avoid reallocations
- Dynamic resizing only when adding new veins

### Rendering Pipeline
1. Clear background (black)
2. Process input and update simulation state
3. Draw proximity rings (rings drawn first, occluded by circles)
4. Draw circles (veins and auxins layered)
5. Draw convex hull outline
6. Present frame

## Implementation Highlights

### Vectorized Growth Direction
Instead of growing veins directly toward single auxins, the algorithm accumulates influences from all auxins that select a vein, then normalizes:

```cpp
// Accumulate influences
CVmap[cvein_idx] = Vector2Add(CVmap[cvein_idx], Vector2Subtract(a, veins[cvein_idx]));

// Normalize before growing
if(Vector2Length(CVmap[k]) > 0.0f)
    CVmap[k] = Vector2Normalize(CVmap[k]);
```

This creates more organic, branching patterns rather than direct point-to-point connections.

### Efficient Auxin Removal
Uses backwards iteration to safely remove elements during traversal:
```cpp
for(int i = auxins.size(); i-- > 0;) {
    if(should_remove(i)) {
        auxins.erase(auxins.begin() + i);
    }
}
```

## Future Enhancements

- [ ] Add vein connectivity tracking (parent-child relationships)
- [ ] Export vein network as SVG or mesh
- [ ] Color gradient based on vein depth/hierarchy
- [ ] Adjustable parameters via GUI sliders
- [ ] Different growth patterns (pinnate, palmate, parallel)
- [ ] Texture generation for 3D leaf models

## References

- [Space Colonization Algorithm - Algorithmic Botany](http://algorithmicbotany.org/papers/colonization.egwnp2007.html)
- [Raylib Documentation](https://www.raylib.com/)
- [Tsoding's Leaf Venation](https://github.com/tsoding/leaf-venation) - Original inspiration

## License

This project builds upon concepts from procedural generation and algorithmic botany. Feel free to use and modify for your own projects.

---

**Note**: This implementation was created as a learning exercise in procedural generation, computational geometry, and real-time graphics programming with Raylib.
