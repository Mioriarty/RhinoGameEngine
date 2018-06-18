#pragma once

#include "Component.h"
#include "System.h"

#include <map>

namespace rhino { namespace ecs {

	class ECS {

		private:
			std::vector<BaseSystem*> systems;
			std::map<unsigned int, std::vector<char>> components;
			std::vector<std::pair<unsigned int, std::vector<std::pair<unsigned int, unsigned int>>>*> entities;

			inline std::pair<unsigned int, std::vector<std::pair<unsigned int, unsigned int>>>* handleToRawType(EntityHandle handle) {
				return (std::pair<unsigned int, std::vector<std::pair<unsigned int, unsigned int>>>*)handle;
			}

			inline std::vector<std::pair<unsigned int, unsigned int>>& handleToEntity(EntityHandle handle) {
				return handleToRawType(handle)->second;
			}

			inline unsigned int handleToEntityIndex(EntityHandle handle) {
				handleToRawType(handle)->first;
			}

			void removeComponentInternal(unsigned int componentId, unsigned int index);

		public:
			ECS() = default;
			~ECS();

			// Entity methods
			EntityHandle makeEntity(BaseComponent* components, const unsigned int* componentIds, unsigned int numConponents);
			void removeEntity(EntityHandle handle);

			// Component methods
			template<typename T>
			void addComponent(EntityHandle entity, T* component);
			template<typename T>
			void removeComponent(EntityHandle entity);
			template<typename T>
			void getComponent(EntityHandle entity);

			// System methods
			void addSystem(BaseSystem* system);
			void removeSystem(BaseSystem* system);
			void updateSystems();
	};

} }