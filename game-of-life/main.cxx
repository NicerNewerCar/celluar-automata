#include <iostream>
#include <vector>

#define BORDER_SIZE 50

struct Cell {
  Cell(bool _state) : state(_state) {}
  ~Cell() {}
  bool state;
};

struct World {
  using rowiter = std::vector<std::vector<Cell>>::iterator;
  using coliter = std::vector<Cell>::iterator;
  World() {}
  ~World() {
    world.clear();
    tmp_world.clear();
  }
  std::vector<std::vector<Cell>> world;
  std::vector<std::vector<Cell>> tmp_world;
  void UpdateWorld();
  void UpdateCell(rowiter row, coliter col);
  unsigned int CheckNeighbours(rowiter row, coliter col);

  friend std::ostream &operator<<(std::ostream &os, World const &w);
};

std::ostream &operator<<(std::ostream &os, World const &w) {
  for (int i = 0; i < BORDER_SIZE; i++) {
    os << "~";
  }
  os << std::endl;

  for (std::vector<std::vector<Cell>>::const_iterator r = w.world.begin();
       r != w.world.end(); ++r) {
    for (std::vector<Cell>::const_iterator c = r->begin(); c != r->end(); ++c) {
      os << c->state << " ";
    }
    os << "\n";
  }

  for (int i = 0; i < BORDER_SIZE; i++) {
    os << "~";
  }
  os << std::endl;

  return os;
}

void World::UpdateWorld() {
  // Allocate a tmp world
  // Parallelize this?
  for (rowiter row = this->world.begin(); row != this->world.end(); ++row) {
    for (coliter col = row->begin(); col != row->end(); ++col) {
      this->UpdateCell(row, col);
    }
  }
}

unsigned int World::CheckNeighbours(rowiter row, coliter col) {
  size_t rowidx = std::distance(this->world.begin(), row);
  size_t colidx = std::distance(row->begin(), col);

  unsigned int count = 0;
  for (size_t r = rowidx - 1; r < rowidx + 1; ++r) {
    for (size_t c = colidx - 1; c < colidx + 1; ++c) {
      // Bounds check
      if (r < 0 || c < 0)
        continue;
      if (r > this->world.size() || c > this->world[r].size())
        continue;
      if (r == rowidx && c == colidx)
        continue;

      // State check
      if (this->world[r][c].state)
        count++;
    }
  }

  return count;
}

void World::UpdateCell(rowiter row, coliter col) {
  // Update the world based on the following conditions
  // 1. Any live cell with fewer than two live neighbours dies, as if by
  // underpopulation.
  // 2. Any live cell with two or three live neighbours lives on to the next
  // generation.
  // 3. Any live cell with more than three live neighbours dies, as if by
  // overpopulation.
  // 4. Any dead cell with exactly three live neighbours becomes a live cell, as
  // if by reproduction.

  unsigned int alive_neighbours = this->CheckNeighbours(row, col);
  if (col->state) {
    if (alive_neighbours < 2 || alive_neighbours > 3) {
      // Cell is alive and has less than 2 or more than 3 neighbours, we kill
      // it.
      col->state = !col->state;
    }
  } else if (alive_neighbours == 3) {
    // Cell is dead and has exactly 3 neighbours, it becomes alive.
    col->state = !col->state;
  }
  // Otherwise nothing happens!
}

int main() {
  // TODO:
  // 1. Setup seed for starting
  // Overload output operatirs
  // 2. Some display function
  // 3. Optimize the get number of neighbours function
  World w;
  w.world.push_back({Cell(false), Cell(true), Cell(true)});
  w.world.push_back({Cell(false), Cell(false), Cell(true)});
  w.world.push_back({Cell(true), Cell(true), Cell(true)});
  std::cout << w;
  w.UpdateWorld();
  std::cout << w;
}
