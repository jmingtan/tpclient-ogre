solution "OgreClientPrototyping"
    configurations { "Release" }

    build_dir = "build"
    targetdir(build_dir)
    objdir(build_dir)
    location(build_dir)

    ogre_dependencies = {
        "OgreMain", "OIS", "RenderSystem_Direct3D9", "RenderSystem_GL",
        "Plugin_ParticleFX"
    }
    cegui_dependencies = {
        "CEGUIBase", "CEGUIOgreRenderer", "CEGUIExpatParser",
        "CEGUIFalagardWRBase"
    }

    configuration {"Release", "windows", "vs20*"}
        includedirs {
            "$(OGRE_HOME)/include/OGRE",
            "$(OGRE_HOME)/include/OIS",
            "$(OGRE_HOME)/boost_1_42",
            "$(CEGUI_HOME)/cegui/include",
            "$(ZMQ_HOME)/include",
            "include",
            "libs",
        }
        libdirs {
            "$(OGRE_HOME)/lib/release",
            "$(OGRE_HOME)/boost_1_42/lib",
            "$(CEGUI_HOME)/lib",
            "$(ZMQ_HOME)/lib",
        }
        links { "OgreMain", "OIS", "CEGUIBase", "CEGUIOgreRenderer", "libzmq" }
        buildoptions {"/MD"}
        defines { "NDEBUG" }
        flags   { "Optimize" }

        if string.startswith(_ACTION, "vs") then
            os.mkdir(build_dir)
            os.mkdir(build_dir .. "\\scripts")
            os.execute("xcopy cfg\\*.cfg " .. build_dir)
            os.execute("xcopy cfg\\win\\*.cfg " .. build_dir)
            for k, v in pairs(ogre_dependencies) do
                os.execute("xcopy " .. os.getenv("OGRE_HOME") .. "\\bin\\release\\" .. v .. ".dll " .. build_dir)
            end
            for k, v in pairs(cegui_dependencies) do
                os.execute("xcopy " .. os.getenv("CEGUI_HOME") .. "\\bin\\" .. v .. ".dll " .. build_dir)
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
        links { "OgreMain", "OIS", "CEGUIBase", "CEGUIOgreRenderer", "zmq" }
        if _ACTION ~= "clean" and os.get() == "linux" then
            os.mkdir(build_dir)
            os.execute("cp cfg/linux/*.cfg " .. build_dir)
            os.execute("cp cfg/*.cfg " .. build_dir)
        end

    configuration {"Release", "macosx"}
        platforms { "x32" }
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
        links { "OIS", "Ogre.framework", "CEGUIBase.framework",
            "CEGUILuaScriptModule.framework", "CEGUIOgreRenderer.framework",
            "Carbon.framework", "IOKit.framework", "zmq" }
        if _ACTION ~= "clean" and os.get() == "macosx" then
            os.mkdir(build_dir)
            os.mkdir(build_dir .. "/Contents")
            os.mkdir(build_dir .. "/Contents/Resources")
            os.mkdir(build_dir .. "/Contents/Plugins")
            os.execute("cp " .. os.getenv('OGRE_HOME') .. "/lib/*.dylib " .. build_dir .. "/Contents/Plugins")
            os.execute("cp -r " .. os.getenv('CEGUI_HOME') .. "/PlugInBundles/Release/*.bundle " .. build_dir .. "/Contents/Plugins")
            --os.execute("cp cfg/osx/*.cfg " .. build_dir .. "/Contents/Resources")
            os.execute("cp cfg/*.cfg " .. build_dir)
            os.execute("cp cfg/osx/*.cfg " .. build_dir)
        end

    project "Prototype"
        language "C++"
        kind     "ConsoleApp"
        files  { "**.h", "src/*.cpp", "utils/ogreclient.cpp", "libs/**.c" }

    project "TestCache"
        language "C++"
        kind     "ConsoleApp"
        files  { "**.h", "src/*.cpp", "utils/testcache.cpp", "libs/**.c" }

    project "SceneMgrEnum"
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

