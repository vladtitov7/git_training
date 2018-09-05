#ifndef __ASTAR_H__
#define __ASTAR_H__

#include <vector>
#include <functional>
#include <set>

namespace AStar
{

  struct Vec
  {
    int x, y;
    bool operator == (const Vec& m_coordinates);
  };

  using uint = unsigned int;
  using heuristicFunc = std::function<uint(Vec, Vec)>;
  using coordinateList = std::vector<Vec>;

  struct Vertice
  {
    uint G, H;
    Vec coordinates;
    Vertice *parent;
    Vertice(Vec m_coord, Vertice *m_parent = nullptr);
    uint getScore();
  };

  using VerticeSet = std::set<Vertice*>;

  class Generator
  {
    bool detectCollision(Vec m_coordinates);
    Vertice* findVertOnList(VerticeSet& m_nodes, Vec m_coordinates);
    void releaseVert(VerticeSet& m_nodes);

  public:
    Generator();
    void setWorldSize(Vec m_worldSize);
    void setDiagonalMovement(bool m_enable);
    void setHeuristic(heuristicFunc m_heuristic);
    coordinateList findPath(Vec m_source, Vec m_target);
    void addCollision(Vec m_coordinates);
    void removeCollision(Vec m_coordinates);
    void clearCollisions();

  private:
    heuristicFunc heuristic;
    coordinateList direction, walls;
    Vec worldSize;
    uint directions;
  };

  class Heuristic
  {
    static Vec getDelta(Vec m_source, Vec m_target);
    
  public:
    static uint manhattan(Vec m_source, Vec m_target);
    static uint euclidean(Vec m_source, Vec m_target);
  };
}

#endif
