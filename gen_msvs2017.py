import os

if __name__ == '__main__':
    os.system(r'gyp --depth=. --generator-output=./msvs2017 --f=msvs -D library="shared_library" -D OS="win" -D build_type="win_exe" -D build_env="msvc2017" -D opengl_library="GLEW" -G msvs_version=2017 stark3d.gyp')