#!/bin/bash

# 确保当前路径是 ~/Desktop/sheer_third_party
if [[ "$(pwd)" != *"sheer_third_party"* ]]; then
  echo "Error: This script must be run from the sheer_third_party directory."
  exit 1
fi

# 遍历 build_scripts 目录中的所有子目录
for dir in build_scripts/*/ ; do
    # 查找当前子目录中的 Python 和 Bash 脚本
    py_script=$(find "$dir" -maxdepth 1 -name "*.py" | head -n 1)
    sh_script=$(find "$dir" -maxdepth 1 -name "*.sh" | head -n 1)

    # 优先执行 Python 脚本
    if [[ -n "$py_script" ]]; then
        echo "Running Python script: $py_script"
        python3 "$py_script" || python "$py_script"  # 使用 python3 或 python 来执行

    # 如果没有 Python 脚本，则执行 Bash 脚本
    elif [[ -n "$sh_script" ]]; then
        echo "Running Bash script: $sh_script"
        bash "$sh_script"

    else
        echo "No Python or Bash script found in $dir"
    fi
done
