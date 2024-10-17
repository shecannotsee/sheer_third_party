#python3 setup.py bdist_wheel

# 指定 dist 目录路径
DIR="./dist"

# 遍历 dist 目录下的所有文件，并依次 cat 文件内容
for file in "$DIR"/*; do
    if [ -f "$file" ]; then  # 确保只处理文件，忽略子目录
        echo "==== install of $file ===="
        pip3 install "$file"
        echo  # 打印一个空行来分隔文件内容
    fi
done
