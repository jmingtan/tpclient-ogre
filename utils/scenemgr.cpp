#include <iostream>
#include "main.h"

int main(int argc, char **argv) {
	using namespace Ogre;
	using namespace std;
	LogManager* logMgr = new LogManager(); // prevent debug logging
	logMgr->createLog("Ogre.log", true, false, false);
	Root* root = new Root();
	if (!root->restoreConfig() && !root->showConfigDialog())
		throw Ogre::Exception(52, "User canceled the config dialog!", "main()");
	root->initialise(true, "Render Window");
	SceneManagerEnumerator::MetaDataIterator iter = root->getSceneManagerMetaDataIterator();
	cout << "Iterating list of scene managers" << endl;
	cout << "================================" << endl;
	while (iter.hasMoreElements()) {
		const SceneManagerMetaData* data = iter.getNext();
		cout << data->typeName << endl << "\t" << data->description << endl;
	}
	delete root;
}

