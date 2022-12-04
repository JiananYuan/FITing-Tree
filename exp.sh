# cmake -DCMAKE_BUILD_TYPE=Release ..

dataset=(linear seg1 seg10 normal books_200M_uint64 fb_200M_uint64 osmc_200M_uint64 wiki_ts_200M_uint64)
for ds in ${dataset[@]}
do
    echo ">>>>>>>>>> $ds: 时延 <<<<<<<<<<"
    ./build/main_latency ./dataset/$ds.csv 0 1
done

for ds in ${dataset[@]}
do
    echo ">>>>>>>>>> $ds: 不同静态数据集吞吐量 <<<<<<<<<<"
    ./build/main_goodput ./dataset/$ds.csv 0 1
done

# # 读多写少
# for ds in ${dataset[@]}
# do
#     echo ">>>>>>>>>> $ds: 读多写少负载的吞吐量 <<<<<<<<<<"
#     ./build/main_workload ./dataset/$ds.csv 0 1 0.8 0.2
# done

# # 写多读少
# for ds in ${dataset[@]}
# do
#     echo ">>>>>>>>>> $ds: 写多读少负载的吞吐量 <<<<<<<<<<"
#     ./build/main_workload ./dataset/$ds.csv 0 1 0.2 0.8
# done

# # 读写均衡
# for ds in ${dataset[@]}
# do
#     echo ">>>>>>>>>> $ds: 读写均衡负载的吞吐量 <<<<<<<<<<"
#     ./build/main_workload ./dataset/$ds.csv 0 1 0.5 0.5
# done
