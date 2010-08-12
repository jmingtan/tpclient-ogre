#include <iostream>
#include <string>

#include <boost/python.hpp>

#include "main.h"

using namespace std;

void list_scene_managers() {
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

void doSomethingWithColour(Ogre::ColourValue value) {
	cout << value << endl;
}

//Ogre::Log* getLog() {
	//return Ogre::LogManager::getSingletonPtr()->getLog("sdf");
//}

BOOST_PYTHON_MODULE(boostpy) {
	using namespace boost::python;
	//def("list_scene_managers", list_scene_managers);
	//def("getLog", getLog);
	def("doSomethingWithColour", doSomethingWithColour);

	class_<Ogre::ColourValue>("ColourValue");
	//class_<Ogre::Root>("Root");
	//class_<Ogre::LogManager>("LogManager")
		//.def("greet", &Ogre::LogManager::greet)
		//.def("set", &Ogre::LogManager::set)
	//;
}

