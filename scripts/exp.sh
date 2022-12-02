# cmake -DCMAKE_BUILD_TYPE=Release ..

../build/main_latency ../dataset/linear.csv 0 1
echo "==============================="
../build/main_latency ../dataset/seg1.csv 0 1
echo "==============================="
../build/main_latency ../dataset/seg10.csv 0 1
echo "==============================="
../build/main_latency ../dataset/normal.csv 0 1
echo "==============================="
../build/main_goodput ../dataset/linear.csv 0 1
echo "==============================="
../build/main_goodput ../dataset/seg1.csv 0 1
echo "==============================="
../build/main_goodput ../dataset/seg10.csv 0 1
echo "==============================="
../build/main_goodput ../dataset/normal.csv 0 1
