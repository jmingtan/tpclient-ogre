solution "OgreClient"
	configurations { "Release" }
    platforms { "x32" }

	build_dir = "build"
	targetdir(build_dir)
	objdir(build_dir)
	location(build_dir)

    ogre_dependencies = {
        "OgreMain", "OIS", "RenderSystem_Direct3D9", "RenderSystem_GL", "Plugin_ParticleFX" }
    cegui_dependencies = {
        "CEGUIBase", "CEGUIOgreRenderer", "CEGUIExpatParser", "CEGUIFalagardWRBase", "CEGUILuaScriptModule", "tolua++" }
    cegui_additional_dependencies = { "lua" }

	configuration {"Release", "windows", "vs20*"}
        includedirs {
            "$(OGRE_HOME)/include/OGRE",
            "$(OGRE_HOME)/include/OIS",
            "$(OGRE_HOME)/boost_1_42",
            "$(CEGUI_HOME)/cegui/include",
            "$(LUA_DEV)/include",
            "$(ZMQ_HOME)/include",
            "include",
            "libs",
        }
        libdirs {
            "$(OGRE_HOME)/lib/release",
            "$(OGRE_HOME)/boost_1_42/lib",
            "$(CEGUI_HOME)/lib",
            "$(ZMQ_HOME)/lib",
            "$(LUA_DEV)/lib",
        }
		links {"OgreMain", "OIS", "CEGUIBase", "CEGUIOgreRenderer", "lua51", "CEGUILuaScriptModule", "libzmq"}
        buildoptions {"/MD"}
        defines { "NDEBUG" }
        flags   { "Optimize" }

		if string.startswith(_ACTION, "vs") then
			os.mkdir(build_dir)
            os.mkdir(build_dir .. "\\scripts")
			os.execute("xcopy cfg\\win\\*.cfg " .. build_dir)
            os.execute("xcopy scripts " .. build_dir .. "\\scripts")
            for k, v in pairs(ogre_dependencies) do
                os.execute("xcopy " .. os.getenv("OGRE_HOME") .. "\\bin\\release\\" .. v .. ".dll " .. build_dir)
            end
            for k, v in pairs(cegui_dependencies) do
                os.execute("xcopy " .. os.getenv("CEGUI_HOME") .. "\\bin\\" .. v .. ".dll " .. build_dir)
            end
            for k, v in pairs(cegui_additional_dependencies) do
                os.execute("xcopy " .. os.getenv("CEGUI_HOME") .. "\\dependencies\\bin\\" .. v .. ".dll " .. build_dir)
            end
		end

    configuration {"Release", "linux"}
        includedirs {
            "/usr/include/OGRE",
            "/usr/include/OIS",
            "/usr/include/CEGUI",
            "include",
            "libs",
        }
		links {"OgreMain", "OIS", "CEGUIBase", "CEGUIOgreRenderer", "CEGUILuaScriptModule", "lua", "luabindd"}
		if _ACTION ~= "clean" and os.get() == "linux" then
			os.mkdir(build_dir)
			os.execute("cp cfg/linux/*.cfg " .. build_dir)
			os.execute("cp -r scripts " .. build_dir)
		end

	configuration {"Release", "macosx"}
        includedirs {
            os.getenv('OGRE_HOME') .. "/include/OGRE",
            os.getenv('OGRE_HOME') .. "/include/OIS",
            os.getenv('OGRE_HOME') .. "/boost_1_42",
            "/Library/Frameworks/CEGUIBase.framework/Headers",
            "/Library/Frameworks/CEGUIOgreRenderer.framework/Headers",
			"include",
            "libs",
        }
		buildoptions { "-fvisibility=hidden" }
        libdirs { os.getenv('OGRE_HOME') .. "/lib/release" }
        links { "OIS", "lua", "luabindd", "Ogre.framework", "CEGUIBase.framework",
            "CEGUILuaScriptModule.framework", "CEGUIOgreRenderer.framework",
            "Carbon.framework", "IOKit.framework", "zmq" }
		if _ACTION ~= "clean" and os.get() == "macosx" then
			os.mkdir(build_dir)
			os.mkdir(build_dir .. "/Contents")
			os.mkdir(build_dir .. "/Contents/Resources")
			os.mkdir(build_dir .. "/Contents/Plugins")
            os.execute("cp " .. os.getenv('OGRE_HOME') .. "/lib/*.dylib " .. build_dir .. "/Contents/Plugins")
            os.execute("cp -r " .. os.getenv('CEGUI_HOME') .. "/PlugInBundles/Release/*.bundle " .. build_dir .. "/Contents/Plugins")
            os.execute("cp -r media " .. build_dir)
            os.execute("cp -r scripts " .. build_dir)
			os.execute("cp cfg/osx/*.cfg " .. build_dir .. "/Contents/Resources")
		end

    project "OgreClient"
        language "C++"
        kind     "ConsoleApp"
        files  { "**.h", "src/**.cpp" }

    project "SceneMgr"
        language "C++"
        kind     "ConsoleApp"
        files  { "**.h", "utils/scenemgr.cpp" }

    configuration { "Debug*" }
        defines { "_DEBUG", "DEBUG" }
        flags   { "Symbols" }

    configuration { "Release*" }
        defines { "NDEBUG" }
        flags   { "Optimize" }

    if _ACTION == "clean" then
        os.rmdir(build_dir)
    end

