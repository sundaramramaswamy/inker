# Tools

Make sure the following tools are installed:

* Visual Studio 2017+
* [CMake][]

Make sure `Microsoft.VisualStudio.Workload.NativeDesktop` workload is installed.

**`cmake` should be in `$PATH` / `%PATH%`**.  Verify if `cmake --version`
displays the version properly.

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


[CMake]: https://cmake.org/
[vcpkg]: https://vcpkg.io/en/getting-started.html
[mingw]: https://sourceforge.net/projects/mingw-w64/files/mingw-w64/mingw-w64-release/
[fltk]: https://www.fltk.org/
[spdlog]: https://github.com/gabime/spdlog
[vcpkg manifest documentation]: https://vcpkg.io/en/docs/users/manifests.html
[vcpkg cmake example]: https://vcpkg.io/en/docs/examples/manifest-mode-cmake.html
[cmake-doc]: https://cmake.org/cmake/help/latest/index.html
[packages]: https://vcpkg.io/en/packages.html
