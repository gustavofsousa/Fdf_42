<h1 align="center">FdF — Fil de Fer</h1>

<p align="center">
  <img src="https://img.shields.io/badge/linguagem-C-blue.svg" alt="Linguagem">
  <img src="https://img.shields.io/badge/42-School-black.svg" alt="42 School">
  <img src="https://img.shields.io/badge/status-completo-brightgreen.svg" alt="Status">
</p>

<p align="center">
  Um renderizador wireframe 3D que lê arquivos de mapa e exibe projeções isométricas de terreno usando uma biblioteca gráfica customizada.
</p>

<p align="center">
  <a href="README.md">🇺🇸 Read in English</a>
</p>

---

## Por que este projeto importa

> "Este projeto me ensinou os fundamentos de computação gráfica — como coordenadas 3D são projetadas numa tela 2D usando álgebra linear, como pixels são desenhados um a um com clipping correto, e como um loop de renderização em tempo real é estruturado. São os fundamentos por trás de todo game engine, ferramenta de visualização de dados e software de modelagem 3D."

O algoritmo de Bresenham, projeção isométrica e renderização orientada a eventos são conceitos que você encontrará em desenvolvimento de jogos, visualização geoespacial e gráficos científicos.

---

## Preview

> *Um mapa de terreno renderizado como wireframe isométrico*

O renderizador lê arquivos de mapa `.fdf` como este:

```
0  0  0  0  0
0  1  2  1  0
0  2  4  2  0
0  1  2  1  0
0  0  0  0  0
```

E produz uma projeção 3D wireframe interativa com níveis de altitude coloridos.

---

## O que foi construído

- **Parser de mapa** — lê arquivos `.fdf`, suporta códigos de cor por vértice (`0xRRGGBB`)
- **Projeção isométrica** — transforma coordenadas 3D `(x, y, z)` em coordenadas 2D de tela
- **Desenho de linhas** — implementa o algoritmo de Bresenham para linhas pixel-perfect
- **Integração MiniLibX** — criação de janela, buffer de imagem, eventos de teclado/mouse
- **Interpolação de cores** — gradiente de cores entre níveis de altitude
- **Controles interativos** — zoom, rotação e translação via teclado

---

## Um detalhe técnico que se destaca

O parser é dividido em componentes modulares (`parser.c`, `parser_char.c`, `parser_int.c`, `ft_split_int.c`), separando as responsabilidades de leitura do arquivo, parsing de strings e conversão para valores inteiros/cor. Esse nível de modularidade em um projeto C — mantendo cada função focada em uma única responsabilidade — reflete um pensamento sólido de design de software.

---

## Como usar

### Pré-requisitos

```bash
# No Ubuntu/Debian
sudo apt-get install libxext-dev libx11-dev
```

```bash
git clone https://github.com/gustavofsousa/Fdf_42.git
cd Fdf_42
make
```

### Executando

```bash
./fdf test_maps/42.fdf
./fdf test_maps/mars.fdf
./fdf test_maps/t1.fdf
```

### Controles

| Tecla | Ação |
|---|---|
| `W` `A` `S` `D` | Mover câmera |
| `+` / `-` | Zoom in / out |
| Setas | Rotacionar |
| `ESC` | Sair |

---

## Estrutura do projeto

```
Fdf_42/
├── src/
│   ├── main.c              # Ponto de entrada, configuração da janela
│   ├── draw.c              # Loop de renderização
│   ├── draw_line.c         # Algoritmo de Bresenham
│   ├── parser.c            # Parsing do arquivo de mapa
│   ├── parser_char.c       # Parsing no nível de string
│   ├── parser_int.c        # Parsing de inteiro/cor
│   ├── please_put_pixel.c  # Desenho de pixel com verificação de limites
│   ├── mlx.c               # Configuração de eventos MiniLibX
│   └── quit.c              # Saída limpa e liberação de memória
├── include/                # Headers
├── libft/                  # Biblioteca C pessoal
├── miniLibX/               # Biblioteca gráfica
├── ft_printf/              # Printf customizado
└── test_maps/              # Arquivos de mapa .fdf de exemplo
```

---

## Habilidades demonstradas

- Computação gráfica e projeção 3D→2D (isométrica)
- Algoritmo de desenho de linhas de Bresenham
- Parsing de arquivos e manipulação de dados estruturados
- Programação orientada a eventos (teclado, fechamento de janela)
- Gerenciamento de memória em projeto C multi-arquivo

---

## Licença

Este projeto foi desenvolvido como parte do currículo da [42 School](https://42.fr).

---

<p align="center">Feito com ☕ na 42 Rio de Janeiro</p>
