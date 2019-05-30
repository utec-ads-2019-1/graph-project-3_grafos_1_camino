#ifndef CONFIG_HPP
#define CONFIG_HPP

#include <fstream>
#include <cmath>
#include <SFML/Graphics.hpp>
#include "../../Graph/graph.h"

// WINDOW SETTINGS
const int WIDTH = sf::VideoMode::getDesktopMode().width;
const int HEIGHT = sf::VideoMode::getDesktopMode().height;
const std::string WINDOW_NAME = "Graph";
const float PROGRAM_PADDING = 20.f;

// FONT
const std::string FONT_PATH = "./ui/fonts/arial.ttf";

// MENU
const std::vector <std::string> MENU_OPTIONS = {
  "Load File",
  "DFS",
  "BFS",
  "Prim",
  "Kruskal",
  "Bipartite",
  "SCC",
  "Properties"
};
enum class MENU_INDEX {
  LOAD_FILE,
  DFS,
  BFS,
  PRIM,
  KRUSKAL,
  SCC,
  PROPERTIES
};
const float OPTION_WIDTH = 1.0 * (WIDTH - 2 * PROGRAM_PADDING) / 5;
const float OPTION_HEIGHT = 1.0 * (HEIGHT - 2 * PROGRAM_PADDING) / int(MENU_OPTIONS.size());
const float OPTION_PADDING = std::min(OPTION_WIDTH / 10.f, OPTION_HEIGHT / 10.f);
const sf::Color OPTION_COLOR(119, 136, 153); // Light Gray
const sf::Color OPTION_HOVER_COLOR(sf::Color::Blue);

// GRID
const float CHARDS_THICKNESS = 4;
const float GRID_WIDTH = 4.0 * (WIDTH - 2 * PROGRAM_PADDING) / 5;
const float GRID_HEIGHT = 4.0 * (HEIGHT - 2 * PROGRAM_PADDING) / 5;
const float GRID_POS_X = OPTION_WIDTH + PROGRAM_PADDING;
const float GRID_POS_Y = PROGRAM_PADDING;
const float ORIGIN_X = GRID_POS_X + GRID_WIDTH / 2;
const float ORIGIN_Y = GRID_POS_Y + GRID_HEIGHT / 2;
const int ORIGIN_THICK = 3;
const int NOT_ORIGIN_THICK = 1;
const float GRID_INTERVAL = GRID_HEIGHT / 8;
const float SEGMENT_LENGTH = GRID_INTERVAL / 10;

// LOAD GRAPH
const float FILE_PADDING = GRID_INTERVAL / 15;
const sf::Color FILE_COLOR = sf::Color::Red;
const sf::Color FILE_HOVER_COLOR = sf::Color::Blue;
const std::string PATH_INPUT = "./ui/input/";

// CONSOLE
const float CONSOLE_POS_X = GRID_POS_X;
const float CONSOLE_POS_Y = GRID_POS_Y + GRID_HEIGHT + PROGRAM_PADDING;
const float CONSOLE_WIDTH = GRID_WIDTH / 5;
const float CONSOLE_HEIGHT = HEIGHT - CONSOLE_POS_Y - 2 * PROGRAM_PADDING;
const float CONSOLE_PADDING = CONSOLE_WIDTH / 10;
const sf::Color CONSOLE_COLOR = sf::Color::Green;

// GRAPH UI
const float VERTEX_RADIUS = 15.f;
const sf::Color VERTEX_COLOR = sf::Color::White;
const sf::Color VERTEX_TEXT_COLOR = sf::Color::Red;
static std::vector <sf::Color> GRAPH_COLORS = {
  sf::Color::Blue,
  sf::Color::Yellow,
  sf::Color::Magenta,
  sf::Color::Cyan
};
const sf::Color EDGE_COLOR = sf::Color::Red;
const float EDGE_THICK = 5.f;
const float VERTEX_THICK = 0;
const float VERTEX_HOVER_THICK = 3;
const sf::Color VERTEX_THICK_COLOR = sf::Color::Red;
const sf::Color EDGE_MST = sf::Color::Yellow;

// UTIL
static sf::RectangleShape* buildRectangle (sf::Vector2f dimentions, sf::Vector2f position, sf::Color background, int thick = 1, bool border = false) {
  sf::RectangleShape* box = new sf::RectangleShape();
  box -> setSize(dimentions);
  box -> setPosition(position);
  if (border) {
    box -> setOutlineThickness(CHARDS_THICKNESS);
    box -> setOutlineColor(background);
    box -> setFillColor(sf::Color::Black);
  } else {
    box -> setFillColor(background);
  }
  return box;
}

static sf::Vector2f getWindowCoordinates (float x, float y) {
  float windowX = ORIGIN_X + (x * GRID_INTERVAL) / 10.f;
  float windowY = ORIGIN_Y - (y * GRID_INTERVAL) / 10.f;
  return sf::Vector2f(windowX, windowY);
}

static sf::Vertex* buildLine (sf::Vector2f from, sf::Vector2f to, sf::Color background, float thickness) {
  sf::Vector2f direction = to - from;
  sf::Vector2f unitDirection = direction / std::sqrt(direction.x * direction.x + direction.y * direction.y);
  sf::Vector2f unitPerpendicular(-unitDirection.y, unitDirection.x);
  sf::Vector2f offset = (thickness / 2.f) * unitPerpendicular;
  sf::Vertex* vertices = new sf::Vertex[4];
  vertices[0].position = from + offset;
  vertices[1].position = to + offset;
  vertices[2].position = to - offset;
  vertices[3].position = from - offset;
  for (int i = 0; i < 4; ++i) vertices[i].color = background;
  return vertices;
}

static sf::CircleShape* buildCircle (float radius, sf::Vector2f position, sf::Color background) {
  sf::CircleShape* circle = new sf::CircleShape();
  position.x -= VERTEX_RADIUS;
  position.y -= VERTEX_RADIUS;
  circle -> setPosition(position);
  circle -> setRadius(radius);
  circle -> setFillColor(background);
  return circle;
}

static sf::Text* buildText (sf::Vector2f dimentions, sf::Vector2f position, std::string text, sf::Font*& font) {
  sf::Text* msg = new sf::Text();
  msg -> setFont(*font);
  msg -> setString(text);
  sf::FloatRect msgDimentions = msg -> getLocalBounds();
  double msgW = position.x + (dimentions.x - msgDimentions.width) / 2.0;
  double msgH = position.y + (dimentions.y - msgDimentions.height) / 2.0;
  msg -> setPosition(sf::Vector2f(msgW, msgH));
  return msg;
}

template <typename N, typename E>
static void loadFromFile (std::string fileName, Graph <N, E>*& graph) {
  ifstream file;
  file.open(fileName);
  int n, e;
  bool is_directed;
  file >> n >> e >> is_directed;
  graph = new Graph <N, E> (is_directed);
  for (int i = 0; i < n; i++) {
    N tag;
    float x, y;
    file >> tag >> x >> y;
    graph -> addNode(tag, x, y);
  }
  for (int i = 0; i < e; i++) {
    N u, v;
    E w;
    file >> u >> v >> w;
    graph -> addEdge(u, v, w);
  }
}

#endif
