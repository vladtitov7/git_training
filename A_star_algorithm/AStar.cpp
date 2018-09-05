#include "AStar.h"
#include <algorithm>

using namespace std::placeholders;
using namespace AStar;

bool Vec::operator == (const Vec& m_coordinates)
{
  return (x == m_coordinates.x && y == m_coordinates.y);
}

Vec operator + (const Vec& m_left, const Vec& m_right)
{
  return {m_left.x + m_right.x, m_left.y + m_right.y};
}

Vertice::Vertice(Vec m_coordinates, Vertice *m_parent)
{
  parent = m_parent;
  coordinates = m_coordinates;
  G = H = 0;
}

uint Vertice::getScore()
{
  return G + H;
}

Generator::Generator()
{
  setDiagonalMovement(false);
  setHeuristic(&Heuristic::manhattan);
  direction = {{0,1}, {1, 0}, {0, -1}, {-1, 0},
	       {-1, -1}, {1, 1}, {-1, 1}, {1, -1}};
}

void Generator::setWorldSize(Vec m_worldSize)
{
  worldSize = m_worldSize;
}

void Generator::setDiagonalMovement(bool m_enable)
{
  directions = (m_enable ? 8 : 4);
}

void Generator::setHeuristic(heuristicFunc m_heuristic)
{
  heuristic = std::bind(m_heuristic, _1, _2);
}

void Generator::addCollision(Vec m_coordinates)
{
  walls.push_back(m_coordinates);
}

void Generator::removeCollision(Vec m_coordinates)
{
  auto it = std::find(walls.begin(), walls.end(), m_coordinates);
  if(it != walls.end())
    walls.erase(it);
}

void Generator::clearCollisions()
{
  walls.clear();
}

coordinateList Generator::findPath(Vec m_source, Vec m_target)
{
  Vertice *current = nullptr;
  VerticeSet openSet, closedSet;
  openSet.insert(new Vertice(m_source));

  while(!openSet.empty())
    {
      current = *openSet.begin();
      for(auto vertice : openSet)
	{
	  if(vertice->getScore() <= current->getScore())
	    current = vertice;
	}
    
      if(current->coordinates == m_target)
	break;

      closedSet.insert(current);
      openSet.erase(std::find(openSet.begin(), openSet.end(), current));
      for(uint i = 0; i < directions; ++i)
	{
	  Vec newCoordinates(current->coordinates + direction[i]);
	  if(detectCollision(newCoordinates) || findVertOnList(closedSet, newCoordinates))
	    continue;

	  uint totalCost = current->G + ((i < 4) ? 10 : 14);

	  Vertice *successor = findVertOnList(openSet, newCoordinates);
	  if(successor == nullptr)
	    {
	      successor = new Vertice(newCoordinates, current);
	      successor->G = totalCost;
	      successor->H = heuristic(successor->coordinates, m_target);
	      openSet.insert(successor);
	    }
	  else if(totalCost < successor->G)
	    {
	      successor->parent = current;
	      successor->G = totalCost;
	    }
	}
    }

  coordinateList path;
  while(current != nullptr)
    {
      path.push_back(current->coordinates);
      current = current->parent;
    }

  releaseVert(openSet);
  releaseVert(closedSet);

  return path;
}

Vertice* Generator::findVertOnList(VerticeSet& m_vertices, Vec m_coordinates)
{
  for(auto vertice : m_vertices)
    {
      if(vertice->coordinates == m_coordinates)
	return vertice;
    }

  return nullptr;
}

void Generator::releaseVert(VerticeSet& m_vertices)
{
  for(auto it = m_vertices.begin(); it != m_vertices.end();)
    {
      delete *it;
      it = m_vertices.erase(it);
    }
}

bool Generator::detectCollision(Vec m_coordinates)
{
  if(m_coordinates.x < 0 || m_coordinates.x >= worldSize.x ||
     m_coordinates.y < 0 || m_coordinates.y >= worldSize.y ||
     std::find(walls.begin(), walls.end(), m_coordinates) != walls.end())
    return true;

  return false;
}

Vec Heuristic::getDelta(Vec m_source, Vec m_target)
{
  return {abs(m_source.x - m_target.x), abs(m_source.y - m_target.y)};
}

uint Heuristic::manhattan(Vec m_source, Vec m_target)
{
  auto delta = std::move(getDelta(m_source, m_target));
  return static_cast<uint>((delta.x + delta.y));
}

uint Heuristic::euclidean(Vec m_source, Vec m_target)
{
  auto delta = std::move(getDelta(m_source, m_target));
  return static_cast<uint>(sqrt(delta.x * delta.x + delta.y * delta.y));
}
