#ifndef OGREUTILS_H
#define OGREUTILS_H

namespace OgreUtils {
	/**
	 * Utility method for getting a camera ray from current mouse coordinates
	 */
	Ogre::Ray getCameraRay(Ogre::Camera *camera, int mouseX, int mouseY) {
		Ogre::Real x, y;

		x = mouseX / camera->getViewport()->getActualWidth();
		y = mouseY / camera->getViewport()->getActualHeight();
		return camera->getCameraToViewportRay(x, y);
	}

	/**
	 * Creates a line with random colours on each end
	 * Side effects:
	 *  - Uses "GridMaterial" material
	 *  - Creates entity with "line%d", with %d being the value of index
	 */
	Ogre::ManualObject* getLine(Ogre::SceneManager *mgr, Ogre::Vector3 origin, Ogre::Vector3 point, int index) {
		using namespace Ogre;

		char* lineName = new char[100];
		ManualObject *line;

		sprintf(lineName, "line%d", index);
		line = mgr->createManualObject(lineName);
		line->begin("GridMaterial", RenderOperation::OT_LINE_LIST);
		line->position(origin);
		line->colour(Math::RangeRandom(0, 1), Math::RangeRandom(0, 1), Math::RangeRandom(0, 1), 0.8f);
		line->position(point);
		line->colour(Math::RangeRandom(0, 1), Math::RangeRandom(0, 1), Math::RangeRandom(0, 1), 0.3f);
		line->end();
		return line;
	}

	/**
	 * Creates a set of grid lines using the given scene manager
	 * Side effects:
	 *	- Creates "GridMaterial" material under default resource group
	 *	- Creates "Grid" entity
	 *	- Creates "GridNode" scene node under given node
	 *
	 * Parameters:
	 *  gridLines - individual grid size, as well as total grid size
	 */
	void createGrid(Ogre::SceneManager *mgr, Ogre::SceneNode *parentNode, int gridLines) {
		using namespace Ogre;

		ManualObject *grid;
		SceneNode *gridNode;
		int i;

		MaterialPtr material = MaterialManager::getSingletonPtr()->create("GridMaterial", ResourceGroupManager::DEFAULT_RESOURCE_GROUP_NAME);
		material->setLightingEnabled(false);
		material->setSceneBlending(SBT_TRANSPARENT_ALPHA);
		grid = mgr->createManualObject("Grid");
		grid->begin("GridMaterial", RenderOperation::OT_LINE_LIST);
		grid->colour(1.0f, 1.0f, 1.0f, 0.1f);
		for (i = 0; i < gridLines; i++) {
			// vertical lines
			grid->position(0.0f + (i * gridLines), 0.0f, 0.0f);
			grid->position(0.0f + (i * gridLines), 0.0f, (gridLines - 1.0f) * gridLines);
			// horizontals
			grid->position(0.0f, 0.0f, 0.0f + (i * gridLines));
			grid->position((gridLines - 1.0f) * gridLines, 0.0f, 0.0f + (i * gridLines));
		}
		grid->end();
		gridNode = parentNode->createChildSceneNode("GridNode", Vector3(0, 0, 0));
		gridNode->attachObject(grid);
	}

	/**
	 * Highlights a particular grid tile
	 * Side effects:
	 * - Uses "GridMaterial" material
	 * - Creates "GridHighlight" entity, if not found
	 * - Creates "GridHighlightNode" scene node, if not found
	 */
	void highlightGrid(Ogre::SceneManager *mgr, Ogre::SceneNode *parent, std::pair<int, int> index, int gridLines) {
		using namespace Ogre;

		ManualObject *highlightEntity;
		SceneNode *highlightNode;
		const char* highlightName = "GridHighlight";
		const char* sceneNodeName = "GridHighlightNode";

		if (mgr->hasSceneNode(sceneNodeName)) {
			highlightNode = mgr->getSceneNode(sceneNodeName);
		}
		else {
			if (mgr->hasManualObject(highlightName))
				highlightEntity = mgr->getManualObject(highlightName);
			else {
				highlightEntity = mgr->createManualObject(highlightName);
				highlightEntity->begin("GridMaterial", RenderOperation::OT_LINE_STRIP);
				highlightEntity->position(0, 0, 0);
				highlightEntity->colour(Math::RangeRandom(0, 1), Math::RangeRandom(0, 1), Math::RangeRandom(0, 1), 0.8f);
				highlightEntity->position(0, 0, gridLines);
				highlightEntity->colour(Math::RangeRandom(0, 1), Math::RangeRandom(0, 1), Math::RangeRandom(0, 1), 0.8f);
				highlightEntity->position(gridLines, 0, gridLines);
				highlightEntity->colour(Math::RangeRandom(0, 1), Math::RangeRandom(0, 1), Math::RangeRandom(0, 1), 0.8f);
				highlightEntity->position(gridLines, 0, 0);
				highlightEntity->colour(Math::RangeRandom(0, 1), Math::RangeRandom(0, 1), Math::RangeRandom(0, 1), 0.8f);
				highlightEntity->position(0, 0, 0);
				highlightEntity->colour(Math::RangeRandom(0, 1), Math::RangeRandom(0, 1), Math::RangeRandom(0, 1), 0.8f);
				highlightEntity->end();
			}
			highlightNode = parent->createChildSceneNode(sceneNodeName);
			highlightNode->attachObject(highlightEntity);
		}
		highlightNode->setPosition(index.first * gridLines, 0.1f, index.second * gridLines);
	}
}

#endif
