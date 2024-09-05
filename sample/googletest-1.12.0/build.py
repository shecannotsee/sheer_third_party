import sys
import os
sys.path.append("build_utils/use_python")
import record
import check
import get_source_code
import project
import build_project


if __name__ == "__main__":
    logger = build_record(log_file="build_process.log")
    try:
        # projcet info
        gtest: project.info = project.info("gtest","https://github.com/google/googletest.git", "release-1.12.0", "libraries")

        ##### check_path #####
        # ensure to stay on path: sheer_third_party
        check.work_path("sheer_third_party")
        # build and install path
        check.directory_exists(gtest.build_dir)

        ##### clone_repository #####
        source_file_name = f"{gtest.name}-{gtest.version}-src" # {name}-{version}-src
        install_path = os.path.join(os.getcwd(), gtest.build_dir, f"{gtest.name}-{gtest.version}") # {pwd}/{project.info.build_dir}/{name}-{version}
        clone_path = source_file_name if not gtest.build_dir else os.path.join(".", gtest.build_dir, source_file_name) # ./{project.info.build_dir}/{source_file_name}
        get_source_code.clone_repository(gtest.get_path, clone_path)

        ##### switch branch #####
        check.change_path(clone_path)
        check.work_path(source_file_name)
        get_source_code.switch_branches(gtest.version)

        ##### prepare_build #####
        check.directory_exists("build")
        check.change_path("build")
        install_param: str = (f"-DCMAKE_INSTALL_PREFIX={install_path}")
        compile_path: str  = ".."
        build_project.cmake(install_param, compile_path)

        ##### build_and_install #####
        build_project.make()
        build_project.install()

    except Exception as e:
        record.log_message(f"Build process failed: {str(e)}")
