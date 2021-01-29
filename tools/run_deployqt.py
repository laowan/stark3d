import sys
import os

if __name__ == "__main__":
    if len(sys.argv) <= 1:
        print("arguments is not enough")
    else:
        qt_dir = sys.argv[1]
        exe_path = sys.argv[2]

        exe_path = os.path.abspath(exe_path)

        deployqt_path = os.path.join(qt_dir, "bin")
        deployqt_path = os.path.join(deployqt_path, "windeployqt")

        #
        # Check whether debug or release.
        #
        path, folder = os.path.split(exe_path)
        path, folder = os.path.split(path)
        folder = folder.lower()
        config_arg = "--release"
        if "debug" in folder:
            config_arg = "--debug"

        current_work_dir = os.getcwd()
        print('qt_dir: ' + qt_dir)
        print('current_work_dir: ' + current_work_dir)
        print('exe_path: ' + exe_path)
        os.chdir(os.path.split(deployqt_path)[0])
        os.system("%s %s %s" % (deployqt_path, config_arg, exe_path))
        os.chdir(current_work_dir)
