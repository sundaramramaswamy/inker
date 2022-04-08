# Tools

Make sure the following tools are installed:

* Visual Studio 2017+
  - `Microsoft.VisualStudio.Workload.NativeDesktop` workload is needed for Desktop C++ development
* [CMake][]
  - Command `cmake` should be in `%PATH%`
  - Verify if `cmake --version` shows version

If in doubt, run `python3 verify_or_install_tools.py` (requires [Python 3.7+][python3]).

# Build

``` shell
git clone https://github.com/sundaramramaswamy/inker

cd inker

cmake -B build

cmake --build build
```

This should build `ink.exe` under `//build/Debug`.

Open Visual Studio with

``` shell
start build\Inker.sln
```

In the _Solution Explorer_, right-click `ink` project and click _Set as Startup Project_.


[CMake]: https://cmake.org/
[vcpkg]: https://vcpkg.io/en/getting-started.html
[mingw]: https://sourceforge.net/projects/mingw-w64/files/mingw-w64/mingw-w64-release/
[fltk]: https://www.fltk.org/
[spdlog]: https://github.com/gabime/spdlog
[vcpkg manifest documentation]: https://vcpkg.io/en/docs/users/manifests.html
[vcpkg cmake example]: https://vcpkg.io/en/docs/examples/manifest-mode-cmake.html
[cmake-doc]: https://cmake.org/cmake/help/latest/index.html
[packages]: https://vcpkg.io/en/packages.html
[python3]: https://www.python.org/downloads/
