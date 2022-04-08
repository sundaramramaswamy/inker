#!/usr/bin/env python3

import shutil
import sys
import requests
import tempfile
import subprocess
import os
import hashlib

def install_cmake_if_missing():
    if not shutil.which('cmake'):
        print("CMake not found!  Attempting to download", file=sys.stderr)
        cmake_url = 'https://github.com/Kitware/CMake/releases/download/v3.23.0/cmake-3.23.0-windows-x86_64.msi'
        cmake_inst = requests.get(cmake_url)
        inst_file = 'cmake-3.23.0-windows-x86_64.msi'
        cmake_inst_path = os.path.join(tempfile.gettempdir(), inst_file)
        f = open(cmake_inst_path, 'w+b')
        if not f:
            print("Unable to download CMake installer.", file=sys.stderr)
            exit(1)
        f.write(cmake_inst.content)
        f.close()
        if hashlib.md5(cmake_inst.content).hexdigest() != 'cb9661a1f3f9886e73dd333f0be5334b':
            print("Invalid file download", file=sys.stderr)
            exit(1)
        print(f"Downloaded CMake installer to {cmake_inst_path}")
        os.system(f'start {cmake_inst_path}')
    else:
        print("CMake available in %PATH%.  Skipping installation.")

def install_vc_workload_if_missing():
    prog_files = os.environ['PROGRAMFILES(X86)']
    vc_path = f'{prog_files}/Microsoft Visual Studio/Installer'
    if not os.path.isdir(vc_path):
        print("Unable to validate VS Installation.\n"
              "Install VS 2017 or later with 'Microsoft.VisualStudio.Workload.NativeDesktop' workload.", file=sys.stderr)
        exit(1)
    vswhere_path = os.path.join(vc_path, 'vswhere.exe')
    if not os.path.isfile(vswhere_path):
        print("Unable to validate VS Installation.\n"
              "Install VS 2017 or later with 'Microsoft.VisualStudio.Workload.NativeDesktop' workload.")
        exit(1)
    p1 = subprocess.run([vswhere_path, '/latest', '-property', 'catalog_productLineVersion'], capture_output=True)
    if p1.returncode != 0:
        print("Unable to validate VS Installation.\n"
              "Install VS 2017 or later with 'Microsoft.VisualStudio.Workload.NativeDesktop' workload.")
        exit(1)
    vs_ver = int(p1.stdout)
    if vs_ver < 2017:
        print("Please install Visual Studio 2017 or later.  Older versions don't support C++17")
        exit(1)
    p2 = subprocess.run([vswhere_path, '/latest', '-property',
                         'InstallationPath'], capture_output=True)
    if p2.returncode != 0:
        print("Unable to validate VS Installation.\n"
              "Install VS 2017 or later with 'Microsoft.VisualStudio.Workload.NativeDesktop' workload.")
        exit(1)
    install_path = p2.stdout.strip()
    print(f"Found Visual Studio {vs_ver} at {install_path.decode('UTF-8')}.\n"
          "Launching installer.  Install 'Microsoft.VisualStudio.Workload.NativeDesktop' workload if not already installed.")
    setup_path = os.path.join(vc_path, 'setup.exe')
    p = subprocess.run([setup_path, 'modify', '--installPath', install_path,
                        '--add', 'Microsoft.VisualStudio.Workload.NativeDesktop'])

if __name__ == '__main__':
    install_vc_workload_if_missing()
    install_cmake_if_missing()
