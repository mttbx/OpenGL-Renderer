#pragma once

#include "../Graphics/GLShaderProgram.h"
#include "../Graphics/GLVertexArray.h"
#include "../Graphics/StaticDirectionalLight.h"

//http://victorbush.com/2015/01/tessellated-terrain/

/***********************************************************************************/
// Forward Declarations
struct TerrainNode;

/***********************************************************************************/
class Terrain {

public:
	Terrain() = default;

	~Terrain() = default;

	void Init(const std::string_view heightmapPath);
	// Builds the terrain quadtree based on specified parameters and current camera position.
	void Update(const float x, const float y, const float z, const float width, const float height, const glm::vec3& camPos);
	void Render(const glm::mat4x4& viewMatrix);
	void Shutdown();

private:
	// Resets the terrain quadtree
	void clearTerrainTree();
	// Traverses the terrain quadtree to draw nodes with no children
	void renderRecursive(TerrainNode* node, const glm::mat4x4& viewMatrix);
	// Renders a node
	void renderNode(TerrainNode* node, const glm::mat4x4& viewMatrix);
	// Calculate the tessellation scale factor for a node depending on the neighboring patches
	void calcTesselationScale(TerrainNode* node);
	// Search for a node in the tree given xz coordinate
	TerrainNode* findNode(TerrainNode* node, const float x, const float z);
	// Adds a new node to terrain quadtree memory block
	TerrainNode* createNode(TerrainNode* parent, const int type, const float x, const float y, const float z, const float width, const float height);
	// Returns true if node is sub-divided.
	void divideNode(TerrainNode* node, const glm::vec3& camPos);
	// Determines whether a node should be subdivided based on its distance to the camera.
	bool shouldDivideNode(TerrainNode* node, const glm::vec3& camPos) const;

	TerrainNode* m_terrainTree = nullptr;
	TerrainNode* m_terrainTreeTail = nullptr;

	GLVertexArray m_vao;
	std::size_t m_renderDepth = 0;
	GLShaderProgram m_program;
	
	const std::size_t m_MaxTerrainNodes = 500;
	std::size_t m_numTerrainNodes = 0;
};