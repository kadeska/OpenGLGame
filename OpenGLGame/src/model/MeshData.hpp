#pragma once
#include <vector>
#include <string>
#include <glm/glm.hpp>

namespace MeshData
{
	// --- define nested MeshData so FileManager::MeshData is a complete type (was previously a file-local struct) ---
	struct MeshData
	{
		struct Texture
		{
			unsigned int id;
			std::string type;
			std::string path;
		};

		struct Vertex
		{
			glm::vec3 Position;
			glm::vec3 Normal;
			glm::vec2 TexCoords;
			glm::vec3 Tangent;
			glm::vec3 Bitangent;
			int m_BoneIDs[4];
			float m_Weights[4];

			Vertex()
				: Position(0.0f), Normal(0.0f), TexCoords(0.0f), Tangent(0.0f), Bitangent(0.0f)
			{
				for (int i = 0; i < 4; ++i) {
					m_BoneIDs[i] = 0;
					m_Weights[i] = 0.0f;
				}
			}
		};

		std::vector<Vertex> vertices;
		std::vector<unsigned int> indices;
		std::vector<Texture> textures;
	};
}