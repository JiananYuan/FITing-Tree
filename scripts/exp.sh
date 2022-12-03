# cmake -DCMAKE_BUILD_TYPE=Release ..

dataset=(linear seg1 seg10 normal)
for ds in ${dataset[@]}
do
    echo ">>>>>>>>>> $ds: 时延 <<<<<<<<<<"
    ../build/main_latency ../dataset/$ds.csv 0 1
done

for ds in ${dataset[@]}
do
    echo ">>>>>>>>>> $ds: 不同静态数据集吞吐量 <<<<<<<<<<"
    ../build/main_goodput ../dataset/$ds.csv 0 1
done

# 读多写少
for ds in ${dataset[@]}
do
    echo ">>>>>>>>>> $ds: 读多写少负载的吞吐量 <<<<<<<<<<"
    ../build/main_workload ../dataset/$ds.csv 0 1 0.8 0.2
done

# 写多读少
for ds in ${dataset[@]}
do
    echo ">>>>>>>>>> $ds: 写多读少负载的吞吐量 <<<<<<<<<<"
    ../build/main_workload ../dataset/$ds.csv 0 1 0.2 0.8
done

# 读写均衡
for ds in ${dataset[@]}
do
    echo ">>>>>>>>>> $ds: 读写均衡负载的吞吐量 <<<<<<<<<<"
    ../build/main_workload ../dataset/$ds.csv 0 1 0.5 0.5
done

# 实验准备
# 1. 增加4个实验数据集：wiki_ts, books, osm_cellids, fb
# 2. 增加工作负载的测试：写多读少(8:2)、读多写少(8:2)、读写均衡(1:1)，这种情况测吞吐量就好
# 总结：读延迟、写延迟、读吞吐量、写吞吐量、索引空间大小、不同工作负载下的吞吐量(3组)

