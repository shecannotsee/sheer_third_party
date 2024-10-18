python3 setup.py bdist_wheel || \
  { echo "build whl failed"; exit 1; }
pip3 install dist/double_vector_1D-0.1.0-py3-none-any.whl || \
  { echo "pip install failed"; exit 1; }
# uninstall
# pip3 uninstall double_vector_1D

echo "start test"
python3 after_install.py
