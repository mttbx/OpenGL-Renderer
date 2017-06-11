#pragma once

#include "Model.h"

#include <memory>

class HeightGenerator;

class Terrain {
public:
	Terrain(const std::size_t gridX, const std::size_t gridZ, const std::size_t seed) noexcept;

	void Draw(GLShaderProgram& shader, const glm::vec3& cameraPos) const {
		shader.Bind();
		shader.SetUniform("modelMatrix", m_terrainModel->GetModelMatrix());
		shader.SetUniform("light.direction", {-0.2f, -1.0f, -0.3f});
		shader.SetUniform("light.ambient", {0.1f, 0.1f, 0.1f});
		shader.SetUniform("light.diffuse", glm::vec3(0.5f, 0.5f, 0.0f));
		shader.SetUniform("light.specular", glm::vec3(1.0f));
		shader.SetUniform("viewPos", cameraPos);

		m_terrainModel->Draw(&shader);
	}

private:
	Mesh generateTerrain(const std::size_t x, const std::size_t z);
	std::vector<Vertex> generateVertices(const HeightGenerator& generator) const;
	std::vector<GLuint> calculateIndices() const noexcept;
	std::vector<GLTexture> loadTextures() const;
	glm::vec3 calculateNormal(const int x, const int y, const HeightGenerator& generator) const;

	ModelPtr m_terrainModel;

	std::vector<std::vector<float>> m_heightData;

	std::size_t VERTEX_COUNT;
	const std::size_t SIZE = 1000, MAX_HEIGHT = 75;
	const std::size_t m_seed;
};

