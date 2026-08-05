g++ -O2 -shared -fPIC example.cpp -o example.so -I/usr/include/python3.10 -lboost_python310

g++ -Wall -Wextra -fPIC -shared -I/usr/include/python3.10/ numpy_example.cc -o numpy_example.so -lboost_python310 -lboost_numpy310

g++ -Wall -Wextra -fPIC -shared -I/usr/include/python3.10/ docstrings_example.cc -o docstrings_example.so -lboost_python310

g++ -Wall -Wextra -fPIC -shared -I/usr/include/python3.10/ compiled_script_example_01.cc -o compiled_script_example_01.so -lboost_python310
