<h1 align="center">FdF — Fil de Fer</h1>

<p align="center">
  <img src="https://img.shields.io/badge/language-C-blue.svg" alt="Language">
  <img src="https://img.shields.io/badge/42-School-black.svg" alt="42 School">
  <img src="https://img.shields.io/badge/status-complete-brightgreen.svg" alt="Status">
</p>

<p align="center">
  A 3D wireframe renderer that reads map files and displays isometric terrain projections using a custom graphics library.
</p>

<p align="center">
  <a href="README.pt-br.md">🇧🇷 Leia em Português</a>
</p>

---

## Why this project matters

> "This project taught me the fundamentals of computer graphics — how 3D coordinates are projected onto a 2D screen using linear algebra, how pixels are drawn one by one with correct clipping, and how a real-time render loop is structured. These are the foundations behind every game engine, data visualization tool, and 3D modeling software."

The Bresenham line algorithm, isometric projection, and event-driven rendering are concepts you'll encounter in game development, geospatial visualization, and scientific graphics.

---

## Preview

> *A terrain map rendered as an isometric wireframe*

The renderer reads `.fdf` map files like this:

```
0  0  0  0  0
0  1  2  1  0
0  2  4  2  0
0  1  2  1  0
0  0  0  0  0
```

And produces an interactive 3D wireframe projection with colored altitude levels.

---

## What was built

- **Map parser** — reads `.fdf` files, supports color codes per vertex (`0xRRGGBB`)
- **Isometric projection** — transforms 3D `(x, y, z)` coordinates to 2D screen coordinates
- **Line drawing** — implements Bresenham's line algorithm for pixel-perfect lines
- **MiniLibX integration** — window creation, image buffer, keyboard/mouse events
- **Color interpolation** — gradient coloring between altitude levels
- **Interactive controls** — zoom, rotation, and translation via keyboard

---

## A standout technical detail

The parser is split into modular components (`parser.c`, `parser_char.c`, `parser_int.c`, `ft_split_int.c`), separating the concerns of reading the file, parsing strings, and converting to integer/color values. This level of modularity in a C project — keeping each function focused on a single responsibility — reflects solid software design thinking.

---

## Getting Started

### Prerequisites

```bash
# On Ubuntu/Debian
sudo apt-get install libxext-dev libx11-dev
```

```bash
git clone https://github.com/gustavofsousa/Fdf_42.git
cd Fdf_42
make
```

### Running

```bash
./fdf test_maps/42.fdf
./fdf test_maps/mars.fdf
./fdf test_maps/t1.fdf
```

### Controls

| Key | Action |
|---|---|
| `W` `A` `S` `D` | Move camera |
| `+` / `-` | Zoom in / out |
| Arrow keys | Rotate |
| `ESC` | Quit |

---

## Project structure

```
Fdf_42/
├── src/
│   ├── main.c              # Entry point, window setup
│   ├── draw.c              # Render loop
│   ├── draw_line.c         # Bresenham line algorithm
│   ├── parser.c            # Map file parsing
│   ├── parser_char.c       # String-level parsing
│   ├── parser_int.c        # Integer/color parsing
│   ├── please_put_pixel.c  # Pixel drawing with bounds check
│   ├── mlx.c               # MiniLibX event setup
│   └── quit.c              # Clean exit and memory free
├── include/                # Headers
├── libft/                  # Personal C library
├── miniLibX/               # Graphics library
├── ft_printf/              # Custom printf
└── test_maps/              # Sample .fdf map files
```

---

## Skills demonstrated

- Computer graphics and 3D-to-2D projection (isometric)
- Bresenham's line drawing algorithm
- File parsing and structured data handling
- Event-driven programming (keyboard, window close)
- Memory management in a multi-file C project

---

## License

This project was developed as part of the [42 School](https://42.fr) curriculum.

---

<p align="center">Made with ☕ at 42 Rio de Janeiro</p>
