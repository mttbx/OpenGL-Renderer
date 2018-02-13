#pragma once

#include "../Graphics/GLFramebuffer.h"

#include <cstddef>

/***********************************************************************************/
// Forward Declarations
struct nk_context;
struct GLFWwindow;

/***********************************************************************************/
class GUISystem {
public:
	GUISystem() = default;
	GUISystem(const GUISystem&) = delete;
	GUISystem& operator=(const GUISystem&) = delete;

	void Init(GLFWwindow* windowPtr);
	void Update();
	void Render();
	void Shutdown();

private:
	nk_context* m_nuklearContext;

	std::size_t m_maxVertexBuffer = 512 * 1024;
	std::size_t m_maxElementBuffer = 128 * 1024;

	GLFramebuffer m_guiFBO;
};
