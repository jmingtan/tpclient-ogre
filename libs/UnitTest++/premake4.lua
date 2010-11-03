solution "UnitTest++"
    platforms { "x32" }
    configurations { "Release" }

    build_dir = "build"
    targetdir(build_dir)
    objdir(build_dir)
    location(build_dir)

    configuration { "macosx" }
        buildoptions { "-fvisibility=hidden" }

    configuration { "windows" }
        files { "src/Win32/*.cpp" }

    configuration { "not windows" }
        files { "src/Posix/*.cpp" }

    project "UnitTest"
        language "C++"
        kind     "StaticLib"
        files  { "src/*.h", "src/*.cpp" }

    configuration { "Release*" }
        defines { "NDEBUG" }
        flags   { "Optimize" }

    if _ACTION == "clean" then
        os.rmdir(build_dir)
    end

