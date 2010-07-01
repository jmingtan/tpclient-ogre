solution "OgreClient"
    configurations { "Debug", "Release" }

    configuration { "Debug" }
        targetdir "bin/debug"

    configuration { "Release" }
        targetdir "bin/release"

    if _ACTION == "clean" then
        os.rmdir("bin")
        os.rmdir("obj")
    end

    configuration { "*" }
        includedirs {
            os.getenv('OGRE_HOME') .. "/include/OGRE",
            os.getenv('OIS_HOME') .. "/include/OIS",
            "include"
        }
        links { "OgreMain", "OIS" }

    configuration { "windows" }
        includedirs {
            os.getenv('OGRE_HOME') .. "/boost_1_42",
        }
        libdirs {
            os.getenv('OGRE_HOME') .. "/lib/release",
            os.getenv('OGRE_HOME') .. "/boost_1_42/lib"
        }
        buildoptions { "/MD" }
        flags   { "Optimize" }

    configuration { "linux" }
        libdirs { os.getenv('OGRE_HOME') .. "/lib" }

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

